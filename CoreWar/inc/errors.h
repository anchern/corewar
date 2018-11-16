/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:37:44 by achernys          #+#    #+#             */
/*   Updated: 2018/09/28 06:30:31 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define MANY_PLAYERS_ERR 70
# define FILE_ERR 71
# define FILE_INFORM_ERR 72
# define INIT_ERR 73
# define ARG_ERR 74

void	file_error(char *path);
void	too_many_players_err(void);

#endif
