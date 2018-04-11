/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:11:29 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 14:13:19 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		fill_tube2(t_lemin *data, char **tab, int room1, int room2)
{
	t_room		**tmp;
	int			count;

	if (data->map[room2]->links == NULL)
	{
		if ((data->map[room2]->links = malloc(sizeof(t_room *))) == NULL)
			lemin_exit(data, tab, "Malloc Error");
		data->map[room2]->links[0] = data->map[room1];
		++data->map[room2]->nlink;
	}
	else
	{
		check_duplicate_link(data, tab, room2, room1);
		++data->map[room2]->nlink;
		if ((tmp = malloc(data->map[room2]->nlink * sizeof(t_room *))) == NULL)
			lemin_exit(data, NULL, "Malloc Error");
		count = -1;
		while (++count < (data->map[room2]->nlink - 1))
			tmp[count] = data->map[room2]->links[count];
		free(data->map[room2]->links);
		data->map[room2]->links = tmp;
		data->map[room2]->links[data->map[room2]->nlink - 1] = data->map[room1];
	}
}

static void		fill_tube1(t_lemin *data, char **tab, int room1, int room2)
{
	t_room		**tmp;
	int			count;

	if (data->map[room1]->links == NULL)
	{
		if ((data->map[room1]->links = malloc(sizeof(t_room *))) == NULL)
			lemin_exit(data, tab, "Malloc Error");
		data->map[room1]->links[0] = data->map[room2];
		++data->map[room1]->nlink;
	}
	else
	{
		check_duplicate_link(data, tab, room1, room2);
		++data->map[room1]->nlink;
		if ((tmp = malloc(data->map[room1]->nlink * sizeof(t_room *))) == NULL)
			lemin_exit(data, NULL, "Malloc Error");
		count = -1;
		while (++count < (data->map[room1]->nlink - 1))
			tmp[count] = data->map[room1]->links[count];
		free(data->map[room1]->links);
		data->map[room1]->links = tmp;
		data->map[room1]->links[data->map[room1]->nlink - 1] = data->map[room2];
	}
}

void			create_tube(t_lemin *data, char *line, char **tab)
{
	int			count;
	int			room1;
	int			room2;

	check_error_tube(data, tab, line);
	room1 = -1;
	room2 = -1;
	count = -1;
	while (++count < data->map_size)
	{
		if (ft_strcmp(tab[0], data->map[count]->name) == 0)
			room1 = count;
		if (ft_strcmp(tab[1], data->map[count]->name) == 0)
			room2 = count;
	}
	if (room1 == -1 || room2 == -1)
		lemin_exit(data, tab, "Error: tube link room doesn't exist");
	fill_tube1(data, tab, room1, room2);
	fill_tube2(data, tab, room1, room2);
	delete_tab(tab);
}
