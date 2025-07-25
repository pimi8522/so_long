/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:49 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 11:01:22 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	xclose(t_vars *vars)
{
	free_map(vars->map);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	exit(0);
}

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
	/* 1) bounds check */
	if (gy < 0 || gy >= get_map_height(vars->map))
		return (false);
	if (gx < 0 || gx >= ft_strlen(vars->map[0]))
		return (false);
	/* 2) wall check */
	if (vars->map[gy][gx] == '1')
		return (false);
	return (true);
}

int	handleKeypress(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		xclose(vars);
	else if (keycode == XK_Left && can_move(vars, -TILE_SIZE, 0))
		move_player(vars, -TILE_SIZE, 0);
	else if (keycode == XK_Right && can_move(vars, TILE_SIZE, 0))
		move_player(vars, TILE_SIZE, 0);
	else if (keycode == XK_Up && can_move(vars, 0, -TILE_SIZE))
		move_player(vars, 0, -TILE_SIZE);
	else if (keycode == XK_Down && can_move(vars, 0, TILE_SIZE))
		move_player(vars, 0, TILE_SIZE);
	

	return (0);
}

int	handleKeyRelease(int keycode, t_vars *vars)
{
	if (keycode == XK_Left || keycode == XK_Right || keycode == XK_Up
		|| keycode == XK_Down)
		vars->state = STATE_IDLE;
	return (0);
}