/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:39:54 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/27 12:20:40 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_info *info)
{
	int	i;

	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_image(info->mlx, info->img->img);
	mlx_destroy_display(info->mlx);
	i = 0;
	if ((info->scene.cylinder_n > 0) && info->scene.cylinder)
	{
		if (info->scene.cylinder[i])
			free(info->scene.cylinder[i]);
		i++;
	}
	if (i)
		free (info->scene.cylinder);
	i = 0;
	if ((info->scene.sphere_n > 0) && info->scene.sphere)
	{
		if (info->scene.sphere[i])
			free(info->scene.sphere[i]);
		i++;
	}
	if (i)
		free (info->scene.sphere);
	i = 0;
	if ((info->scene.plane_n > 0) && info->scene.plane)
	{
		if (info->scene.plane[i])
			free(info->scene.plane[i]);
		i++;
	}
	if (i)
		free (info->scene.plane);
	free(info->mlx);
	exit(0);
	return (0);
}

void	install_hooks(t_info *info)
{
	mlx_hook(info->win, 17, 0, close_window, info);
	mlx_hook(info->win, 2, 1L << 0, key_pressed, info);
	mlx_hook(info->win, 3, 1L << 1, key_off, info);
	mlx_hook(info->win, 4, 1L << 2, mouse_clicks, info);
	mlx_hook(info->win, 5, 1L << 3, mouse_off, info);
	mlx_hook(info->win, 6, 1L << 13, mouse_moves, info);
}

void	info_initializer(t_info *info)
{
	info->moving_map = 0;
	info->rotating_map = 0;
	info->moving_text = 0;
	info->text_x = SCREEN_WIDTH - 300;
	info->text_y = SCREEN_HEIGHT - 250;
	info->is_input = 0;
	info->last_scroll_time = 0;
	info->render_type = FULL_RENDER;
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_info	info;
	t_scene	scene;

	// if (argc != 2)
	// 	exit_error(NULL, 0, "Wrong arguments. Format: ./miniRT \"path_to_rt_scene\"");
	parse_scene(argv[1], &scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	info.img = &img;
	info.mlx = mlx;
	info.win = mlx_win;
	info_initializer(&info);

	info.scene.cylinder_n = 0;
	info.scene.sphere_n = 0;
	info.scene.plane_n = 0;

	// Create room with plane walls
    info.scene.plane_n = 5;  // Floor, ceiling, and 3 walls
    info.scene.plane = malloc(sizeof(t_plane *) * info.scene.plane_n);
    for (int i = 0; i < info.scene.plane_n; i++) {
        info.scene.plane[i] = malloc(sizeof(t_plane));
    }

    // Floor - light gray
    info.scene.plane[0]->coordinates = vec3(0, 0, 0);
    info.scene.plane[0]->normal_vector = vec3(0, 1, 0);
    info.scene.plane[0]->color = (t_color){220, 220, 220};

    // Ceiling - white
    info.scene.plane[1]->coordinates = vec3(0, 20, 0);
    info.scene.plane[1]->normal_vector = vec3(0, -1, 0);
    info.scene.plane[1]->color = (t_color){255, 255, 255};

    // Left wall (white)
    info.scene.plane[2]->coordinates = vec3(-20, 0, 0);
    info.scene.plane[2]->normal_vector = vec3(1, 0, 0);
    info.scene.plane[2]->color = (t_color){255, 255, 255};

    // Back wall (pink)
    info.scene.plane[3]->coordinates = vec3(0, 0, 40);
    info.scene.plane[3]->normal_vector = vec3(0, 0, -1);
    info.scene.plane[3]->color = (t_color){255, 182, 193};

    // Right wall (gray)
    info.scene.plane[4]->coordinates = vec3(20, 0, 0);
    info.scene.plane[4]->normal_vector = vec3(-1, 0, 0);
    info.scene.plane[4]->color = (t_color){200, 200, 200};

    // Create decorative cylinders
    info.scene.cylinder_n = 3;
    info.scene.cylinder = malloc(sizeof(t_cylinder *) * info.scene.cylinder_n);
    for (int i = 0; i < info.scene.cylinder_n; i++) {
        info.scene.cylinder[i] = malloc(sizeof(t_cylinder));
    }

    // Tall thin white cylinder
    info.scene.cylinder[0]->coordinates = vec3(-10, 0, 15);
    info.scene.cylinder[0]->axis_vector = vec3(0, 1, 0);
    info.scene.cylinder[0]->color = (t_color){255, 255, 255};
    info.scene.cylinder[0]->cy_diameter = 4;
    info.scene.cylinder[0]->cy_height = 15;

    // Medium gray cylinder
    info.scene.cylinder[1]->coordinates = vec3(10, 0, 25);
    info.scene.cylinder[1]->axis_vector = vec3(0, 1, 0);
    info.scene.cylinder[1]->color = (t_color){180, 180, 180};
    info.scene.cylinder[1]->cy_diameter = 6;
    info.scene.cylinder[1]->cy_height = 12;

    // Short wide cylinder
    info.scene.cylinder[2]->coordinates = vec3(0, 0, 30);
    info.scene.cylinder[2]->axis_vector = vec3(0, 1, 0);
    info.scene.cylinder[2]->color = (t_color){200, 200, 200};
    info.scene.cylinder[2]->cy_diameter = 8;
    info.scene.cylinder[2]->cy_height = 8;

    // Add spheres
    info.scene.sphere_n = 5;
    info.scene.sphere = malloc((sizeof(t_sphere *)) * info.scene.sphere_n);
    for (int i = 0; i < info.scene.sphere_n; i++) {
        info.scene.sphere[i] = malloc(sizeof(t_sphere));
    }

    // Golden sphere (main feature)
    info.scene.sphere[0]->coordinates = vec3(0, 12, 20);
    info.scene.sphere[0]->color = (t_color){255, 215, 0};
    info.scene.sphere[0]->sp_diameter = 8;

    // White sphere
    info.scene.sphere[1]->coordinates = vec3(-12, 6, 25);
    info.scene.sphere[1]->color = (t_color){255, 255, 255};
    info.scene.sphere[1]->sp_diameter = 6;

    // Silver sphere
    info.scene.sphere[2]->coordinates = vec3(15, 8, 15);
    info.scene.sphere[2]->color = (t_color){192, 192, 192};
    info.scene.sphere[2]->sp_diameter = 5;

    // Small decorative spheres
    info.scene.sphere[3]->coordinates = vec3(-8, 4, 35);
    info.scene.sphere[3]->color = (t_color){200, 200, 255};
    info.scene.sphere[3]->sp_diameter = 4;

    info.scene.sphere[4]->coordinates = vec3(8, 4, 35);
    info.scene.sphere[4]->color = (t_color){255, 200, 200};
    info.scene.sphere[4]->sp_diameter = 4;

    // Lighting setup
    info.scene.ambient.a_ratio = 0.5;
    info.scene.ambient.color = (t_color){255, 255, 255};

    // Main light source
    info.scene.light.coordinates = vec3(0, 15, 0);
    info.scene.light.color = (t_color){255, 255, 255};
    info.scene.light.l_brightness = 1.0;

    // Camera positioned for a good view
    info.scene.camera.coordinates = vec3(0, 10, -15);
	info.scene.camera.orientation = vec3(0, 0, 1);
    info.scene.camera.c_view = 90;

	render_next_frame(&info);
	install_hooks(&info);
	mlx_loop_hook(info.mlx, render_next_frame, &info);
	mlx_loop(info.mlx);
	return (0);
}
