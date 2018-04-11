/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:11:25 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 16:05:12 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			check_duplicate(t_lemin *data, t_room *room, int flag)
{
	int				count;

	if (flag == 0)
	{
		count = -1;
		while (++count < data->map_size)
		{
			if (ft_strcmp(room->name, data->map[count]->name) == 0)
				lemin_exit(data, NULL, "Error: same name\'s room");
			if (room->pos.x == data->map[count]->pos.x
				&& room->pos.y == data->map[count]->pos.y)
				lemin_exit(data, NULL, "Error: room with same x / y");
		}
	}
	else
	{
		if (room->type == 1)
			data->start = data->map[data->map_size - 1];
		if (room->type == 2)
			data->end = data->map[data->map_size - 1];
	}
}

static void			fill_map(t_lemin *data, t_room *room)
{
	t_room			**tmp;
	int				count;

	if (data->map == NULL)
	{
		data->map_size = 1;
		if ((data->map = malloc(data->map_size * sizeof(t_room *))) == NULL)
			lemin_exit(data, NULL, "malloc Error");
		data->map[0] = room;
	}
	else
	{
		check_duplicate(data, room, 0);
		if ((tmp = malloc((data->map_size + 1) * sizeof(t_room*))) == NULL)
			lemin_exit(data, NULL, "malloc Error");
		count = -1;
		while (++count < data->map_size)
			tmp[count] = data->map[count];
		free(data->map);
		data->map = tmp;
		data->map[data->map_size] = room;
		++data->map_size;
	}
	check_duplicate(data, room, 1);
}

static void			init_room(t_lemin *data, t_room **room, char **tab
						, int type)
{
	if (((*room)->name = ft_memalloc((ft_strlen(tab[0]) + 1) * sizeof(char)))
		== NULL)
		lemin_exit(data, tab, "malloc Error");
	ft_bzero((*room)->name, ft_strlen(tab[0]));
	if (((*room)->name = ft_strcpy((*room)->name, tab[0])) == NULL)
		lemin_exit(data, tab, "Error");
	test_numbers(data, tab);
	(*room)->pos.x = ft_atoi(tab[1]);
	(*room)->pos.y = ft_atoi(tab[2]);
	(*room)->dtoe = -1;
	(*room)->rat = 0;
	(*room)->nlink = 0;
	(*room)->type = type;
	if (type == 1)
		(*room)->rat = 1;
	(*room)->links = NULL;
	(*room)->color[0] = data->color[0];
	(*room)->color[1] = data->color[1];
	(*room)->color[2] = data->color[2];
}

void				create_room(t_lemin *data, char *line, int type, char **tab)
{
	t_room			*room;

	delete_tab(tab);
	tab = NULL;
	if ((tab = ft_split_string(line, ' ', ' ')) == NULL)
		lemin_exit(data, NULL, "malloc Error");
	check_error_room(data, tab);
	if ((room = malloc(sizeof(t_room))) == NULL)
		lemin_exit(data, tab, "malloc Error");
	init_room(data, &room, tab, type);
	fill_map(data, room);
	delete_tab(tab);
}
