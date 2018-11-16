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

header_t	*init_header(header_t *header)
{
	if (!(header = (header_t *)ft_memalloc(sizeof(header_t))))
		exit(INIT_ERR);
	return (header);
}

void		nulling_header(header_t *header)
{
	header->magic = 0;
	header->prog_size = 0;
}
