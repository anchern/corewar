/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:04:39 by achernys          #+#    #+#             */
/*   Updated: 2018/09/21 15:09:49 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VM_H
# define VM_H

# include "../lib/mylib/ft_printf.h"
# include "../inc/op.h"
# include <fcntl.h>

# define FIELD_SIZE 4096

typedef struct	s_pc
{
	int			pc_index;
	int			global_i;
	char		alive_label;
	int			time_todo;
	int			command;
	struct s_pc *next;
}				t_pc;

typedef struct	s_player
{
	int 				carry;
	int 				alive_counter;
	int 				last_live;
	unsigned int 		*registry;
	t_pc				pc;
	struct	s_player 	*next;
}				t_player;

typedef struct	s_sell
{
	char 			owner;
	unsigned char	value;
}				t_sell;

typedef struct	s_game_info
{
	int			counter;
	int			cycle_delta_counter;
	int			max_checks_counter;
	t_sell		field[FIELD_SIZE];
}				t_game_info;




#endif
