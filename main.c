/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:15 by miduarte          #+#    #+#             */
/*   Updated: 2025/06/24 15:57:26 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	xclose(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	exit(0);
}

int handleKeypress(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		xclose(vars);
	return (0);
}
int	ft_render(t_vars *vars)
{
	// Alternate frame every xrenders (adjust for speed)
	static int	count = 0;
	if (++count >= 10000)
	{
		vars->frame = 1 - vars->frame; // swap between 0 and 1
		count = 0;
	}
	vars->img.img = vars->sprites->idle[vars->frame];
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 1920 / 2, 1080 / 2);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_imgs	idleSprites;
	int		img_width;
	int		img_height;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Silklong");
	idleSprites.idle[0] = mlx_xpm_file_to_image(vars.mlx, "./assets/Hornet-idle0000.xpm", &img_width, &img_height);
	idleSprites.idle[1] = mlx_xpm_file_to_image(vars.mlx, "./assets/Hornet-idle0001.xpm", &img_width, &img_height);

	vars.sprites = &idleSprites;
	vars.frame = 0;
	vars.img.img = idleSprites.idle[0];

	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, handleKeypress, &vars); // KeyPress = 2, KeyPressMask = 1L<<0
	mlx_loop(vars.mlx);
	return (0);
}

/*
int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}*/