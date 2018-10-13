/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:04:39 by achernys          #+#    #+#             */
/*   Updated: 2018/10/13 03:18:06 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VM_H
# define VM_H

# include "../lib/mylib/ft_printf.h"
# include "../inc/op.h"
# include "errors.h"
# include <fcntl.h>

# define FIELD_SIZE 4096
# define FALSE 0
# define TRUE 1
# define FIRST_CODE(x) (x >> 6 & 3)
# define MIDDLE_CODE(x) (x >> 4 & 3)
# define LAST_CODE(x) (x >> 2 & 3)

typedef struct			s_options
{
	char 				reg[3];
	unsigned int		dir[3];
	short				ind[2];
	char				option_number[3];
}						t_options;

typedef struct			s_pc
{
	short				pc_index;
	unsigned char		alive_label;
	unsigned short		time_todo;
	unsigned char		command;
	unsigned char		jump;
	char 				label;
	unsigned int 		registry[REG_NUMBER];
	t_options		*options;
	struct s_pc 		*next;
}						t_pc;

typedef struct			s_player
{
	header_t			*header;
	unsigned			player_number;
	char 				carry;
	int 				alive_counter;
	int 				last_live;
	unsigned int 		registry[REG_NUMBER];
	t_pc				*pc;
	t_pc				*first_pc;
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

typedef struct 			s_arrays
{
	char				(*options_array[15])(t_options *options, t_sell *field, short pc_i, char dir_size);
	unsigned int		(*functions_array[14])(t_options *options, t_player *player, t_sell *field);
}						t_arrays;

typedef struct			s_data_prog
{
	t_game_info		*game_info;
	t_player		*player;
	t_player		*first_player;
	t_arrays		*arrays;
	unsigned short 	to_do_list[15];
}						t_data_prog;

unsigned int			bytestoui(const t_sell *byte, short index);
short					bytestos(const t_sell *byte, short index);
void					uitobytes(unsigned value, t_sell *field, short index);

unsigned int			alive_command(t_options *options,
										t_data_prog *data_prog, int counter);
unsigned int			load_command(t_options *options, t_player *player,
										t_sell *field);
unsigned int			store_command(t_options *options, t_player *player,
										t_sell *field);
unsigned int			addition_command(t_options *options, t_player *player);
unsigned int			substraction_command(t_options *options, t_player *player);
unsigned int			and_function(t_options *options, t_player *player);
unsigned int			or_function(t_options *options, t_player *player);
unsigned int			xor_function(t_options *options, t_player *player);
unsigned int			jump_function(t_options *options, t_player *player);
unsigned int			load_index_function(t_options *options,
										t_player *player, t_sell *field);
unsigned int			store_index_function(t_options *options,
										t_player *player, t_sell *field);
unsigned int			fork_function(t_options *options, t_player *player);
unsigned int			long_load_command(t_options *options, t_player *player,
										t_sell *field);
unsigned int			long_load_index_function(t_options *options,
										t_player *player, t_sell *field);
unsigned int			long_fork_function(t_options *options,
										t_player *player);
short					true_value_pc_index(short pc_index);
char					isrdi(unsigned char byte, char shift);
char					save_reg(t_sell *field, t_options *opt, char opt_num);
char					save_dir(t_sell *field, t_options *opt, char opt_num);
char					save_ind(t_sell *field, t_options *opt, char opt_num);
char					add_indent(char arg, int dir_size);
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

void					set_players(t_data_prog *data_prog, int start_arg,
										int argc, char **argv);
void					goround_players(t_data_prog *data_prog);
void					current_cycle_to_die(t_data_prog *data_prog);

void					print_field(t_game_info *game_info, t_pc *pc);
char					get_indent_pc(unsigned char codage_octal,
										char dir_size);
void					copy_registry(t_pc *new_pc, t_pc *pc);
#endif
