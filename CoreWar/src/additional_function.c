/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:56:18 by achernys          #+#    #+#             */
/*   Updated: 2018/09/22 02:57:15 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

short	true_value_pc_index(short pc_index)
{
	if (pc_index < 0)
		return (pc_index + (short)FIELD_SIZE);
	if (pc_index >= 0)
		return (pc_index % (short)FIELD_SIZE);
	return (pc_index);
}