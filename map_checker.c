/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:30:08 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 13:05:35 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Count all 'C' in the map */
int	count_item(char **map, char item)
{
	int y, x, cnt;
	y = 0, x = 0, cnt = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == item)
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}
//count_item(vars.map, 'C');

int map_gauntlet (char **map)
{
	if (count_item(map, 'P') != 1)
		return (0);
	else if (count_item(map, 'E') != 1)
		return (0);
	else if (count_item(map, 'C') <= 0)
		return (0);
	return (1);
}
