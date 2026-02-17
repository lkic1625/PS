#!/bin/bash
# Move completed LeetCode problem from bin/ to leetcode/
# Usage: ./scripts/done.sh <snake_name>
# Example: ./scripts/done.sh two_sum

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$SCRIPT_DIR/../src"

# Parse arguments: either --num <number> or <snake_name>
if [ "$1" = "--num" ]; then
    NUM="$2"
    if [ -z "$NUM" ]; then
        echo "Usage: $0 --num <number>"
        echo "Example: $0 --num 210"
        exit 1
    fi
    BIN_FILE=$(ls "$SRC_DIR/bin/" 2>/dev/null | grep "^leet_${NUM}_.*\.rs$" | head -1)
    if [ -z "$BIN_FILE" ]; then
        echo "Error: No file matching 'leet_${NUM}_*.rs' found in src/bin/"
        echo ""
        echo "Available problems:"
        ls "$SRC_DIR/bin/" 2>/dev/null | grep "^leet_" | sed 's/^leet_/  /' | sed 's/\.rs$//'
        exit 1
    fi
    NAME=$(echo "$BIN_FILE" | sed "s/^leet_${NUM}_//" | sed 's/\.rs$//')
else
    NAME="$1"

    if [ -z "$NAME" ]; then
        echo "Usage: $0 <snake_name>"
        echo "       $0 --num <number>"
        echo "Example: $0 two_sum"
        echo "         $0 --num 1"
        echo ""
        echo "Available problems in bin/:"
        ls "$SRC_DIR/bin/" 2>/dev/null | grep "^leet_" | sed 's/^leet_[0-9]*_/  /' | sed 's/\.rs$//'
        exit 1
    fi

    # Find the bin file matching the name
    BIN_FILE=$(ls "$SRC_DIR/bin/" 2>/dev/null | grep "^leet_.*_${NAME}\.rs$" | head -1)

    if [ -z "$BIN_FILE" ]; then
        echo "Error: No file matching 'leet_*_${NAME}.rs' found in src/bin/"
        echo ""
        echo "Available problems:"
        ls "$SRC_DIR/bin/" 2>/dev/null | grep "^leet_" | sed 's/^leet_[0-9]*_/  /' | sed 's/\.rs$//'
        exit 1
    fi
fi

BIN_PATH="$SRC_DIR/bin/$BIN_FILE"
DEST_PATH="$SRC_DIR/leetcode/${NAME}.rs"

if [ -f "$DEST_PATH" ]; then
    echo "Error: $DEST_PATH already exists"
    exit 1
fi

echo "Processing: $BIN_PATH"

# Extract slug from URL in file header
SLUG=$(grep "^//! - URL:" "$BIN_PATH" | sed 's|.*leetcode.com/problems/||' | sed 's|/$||')

if [ -z "$SLUG" ]; then
    echo "Error: Could not extract slug from file"
    exit 1
fi

echo "Fetching tags for '$SLUG'..."

# Fetch tags from LeetCode API
API_RESULT=$(curl -s 'https://leetcode.com/graphql' \
    -H 'Content-Type: application/json' \
    --data-raw "{\"query\":\"query { question(titleSlug: \\\"$SLUG\\\") { topicTags { name } } }\"}")

# Parse tags (comma-separated)
TAGS=$(echo "$API_RESULT" | jq -r '.data.question.topicTags[].name' 2>/dev/null | paste -sd ',' -)

if [ -z "$TAGS" ] || [ "$TAGS" = "null" ]; then
    echo "Warning: Could not fetch tags from API"
    TAGS=""
fi

# Process the file:
# 1. Add Tags line after URL line (if tags exist)
# 2. Remove fn main() { ... } block

awk -v tags="$TAGS" '
BEGIN { in_main = 0; brace_count = 0 }

# Add Tags line after URL line
/^\/\/! - URL:/ {
    print
    if (tags != "") {
        print "//! - Tags: " tags
    }
    next
}

# Detect start of main function
/^fn main\(\)/ {
    in_main = 1
    brace_count = 0
    # Count braces on this line
    line = $0
    while (match(line, /[{}]/)) {
        c = substr(line, RSTART, 1)
        if (c == "{") brace_count++
        if (c == "}") brace_count--
        line = substr(line, RSTART + 1)
    }
    if (brace_count <= 0) in_main = 0
    next
}

# When inside main, track braces
in_main {
    line = $0
    while (match(line, /[{}]/)) {
        c = substr(line, RSTART, 1)
        if (c == "{") brace_count++
        if (c == "}") brace_count--
        line = substr(line, RSTART + 1)
    }
    if (brace_count <= 0) in_main = 0
    next
}

# Print other lines
{ print }
' "$BIN_PATH" > "$DEST_PATH.tmp"

# Remove trailing blank lines (macOS compatible)
perl -pe 'chomp if eof' "$DEST_PATH.tmp" | cat -s > "$DEST_PATH"
rm "$DEST_PATH.tmp"

# Add to mod.rs
MOD_FILE="$SRC_DIR/leetcode/mod.rs"
if ! grep -q "^pub mod ${NAME};$" "$MOD_FILE" 2>/dev/null; then
    echo "pub mod ${NAME};" >> "$MOD_FILE"
fi

# Remove the bin file
rm "$BIN_PATH"

echo "Moved: $BIN_PATH → $DEST_PATH"
echo "Added to mod.rs: pub mod ${NAME};"
if [ -n "$TAGS" ]; then
    echo "Tags: $TAGS"
fi
echo ""
echo "Done! Run tests with: cargo test --lib leetcode::${NAME}"
