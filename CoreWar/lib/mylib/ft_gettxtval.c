/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettxtval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:10:22 by achernys          #+#    #+#             */
/*   Updated: 2018/05/03 19:10:56 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	get_char(va_list *argptr)
{
	return ((char)va_arg(*argptr, int));
}

wchar_t	get_wchar(va_list *argptr)
{
	return (va_arg(*argptr, wchar_t));
}

char	*get_str(va_list *argptr)
{
	return (va_arg(*argptr, char *));
}

wchar_t	*get_wstr(va_list *argptr)
{
	return (va_arg(*argptr, wchar_t *));
}
