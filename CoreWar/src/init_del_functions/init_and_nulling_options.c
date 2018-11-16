/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_nulling_options.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:11:31 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 08:14:41 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

t_options	*init_options(t_options *options)
{
	if (!(options = (t_options *)ft_memalloc(sizeof(t_options))))
		exit(INIT_ERR);
	return (options);
}

void		nulling_options(t_options *options)
{
	int i;

	i = 0;
	while (i < 3)
	{
		options->dir[i] = 0;
		options->reg[i] = 0;
		if (i < 2)
			options->ind[i] = 0;
		options->option_number[i] = 0;
		i++;
	}
}
