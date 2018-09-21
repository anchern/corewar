/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:41:49 by achernys          #+#    #+#             */
/*   Updated: 2018/05/03 19:42:15 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_int(va_list *argptr)
{
	return (va_arg(*argptr, int));
}

long		get_long(va_list *argptr)
{
	return (va_arg(*argptr, long));
}

short		get_short(va_list *argptr)
{
	return ((short int)va_arg(*argptr, int));
}

intmax_t	*get_intmptr(va_list *argptr)
{
	return (va_arg(*argptr, intmax_t *));
}

int			*get_intptr(va_list *argptr)
{
	return (va_arg(*argptr, int *));
}
