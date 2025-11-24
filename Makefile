# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 15:35:28 by dedavid           #+#    #+#              #
#    Updated: 2025/11/24 15:53:49 by dedavid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g -Iincludes -ILibft/includes -lreadline
SRC_DIR	:= src
SRCS	:= $(shell find $(SRC_DIR) -type f -name "*.c")
LIBS	:= Libft/libft.a

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
