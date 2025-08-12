/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:59 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 11:22:28 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include "get_next_line.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define IDLE_FRAMES 5
#define TILE_SIZE 100 // pixels per map cell

typedef enum e_state
{
	STATE_IDLE
}						t_state;

typedef struct s_imgs
{
	void				*idle[IDLE_FRAMES];
}						t_imgs;

typedef struct s_map_textures
{
	void				*wall;
	void				*floor;
	void				*collectible;
	void				*exit;
	void				*player;
}						t_map_textures;

typedef struct s_line_node
{
	char				*line;
	struct s_line_node	*next;
}						t_line_node;

typedef struct s_vars
{
	void				*mlx;
	void				*win;
	char				**map;
	int					pos_x;
	int					pos_y;
	t_state				state;
	int					anim_frame;
	int					collected;
	int					total_collectibles;
	t_imgs				sprites;
	t_map_textures		map_textures;
	int					moves;
}						t_vars;

int						count_item(char **map, char item);
int						map_gauntlet(char **map);
void					move_player(t_vars *vars, int dx, int dy);
int						load_map_textures(t_vars *vars);
void					render_map(t_vars *vars);
char					**load_map(const char *filename);
int						ft_render(t_vars *vars);
void					render_tile(t_vars *vars, int x, int y,
							int player_pos[2]);
void					set_player_start(t_vars *vars);
void					free_map(char **map);
char					**list_to_map_array(t_line_node *head, int rows);
t_line_node				*read_lines_to_list(int fd, int *rows);
t_line_node				*create_line_node(char *line);
void					free_line_list(t_line_node *head);
int						xclose(t_vars *vars);
int						get_map_height(char **map);
bool					can_move(t_vars *vars, int dx, int dy);
int						handle_keypress(int keycode, t_vars *vars);
int						handle_keyrelease(int keycode, t_vars *vars);
int						check_args_and_load_map(int argc, char **argv,
							t_vars *vars);
void					print_boot_message(void);
int						setup_window_and_textures(t_vars *vars);
void					load_idle_sprites(t_vars *vars);
void					setup_vars(t_vars *vars);
void					free_dup(char **m);
void					free_map(char **map);
void					flood_fill(char **m, int y, int x);
int						find_start(char **m, int *out_y, int *out_x);
char					**dup_map(char **map);
int						valid_rectangle(char **map);
int						valid_chars(char **map);
int						valid_char_row(char *row);
int						valid_rectangle_row(char **map, int len);
int						walls_closed(char **map);
int						find_start_row(char *row, int *out_x);
int						wall_row_closed(char *row);
int						wall_sides_closed(char *row);
int						handle_exit(t_vars *vars);
void					move_player_to_new_pos(t_vars *vars, int dx, int dy);
void					handle_collectible(t_vars *vars);
int						get_grid_y(int pos_y, int dy);
int						get_grid_x(int pos_x, int dx);
int						dup_map_cleanup(char **copy, int i);
int						map_row_count(char **map);
int						count_item_row(char *row, char item);
int						handle_cell_interaction(t_vars *vars, char cell, int gx,
							int gy);
