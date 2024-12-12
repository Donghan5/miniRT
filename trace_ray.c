/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:25 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/10 14:25:15 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Fills material properties of object hit
*/
void	fill_material(t_hit_material *closest, t_info *info, t_vec3 *normal, t_ray ray)
{
	t_vec3 hit_point;

	hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, closest->t));
	if (closest->type == 0)
	{
		t_sphere *sphere = info->scene.sphere[closest->index];
		*normal = vec3_normalize(vec3_sub(hit_point, sphere->coordinates));
		closest->base_color.r = sphere->color.r;
		closest->base_color.g = sphere->color.g;
		closest->base_color.b = sphere->color.b;
		closest->shininess = 50.0;
		closest->spec_intensity = 0.4;
		closest->diffuse_strength = 0.6;
		closest->reflectivity = 0.5;
	}
	else if (closest->type == 1)
	{
		t_plane *plane = info->scene.plane[closest->index];
		*normal = vec3_normalize(plane->normal_vector);
		closest->base_color.r = plane->color.r;
		closest->base_color.g = plane->color.g;
		closest->base_color.b = plane->color.b;
		closest->shininess = 1.0;
		closest->spec_intensity = 0.1;
		closest->diffuse_strength = 0.8;
		closest->reflectivity = 0.0;
	}
	else if (closest->type == 2)
	{
		t_cylinder *cyl = info->scene.cylinder[closest->index];
		t_vec3 axis = vec3_normalize(cyl->axis_vector);
		t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, closest->t));

		double height = vec3_dot(vec3_sub(hit_point, cyl->coordinates), axis);
		if (fabs(height) < EPSILON || fabs(height - cyl->cy_height) < EPSILON)
			*normal = height < EPSILON ? vec3_mul(axis, -1.0) : axis;
		else
		{
			t_vec3 cp = vec3_sub(hit_point, cyl->coordinates);
			double proj = vec3_dot(cp, axis);
			t_vec3 axis_point = vec3_add(cyl->coordinates, vec3_mul(axis, proj));
			*normal = vec3_normalize(vec3_sub(hit_point, axis_point));
		}
		closest->base_color.r = cyl->color.r;
		closest->base_color.g = cyl->color.g;
		closest->base_color.b = cyl->color.b;
		closest->shininess = 30.0;
		closest->spec_intensity = 0.3;
		closest->diffuse_strength = 0.7;
		closest->reflectivity = 0.5;
	}
	else if (closest->type == 3)
	{
		t_cone *co = info->scene.cone[closest->index];
		t_vec3 axis = vec3_normalize(co->axis_vector);
		t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, closest->t));
		t_vec3 to_hit = vec3_sub(hit_point, co->coordinates);
		double height = vec3_dot(to_hit, axis);

		if (fabs(height - co->co_height/2.0) < EPSILON)
			*normal = axis;
		else if (fabs(height + co->co_height/2.0) < EPSILON)
			*normal = vec3_mul(axis, -1.0);
		else
		{
			t_vec3 cp = vec3_sub(hit_point, co->coordinates);
			double proj = vec3_dot(cp, axis);
			t_vec3 axis_point = vec3_add(co->coordinates, vec3_mul(axis, proj));
			*normal = vec3_normalize(vec3_sub(hit_point, axis_point));
		}
		closest->base_color.r = co->color.r;
		closest->base_color.g = co->color.g;
		closest->base_color.b = co->color.b;
		closest->shininess = 10.0;
		closest->spec_intensity = 0.4;
		closest->diffuse_strength = 0.4;
		closest->reflectivity = 0.0;
	}
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
	return (closest);
}

t_color	trace_ray(t_ray ray, t_info *info, int depth)
{
	t_color			result;
	t_hit_material	closest;
	t_vec3			normal;

	if (depth >= MAX_REFLECTION_DEPTH)
		return ((t_color){0, 0, 0});
	closest = find_closest(ray, info);
	if (closest.t >= DBL_MAX)
		return ((t_color){0, 0, 0});
	closest.hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, closest.t));
	fill_material(&closest, info, &normal, ray);
	result = add_lights(closest, info, normal, ray);
	if (closest.reflectivity > 0.0 && depth < MAX_REFLECTION_DEPTH)
	{
		ray.origin = vec3_add(closest.hit_point, vec3_mul(normal, EPSILON));
		ray.direction = vec3_reflect(ray.direction, normal);
		t_color reflected_color = trace_ray(ray, info, depth + 1);
		result.r = result.r * (1 - closest.reflectivity) + reflected_color.r * closest.reflectivity;
		result.g = result.g * (1 - closest.reflectivity) + reflected_color.g * closest.reflectivity;
		result.b = result.b * (1 - closest.reflectivity) + reflected_color.b * closest.reflectivity;
	}
	return (result);
}
