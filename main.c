/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:50:31 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/24 18:20:48 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	int w, h;

	if (argc != 2)
		return (ft_printf("Usage: Silklong <map.ber>\n"));
	vars.map = load_map(argv[1]);
	if (!vars.map)
		return (1);
	if (map_gauntlet(vars.map) == 0)
	{
		ft_printf("Error: Invalid Map Layout!\n");
		free_map(vars.map);
		return (1);
	}
	set_player_start(&vars);
	vars.collected = 0;
	vars.moves = 0;
	vars.total_collectibles = count_item(vars.map, 'C');

	// -- BOOT MESSAGE --
	ft_printf("Welcome to Silklong!\n");
	ft_printf("Hornet seems to have lost her way in search of the release date. Help her collect everything!\n");

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, TILE_SIZE * ft_strlen(vars.map[0]),
			TILE_SIZE * get_map_height(vars.map), "Silklong");

	if (!load_map_textures(&vars))
	{
		ft_printf("Error: Failed loading map textures\n");
		free_map(vars.map);
		return (1);
	}

	vars.state = STATE_IDLE;
	vars.anim_frame = 0;
	vars.collected = 0; // initialize

	/* load idle sprites */
	vars.sprites.idle[0] = mlx_xpm_file_to_image(vars.mlx, "./assets/idle0.xpm",
			&w, &h);
	vars.sprites.idle[1] = mlx_xpm_file_to_image(vars.mlx, "./assets/idle1.xpm",
			&w, &h);
	vars.sprites.idle[2] = mlx_xpm_file_to_image(vars.mlx, "./assets/idle2.xpm",
			&w, &h);
	vars.sprites.idle[3] = mlx_xpm_file_to_image(vars.mlx, "./assets/idle3.xpm",
			&w, &h);
	vars.sprites.idle[4] = mlx_xpm_file_to_image(vars.mlx, "./assets/idle4.xpm",
			&w, &h);

	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, handleKeypress, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, handleKeyRelease, &vars);
	mlx_hook(vars.win, 17, 0, xclose, &vars);
	mlx_loop(vars.mlx);

	free_map(vars.map);
	return (0);
}