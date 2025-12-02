/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_length.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:14:08 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 14:12:18 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LENGTH_H
# define LIBFT_LENGTH_H

# include <sys/types.h>

size_t	ft_strlen(const char *s);
size_t	nbsize(ssize_t n);
size_t	nbsize_base(ssize_t n, char *base);

#endif
