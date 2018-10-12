/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iobytes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 22:40:15 by achernys          #+#    #+#             */
/*   Updated: 2018/09/21 23:21:00 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/vm.h"

unsigned int	bytestoui(const t_sell *byte, short index)
{
	unsigned int	result;

	if (index < 0)
		index += FIELD_SIZE;
	result = 0;
	result = (result | byte[index].value) << 8;
	result = (result | byte[(index + 1) >= FIELD_SIZE ? (index + 1) % FIELD_SIZE
													: index + 1].value) << 8;
	result = (result | byte[(index + 2) >= FIELD_SIZE ? (index + 2) % FIELD_SIZE
													  : index + 2].value) << 8;
	result = result | byte[(index + 3) >= FIELD_SIZE ? (index + 3) % FIELD_SIZE
													 : index + 3].value;
	return (result);
}

short			bytestos(const t_sell *byte, short index)
{
	short	result;

	if (index < 0)
		index += FIELD_SIZE;
	result = 0;
	result = (result | byte[index].value) << 8;
	result = result | byte[(index + 1) >= FIELD_SIZE ? (index + 1) % FIELD_SIZE
													  : index + 1].value;
	return (result);
}

void			uitobytes(unsigned value, t_sell *field, short index)
{
	if (index < 0)
		index += FIELD_SIZE;
	field[(index + 3) >= FIELD_SIZE ? (index + 3) % FIELD_SIZE :
			index + 3].value = (unsigned char) value;
	value >>= 8;
	field[(index + 2) >= FIELD_SIZE ? (index + 2) % FIELD_SIZE :
			index + 2].value = (unsigned char) value;
	value >>= 8;
	field[(index + 1) >= FIELD_SIZE ? (index + 1) % FIELD_SIZE :
			index + 1].value = (unsigned char) value;
	value >>= 8;
	field[index].value = (unsigned char) value;
}
