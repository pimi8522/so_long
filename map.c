/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:29 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 10:59:51 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


/*
 * Load the .ber file into a NULL-terminated array of strings.
 */
char	**load_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		rows;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	map = NULL;
	rows = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map = realloc(map, sizeof(char *) * (rows + 1));
		if (!map)
		{
			perror("Error allocating memory");
			close(fd);
			return (NULL);
		}
		map[rows++] = line;
	}
	map = realloc(map, sizeof(char *) * (rows + 1));
	if (!map)
	{
		perror("Error reallocating memory");
		close(fd);
		return (NULL);
	}
	map[rows] = NULL;
	close(fd);
	return (map);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		free(map[i++]);
	free(map);
}

void	set_player_start(t_vars *vars)
{
	int	y;
	int	x;

	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			if (vars->map[y][x] == 'P')
			{
				vars->pos_x = x * TILE_SIZE;
				vars->pos_y = y * TILE_SIZE;
				vars->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}