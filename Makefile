NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -pthread

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
INCLUDE_DIR = include

# Source directories
CORE_DIR = $(SRC_DIR)/core
ACTIONS_DIR = $(SRC_DIR)/actions
MONITOR_DIR = $(SRC_DIR)/monitor
UTILS_DIR = $(SRC_DIR)/utils

# Source files organized by category
CORE_SRC = $(CORE_DIR)/philo.c $(CORE_DIR)/init.c $(CORE_DIR)/threads.c $(CORE_DIR)/routine.c
ACTIONS_SRC = $(ACTIONS_DIR)/actions.c $(ACTIONS_DIR)/actions_utils.c $(ACTIONS_DIR)/forks.c
MONITOR_SRC = $(MONITOR_DIR)/monitor.c $(MONITOR_DIR)/monitor_utils.c
UTILS_SRC = $(UTILS_DIR)/utils.c $(UTILS_DIR)/getters.c $(UTILS_DIR)/log_utils.c \
           $(UTILS_DIR)/sim_utils.c $(UTILS_DIR)/timing.c $(UTILS_DIR)/special_cases.c

# All source files
SRC = $(CORE_SRC) $(ACTIONS_SRC) $(MONITOR_SRC) $(UTILS_SRC)

# Object files with proper directory structure
CORE_OBJ = $(CORE_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ACTIONS_OBJ = $(ACTIONS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MONITOR_OBJ = $(MONITOR_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
UTILS_OBJ = $(UTILS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ = $(CORE_OBJ) $(ACTIONS_OBJ) $(MONITOR_OBJ) $(UTILS_OBJ)

HEADERS = $(INCLUDE_DIR)/philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Create object directories and compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: $(NAME)

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the project"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove object files and executable"
	@echo "  re      - Rebuild everything"
	@echo "  debug   - Build with debug flags"
	@echo "  help    - Show this help message"

.PHONY: all clean fclean re debug help
