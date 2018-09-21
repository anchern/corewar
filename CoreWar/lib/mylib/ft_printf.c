/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:23:08 by achernys          #+#    #+#             */
/*   Updated: 2018/05/09 20:21:48 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "ft_printf.h"

static void		printarg(const char *str, const size_t *addi, t_data *data,
							t_argptrsave *structarg)
{
	char	*argstr;

	argstr = getargstr(str[*addi], data, structarg);
	if (argstr != 0 && ft_strcmp(argstr, "0x"))
		structarg->len += write(1, argstr, ft_strlen(argstr));
	else if (ft_strchr("cCsS", str[*addi]))
		structarg->len += printnullstr(data, str[*addi]);
	else if (str[*addi] == 'p')
		structarg->len += write(1, data->prec == 0 ? "0x" : "0x0",
								data->prec == 0 ? 2 : 3);
	else if (ft_strchr("oOxX", str[*addi]) && (argstr == 0 || *argstr == 0) &&
			data->prec != 0)
		structarg->len += write(1, "0", 1);
	ft_memdel((void **)&argstr);
}

static size_t	parse_arg(const char *str, t_argptrsave *structarg)
{
	size_t	addi;
	t_data	*data;

	data = getdatastruct();
	addi = 1;
	processingflags(str, structarg, &addi, data);
	if (str[addi] == 'n')
		procn(structarg->len, structarg, data);
	else if (str[addi] != 0)
		printarg(str, &addi, data, structarg);
	addi = str[addi] == 0 ? addi + 0 : addi + 1;
	ft_memdel((void **)&data);
	return (addi);
}

static int		getoutstr(const char *format, t_argptrsave *structarg)
{
	size_t	i;
	size_t	lencurpart;

	i = 0;
	lencurpart = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '{')
			set_color(&(structarg->len), &i, &lencurpart, format);
		if (format[i] == 0)
			break ;
		if (format[i] == '%' && format[i + 1] != 0)
		{
			structarg->len += write(1, &format[i - lencurpart], lencurpart);
			lencurpart = 0;
			i += parse_arg(&format[i], structarg);
			continue ;
		}
		i++;
		lencurpart++;
	}
	if (lencurpart != 0)
		structarg->len += write(1, &format[i - lencurpart],
					format[i - 1] == '%' ? lencurpart - 1 : lencurpart);
	return (structarg->len);
}

int				ft_printf(const char *format, ...)
{
	t_argptrsave	*structarg;
	int				len;

	if (format == 0)
		return (0);
	structarg = (t_argptrsave *)ft_memalloc(sizeof(*structarg));
	structarg->len = 0;
	va_start(structarg->argptrstart, format);
	va_copy(structarg->argptrcurr, structarg->argptrstart);
	va_copy(structarg->argstar, structarg->argptrstart);
	if ((len = getoutstr(format, structarg)) > -1)
	{
		closearglst(structarg);
		ft_memdel((void **)&structarg);
		return (len);
	}
	closearglst(structarg);
	ft_memdel((void **)&structarg);
	return (-1);
}
