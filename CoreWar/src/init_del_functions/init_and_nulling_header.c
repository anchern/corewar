/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_nulling_header.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 08:08:43 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 08:08:43 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

t_header	*init_header(t_header *header)
{
	if (!(header = (t_header *)ft_memalloc(sizeof(t_header))))
		exit(INIT_ERR);
	return (header);
}

void		nulling_header(t_header *header)
{
	header->magic = 0;
	header->prog_size = 0;
}
