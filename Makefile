NAME := minishell

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -Iincludes -I/opt/homebrew/opt/readline/include
LDFLAGS := -L/opt/homebrew/opt/readline/lib -lreadline
RM := rm -rf

# Directory structure
MAIN_DIR := main
PARSE_DIR := parse
OBJ_DIR := obj
LIBFT := libft/libft.a

# Source files
MAIN_SRCS := main.c
PARSE_SRCS := parse.c token.c checks.c helpers.c lexer.c tokenizer.c

# Add directory prefixes
MAIN_SRCS := $(addprefix $(MAIN_DIR)/, $(MAIN_SRCS))
PARSE_SRCS := $(addprefix $(PARSE_DIR)/, $(PARSE_SRCS))
SRCS := $(MAIN_SRCS) $(PARSE_SRCS)

# Object files
OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
