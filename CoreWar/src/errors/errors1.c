/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:51:05 by achernys          #+#    #+#             */
/*   Updated: 2018/09/28 06:27:18 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	too_many_players_err()
{
	ft_printf("Too many champions.\n");
	exit(MANY_PLAYERS_ERR);
}

void	file_error(char *path)
{
	ft_printf("Can't read source file %s", path);
	exit(FILE_ERR);
}