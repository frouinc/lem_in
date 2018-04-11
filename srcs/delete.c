/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:12:08 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 15:55:58 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			lemin_exit(t_lemin *data, char **tab, char *str)
{
	int			count;

	if (data->map != NULL)
	{
		count = -1;
		while (++count < data->map_size)
		{
			free(data->map[count]->name);
			free(data->map[count]->links);
			free(data->map[count]);
		}
		free(data->map);
	}
	if (tab != NULL)
	{
		delete_tab(tab);
		tab = NULL;
	}
	if (str)
		ft_putendl(str);
	exit(EXIT_FAILURE);
}

void			delete_tab(char **tab)
{
	int			count;

	count = -1;
	while (tab[++count] != NULL)
		free(tab[count]);
	free(tab);
}
