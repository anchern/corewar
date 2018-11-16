/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_nulling_pc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:14:44 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 14:36:04 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

t_pc	*init_pc(void)
{
	t_pc *pc;

	if (!(pc = (t_pc *)malloc(sizeof(t_pc))))
		exit(INIT_ERR);
	pc->options = init_options(pc->options);
	return (pc);
}

void	nulling_pc(t_pc *pc, short pc_index)
{
	int i;

	i = 0;
	while (i < 16)
	{
		pc->registry[i] = 0;
		i++;
	}
	pc->carry = 0;
	pc->next = 0;
	pc->action = 0;
	pc->pc_index = pc_index;
	nulling_options(pc->options);
	pc->command = 0;
	pc->alive_label = 0;
	pc->time_todo = 0;
	pc->pc_number = 0;
}
