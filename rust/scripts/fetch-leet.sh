#!/bin/bash
# Fetch LeetCode problem and create Rust binary template
# Usage:
#   ./scripts/fetch-leet.sh <slug>
#   ./scripts/fetch-leet.sh --num <number>

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$SCRIPT_DIR/../src"

# Parse arguments
if [ "$1" = "--num" ] || [ "$1" = "-n" ]; then
    NUM_INPUT="$2"

    if [ -z "$NUM_INPUT" ]; then
        echo "Usage: $0 --num <number>"
        exit 1
    fi

    # Fetch slug from problem number
    echo "Fetching problem #$NUM_INPUT..."
    SLUG=$(curl -s 'https://leetcode.com/api/problems/all/' | \
        jq -r ".stat_status_pairs[] | select(.stat.frontend_question_id == $NUM_INPUT) | .stat.question__title_slug")

    if [ -z "$SLUG" ] || [ "$SLUG" = "null" ]; then
        echo "Error: Problem #$NUM_INPUT not found"
        exit 1
    fi
else
    SLUG="$1"

    if [ -z "$SLUG" ]; then
        echo "Usage: $0 <slug>"
        echo "       $0 --num <number>"
        echo ""
        echo "Examples:"
        echo "  $0 two-sum"
        echo "  $0 --num 1"
        exit 1
    fi
fi

# Fetch from LeetCode GraphQL API
API_RESULT=$(curl -s 'https://leetcode.com/graphql' \
    -H 'Content-Type: application/json' \
    --data-raw "{\"query\":\"query { question(titleSlug: \\\"$SLUG\\\") { questionId title difficulty codeSnippets { langSlug code } } }\"}")

# Parse response
NUM=$(echo "$API_RESULT" | jq -r '.data.question.questionId')
NAME=$(echo "$API_RESULT" | jq -r '.data.question.title')
DIFF=$(echo "$API_RESULT" | jq -r '.data.question.difficulty')
CODE=$(echo "$API_RESULT" | jq -r '.data.question.codeSnippets[] | select(.langSlug == "rust") | .code')

if [ "$NUM" = "null" ] || [ -z "$NUM" ]; then
    echo "Error: Problem '$SLUG' not found"
    exit 1
fi

# Convert to snake_case
SNAKE_NAME=$(echo "$SLUG" | tr '[:upper:]' '[:lower:]' | sed 's/-/_/g')

# Create bin directory if not exists
mkdir -p "$SRC_DIR/bin"

# Binary file: leet_{NUM}_{snake_name}.rs
FILE="$SRC_DIR/bin/leet_${NUM}_${SNAKE_NAME}.rs"

if [ -f "$FILE" ]; then
    echo "Error: $FILE already exists"
    exit 1
fi

# Create binary file (no TAGS - will be fetched from API on 'done')
cat > "$FILE" << EOF
//! # $NAME
//!
//! - Platform: LeetCode
//! - Number: $NUM
//! - Difficulty: $DIFF
//! - URL: https://leetcode.com/problems/$SLUG/

pub struct Solution;

$CODE

fn main() {
    // TODO: Add example test
    println!("Solution compiled successfully");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example() {
        todo!()
    }
}
EOF

echo "Fetched: $NAME (#$NUM, $DIFF)"
echo "Created: $FILE"
echo ""
echo "Commands:"
echo "  cargo run --bin leet_${NUM}_${SNAKE_NAME}"
echo "  cargo test --bin leet_${NUM}_${SNAKE_NAME}"
echo ""
echo "When done: make done NAME=${SNAKE_NAME}"
