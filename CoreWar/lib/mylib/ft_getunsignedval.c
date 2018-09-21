/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getunsignedval.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:23:46 by achernys          #+#    #+#             */
/*   Updated: 2018/04/20 14:41:11 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int		get_unint(va_list *argptr)
{
	return (va_arg(*argptr, unsigned int));
}

unsigned long		get_unlong(va_list *argptr)
{
	return (va_arg(*argptr, unsigned long));
}

unsigned long long	get_ullong(va_list *argptr)
{
	return (va_arg(*argptr, unsigned long long));
}

unsigned short		get_unshort(va_list *argptr)
{
	return ((unsigned short)va_arg(*argptr, int));
}

unsigned char		get_unchar(va_list *argptr)
{
	return ((unsigned char)va_arg(*argptr, int));
}
