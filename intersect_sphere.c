/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:51:07 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/10 13:51:11 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > EPSILON)
		return (t);
	return (-1.0);
}

double	intersect_sphere(t_ray ray, t_sphere *sphere)
{
	t_vec3	center;
	double	radius;
	t_vec3	oc;

	center = sphere->coordinates;
	radius = sphere->sp_diameter / 2.0;
	oc = vec3_sub(ray.origin, center);
	return (solve_quadratic(vec3_dot(ray.direction, ray.direction),
			2.0 * vec3_dot(oc, ray.direction),
			vec3_dot(oc, oc) - radius * radius));
}
