/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_convert.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:14:36 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:04:41 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERT_H
#define LIBFT_CONVERT_H

#include <stdlib.h>
#include <libft_string.h>
#include <libft_io.h>
#include <libft_char.h>

int     ft_atoi(const char *str);
char    *ft_itoa(int n);
char	*itoa_base(int n, char *base);

int		atoi_base(char *str, char *base);
size_t	uatol_base(char *str, char *base);
char    *ft_convert_base(char *nbr, char *base_from, char *base_to);

#endif