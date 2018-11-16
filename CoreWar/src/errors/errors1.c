/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:51:05 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 13:54:38 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	too_many_players_err(void)
{
	ft_printf("Too many champions.\n");
	exit(MANY_PLAYERS_ERR);
}

void	file_error(char *path)
{
	ft_printf("Can't read source file %s\n", path);
	exit(FILE_ERR);
}
