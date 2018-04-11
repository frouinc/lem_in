/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrouin <cfrouin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 15:35:17 by cfrouin           #+#    #+#             */
/*   Updated: 2017/10/31 17:17:20 by cfrouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			get_length(t_lemin *data, t_room *room, int l)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (l <= room->dtoe || room->dtoe == -1)
	{
		room->dtoe = l;
		while (i < room->nlink)
		{
			if (((data->multipass == 0) ? room->links[i]->dtoe == -1 : 1) == 1
			&& get_length(data, room->links[i], l + 1) == 1)
				flag++;
			i++;
		}
		if (flag == i && room->type != 1)
		{
			if (data->multipass == 0)
				room->dtoe = -1;
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

void		sort_map(t_room **map, int map_size)
{
	int		i;
	int		flag;
	t_room	*tmp;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < map_size - 1)
		{
			if (map[i]->dtoe > map[i + 1]->dtoe
				|| (map[i]->dtoe == map[i + 1]->dtoe && map[i]->type == 1))
			{
				tmp = map[i];
				map[i] = map[i + 1];
				map[i + 1] = tmp;
				flag = 1;
			}
			i++;
		}
	}
}

void		move_rat(t_lemin *data, int id)
{
	int		i;
	int		x;
	t_room	*map;
	t_room	*mapto;

	map = data->map[id];
	i = -1;
	x = 0;
	while (++i < map->nlink)
	{
		mapto = map->links[i];
		if (mapto->dtoe != -1 && map->dtoe > mapto->dtoe - x && map->rat != 0
			&& ((mapto->type != 2 && mapto->rat == 0) || mapto->type == 2))
		{
			mapto->rat = map->rat;
			ft_printf("L%d-%s ", mapto->rat, mapto->name);
			map->rat = 0;
			x++;
			if (map->type == 1 && ++data->rats_launched <= data->rats_max)
				map->rat = data->rats_launched;
			if (mapto->type == 2 && ++data->rats_end)
				return ;
		}
	}
}

int			solve(t_lemin *data)
{
	int		i;

	while (data->rats_end < data->rats_max)
	{
		i = 0;
		while (i < data->map_size)
		{
			if (data->map[i]->dtoe > 0 && data->map[i]->rat > 0)
			{
				if (data->map[i]->type == 1
					&& data->rats_launched > data->rats_max)
					;
				else
					move_rat(data, i);
			}
			i++;
		}
		ft_printf("\n");
	}
	return (1);
}

int			resolve(t_lemin *data)
{
	int		i;

	i = 0;
	get_length(data, data->end, 0);
	if (data->start->dtoe == -1)
		lemin_exit(data, NULL, "No path from start to exit found.");
	sort_map(data->map, data->map_size);
	while (i < data->map_size)
	{
		sort_map(data->map[i]->links, data->map[i]->nlink);
		i++;
	}
	solve(data);
	return (1);
}
