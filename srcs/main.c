/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:14:00 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/31 17:17:34 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_flag(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'm')
			return (1);
		else
			return (-1);
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_lemin		data;
	int			multipass;

	multipass = 0;
	if ((multipass = check_flag(ac, av)) == -1)
	{
		ft_putstr_fd("Error usage : ./lem_in [-m] < map\n", 2);
		return (-1);
	}
	get_data(&data);
	data.multipass = multipass;
	ft_putchar('\n');
	resolve(&data);
	lemin_exit(&data, NULL, NULL);
	return (0);
}
