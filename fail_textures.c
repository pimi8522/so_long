/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:56:55 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 14:58:11 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	fail_mlx(t_vars *vars)
{
	free_map(vars->map);
	return (1);
}

static int	fail_textures(t_vars *vars)
{
	ft_printf("Error: Failed loading map textures\n");
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	vars->mlx = NULL;
	free_map(vars->map);
	return (1);
}

static int	fail_window(t_vars *vars)
{
	destroy_textures(vars);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	vars->mlx = NULL;
	free_map(vars->map);
	return (1);
}

int	setup_window_and_textures(t_vars *vars)
{
	int	width;
	int	height;

	width = TILE_SIZE * ft_strlen(vars->map[0]);
	height = TILE_SIZE * get_map_height(vars->map);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (fail_mlx(vars));
	if (!load_map_textures(vars))
		return (fail_textures(vars));
	vars->win = mlx_new_window(vars->mlx, width, height, "Silklong");
	if (!vars->win)
		return (fail_window(vars));
	return (0);
}
