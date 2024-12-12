/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:06:23 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/10 13:42:04 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	validate_t(double t, t_ray ray, t_cone *co)
{
	t_vec3 axis = vec3_normalize(co->axis_vector);
	t_vec3 center = co->coordinates;
	double half_height = co->co_height / 2.0;
	if (t < EPSILON)
		return -1.0;
		
	t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, t));
	t_vec3 hp_c = vec3_sub(hit_point, center);
	double height = vec3_dot(hp_c, axis);

	if (fabs(height) > half_height)
		return -1.0;
		
	return t;
}

double intersect_cone(t_ray ray, t_cone *co)
{
    t_vec3 axis = vec3_normalize(co->axis_vector);
    t_vec3 center = co->coordinates;
    
    double radius = co->co_diameter / 2.0;
    double half_height = co->co_height / 2.0;
    double tan_theta = radius / half_height;
    
    // Check intersection with end caps first
    double t_cap = -1.0;
    double denom = vec3_dot(ray.direction, axis);
    
    if (fabs(denom) > EPSILON)
    {
        // Check bottom cap
        t_vec3 bottom_center = vec3_add(center, vec3_mul(axis, -half_height));
        t_vec3 to_bottom = vec3_sub(bottom_center, ray.origin);
        double t_bottom = vec3_dot(to_bottom, axis) / denom;
        
        if (t_bottom > EPSILON)
        {
            t_vec3 p = vec3_add(ray.origin, vec3_mul(ray.direction, t_bottom));
            t_vec3 v = vec3_sub(p, bottom_center);
            double d2 = vec3_dot(v, v) - pow(vec3_dot(v, axis), 2);
            if (d2 <= radius * radius)
                t_cap = t_bottom;
        }

        // Check top cap
        t_vec3 top_center = vec3_add(center, vec3_mul(axis, half_height));
        t_vec3 to_top = vec3_sub(top_center, ray.origin);
        double t_top = vec3_dot(to_top, axis) / denom;
        
        if (t_top > EPSILON && (t_cap < 0 || t_top < t_cap))
        {
            t_vec3 p = vec3_add(ray.origin, vec3_mul(ray.direction, t_top));
            t_vec3 v = vec3_sub(p, top_center);
            double d2 = vec3_dot(v, v) - pow(vec3_dot(v, axis), 2);
            if (d2 <= radius * radius)
                t_cap = t_top;
        }
    }

    // Check cone surface intersection
    t_vec3 oc = vec3_sub(ray.origin, center);
    
    double dot_v_v = vec3_dot(ray.direction, ray.direction);
    double dot_v_a = vec3_dot(ray.direction, axis);
    double dot_p_a = vec3_dot(oc, axis);
    double dot_p_p = vec3_dot(oc, oc);
    
    double a = dot_v_v - (1.0 + tan_theta * tan_theta) * dot_v_a * dot_v_a;
    double b = 2.0 * (vec3_dot(ray.direction, oc) - 
                     (1.0 + tan_theta * tan_theta) * dot_v_a * dot_p_a);
    double c = dot_p_p - (1.0 + tan_theta * tan_theta) * dot_p_a * dot_p_a;
    
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return t_cap;  // Return cap intersection if no cone intersection
    
    double sqrt_disc = sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2.0*a);
    double t2 = (-b + sqrt_disc) / (2.0*a);
    

    
    double t_con = -1.0;
    double t_near = validate_t(t1, ray, co);
    if (t_near > EPSILON)
        t_con = t_near;
    else {
        double t_far = validate_t(t2, ray, co);
        if (t_far > EPSILON)
            t_con = t_far;
    }
    
    // Return nearest valid intersection
    if (t_con > EPSILON && t_cap > EPSILON)
        return fmin(t_con, t_cap);
    else if (t_con > EPSILON)
        return t_con;
    return t_cap;
}
