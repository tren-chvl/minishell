# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 15:35:28 by dedavid           #+#    #+#              #
#    Updated: 2025/12/06 15:59:00 by dedavid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g -Iincludes -ILibft/includes
SRC_DIR := src
OBJ_DIR := obj
SRCS    := $(shell find $(SRC_DIR) -type f -name "*.c")
LIBS    := Libft/libft.a
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS    := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C Libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -lncurses -o $(NAME)
	@echo "✅ Build complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

clean:
	@make clean -C Libft
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objects cleaned"

fclean: clean
	@make fclean -C Libft
	@rm -rf $(NAME)
	@echo "🗑️ Full clean done"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re $(NAME)
