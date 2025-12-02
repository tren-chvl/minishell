/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:58:15 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 14:47:34 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <libft_io.h>
# include <libft_length.h>

int	handle_c(va_list list);
int	handle_s(va_list list);
int	handle_p(va_list list);
int	handle_d(va_list list);
int	handle_i(va_list list);
int	handle_u(va_list list);
int	handle_x(va_list list);
int	handle_xx(va_list list);

int	ft_printf(const char *str, ...);

#endif
