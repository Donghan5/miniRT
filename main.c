/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:39:54 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 15:27:59 by donghank         ###   ########.fr       */
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
	while ((i < info->scene.cylinder_n) && info->scene.cylinder && info->scene.cylinder[i])
		free(info->scene.cylinder[i++]);
	if (i)
		free (info->scene.cylinder);
	i = 0;
	while ((i < info->scene.sphere_n) && info->scene.sphere && info->scene.sphere[i])
		free(info->scene.sphere[i++]);
	if (i)
		free (info->scene.sphere);
	i = 0;
	while ((i < info->scene.plane_n) && info->scene.plane && info->scene.plane[i])
		free(info->scene.plane[i++]);
	if (i)
		free (info->scene.plane);
	i = 0;
	while ((i < info->scene.light_n) && info->scene.light && info->scene.light[i])
		free(info->scene.light[i++]);
	if (i)
		free (info->scene.light);
	return (free(info->mlx), exit (0), 0);
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
	info->rotate_camera = 0;
	info->moving_text = 0;
	info->text_x = SCREEN_WIDTH - 300;
	info->text_y = SCREEN_HEIGHT - 250;
	info->is_input = 0;
	info->last_scroll_time = 0;
	info->render_type = FULL_RENDER;
	info->toggle_mode = TOGGLE_OFF;
}

#include <stdio.h>
void print_color(t_color color, const char *prefix) {
    printf("%s: R:%d G:%d B:%d\n", prefix, color.r, color.g, color.b);
}

void print_vector(t_vec3 vec, const char *prefix) {
    printf("%s: x:%f y:%f z:%f\n", prefix, vec.x, vec.y, vec.z);
}

void print_scene_info(t_scene *scene) {
    // Print Ambient Light info
    printf("\n=== Ambient Light ===\n");
    printf("Ratio: %f\n", scene->ambient.a_ratio);
    print_color(scene->ambient.color, "Color");

    // Print Camera info
    printf("\n=== Camera ===\n");
    print_vector(scene->camera.coordinates, "Position");
    print_vector(scene->camera.orientation, "Orientation");
    printf("Field of View: %d\n", scene->camera.c_view);

    // Print Light info
    printf("\n=== Light ===\n");
	for (int i = 0; i < scene->light_n; i++) {
		print_vector(scene->light[i]->coordinates, "Position(light)");
		print_color(scene->light[i]->color, "Color(light)");
		printf("Brightness: %f\n", scene->light[i]->l_brightness);
	}

    // Print Sphere info
    printf("\n=== Spheres (%d) ===\n", scene->sphere_n);
    for (int i = 0; i < scene->sphere_n; i++) {
        if (scene->sphere[i]) {
            printf("\nSphere %d:\n", i + 1);
            print_vector(scene->sphere[i]->coordinates, "Position");
            print_color(scene->sphere[i]->color, "Color");
            printf("Diameter: %f\n", scene->sphere[i]->sp_diameter);
        }
    }

    // Print Plane info
    printf("\n=== Planes (%d) ===\n", scene->plane_n);
    for (int i = 0; i < scene->plane_n; i++) {
        if (scene->plane[i]) {
            printf("\nPlane %d:\n", i + 1);
            print_vector(scene->plane[i]->coordinates, "Position");
            print_vector(scene->plane[i]->normal_vector, "Normal");
            print_color(scene->plane[i]->color, "Color");
        }
    }

    // Print Cylinder info
    printf("\n=== Cylinders (%d) ===\n", scene->cylinder_n);
    for (int i = 0; i < scene->cylinder_n; i++) {
        if (scene->cylinder[i]) {
            printf("\nCylinder %d:\n", i + 1);
            print_vector(scene->cylinder[i]->coordinates, "Position");
            print_vector(scene->cylinder[i]->axis_vector, "Axis");
            print_color(scene->cylinder[i]->color, "Color");
            printf("Diameter: %f\n", scene->cylinder[i]->cy_diameter);
            printf("Height: %f\n", scene->cylinder[i]->cy_height);
        }
    }
    printf("\n");
}
// int	main(int argc, char **argv)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;
// 	t_info	info;

// 	if (argc != 2)
// 		exit_error(info.scene, 0, "Wrong arguments. Format: ./miniRT \"path_to_rt_scene\"");
// 	// if (!check_map(argv[1]))
// 	// 	handle_error("Invaild map name, verify once again");
// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
// 	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	img.addr = mlx_get_data_addr(img.img,
// 			&img.bits_per_pixel, &img.line_length, &img.endian);
// 	info.img = &img;
// 	info.mlx = mlx;
// 	info.win = mlx_win;
// 	info_initializer(&info);
// 	parse_scene(argv[1], &info.scene);
// 	print_scene_info(&info.scene);

// 	render_next_frame(&info);
// 	install_hooks(&info);
// 	mlx_loop_hook(info.mlx, render_next_frame, &info);
// 	mlx_loop(info.mlx);
// 	// free_scene(&info.scene);
// 	return (0);
// }

int    main(int argc, char **argv)
{
    void    *mlx;
    void    *mlx_win;
    t_data    img;
    t_info    info;

    if (argc != 2)
        exit_error(info.scene, 0, "Wrong arguments. Format: ./miniRT ""path_to_rt_scene""");
    // if (!check_map(argv[1]))
    //     handle_error("Invaild map name, verify once again");
    parse_scene(argv[1], &info.scene);
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
    img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    img.addr = mlx_get_data_addr(img.img,
            &img.bits_per_pixel, &img.line_length, &img.endian);
    info.img = &img;
    info.mlx = mlx;
    info.win = mlx_win;
    info_initializer(&info);
    // print_scene_info(&info.scene);

    // render_next_frame(&info);
    // install_hooks(&info);
    // mlx_loop_hook(info.mlx, render_next_frame, &info);
    // mlx_loop(info.mlx);

    printf("Passed rendering\n");

	free_just_scene(&info.scene);
    mlx_destroy_window(info.mlx, info.win);
    mlx_destroy_image(info.mlx, info.img->img);
    mlx_destroy_display(info.mlx);


    free(info.mlx);
    exit(0);
    return (0);
}
