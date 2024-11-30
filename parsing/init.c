/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:12:42 by donghank          #+#    #+#             */
/*   Updated: 2024/11/30 15:46:52 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	initailze all element of scene
	@param
		scene: want to init
*/
void	init_scene(char *path, t_scene *scene)
{
	scene->plane_n = 0;
	scene->sphere_n = 0;
	scene->cylinder_n = 0;
	count_objs(path, scene);
	init_ambient(scene);
	init_camera(scene);
	init_light(scene);
	init_sphere(scene);
	init_plane(scene);
	init_cylinder(scene);
}

/*
	initailze ambient
	@param
		scene: want to init
*/
void	init_ambient(t_scene *scene)
{
	scene->ambient.a_ratio = 0.0;
	scene->ambient.color.r = 0;
	scene->ambient.color.g = 0;
	scene->ambient.color.b = 0;
}

/*
	initailze camera
	@param
		scene: want to init
*/
void	init_camera(t_scene *scene)
{
	scene->camera.c_view = 0.0;
	scene->camera.coordinates.x = 0.0;
	scene->camera.coordinates.y = 0.0;
	scene->camera.coordinates.z = 0.0;
	scene->camera.orientation.x = 0.0;
	scene->camera.orientation.y = 0.0;
	scene->camera.orientation.z = 0.0;
}

/*
	initailze light
	@param
		scene: want to init
*/
void	init_light(t_scene *scene)
{
	scene->light.color.r = 0;
	scene->light.color.g = 0;
	scene->light.color.b = 0;
	scene->light.coordinates.x = 0.0;
	scene->light.coordinates.y = 0.0;
	scene->light.coordinates.z = 0.0;
	scene->light.l_brightness = 0.0;
}

void	init_indices(t_indices *indices)
{
	indices->cy_idx = 0;
	indices->pl_idx = 0;
	indices->sp_idx = 0;
}
