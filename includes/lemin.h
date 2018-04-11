/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:13:05 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/30 19:29:36 by cfrouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdbool.h>
# include "libft.h"

typedef	struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

/*
** type : 0 = normal; 1 = start; 2 = end
*/

typedef	struct		s_room
{
	char			*name;
	t_pos			pos;
	int				dtoe;
	int				rat;
	int				nlink;
	int				type;
	unsigned char	color[3];
	struct s_room	**links;
}					t_room;

typedef	struct		s_lemin
{
	t_room			**map;
	int				map_size;
	int				rats_max;
	int				rats_launched;
	int				rats_end;
	bool			multipass;
	unsigned char	color[3];
	t_room			*start;
	t_room			*end;
}					t_lemin;

/*
** get_data.c
*/

bool				do_map(t_lemin *data, char *line, int type, bool flag);
void				get_data(t_lemin *data);

/*
** create_room.c
*/

void				create_room(t_lemin *data, char *line, int type
						, char **tab);

/*
** create_tube.c
*/

void				create_tube(t_lemin *data, char *line, char **tab);

/*
** take_color.c
*/

void				take_color(t_lemin *data, char *line);

/*
** ft_split_string.c
*/

char				**ft_split_string(char const *s, char c1, char c2);
int					ft_tablen(char **tab);

/*
** check_error.c
*/
void				check_error_room(t_lemin *data, char **tab);
void				check_error_tube(t_lemin *data, char **tab, char *line);
void				check_duplicate_link(t_lemin *data, char **tab
						, int actual_room, int room_linked);
void				test_numbers(t_lemin *data, char **tab);
void				test_notube(t_lemin *data);

/*
** safe_gnl.c
*/

void				safe_gnl(t_lemin *data, char *line, int type, bool flag);
char				*ft_free(char *line);

/*
** delete.c
*/

void				lemin_exit(t_lemin *data, char **tab, char *str);
void				delete_tab(char **tab);

/*
** resolve.c
*/

int					resolve(t_lemin *data);

#endif
