/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:12:42 by donghank          #+#    #+#             */
/*   Updated: 2024/12/09 14:12:12 by donghank         ###   ########.fr       */
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
	scene->light_n = 0;
	scene->cone_n = 0;
	count_objs(path, scene);
	init_ambient(scene);
	init_camera(scene);
	init_light(scene);
	init_sphere(scene);
	init_plane(scene);
	init_cylinder(scene);
	init_cone(scene);
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
	int	l_idx;

	l_idx = 0;
	scene->light = malloc(scene->light_n * sizeof(t_light *));
	if (!scene->light)
		handle_error("Fail to dynamic allocatie t_light");
	while (l_idx < scene->light_n)
	{
		scene->light[l_idx] = ft_calloc(1, sizeof(t_light));
		if (!scene->light[l_idx])
			handle_error("Fail to dynamic allocat t_light");
		scene->light[l_idx]->color.r = 0;
		scene->light[l_idx]->color.g = 0;
		scene->light[l_idx]->color.b = 0;
		scene->light[l_idx]->coordinates.x = 0.0;
		scene->light[l_idx]->coordinates.y = 0.0;
		scene->light[l_idx]->coordinates.z = 0.0;
		scene->light[l_idx]->l_brightness = 0.0;
		l_idx++;
	}
}

void	init_indices(t_indices *indices)
{
	indices->cy_idx = 0;
	indices->pl_idx = 0;
	indices->sp_idx = 0;
	indices->l_idx = 0;
	indices->co_idx = 0;
}
