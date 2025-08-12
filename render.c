/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:35 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 14:52:13 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map_textures(t_vars *vars)
{
	int				w;
	int				h;
	void			*mlx;
	t_map_textures	*t;

	t = &vars->map_textures;
	mlx = vars->mlx;
	ft_bzero(t, sizeof(*t));
	t->wall = mlx_xpm_file_to_image(mlx, "./assets/wall.xpm", &w, &h);
	t->floor = mlx_xpm_file_to_image(mlx, "./assets/floor.xpm", &w, &h);
	t->collectible = mlx_xpm_file_to_image(mlx, "./assets/collectible.xpm", &w,
			&h);
	t->exit = mlx_xpm_file_to_image(mlx, "./assets/exit.xpm", &w, &h);
	t->player = mlx_xpm_file_to_image(mlx, "./assets/floor.xpm", &w, &h);
	if (!t->wall || !t->floor || !t->collectible || !t->exit || !t->player)
	{
		destroy_textures(vars);
		return (0);
	}
	return (1);
}

void	render_tile(t_vars *vars, int x, int y, int player_pos[2])
{
	void	*img;

	if (x == player_pos[0] && y == player_pos[1])
		return ;
	if (vars->map[y][x] == '1')
		img = vars->map_textures.wall;
	else if (vars->map[y][x] == 'C')
		img = vars->map_textures.collectible;
	else if (vars->map[y][x] == 'E')
	{
		if (vars->collected == vars->total_collectibles)
			img = vars->map_textures.exit;
		else
			img = vars->map_textures.floor;
	}
	else
		img = vars->map_textures.floor;
	if (!img)
		img = vars->map_textures.floor;
	if (!img)
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
}

void	render_map(t_vars *vars)
{
	int	x;
	int	y;
	int	player_pos[2];

	player_pos[0] = vars->pos_x / TILE_SIZE;
	player_pos[1] = vars->pos_y / TILE_SIZE;
	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			render_tile(vars, x, y, player_pos);
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
	if (!img)
		img = vars->map_textures.player;
	if (!img)
		img = vars->map_textures.floor;
	if (img)
		mlx_put_image_to_window(vars->mlx, vars->win, img, vars->pos_x,
			vars->pos_y);
	if (++count >= 300)
	{
		vars->anim_frame = (vars->anim_frame + 1) % IDLE_FRAMES;
		count = 0;
	}
	return (0);
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
				return ;
			}
			x++;
		}
		y++;
	}
}
