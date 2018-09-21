/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 20:31:20 by achernys          #+#    #+#             */
/*   Updated: 2018/04/20 20:31:20 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	closearglst(t_argptrsave *structarg)
{
	va_end(structarg->argptrstart);
	va_end(structarg->argptrcurr);
	va_end(structarg->argstar);
}
