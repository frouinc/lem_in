/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kda-silv <kda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:12:24 by kda-silv          #+#    #+#             */
/*   Updated: 2017/10/25 16:12:26 by kda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_tablen(char **tab)
{
	int		count;

	count = 0;
	while (tab[count] != NULL)
		++count;
	return (count);
}

static int	word_count(char const *s, char del1, char del2)
{
	int		i;
	int		word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == del1 || s[i] == del2))
			i++;
		if (s[i] == 0)
			break ;
		while (s[i] && s[i] != del1 && s[i] != del2)
			i++;
		word_count++;
	}
	return (word_count);
}

static int	word_count_size(char const *s, int i, char del1, char del2)
{
	int		word_size;

	word_size = 0;
	while (s[i + word_size] && s[i + word_size] != del1
		&& s[i + word_size] != del2)
		word_size++;
	return (word_size);
}

static char	*get_next_word(char const *s, int i, char del1, char del2)
{
	int		j;
	char	*str;

	if ((str = malloc(sizeof(char) * (word_count_size(s, i, del1, del2) + 1)))
		== NULL)
		return (NULL);
	j = 0;
	while (s[i + j] && s[i + j] != del1 && s[i + j] != del2)
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = 0;
	return (str);
}

char		**ft_split_string(char const *s, char c1, char c2)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if ((tab = malloc(sizeof(char*) * (word_count(s, c1, c2) + 1))) == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] && (s[i] == c1 || s[i] == c2))
			i++;
		if (s[i] == 0)
			break ;
		if ((tab[j] = get_next_word(s, i, c1, c2)) == NULL)
			return (NULL);
		while (s[i] && s[i] != c1 && s[i] != c2)
			i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
