/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:30:08 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 10:25:22 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_item_row(char *row, char item)
{
	int	x;
	int	cnt;

	x = 0;
	cnt = 0;
	while (row[x])
	{
		if (row[x] == item)
			cnt++;
		x++;
	}
	return (cnt);
}

int	map_row_count(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

int	dup_map_cleanup(char **copy, int i)
{
	while (i-- > 0)
		free(copy[i]);
	free(copy);
	return (0);
}

char	**dup_map(char **map)
{
	int		rows;
	int		i;
	char	**copy;

	rows = map_row_count(map);
	copy = malloc((rows + 1) * sizeof(*copy));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			dup_map_cleanup(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}

void	free_dup(char **m)
{
	int	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}
