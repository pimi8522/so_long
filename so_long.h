/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:59 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 12:38:42 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include "./ft_printf/ft_printf.h"
#include "./libft/libft.h"
#include "get_next_line.h"


#define IDLE_FRAMES 5
#define TILE_SIZE 100 // pixels per map cell

typedef enum e_state
{
	STATE_IDLE
}					t_state;

typedef struct s_imgs
{
	void			*idle[IDLE_FRAMES];
}					t_imgs;

typedef struct s_map_textures
{
	void			*wall;
	void			*floor;
	void			*collectible;
	void			*exit;
	void			*player;
}					t_map_textures;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	char			**map;
	int pos_x, pos_y;
	t_state			state;
	int				anim_frame;
	int collected;          // how many C we’ve picked up
	int total_collectibles; // how many were on the map
	t_imgs			sprites;
	t_map_textures	map_textures;
	int				moves;
}					t_vars;


//main.c
int	ft_strlen(char *s);

//player.c
void	move_player(t_vars *vars, int dx, int dy);

//render.c
int	load_map_textures(t_vars *vars);
void	render_map(t_vars *vars);
char	**load_map(const char *filename);
int	ft_render(t_vars *vars);

//map.c
void	set_player_start(t_vars *vars);
void	free_map(char **map);


//utils.c
int	xclose(t_vars *vars);
int	get_map_height(char **map);
bool	can_move(t_vars *vars, int dx, int dy);
int	handleKeypress(int keycode, t_vars *vars);
int	handleKeyRelease(int keycode, t_vars *vars);


