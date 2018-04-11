/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:11:21 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 16:26:57 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			check_error_room(t_lemin *data, char **tab)
{
	int			count;

	count = -1;
	while (tab[1][++count] != '\0')
		if (!(tab[1][count] >= '0' && tab[1][count] <= '9'))
			lemin_exit(data, tab, "Error: room: \"name x y\"");
	count = -1;
	while (tab[2][++count] != '\0')
		if (!(tab[2][count] >= '0' && tab[2][count] <= '9'))
			lemin_exit(data, tab, "Error: room: \"name x y\"");
	if (tab[0][0] == 'L')
		lemin_exit(data, tab, "Error: room\'s name can\'t start by \'L\'");
}

void			check_error_tube(t_lemin *data, char **tab, char *line)
{
	int			count;
	int			flag;

	if (data->map_size < 2)
		lemin_exit(data, tab, "Error: need more of 2 rooms");
	count = -1;
	flag = 0;
	while (line[++count] != '\0')
		if (line[count] == '-')
			++flag;
	if (flag != 1)
		lemin_exit(data, tab, "Error: tube: name-name (name less \'-\')");
	if (ft_strcmp(tab[0], tab[1]) == 0)
		lemin_exit(data, tab
			, "Error: tube: name-name (names need to be different)");
}

void			check_duplicate_link(t_lemin *data, char **tab, int actual_room
					, int room_linked)
{
	int			count;

	count = -1;
	while (++count < data->map[actual_room]->nlink)
	{
		if (ft_strcmp(data->map[actual_room]->links[count]->name
				, data->map[room_linked]->name) == 0)
			lemin_exit(data, tab, "Error: room already linked");
	}
}

void			test_numbers(t_lemin *data, char **tab)
{
	if (ft_strlen(tab[1]) > 10 || ft_strlen(tab[2]) > 10)
		lemin_exit(data, tab, "Error: room x / y need valid coord");
}

void			test_notube(t_lemin *data)
{
	int			count;
	int			count2;
	int			flag;

	flag = 0;
	count = -1;
	while (++count < data->map_size)
	{
		count2 = -1;
		while (++count2 < data->map[count]->nlink)
			++flag;
	}
	if (flag == 0)
		lemin_exit(data, NULL, "Error: need one tube minimum");
}
