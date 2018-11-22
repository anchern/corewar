/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_manipulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:17:50 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 14:48:16 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

int			pc_number(t_pc *pc)
{
	if (pc == 0)
		return (0);
	return (pc_number(pc->next) + 1);
}

void		dop_pc_delete(t_data_prog *data_prog, t_pc **save_previous,
						t_pc **tmp_pc, char *flag)
{
	t_pc	*first_pc;
	t_pc	*removable_pc;

	first_pc = data_prog->pc;
	while (first_pc != 0)
	{
		if (*save_previous != 0 && *flag == 0)
		{
			*tmp_pc = *save_previous;
			*flag = 1;
		}
		if (first_pc->alive_label == 0)
		{
			removable_pc = first_pc;
			first_pc = first_pc->next;
			if (*save_previous != 0)
				(*save_previous)->next = first_pc;
			free(removable_pc->options);
			free(removable_pc);
		}
		if (first_pc != 0 && first_pc->alive_label == 1)
			*save_previous = first_pc;
		if (first_pc != 0 && first_pc->alive_label == 1)
			first_pc = first_pc->next;
	}
}

void		death_pc_delete(t_data_prog *data_prog)
{
	t_pc	*tmp_pc;
	t_pc	*save_previous;
	char	flag;

	save_previous = 0;
	tmp_pc = data_prog->pc;
	if (tmp_pc->alive_label == 1)
		flag = 1;
	else
		flag = 0;
	dop_pc_delete(data_prog, &save_previous, &tmp_pc, &flag);
	if (flag == 0 && save_previous != 0)
		tmp_pc = save_previous;
	else if (flag == 0)
		tmp_pc = 0;
	data_prog->pc = tmp_pc;
	data_prog->first_pc = data_prog->pc;
}

void		nulling_alive_pc(t_pc *pc, t_data_prog *data_prog)
{
	if (pc == 0)
		return ;
	pc->alive_label = 0;
	nulling_alive_pc(pc->next, data_prog);
}
