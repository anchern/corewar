/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:04:39 by achernys          #+#    #+#             */
/*   Updated: 2018/09/26 10:59:52 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VM_H
# define VM_H

# include "../lib/mylib/ft_printf.h"
# include "../inc/op.h"
# include <fcntl.h>

# define FIELD_SIZE 4096

typedef struct			s_pc
{
	short				pc_index;
	unsigned char		alive_label;
	unsigned short		time_todo;
	unsigned char		command;
	struct s_pc 		*next;
}						t_pc;

typedef struct			s_player
{
	char 				player_number;
	char 				carry;
	int 				alive_counter;
	int 				last_live;
	unsigned int 		registry[REG_NUMBER];
	t_pc				pc;
	struct	s_player 	*next;
}						t_player;

typedef struct			s_sell
{
	char 				owner;
	unsigned char		value;
}						t_sell;

typedef struct			s_game_info
{
	int					counter;
	unsigned short		cycle_delta_counter;
	unsigned short		max_checks_counter;
	t_sell				field[FIELD_SIZE];
}						t_game_info;

typedef struct			s_options
{
	char 				reg[3];
	unsigned int		dir[3];
	short				ind[2];
	char				option_number[3];
}						t_options;

unsigned int			bytestoui(const t_sell *byte, short index);
short					bytestos(const t_sell *byte, short index);
void					uitobytes(unsigned value, t_sell *field, short index);

void 					alive_command(t_options *options, t_player *player,
										int counter);
void					load_command(t_options *options, t_player *player,
										t_sell *field);
void					store_command(t_options *options, t_player *player,
										t_sell *field);
void					addition_command(t_options *options, t_player *player);
void					and_function(t_options *options, t_player *player);
void					or_function(t_options *options, t_player *player);
void					xor_function(t_options *options, t_player *player);
void					jump_function(t_options *options, t_player *player);
void					load_index_function(t_options *options,
										t_player *player, t_sell *field);
void					store_index_function(t_options *options,
										t_player *player, t_sell *field);
void					fork_function(t_options *options, t_player *player);
void					long_load_command(t_options *options, t_player *player,
										t_sell *field);
void					long_load_index_function(t_options *options,
										t_player *player, t_sell *field);
void					long_fork_function(t_options *options,
										t_player *player);
void					add_command(t_options *options, t_player *player);
short					true_value_pc_index(short pc_index);
char					isrdi(unsigned char byte, char shift);
char					save_reg(t_sell *field, t_options *opt, char opt_num);
char					save_dir(t_sell *field, t_options *opt, char opt_num);
char					save_ind(t_sell *field, t_options *opt, char opt_num);
int						add_indent(char arg, int dir_size);
char					d_options(t_options *options, t_sell *field, short pc_i,
										char dir_size);
char					di_r_options(t_options *opt, t_sell *field, short pc_i);
char					r_ri_options(t_options *opt, t_sell *field, short pc_i);
char					r_r_r_options(t_options *options, t_sell *field,
										short pc_i);
char					r_options(t_options *options, t_sell *field,
										short pc_i);
char					rdi_rdi_r_options(t_options *opt, t_sell *field,
										short pc_i);
char					rdi_rd_r_options(t_options *opt, t_sell *field,
										short pc_i);
char					r_rdi_rd_options(t_options *opt, t_sell *field,
										short pc_i);

#endif
