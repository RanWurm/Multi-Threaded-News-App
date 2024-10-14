# Compiler options
CC := gcc
CFLAGS := -w -pthread

# Directories
SRC_DIR := .
OBJ_DIR := obj
BOUNDED_QUEUE_OBJ_DIR := $(OBJ_DIR)/bounded_buffer

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/bounded_buffer/*.c)
SRCS += $(wildcard $(SRC_DIR)/co_editor/*.c)
SRCS += $(wildcard $(SRC_DIR)/data_handler/*.c)
SRCS += $(wildcard $(SRC_DIR)/dispatcher/*.c)
SRCS += $(wildcard $(SRC_DIR)/news_runner/*.c)
SRCS += $(wildcard $(SRC_DIR)/producer/*.c)
SRCS += $(wildcard $(SRC_DIR)/queue/*.c)
SRCS += $(wildcard $(SRC_DIR)/screen_manager/*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: news

# Rule to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the executable
news: $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
	@rm -rf $(OBJ_DIR)

# Target to run the executable with conf.txt as argument
run: news
	@./news config.txt

# Cleanup
clean:
	@rm -f news
	@rm -rf $(OBJ_DIR)

.PHONY: all run clean
