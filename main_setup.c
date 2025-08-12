/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:23:16 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 14:56:40 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_args_and_load_map(int argc, char **argv, t_vars *vars)
{
	if (argc != 2)
		return (ft_printf("Usage: Silklong <map.ber>\n"));
	vars->map = load_map(argv[1]);
	if (!vars->map)
		return (1);
	if (map_gauntlet(vars->map) == 0)
	{
		ft_printf("Error: Invalid Map Layout!\n");
		free_map(vars->map);
		return (1);
	}
	return (0);
}

void	print_boot_message(void)
{
	ft_printf("Welcome to Silklong!\n");
	ft_printf("Hornet seems to have lost her way in search of the release date. \
			Help her collect everything!\n");
}

void	load_idle_sprites(t_vars *vars)
{
	int	w;
	int	h;

	vars->sprites.idle[0] = mlx_xpm_file_to_image(vars->mlx,
			"./assets/idle0.xpm", &w, &h);
	vars->sprites.idle[1] = mlx_xpm_file_to_image(vars->mlx,
			"./assets/idle1.xpm", &w, &h);
	vars->sprites.idle[2] = mlx_xpm_file_to_image(vars->mlx,
			"./assets/idle2.xpm", &w, &h);
	vars->sprites.idle[3] = mlx_xpm_file_to_image(vars->mlx,
			"./assets/idle3.xpm", &w, &h);
	vars->sprites.idle[4] = mlx_xpm_file_to_image(vars->mlx,
			"./assets/idle4.xpm", &w, &h);
}

void	setup_vars(t_vars *vars)
{
	vars->collected = 0;
	vars->moves = 0;
	vars->total_collectibles = count_item(vars->map, 'C');
	vars->state = STATE_IDLE;
	vars->anim_frame = 0;
	vars->collected = 0;
}
