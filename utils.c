/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:49 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 14:44:08 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_height(char **map)
{
	int	rows;

	rows = 0;
	while (map && map[rows])
		rows++;
	return (rows);
}

bool	can_move(t_vars *vars, int dx, int dy)
{
	int	new_px;
	int	new_py;
	int	gx;
	int	gy;

	new_px = vars->pos_x + dx;
	new_py = vars->pos_y + dy;
	gx = new_px / TILE_SIZE;
	gy = new_py / TILE_SIZE;
	if (gy < 0 || gy >= get_map_height(vars->map))
		return (false);
	if (gx < 0 || gx >= ft_strlen(vars->map[0]))
		return (false);
	if (vars->map[gy][gx] == '1')
		return (false);
	return (true);
}

int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		xclose(vars);
	else if ((keycode == XK_a || keycode == XK_A) && can_move(vars, -TILE_SIZE,
			0))
		move_player(vars, -TILE_SIZE, 0);
	else if ((keycode == XK_d || keycode == XK_D) && can_move(vars, TILE_SIZE,
			0))
		move_player(vars, TILE_SIZE, 0);
	else if ((keycode == XK_w || keycode == XK_W) && can_move(vars, 0,
			-TILE_SIZE))
		move_player(vars, 0, -TILE_SIZE);
	else if ((keycode == XK_s || keycode == XK_S) && can_move(vars, 0,
			TILE_SIZE))
		move_player(vars, 0, TILE_SIZE);
	return (0);
}

int	handle_keyrelease(int keycode, t_vars *vars)
{
	if (keycode == XK_a || keycode == XK_A || keycode == XK_d || keycode == XK_D
		|| keycode == XK_w || keycode == XK_W || keycode == XK_s
		|| keycode == XK_S)
		vars->state = STATE_IDLE;
	return (0);
}

// Public helper to destroy map textures (safe to call on partial loads)
void	destroy_textures(t_vars *vars)
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
