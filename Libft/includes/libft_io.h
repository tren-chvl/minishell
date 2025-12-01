/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:23:00 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 14:12:03 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include <unistd.h>
# include <libft_length.h>

void	putchar_fd(char c, int fd);
void	putstr_fd(char *s, int fd);
void	putendl_fd(char *s, int fd);
void	putnbr_fd(ssize_t n, int fd);

void	putnbr_base(ssize_t nbr, char *base);
void	putunsignednbr_base(size_t nb, char *base);

#endif
