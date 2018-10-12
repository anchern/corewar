/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:56:18 by achernys          #+#    #+#             */
/*   Updated: 2018/10/08 18:07:02 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

short		true_value_pc_index(short pc_index)
{
	if (pc_index < 0)
		return (pc_index + (short)FIELD_SIZE);
	if (pc_index >= 0)
		return (pc_index % (short)FIELD_SIZE);
	return (pc_index);
}

t_player	*find_player_by_number(t_player *first_player,
		unsigned desired_number)
{
	if (first_player == 0)
		return (0);
	if (first_player->player_number == desired_number)
		return (first_player);
	return (find_player_by_number(first_player->next, desired_number));
}