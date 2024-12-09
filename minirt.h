/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:40:16 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/09 15:32:55 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <float.h>
# include <sys/time.h>
# define SCREEN_HEIGHT 500 //1080
# define SCREEN_WIDTH 700 //1920
# define MAX_REFLECTION_DEPTH 3
# define EPSILON 0.0001
# define PARSE_ERR "Fail to parse"
# define PARSE_RGB_ERR "Fail to parse RGB"
# define COOR_ERR "Fail to coordinate parse"
# define ORI_ERR "Fail to orientation parse"

typedef struct s_count
{
	int	a_count;
	int	c_count;
	int	l_count;
	int	sp_count;
	int	pl_count;
	int	cy_count;
	int	co_count;
}		t_count;

typedef struct s_indices
{
	int	sp_idx;
	int	pl_idx;
	int	cy_idx;
	int	l_idx;
	int	co_idx;
}			t_indices;

typedef struct s_vec3 {
    double	x;
    double	y;
    double	z;
}				t_vec3;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray {
    t_vec3	origin;
    t_vec3	direction;
}				t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ambient
{
	double	a_ratio;
	t_color	color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3	coordinates;
	t_vec3	orientation;
	int		c_view;
}				t_camera;

typedef struct s_light
{
	t_vec3	coordinates;
	t_color	color;
	double	l_brightness;
}				t_light;

typedef struct s_sphere
{
	t_vec3	coordinates;
	t_color	color;
	double	sp_diameter;
}				t_sphere;

typedef struct s_plane
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	t_color	color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3	coordinates;
	t_vec3	axis_vector;
	t_color	color;
	double	cy_diameter;
	double	cy_height;
}				t_cylinder;

typedef struct s_cone
{
	t_vec3	coordinates;
	t_vec3	axis_vector;
	t_color	color;
	double	co_diameter;
	double	co_height;
}			t_cone;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_cone		**cone;
	t_light		**light;
	t_sphere	**sphere;
	t_plane		**plane;
	t_cylinder	**cylinder;
	int			cone_n;
	int			sphere_n;
	int			plane_n;
	int			cylinder_n;
	int			light_n;
}				t_scene;

enum e_render_type
{
	NO_RENDER,
	LOW_RENDER,
	FULL_RENDER,
	TOGGLE_OFF,
	TOGGLE_LOW,
	TOGGLE_FULL
};

typedef struct s_key_state
{
	int	forward;
	int	backward;
	int	left;
	int	right;
}				t_key_state;

/*
	Rotating camera modes:
		0 - no rotation
		1 - just rotation
		2 - rotation with direction of movement change
*/
typedef struct s_info
{
	t_data	*img;
	t_scene	scene;
	void	*mlx;
	void	*win;
	int		rotate_camera;
	int		moving_text;
	int		moving_origin_x;
	int		moving_origin_y;
	int		text_x;
	int		text_y;
	int		is_input;
	long	last_scroll_time;
	int		render_type;
	int		toggle_mode;
}				t_info;

t_vec3 vec3(double x, double y, double z);

t_vec3 vec3_add(t_vec3 a, t_vec3 b);

t_vec3 vec3_sub(t_vec3 a, t_vec3 b);

t_vec3 vec3_mul(t_vec3 v, double t);

t_vec3 vec3_hadamard(t_vec3 a, t_vec3 b);

double vec3_dot(t_vec3 a, t_vec3 b);

t_vec3 vec3_normalize(t_vec3 v);

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n);

t_vec3 vec3_cross(t_vec3 a, t_vec3 b);

double	ft_atod(const char *str);

int		isEqual(double a, double b);

int		mouse_clicks(int keycode, int x, int y, t_info *info);
int		mouse_off(int keycode, int x, int y, t_info *info);
int		mouse_moves(int x, int y, t_info *info);

int		key_pressed(int keycode, t_info *info);
int		key_off(int keycode, t_info *info);
void	parse_scene(char *path, t_scene *scene);
int		render_next_frame(t_info *info);
void	exit_error(t_scene scene, int free_index_limit, char *message);
void	ft_putstr_fd(char *s, int fd);

void	render_scene(t_info *info);
int		close_window(t_info *info);
int		render_next_frame(t_info *info);

void	handle_map_check(char *map_line, t_scene *scene, t_indices *indices);

// init.c
void	init_scene(char *path, t_scene *scene);
void	init_ambient(t_scene *scene);
void	init_camera(t_scene *scene);
void	init_light(t_scene *scene);
void	init_indices(t_indices *indices);

// init_shape.c
void	init_sphere(t_scene *scene);
void	init_plane(t_scene *scene);
void	init_cylinder(t_scene *scene);
void	init_cone(t_scene *scene);

void	free_scene(t_scene *scene);
// int		check_map(char *map_name);
void	handle_error(char *msg);
int		ft_isspace(char c);
int		is_empty_or_comment(char *line);
void	free_doub_array(char **strs);

// parse_tool.c
void	count_objs(char *path, t_scene *scene);
int		get_type(char *map_info);
void	valid_form(char **sep_info);

// stock_basic.c
void	stock_ambient(t_scene *scene, char *info_map);
void	stock_cam(t_scene *scene, char *info_map);
void	stock_light(t_scene *scene, char *info_map, int l_idx);
void	stock_infos(int type, t_scene *scene, char *info_map);

//stock_shape.c
void	stock_plane(t_scene *scene, char *info_map, int pl_idx);
void	stock_sphere(t_scene *scene, char *info_map, int sp_idx);
void	stock_cylinder(t_scene *scene, char *info_map, int cy_idx);
void	stock_cone(t_scene *scene, char *info_map, int co_idx);

#endif
