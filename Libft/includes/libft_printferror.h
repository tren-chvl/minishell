/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printferror.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:58:15 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 10:59:54 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTFERROR_H
# define LIBFT_PRINTFERROR_H

# include <stdarg.h>
# include <unistd.h>
# include <libft_io.h>
# include <libft_length.h>

int	handle_cerror(va_list list);
int	handle_serror(va_list list);
int	handle_derror(va_list list);
int	handle_ierror(va_list list);
int	handle_uerror(va_list list);

int	ft_printferror(const char *str, ...);

#endif
