/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:25 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/12 19:39:36 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_closest(t_hit_material *closest, t_info *info, t_ray ray)
{
	int		i;
	double	t;
	int		ii;

	i = 0;
	t = -1.0;
	while (i < info->scene.sphere_n || i < info->scene.plane_n
		|| i < info->scene.cylinder_n || i < info->scene.cone_n)
	{
		ii = 1;
		if (i < info->scene.sphere_n && info->scene.sphere[i])
			t = intersect_sphere(ray, info->scene.sphere[i]);
		if (i < info->scene.plane_n && info->scene.plane[i])
			t = intersect_plane(ray, info->scene.plane[i]);
		if (i < info->scene.cylinder_n && info->scene.cylinder[i])
			t = intersect_cylinder(ray, info->scene.cylinder[i]);
		if (i < info->scene.cone_n && info->scene.cone[i])
			t = intersect_cone(ray, info->scene.cone[i]);
		closest->type = ii - 1;
		closest->index = i;
		i++;
	}
	printf("t = %f, type = %d, index = %d\n", t, closest->type, closest->index);
	if (t > EPSILON)
		return (closest->t = t, 0);
	return (closest->type = -1, closest->index = -1, 0);
}

/*
	Finds closest object hit
*/
t_hit_material	find_closest(t_ray ray, t_info *info)
{
	int				i;
	t_hit_material	closest;
	double			t;

	closest.t = DBL_MAX;
	closest.type = -1;
	closest.index = -1;
	i = 0;
	while (i < info->scene.sphere_n)
	{
		if (info->scene.sphere[i])
		{
			t = intersect_sphere(ray, info->scene.sphere[i]);
			if (t > EPSILON && t < closest.t)
			{
				closest.t = t;
				closest.type = 0;
				closest.index = i;
			}
		}
		i++;
	}
	i = 0;
	while (i < info->scene.plane_n)
	{
		if (info->scene.plane[i])
		{
			t = intersect_plane(ray, info->scene.plane[i]);
			if (t > EPSILON && t < closest.t)
			{
				closest.t = t;
				closest.type = 1;
				closest.index = i;
			}
		}
		i++;
	}
	i = 0;
	while (i < info->scene.cylinder_n)
	{
		if (info->scene.cylinder[i])
		{
			t = intersect_cylinder(ray, info->scene.cylinder[i]);
			if (t > EPSILON && t < closest.t)
			{
				closest.t = t;
				closest.type = 2;
				closest.index = i;
			}
		}
		i++;
	}
	i = 0;
	while (i < info->scene.cone_n)
	{
		if (info->scene.cone[i])
		{
			t = intersect_cone(ray, info->scene.cone[i]);
			if (t > EPSILON && t < closest.t)
			{
				closest.t = t;
				closest.type = 3;
				closest.index = i;
			}
		}
		i++;
	}
	// fill_closest(&closest, info, ray);
	return (closest);
}

t_color	trace_ray(t_ray ray, t_info *info, int depth)
{
	t_color			result;
	t_hit_material	closest;
	t_color			refl;

	if (depth >= MAX_DEPTH)
		return ((t_color){0, 0, 0});
	closest = find_closest(ray, info);
	if (closest.t >= DBL_MAX)
		return ((t_color){0, 0, 0});
	closest.hit_point = vec3_add(ray.origin,
			vec3_mul(ray.direction, closest.t));
	fill_material(&closest, info, ray);
	result = add_lights(closest, info, ray);
	if (!info->is_mirror || closest.reflectivity <= 0.0 || depth >= MAX_DEPTH)
		return (result);
	ray.origin = vec3_add(closest.hit_point, vec3_mul(closest.normal, EPSILON));
	ray.direction = vec3_reflect(ray.direction, closest.normal);
	refl = trace_ray(ray, info, depth + 1);
	result.r = result.r * (1 - closest.reflectivity)
		+ refl.r * closest.reflectivity;
	result.g = result.g * (1 - closest.reflectivity)
		+ refl.g * closest.reflectivity;
	result.b = result.b * (1 - closest.reflectivity)
		+ refl.b * closest.reflectivity;
	return (result);
}
