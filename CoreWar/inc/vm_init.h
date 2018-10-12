#ifndef VM_INIT_H
# define VM_INIT_H

# include "vm.h"

t_player	*init_player(void);
void		nulling_player_and_gameinfo(t_player *player,
							t_game_info *game_info);
t_options	*init_options(t_options *options);
t_game_info	*init_game_info(void);
header_t	*init_header(header_t *header);
t_arrays	*init_arrays(t_arrays *arrays);
void		init_options_array(t_arrays **arrays);
void		init_function_array(t_arrays **arrays);
void		nulling_header(header_t *header);
t_pc		*init_pc(void);
void		nulling_pc(t_pc *pc, short pc_index);
void		nulling_options(t_options *options);
void		init_time_to_do_list(unsigned short *to_do_list);
t_data_prog	*data_prog_init(void);
#endif
