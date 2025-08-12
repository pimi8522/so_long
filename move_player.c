/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:51 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 10:36:05 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_vars *vars, int dx, int dy)
{
	int		gx;
	int		gy;
	int		old_gx;
	int		old_gy;
	char	cell;

	gx = get_grid_x(vars->pos_x, dx);
	gy = get_grid_y(vars->pos_y, dy);
	old_gx = vars->pos_x / TILE_SIZE;
	old_gy = vars->pos_y / TILE_SIZE;
	cell = vars->map[gy][gx];
	if (cell == '1')
		return ;
	vars->map[old_gy][old_gx] = '0';
	if (cell == 'C')
		handle_collectible(vars);
	if (cell == 'E')
	{
		if (handle_exit(vars))
			return ;
		vars->map[old_gy][old_gx] = 'P';
		return ;
	}
	move_player_to_new_pos(vars, dx, dy);
}
