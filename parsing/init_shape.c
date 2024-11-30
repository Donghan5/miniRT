/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:20:51 by donghank          #+#    #+#             */
/*   Updated: 2024/11/30 14:18:16 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	init sphere part
	@param
		scene: the structure which want to init
*/
void	init_sphere(t_scene *scene)
{
	int	sp_idx;

	sp_idx = 0;
	scene->sphere = malloc(scene->sphere_n * sizeof(t_sphere *));
	if (!scene->sphere)
		handle_error("Fail dynamic allocate t_sphere scope all");
	while (sp_idx < scene->sphere_n)
	{
		scene->sphere[sp_idx] = ft_calloc(1, sizeof(t_sphere));
		if (!scene->sphere[sp_idx])
			handle_error("Fail dynamic allocate t_sphere scope index");
		scene->sphere[sp_idx]->color.r = 0;
		scene->sphere[sp_idx]->color.g = 0;
		scene->sphere[sp_idx]->color.b = 0;
		scene->sphere[sp_idx]->coordinates.x = 0.0;
		scene->sphere[sp_idx]->coordinates.y = 0.0;
		scene->sphere[sp_idx]->coordinates.z = 0.0;
		scene->sphere[sp_idx]->sp_diameter = 0;
		sp_idx++;
	}
}

/*
	init plane part
	@param
		scene: the structure which want to init
*/
void	init_plane(t_scene *scene)
{
	int	pl_idx;

	pl_idx = 0;
	scene->plane = malloc(scene->plane_n * sizeof(t_plane *));
	if (!scene->plane)
		handle_error("Fail dynamic allocate t_plane");
	while (pl_idx < scene->plane_n)
	{
		scene->plane[pl_idx] = ft_calloc(1, sizeof(t_plane));
		if (!scene->plane[pl_idx])
			handle_error("Fail dynamic allocate t_plane");
		scene->plane[pl_idx]->color.r = 0;
		scene->plane[pl_idx]->color.g = 0;
		scene->plane[pl_idx]->color.b = 0;
		scene->plane[pl_idx]->coordinates.x = 0.0;
		scene->plane[pl_idx]->coordinates.y = 0.0;
		scene->plane[pl_idx]->coordinates.z = 0.0;
		scene->plane[pl_idx]->normal_vector.x = 0.0;
		pl_idx++;
	}
}

/*
	init cylinder part
	@param
		scene: the structure which want to init
*/
void	init_cylinder(t_scene *scene)
{
	int	cy_idx;

	cy_idx = 0;
	scene->cylinder = malloc(scene->cylinder_n * sizeof(t_cylinder *));
	if (!scene->cylinder)
		handle_error("Fail to dynamic allocate t_cylinder");
	while (cy_idx < scene->cylinder_n)
	{
		scene->cylinder[cy_idx] = ft_calloc(1, sizeof(t_cylinder));
		if (!scene->cylinder[cy_idx])
			handle_error("Fail dynamic allocate t_cylinder");
		scene->cylinder[cy_idx]->axis_vector.y = 0.0;
		scene->cylinder[cy_idx]->axis_vector.z = 0.0;
		scene->cylinder[cy_idx]->color.r = 0;
		scene->cylinder[cy_idx]->color.g = 0;
		scene->cylinder[cy_idx]->color.b = 0;
		scene->cylinder[cy_idx]->coordinates.x = 0.0;
		scene->cylinder[cy_idx]->coordinates.y = 0.0;
		scene->cylinder[cy_idx]->coordinates.z = 0.0;
		scene->cylinder[cy_idx]->cy_diameter = 0.0;
		scene->cylinder[cy_idx]->cy_height = 0.0;
		cy_idx++;
	}
}
