/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:17:11 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 17:50:12 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				safe_gnl(t_lemin *data, char *line, int type, bool flag)
{
	if (line != NULL && line[0] != 0)
	{
		if (line[0] != '#')
		{
			flag = do_map(data, line, type, flag);
			free(line);
		}
	}
}

char				*ft_free(char *line)
{
	free(line);
	line = NULL;
	return (line);
}
