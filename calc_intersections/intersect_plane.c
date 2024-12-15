/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:51:41 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/10 13:43:40 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intersect_plane(t_ray ray, t_plane *plane)
{
	t_vec3	normal;
	t_vec3	point;
	double	denom;
	double	t;

	normal = vec3_normalize(plane->normal_vector);
	point = plane->coordinates;
	denom = vec3_dot(normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vec3_dot(vec3_sub(point, ray.origin), normal) / denom;
	if (t > EPSILON)
		return (t);
	return (-1.0);
}
