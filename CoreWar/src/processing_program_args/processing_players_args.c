/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:34:51 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 01:08:44 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

void	save_in_var(unsigned int *var, unsigned char *arr)
{
	*var = (*var | arr[0]) << 8;
	*var = (*var | arr[1]) << 8;
	*var = (*var | arr[2]) << 8;
	*var = *var | arr[3];
}

int		copy_field(t_game_info *game_info, unsigned char *field, int field_size,
				   short start_position)
{
	int i;
	
	i = 0;
	while (i < field_size)
	{
		game_info->field[start_position++].value = field[i];
		i++;
	}
	return(i);
}

int		read_header(t_game_info *game_info, header_t *header, char *filename,
					   short start_position)
{
	unsigned char	buf[COMMENT_LENGTH + 1];
	int				fd;
	ssize_t 		rd;
	
	if ((fd = open(filename, O_RDONLY)) < 0)
		file_error(filename);
	header->magic = 0;
	if (fd < 0)
		return (fd);
	if (read(fd,buf, 4) < 4)
		return (fd);
	save_in_var(&header->magic, buf);
	if (header->magic != COREWAR_EXEC_MAGIC)
		return (fd);
	if (read(fd, buf, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (fd);
	ft_strcpy(header->prog_name, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (fd);
	save_in_var(&header->prog_size, buf);
	if (read(fd, buf, 4) < 4)
		return (fd);
	save_in_var(&header->prog_size, buf);
	if (read(fd, buf, COMMENT_LENGTH) < COMMENT_LENGTH)
		return (fd);
	ft_strcpy(header->comment, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (fd);
	if ((rd = read(fd, buf, header->prog_size)) < header->prog_size || rd > CHAMP_MAX_SIZE)
		return (fd);
	if (header->prog_size != copy_field(game_info, buf, header->prog_size, start_position))
	{
		close(fd);
		ft_printf("Declared bot size is not equal actual bot size.\n");
		exit(322);
	}
	close(fd);
	return (0);
}

void	set_start_numbers(unsigned *free_numbers)
{
	int	i;
	
	i = 0;
	while (i < MAX_PLAYERS)
	{
		free_numbers[i] = (unsigned)-(i + 1);
		i++;
	}
}

char		is_valid_number(t_player *players, t_player *current_player)
{
	if (players == 0)
		return (1);
	if (current_player->player_number < (unsigned)-4)
		return (0);
	if (current_player->player_number == players->player_number &&
		current_player != players)
		return (0);
	return (is_valid_number(players->next, current_player));
}

unsigned	get_free_number(unsigned *free_numbers)
{
	int			i;
	unsigned	out;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (free_numbers[i] != 0)
		{
			out = free_numbers[i];
			free_numbers[i] = 0;
			return (out);
		}
		i++;
	}
	too_many_players_err();
	return (0);
}

void		check_players_numbers(t_player *player, char quantity,
									unsigned *free_numbers)
{
	while (player != NULL)
	{
		if (player->player_number < (unsigned)-quantity || player->player_number == 0)
			player->player_number = get_free_number(free_numbers);
		player = player->next;
	}
}

void		set_registry(t_pc *pc, unsigned int num)
{
	if (pc == 0)
		return ;
	pc->registry[0] = num;
	set_registry(pc->next, num + 1);
}

void		set_start_pc_index(t_pc *pc, char quantity, char i)
{

	if (pc->next == 0)
	{
		pc->pc_index = 0;
		return ;
	}
	pc->pc_index = (short)(FIELD_SIZE / quantity * i);
	set_start_pc_index(pc->next, quantity, i - (char)1);
}

void		set_players(t_data_prog *data_prog, int start_arg, int argc, char **argv)
{
	int				fd;
	unsigned		free_numbers[MAX_PLAYERS];
	t_player		*current_player;
	t_player		*new_player;
	t_pc			*new_pc;
	char			quantity_players;
	unsigned int	player_number;

	if (start_arg == argc)
	{
		ft_printf("Huinya kakae-to!!!\n");
		exit(228);
	}
	set_start_numbers(free_numbers);
	current_player = data_prog->player;
	quantity_players = 0;
	while (start_arg < argc)
	{
		if (current_player->player_number != 0)
		{
			new_player = init_player();
			nulling_player_and_gameinfo(new_player, 0);
			new_player->next = current_player;
			current_player = new_player;
			data_prog->player = new_player;
			new_pc = init_pc();
			nulling_pc(new_pc, 0);
			new_pc->pc_number = ++data_prog->pc_number;
			if (data_prog->pc == 0)
				data_prog->pc = new_pc;
			else
			{
				new_pc->next = data_prog->pc;
				data_prog->pc = new_pc;
			}
		}
		if (!ft_strcmp(argv[start_arg], "-n"))
		{
			if (start_arg + 1 == argc)
				exit(ARG_ERR);
			current_player->player_number = (unsigned)-ft_atoi(argv[++start_arg]);
			if (!is_valid_number(data_prog->player, current_player))
				current_player->player_number = get_free_number(free_numbers);
			free_numbers[-(int)current_player->player_number - 1] = 0;
			start_arg++;
		}
		else
			current_player->player_number = get_free_number(free_numbers);
		current_player->file_name = argv[start_arg++];
		quantity_players++;
	}
	check_players_numbers(data_prog->player, quantity_players, free_numbers);
	set_registry(data_prog->pc, (unsigned int)-quantity_players);
	set_start_pc_index(data_prog->pc, quantity_players, (char)(quantity_players - 1));
	player_number = (unsigned)-quantity_players;
	data_prog->first_pc = data_prog->pc;
	while (current_player != NULL)
	{
		if (current_player->player_number == player_number)
		{
			if ((fd = read_header(data_prog->game_info, current_player->header,
								  current_player->file_name,
								  data_prog->pc->pc_index))) {
				close(fd);
				ft_printf("File information error!\n");
				exit(FILE_INFORM_ERR);
			}
			player_number++;
			current_player = data_prog->player;
			data_prog->pc = data_prog->pc->next;
		}
		else
			current_player = current_player->next;
	}
	data_prog->pc = data_prog->first_pc;
}