# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 15:35:28 by dedavid           #+#    #+#              #
#    Updated: 2025/12/01 10:13:25 by marcheva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -g -Iincludes -ILibft/includes
SRC_DIR := src
SRCS    := $(shell find $(SRC_DIR) -type f -name "*.c") \
		pipex/ft_path.c \
		pipex/ft_utils.c \
		pipex/ft_utils2.c \
		pipex/get_next_line_utils.c \
		pipex/ft_split.c
LIBS    := Libft/libft.a
LDFLAGS := -lreadline -lncurses

all: $(NAME)

$(NAME):
	make -C Libft
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) $(LDFLAGS) -o $(NAME)

clean:
	make clean -C Libft
	rm -rf $(NAME)

fclean:
	make fclean -C Libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)
