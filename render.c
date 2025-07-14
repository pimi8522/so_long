/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:35 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 10:54:17 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map_textures(t_vars *vars)
{
	int w, h;
	vars->map_textures.wall = mlx_xpm_file_to_image(vars->mlx,
			"./assets/wall.xpm", &w, &h);
	vars->map_textures.floor = mlx_xpm_file_to_image(vars->mlx,
			"./assets/floor.xpm", &w, &h);
	vars->map_textures.collectible = mlx_xpm_file_to_image(vars->mlx,
			"./assets/collectible.xpm", &w, &h);
	vars->map_textures.exit = mlx_xpm_file_to_image(vars->mlx,
			"./assets/exit.xpm", &w, &h);
	vars->map_textures.player = mlx_xpm_file_to_image(vars->mlx,
			"./assets/floor.xpm", &w, &h);
	if (!vars->map_textures.wall || !vars->map_textures.floor
		|| !vars->map_textures.collectible || !vars->map_textures.exit
		|| !vars->map_textures.player)
		return (0);
	return (1);
}


void	render_map(t_vars *vars)
{
	void	*img;

	int x, y;
	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			img = NULL;
			if (vars->map[y][x] == '1')
				img = vars->map_textures.wall;
			else if (vars->map[y][x] == 'C')
				img = vars->map_textures.collectible;
			else if (vars->map[y][x] == 'E')
				img = vars->map_textures.exit;
			else if (vars->map[y][x] != 'P')
				img = vars->map_textures.floor;
			/* player tile handled separately */
			if (img)
				mlx_put_image_to_window(vars->mlx, vars->win, img, x
					* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

int	ft_render(t_vars *vars)
{
	void		*img;
	static int	count = 0;

	render_map(vars);
	img = vars->sprites.idle[vars->anim_frame];
	if (++count >= 300)
	{
		vars->anim_frame = (vars->anim_frame + 1) % IDLE_FRAMES;
		count = 0;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img, vars->pos_x,
		vars->pos_y);
	return (0);
}