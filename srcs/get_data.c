/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:12:28 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/31 16:43:06 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

bool				do_map(t_lemin *data, char *line, int type, bool flag)
{
	char			**tab;

	if ((tab = ft_split_string(line, ' ', '-')) == NULL)
		lemin_exit(data, NULL, "Malloc Error");
	if (ft_tablen(tab) == 3)
	{
		if (flag == 1)
			lemin_exit(data, tab, "Error: rooms first and tubes next");
		create_room(data, line, type, tab);
	}
	else if (ft_tablen(tab) == 2)
	{
		if (type != 0)
			lemin_exit(data, tab, "Error: room: \"name x y\"");
		create_tube(data, line, tab);
		flag = 1;
	}
	else
		lemin_exit(data, tab
			, "Error: room: \"name x y\" tube: \"name-name\"");
	tab = NULL;
	return (flag);
}

static int			do_comment(t_lemin *data, char *line, bool *flag_start
						, bool *flag_end)
{
	data->color[0] = (unsigned char)255;
	data->color[1] = (unsigned char)255;
	data->color[2] = (unsigned char)255;
	if (ft_strcmp(line, "##start") == 0)
	{
		if ((*flag_start) == 1)
			lemin_exit(data, NULL, "Error: need only 1 start");
		(*flag_start) = 1;
		return (1);
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		if ((*flag_end) == 1)
			lemin_exit(data, NULL, "Error: need only 1 end");
		(*flag_end) = 1;
		return (2);
	}
	if (ft_strstr(line, "##color"))
	{
		take_color(data, line);
		return (3);
	}
	return (0);
}

static void			take_rooms(t_lemin *data, char *line, bool flag
						, bool flag_start)
{
	bool			flag_end;
	t_pos			pos;

	flag_end = 0;
	while ((pos.x = get_next_line(0, &line)))
	{
		if ((pos.y = 0) == 0 && pos.x == -1)
			lemin_exit(data, NULL, "Malloc Error");
		while (line[0] == '#' && pos.x != 0)
		{
			pos.y = do_comment(data, line, &flag_start, &flag_end);
			ft_printf("%s\n", line);
			free(line);
			if ((pos.x = get_next_line(0, &line)) == -1)
				lemin_exit(data, NULL, "Malloc Error");
		}
		if (pos.x == 0)
			break ;
		flag = do_map(data, line, pos.y, flag);
		ft_printf("%s\n", line);
		line = ft_free(line);
	}
	safe_gnl(data, line, pos.y, flag);
	if (flag_start == 0 || flag_end == 0)
		lemin_exit(data, NULL, "Error: need start & end room");
}

static void			nbr_rats(t_lemin *data, char *line)
{
	int				count;
	bool			tmp;
	int				error;

	while (line[0] == '#' && error != 0)
	{
		tmp = 0;
		do_comment(data, line, &tmp, &tmp);
		ft_printf("%s\n", line);
		free(line);
		if ((error = get_next_line(0, &line)) == -1)
			lemin_exit(data, NULL, "Malloc Error");
	}
	count = -1;
	while (line[++count] != '\0')
		if (!(line[count] >= '0' && line[count] <= '9'))
			lemin_exit(data, NULL, "Error: need positive number of rats");
	data->rats_max = ft_atoi(line);
	if (!(data->rats_max > 0 && data->rats_max < INT_MAX))
		lemin_exit(data, NULL, "Error: need positive number of rats (> 0)");
	data->rats_launched = 1;
	data->rats_end = 0;
	ft_printf("%s\n", line);
	free(line);
}

void				get_data(t_lemin *data)
{
	char			*line;

	if (get_next_line(0, &line) == -1)
		lemin_exit(data, NULL, "Malloc Error");
	data->map_size = 0;
	data->map = NULL;
	data->start = NULL;
	data->end = NULL;
	nbr_rats(data, line);
	take_rooms(data, line, 0, 0);
	if (data->start == NULL || data->end == NULL)
		lemin_exit(data, NULL, "Error: need one start & one end");
	if (ft_strcmp(data->start->name, data->end->name) == 0)
		lemin_exit(data, NULL
			, "Error: need start 7 end can\'t be same room");
	test_notube(data);
}
