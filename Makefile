# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayermeko <ayermeko@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:53:14 by ayermeko          #+#    #+#              #
#    Updated: 2024/09/16 18:56:24 by ayermeko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra - Werror
SRCS = ...
OBJS = ...
OBJ_DIR = ...

LIBFT_PATH	= ../extra_libs/Libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	@echo $(NAME) done

$(LIBFT_A):
	make -C libft

$(OBJ_DIR):
	@mkdir -p $@

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo removed $(OBJ_DIR) folder

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo removed $(NAME)

re: fclean all

.PHONY: all run clean fclean re