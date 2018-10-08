/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_players_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:34:51 by achernys          #+#    #+#             */
/*   Updated: 2018/10/03 21:24:44 by achernys         ###   ########.fr       */
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

void	copy_field(t_game_info *game_info, unsigned char *field, int field_size,
				   short start_position)
{
	int				i;

	i = 0;
	while (i < field_size)
	{
		game_info->field[start_position++].value = field[i];
		i++;
	}
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
	if (read(fd, buf, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (fd);
	ft_strcpy(header->prog_name, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (fd);
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
	copy_field(game_info, buf, header->prog_size, start_position);
	close(fd);
	return (0);
}

void		set_start_numbers(unsigned *free_numbers)
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
		if ((int)player->player_number > (int)quantity)
			player->player_number = get_free_number(free_numbers);
		player = player->next;
	}
}

void		set_registry(t_player *player)
{
	if (player == 0)
		return ;
	player->registry[0] = player->player_number;
	set_registry(player->next);
}

void		set_start_pc_index(t_player *player, char quantity)
{
	short	start_index;

	start_index = 0;
	while (player != NULL)
	{
		player->pc->pc_index = start_index;
		start_index += FIELD_SIZE / quantity;
		player = player->next;
	}
}

void		set_players(t_data_prog *data_prog, int start_arg, int argc, char **argv)
{
	int			fd;
	unsigned	free_numbers[MAX_PLAYERS];
	t_player	*current_player;
	t_player	*new_player;
	char		quantity_players;
	int			file_names_number[4];
	char		quantity_files;

	set_start_numbers(free_numbers);
	current_player = data_prog->player;
	quantity_players = 0;
	quantity_files = 0;
	while (start_arg < argc)
	{
		if (current_player->player_number != 0)
		{
			new_player = init_player();
			nulling_player_and_gameinfo(new_player, 0);
			new_player->next = current_player;
			data_prog->player = new_player;
			current_player = new_player;
		}
		if (!ft_strcmp(argv[start_arg], "-n"))
		{
			if (start_arg + 1 == argc)
				exit(ARG_ERR);
			current_player->player_number = (unsigned)ft_atoi(argv[++start_arg]);
			if (!is_valid_number(data_prog->player, current_player))
				current_player->player_number = get_free_number(free_numbers);
			start_arg++;
		}
		else
			current_player->player_number = get_free_number(free_numbers);
		file_names_number[quantity_files++] = start_arg++;
		quantity_players++;
	}
	check_players_numbers(data_prog->player, quantity_players, free_numbers);
	set_registry(data_prog->player);
	set_start_pc_index(data_prog->player, quantity_players);
	current_player = data_prog->player;
	quantity_files = 0;
	while (current_player != 0)
	{
		if ((fd = read_header(data_prog->game_info, current_player->header,
							  argv[file_names_number[quantity_files]],
							  current_player->pc->pc_index))) {
			close(fd);
			exit(FILE_INFORM_ERR);
		}
		quantity_files++;
		current_player = current_player->next;
	}
}