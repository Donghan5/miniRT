/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:03:28 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/26 23:04:28 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 vec3(double x, double y, double z)
{
    return (t_vec3){x, y, z};
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec3 vec3_mul(t_vec3 v, double t)
{
    return vec3(v.x * t, v.y * t, v.z * t);
}

t_vec3 vec3_hadamard(t_vec3 a, t_vec3 b)
{
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

double vec3_dot(t_vec3 a, t_vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec3_normalize(t_vec3 v)
{
    double len = sqrt(vec3_dot(v, v));
    if (len < 1e-6)
        return vec3(0, 0, 0);
    return vec3_mul(v, 1.0 / len);
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n)
{
    return vec3_sub(v, vec3_mul(n, 2 * vec3_dot(v, n)));
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}
