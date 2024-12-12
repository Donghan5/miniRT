/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:48:42 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 15:28:05 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intersect_cylinder(t_ray ray, t_cylinder *cyl)
{
	t_vec3	axis = vec3_normalize(cyl->axis_vector);
	t_vec3	center = cyl->coordinates;
	double	radius = cyl->cy_diameter / 2.0;
	double	t_cap = -1.0;
	double	denom = vec3_dot(ray.direction, axis);

	if (fabs(denom) > EPSILON)
	{
		double t = -vec3_dot(vec3_sub(ray.origin, center), axis) / denom;
		if (t > EPSILON)
		{
			t_vec3 p = vec3_add(ray.origin, vec3_mul(ray.direction, t));
			if (vec3_dot(vec3_sub(p, center), vec3_sub(p, center)) <= radius * radius)
				t_cap = t;
		}
		t = vec3_dot(vec3_sub(vec3_add(center, vec3_mul(axis, cyl->cy_height)), ray.origin), axis) / denom;
		if (t > EPSILON && (t_cap < 0 || t < t_cap))
		{
			t_vec3 p = vec3_add(ray.origin, vec3_mul(ray.direction, t));
			if (vec3_dot(vec3_sub(p, vec3_add(center, vec3_mul(axis, cyl->cy_height))), 
						vec3_sub(p, vec3_add(center, vec3_mul(axis, cyl->cy_height)))) <= radius * radius)
				t_cap = t;
		}
	}
	t_vec3 oc = vec3_sub(ray.origin, center);
	double a = vec3_dot(ray.direction, ray.direction) - pow(vec3_dot(ray.direction, axis), 2);
	double b = 2.0 * (vec3_dot(ray.direction, oc) - vec3_dot(ray.direction, axis) * vec3_dot(oc, axis));
	double c = vec3_dot(oc, oc) - pow(vec3_dot(oc, axis), 2) - radius * radius;
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0)
		return (t_cap);
	double t = (-b - sqrt(discriminant)) / (2.0*a);
	if (t < EPSILON)
		return (t_cap);
	t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, t));
	double height = vec3_dot(vec3_sub(hit_point, center), axis);
	if (height < 0 || height > cyl->cy_height)
		return (t_cap);
	if (t_cap < 0 || t < t_cap)
		return (t);
	return (t_cap);
}
