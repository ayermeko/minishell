NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
SRCS = error_msg.c fd_handler.c heredoc_exec.c init_minienv.c parser.c \
       redirect.c scanner.c utils.c builtin_exec.c expand_input.c \
       free_utils.c heredoc_handler.c main.c pipe.c redirect_io.c \
       signal_handler.c \
       buildins/cd.c buildins/echo.c buildins/env.c buildins/exit.c \
       buildins/export.c buildins/pwd.c buildins/unset.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = obj
LDLIBS	= -lreadline -lft
LDFLAGS	= -L./extra_libs/Libft
VPATH = src/
LIBFT_A	= extra_libs/Libft//libft.a
LIBFT_PATH	= extra_libs/Libft/

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	@echo $(NAME) done

$(LIBFT_A):
	make bonus -C  $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p $@

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo removed $(OBJ_DIR) folder

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo removed $(NAME)

re: fclean all

.PHONY: all run clean fclean re