/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:29 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 11:07:49 by miduarte         ###   ########.fr       */
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
		ft_printf("Error opening file");
		return (NULL);
	}
	map = NULL;
	rows = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map = malloc(sizeof(char *) * (rows + 1));
		if (!map)
		{
			ft_printf("Error allocating memory");
			close(fd);
			return (NULL);
		}
		map[rows++] = line;
	}
	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
	{
		ft_printf("Error mallocating memory");
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

