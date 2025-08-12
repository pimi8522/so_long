/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:39:03 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 14:32:35 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**load_map(const char *filename)
{
	int			fd;
	int			len;
	int			rows;
	t_line_node	*head;
	char		**map;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
	{
		ft_printf("Error: non .ber file attempted to be read!\n");
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	head = read_lines_to_list(fd, &rows);
	close(fd);
	if (!head)
		return (NULL);
	map = list_to_map_array(head, rows);
	if (!map)
		free_line_list(head);
	return (map);
}

static void	destroy_idle_sprites(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < IDLE_FRAMES)
	{
		if (vars->sprites.idle[i])
			mlx_destroy_image(vars->mlx, vars->sprites.idle[i]);
		i++;
	}
}

static void	destroy_map_textures(t_vars *vars)
{
	if (vars->map_textures.wall)
		mlx_destroy_image(vars->mlx, vars->map_textures.wall);
	if (vars->map_textures.floor)
		mlx_destroy_image(vars->mlx, vars->map_textures.floor);
	if (vars->map_textures.collectible)
		mlx_destroy_image(vars->mlx, vars->map_textures.collectible);
	if (vars->map_textures.exit)
		mlx_destroy_image(vars->mlx, vars->map_textures.exit);
	if (vars->map_textures.player)
		mlx_destroy_image(vars->mlx, vars->map_textures.player);
}

static void	destroy_window_and_display(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}

int	xclose(t_vars *vars)
{
	destroy_idle_sprites(vars);
	destroy_map_textures(vars);
	destroy_window_and_display(vars);
	if (vars->map)
		free_map(vars->map);
	exit(0);
}
