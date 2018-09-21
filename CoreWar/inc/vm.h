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
	short			pc_index;
	unsigned int	global_i;
	unsigned char	alive_label;
	unsigned short	time_todo;
	unsigned char			command;
	struct s_pc 	*next;
}				t_pc;

typedef struct	s_player
{
	char 				player_number;
	char 				carry;
	int 				alive_counter;
	int 				last_live;
	unsigned int 		registry[REG_NUMBER];
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
	int				counter;
	unsigned short	cycle_delta_counter;
	unsigned short	max_checks_counter;
	t_sell		field[FIELD_SIZE];
}				t_game_info;

typedef struct	s_options
{
	char 			reg[3];
	short			dir[3];
	unsigned int	ind[2];
	char			option_number[3];
}				t_options;




#endif
