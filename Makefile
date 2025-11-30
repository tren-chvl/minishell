# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 15:35:28 by dedavid           #+#    #+#              #
#    Updated: 2025/11/25 13:02:25 by marcheva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g -Iincludes -ILibft/includes
SRC_DIR	:= src
SRCS := $(shell find src -type f -name "*.c") \
		pipex_bonus/ft_path.c \
		pipex_bonus/ft_utils.c \
		pipex_bonus/ft_utils2.c \
		pipex_bonus/get_next_line_utils.c \
		pipex_bonus/ft_split.c
LIBS	:= Libft/libft.a
LDFLAGS := -lreadline -lhistory -lncurses
all: $(NAME)

$(NAME):
	make -C Libft
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME) $(LDFLAGS)

clean:
	make clean -C Libft
	rm -rf $(NAME)

fclean:
	make fclean -C Libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)
