/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:53:16 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 14:13:16 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		jump_color(t_lemin *data, char *line)
{
	int			count;

	count = 0;
	while ((line[count] < '0' || line[count] > '9') && line[count] != '\0')
		++count;
	if (line[count] == '\0')
		lemin_exit(data, NULL
			, "Error: ##color nbr nbr nbr (nbr >= 0 & nbr <= 255)");
	if (line[count - 1] == '-')
		lemin_exit(data, NULL
			, "Error: ##color nbr nbr nbr (nbr >= 0 & nbr <= 255)");
	return (count);
}

static void		end_color(t_lemin *data, char *line, int count)
{
	while (line[count] >= '0' && line[count] <= '9')
		++count;
	if (line[count] != '\0')
		lemin_exit(data, NULL
			, "Error: ##color nbr nbr nbr (nbr >= 0 & nbr <= 255)");
}

void			take_color(t_lemin *data, char *line)
{
	int			count;
	int			count2;
	int			tmp;

	count = jump_color(data, line);
	count2 = -1;
	while (++count2 < 3)
	{
		tmp = ft_atoi(&(line[count]));
		if (tmp < 0 || tmp > 255)
			lemin_exit(data, NULL
				, "Error: ##color nbr nbr nbr (nbr >= 0 & nbr <= 255)");
		data->color[count2] = (unsigned char)tmp;
		if (count2 == 2)
			break ;
		while (line[count] != ' ' && line[count] != '\0')
			++count;
		if (line[count] == '\0' || line[count + 1] == '\0'
			|| (line[count + 1] < '0' || line[count + 1] > '9'))
			lemin_exit(data, NULL
				, "Error: ##color nbr nbr nbr (nbr >= 0 & nbr <= 255)");
		++count;
	}
	end_color(data, line, count);
}
