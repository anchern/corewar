#include "../../inc/vm.h"

void 	alive_command(unsigned int dir_argument, t_player *player, int counter)
{
	t_player *player_tmp;

	player_tmp = player;
	player->pc.alive_label = 1;
	if (dir_argument > 4 || dir_argument < 1)
		return ;
	while (player_tmp != NULL)
	{
		if (player_tmp->player_number == dir_argument)
		{
			player_tmp->last_live = counter;
			player_tmp->alive_counter++;
		}
		player_tmp = player_tmp->next;
	}
}

void	load_command(t_options *options, t_sell *field, t_player *player)
{
ftrf
}
