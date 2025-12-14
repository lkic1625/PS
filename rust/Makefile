# PS Rust Makefile
# Usage:
#   make fetch-leet SLUG=two-sum
#   make fetch-leet-num NUM=1
#   make done NAME=two_sum

TEMPLATES_DIR := templates
SRC_DIR := src

# Convert kebab-case to snake_case
define to_snake_case
$(shell echo "$(1)" | tr '[:upper:]' '[:lower:]' | sed 's/-/_/g' | sed 's/ /_/g')
endef

# Fetch LeetCode problem from API (by slug)
.PHONY: fetch-leet
fetch-leet:
ifndef SLUG
	$(error SLUG is required. Usage: make fetch-leet SLUG=two-sum)
endif
	@./scripts/fetch-leet.sh "$(SLUG)"

# Fetch LeetCode problem from API (by number)
.PHONY: fetch-leet-num
fetch-leet-num:
ifndef NUM
	$(error NUM is required. Usage: make fetch-leet-num NUM=1)
endif
	@./scripts/fetch-leet.sh --num "$(NUM)"

# LeetCode template (manual)
.PHONY: new-leet
new-leet:
ifndef NUM
	$(error NUM is required. Usage: make new-leet NUM=42 NAME="two-sum" DIFF=Easy TAGS="Array")
endif
ifndef NAME
	$(error NAME is required. Usage: make new-leet NUM=42 NAME="two-sum" DIFF=Easy TAGS="Array")
endif
	$(eval SNAKE_NAME := $(call to_snake_case,$(NAME)))
	$(eval SLUG := $(shell echo "$(NAME)" | tr '[:upper:]' '[:lower:]' | sed 's/ /-/g'))
	$(eval FILE := $(SRC_DIR)/leetcode/$(SNAKE_NAME).rs)
	$(eval DIFF := $(if $(DIFF),$(DIFF),Medium))
	$(eval TAGS := $(if $(TAGS),$(TAGS),))
	@if [ -f "$(FILE)" ]; then \
		echo "Error: $(FILE) already exists"; \
		exit 1; \
	fi
	@sed -e 's/{{NAME}}/$(NAME)/g' \
		-e 's/{{NUM}}/$(NUM)/g' \
		-e 's/{{DIFF}}/$(DIFF)/g' \
		-e 's/{{TAGS}}/$(TAGS)/g' \
		-e 's/{{SLUG}}/$(SLUG)/g' \
		$(TEMPLATES_DIR)/leetcode.rs.tpl > $(FILE)
	@if ! grep -q "pub mod $(SNAKE_NAME);" $(SRC_DIR)/leetcode/mod.rs 2>/dev/null; then \
		echo "pub mod $(SNAKE_NAME);" >> $(SRC_DIR)/leetcode/mod.rs; \
	fi
	@echo "Created: $(FILE)"
	@echo "Added to mod.rs: pub mod $(SNAKE_NAME);"

# BOJ template
.PHONY: new-boj
new-boj:
ifndef NUM
	$(error NUM is required. Usage: make new-boj NUM=1234 NAME="problem" DIFF=Gold3 TAGS="DP")
endif
ifndef NAME
	$(error NAME is required. Usage: make new-boj NUM=1234 NAME="problem" DIFF=Gold3 TAGS="DP")
endif
	$(eval SNAKE_NAME := boj$(NUM))
	$(eval FILE := $(SRC_DIR)/boj/$(SNAKE_NAME).rs)
	$(eval DIFF := $(if $(DIFF),$(DIFF),Silver))
	$(eval TAGS := $(if $(TAGS),$(TAGS),))
	@if [ -f "$(FILE)" ]; then \
		echo "Error: $(FILE) already exists"; \
		exit 1; \
	fi
	@sed -e 's/{{NAME}}/$(NAME)/g' \
		-e 's/{{NUM}}/$(NUM)/g' \
		-e 's/{{DIFF}}/$(DIFF)/g' \
		-e 's/{{TAGS}}/$(TAGS)/g' \
		$(TEMPLATES_DIR)/boj.rs.tpl > $(FILE)
	@if ! grep -q "pub mod $(SNAKE_NAME);" $(SRC_DIR)/boj/mod.rs 2>/dev/null; then \
		echo "pub mod $(SNAKE_NAME);" >> $(SRC_DIR)/boj/mod.rs; \
	fi
	@echo "Created: $(FILE)"
	@echo "Added to mod.rs: pub mod $(SNAKE_NAME);"

# Mark problem as done (move from bin/ to leetcode/)
.PHONY: done
done:
ifndef NAME
	$(error NAME is required. Usage: make done NAME=two_sum)
endif
	@./scripts/done.sh "$(NAME)"

# List work-in-progress problems
.PHONY: wip
wip:
	@echo "Work in progress (src/bin/):"
	@ls src/bin/ 2>/dev/null | grep "^leet_" | sed 's/^leet_/  /' | sed 's/\.rs$$//' || echo "  (none)"

# Help
.PHONY: help
help:
	@echo "PS Rust Makefile"
	@echo ""
	@echo "=== LeetCode Workflow ==="
	@echo ""
	@echo "  1. Fetch problem (creates binary in src/bin/):"
	@echo "     make fetch-leet SLUG=two-sum"
	@echo "     make fetch-leet-num NUM=1"
	@echo ""
	@echo "  2. Work on the problem:"
	@echo "     cargo run --bin leet_1_two_sum"
	@echo "     cargo test --bin leet_1_two_sum"
	@echo ""
	@echo "  3. Mark as done (moves to src/leetcode/, fetches tags from API):"
	@echo "     make done NAME=two_sum"
	@echo ""
	@echo "  List WIP problems: make wip"
	@echo ""
	@echo "=== Manual Templates ==="
	@echo ""
	@echo "  make new-leet NUM=42 NAME=\"trapping-rain-water\" DIFF=Hard TAGS=\"Stack,DP\""
	@echo "  make new-boj NUM=1234 NAME=\"problem-name\" DIFF=Gold3 TAGS=\"DP,Graph\""
	@echo ""
	@echo "=== Difficulty Levels ==="
	@echo "  LeetCode: Easy, Medium, Hard"
	@echo "  BOJ: Bronze5-1, Silver5-1, Gold5-1, Platinum5-1, Diamond5-1, Ruby5-1"
