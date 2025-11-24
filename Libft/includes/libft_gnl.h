/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:49:00 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:35:58 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <libft_string.h>
#include <libft_length.h>
#include <libft_memory.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);

#endif
