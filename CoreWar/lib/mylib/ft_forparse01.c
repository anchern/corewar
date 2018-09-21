/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forparse01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:16:34 by achernys          #+#    #+#             */
/*   Updated: 2018/05/10 20:46:09 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*isneedtoadd(char *argstr, t_data *data, char identifier)
{
	char	*outstr;

	outstr = 0;
	if (data->width > ft_strlen(argstr))
	{
		outstr = addspace(argstr, data, identifier);
		ft_memdel((void **)&argstr);
	}
	return (outstr);
}

int		getnum(const char *format, t_argptrsave *structarg,
				size_t *addi, t_data *data)
{
	size_t savei;

	savei = *addi;
	if (format[*addi] == '*')
	{
		if (data->pstar || data->wstar)
		{
			procstar(data, structarg);
			data->dollar = 0;
		}
		data->pstar = format[*addi - 1] == '.' ? 1 : 0;
		data->wstar = format[*addi - 1] == '.' ? 0 : 1;
		return (-1);
	}
	else
	{
		while (ft_isdigit(format[*addi]))
			*addi += 1;
		return (ft_atoi((char *)&format[savei]));
	}
}

void	procn(int len, t_argptrsave *structarg, t_data *data)
{
	long long		*n;

	n = (long long *)get_intptr(&structarg->argptrcurr);
	if (data->l == 2)
		*n = (long long)len;
	else if (data->h == 2)
		*n = (char)len;
	else if (data->h == 1)
		*n = (short)len;
	else if (data->z == 1)
		*n = (ssize_t)len;
	else if (data->l == 1)
		*n = (long)len;
	else if (data->j == 1)
		*n = (intmax_t)len;
	else
		*n = len;
}

char	*procdig(char identifier, t_data *data, t_argptrsave *structarg)
{
	char	*argstr;
	char	*outstr;

	if (ft_strchr("diDuU", identifier))
	{
		argstr = procint(data, structarg, identifier);
		outstr = isneedtoadd(argstr, data, identifier);
		return (outstr == 0 ? argstr : outstr);
	}
	if (ft_strchr("xXoObp", identifier))
	{
		argstr = procnotation(data, structarg, identifier);
		outstr = isneedtoadd(argstr, data, identifier);
		return (outstr == 0 ? argstr : outstr);
	}
	return (0);
}

char	*proctext(char identifier, t_data *data, t_argptrsave *structarg)
{
	char	*argstr;
	char	*outstr;

	if (identifier == 'c' || identifier == 'C')
	{
		argstr = procc(identifier, data, structarg);
		if (argstr == 0 || *argstr == 0)
			return (0);
		outstr = isneedtoadd(argstr, data, identifier);
		return (outstr == 0 ? argstr : outstr);
	}
	if (identifier == 's' || identifier == 'S')
	{
		argstr = procs(identifier, data, structarg);
		if (argstr == 0)
			return (0);
		outstr = isneedtoadd(argstr, data, identifier);
		return (outstr == 0 ? argstr : outstr);
	}
	return (0);
}
