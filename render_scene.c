/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:51:26 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/28 20:31:49 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray get_ray(int x, int y, t_info *info)
{
    t_ray ray;
    t_camera camera = info->scene.camera;

    // Set ray origin
    ray.origin = camera.coordinates;

    // Calculate normalized device coordinates
    double fov = camera.c_view * M_PI / 180.0;
    double px = (2.0 * ((double)x / SCREEN_WIDTH) - 1.0) * tan(fov/2.0);
    double py = -(2.0 * ((double)y / SCREEN_HEIGHT) - 1.0) * tan(fov/2.0) * SCREEN_HEIGHT / SCREEN_WIDTH;

    // Create initial ray direction (looking down +X by default)
    t_vec3 dir = vec3_normalize(vec3(1.0, py, px));

    // Get the target direction from camera orientation
    t_vec3 target = vec3_normalize(camera.orientation);

    // If target direction is valid, rotate the ray
    if (target.x != 0 || target.y != 0 || target.z != 0) {
        // Calculate initial right and up vectors
        t_vec3 world_up = {0, 1, 0};
        t_vec3 right = vec3_normalize(vec3_cross(target, world_up));
        t_vec3 up = vec3_normalize(vec3_cross(right, target));

        // Build camera orientation basis vectors
        t_vec3 forward = target;

        // Transform ray direction from camera space to world space
        ray.direction = vec3_normalize(vec3(
            dir.x * forward.x + dir.y * up.x + dir.z * right.x,
            dir.x * forward.y + dir.y * up.y + dir.z * right.y,
            dir.x * forward.z + dir.y * up.z + dir.z * right.z
        ));
    } else {
        ray.direction = dir;  // Use default direction if no orientation specified
    }

    return ray;
}

static double intersect_sphere(t_ray ray, t_sphere *sphere)
{
    t_vec3 center = sphere->coordinates;
    double radius = sphere->sp_diameter / 2.0;

    t_vec3 oc = vec3_sub(ray.origin, center);
    double a = vec3_dot(ray.direction, ray.direction);
    double b = 2.0 * vec3_dot(oc, ray.direction);
    double c = vec3_dot(oc, oc) - radius * radius;

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return -1.0;
        
    double t = (-b - sqrt(discriminant)) / (2.0*a);
    if (t > EPSILON)
        return t;
    return -1.0;
}

static double intersect_plane(t_ray ray, t_plane *plane)
{
    t_vec3 normal = vec3_normalize(plane->normal_vector);
    t_vec3 point = plane->coordinates;

    double denom = vec3_dot(normal, ray.direction);
    if (fabs(denom) < EPSILON)
        return -1.0;

    t_vec3 p0l0 = vec3_sub(point, ray.origin);
    double t = vec3_dot(p0l0, normal) / denom;

    return t > EPSILON ? t : -1.0;
}

static double intersect_cylinder(t_ray ray, t_cylinder *cyl)
{
    // Convert cylinder direction vector to unit vector
    t_vec3 axis = vec3_normalize(cyl->axis_vector);
    t_vec3 center = cyl->coordinates;
    double radius = cyl->cy_diameter / 2.0;
    
    // Calculate ray-cylinder intersection
    t_vec3 oc = vec3_sub(ray.origin, center);
    
    double a = vec3_dot(ray.direction, ray.direction) - 
               pow(vec3_dot(ray.direction, axis), 2);
    double b = 2.0 * (vec3_dot(ray.direction, oc) - 
               vec3_dot(ray.direction, axis) * vec3_dot(oc, axis));
    double c = vec3_dot(oc, oc) - 
               pow(vec3_dot(oc, axis), 2) - radius * radius;
    
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return -1.0;

    double t = (-b - sqrt(discriminant)) / (2.0*a);
    if (t < EPSILON)
        return -1.0;

    // Check if intersection is within cylinder height
    t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, t));
    t_vec3 hit_height = vec3_sub(hit_point, center);
    double height = vec3_dot(hit_height, axis);
    
    if (height < 0 || height > cyl->cy_height)
        return -1.0;

    return t;
}

static double check_shadow(t_info *info, t_vec3 hit_point, t_vec3 light_pos)
{
    t_ray shadow_ray;
    shadow_ray.origin = hit_point;
    shadow_ray.direction = vec3_normalize(vec3_sub(light_pos, hit_point));

    // Compute distance to light
    t_vec3 to_light = vec3_sub(light_pos, hit_point);
    double dist_to_light = sqrt(vec3_dot(to_light, to_light));
    
    // Check spheres
    for (int i = 0; i < info->scene.sphere_n; i++) {
        if (info->scene.sphere[i]) {
            double t = intersect_sphere(shadow_ray, info->scene.sphere[i]);
            if (t > EPSILON && t < (dist_to_light) && !isEqual(t, dist_to_light)) {
                return 0.0;  // Full shadow
            }
        }
    }

    // Check planes
    for (int i = 0; i < info->scene.plane_n; i++) {
        if (info->scene.plane[i]) {
            double t = intersect_plane(shadow_ray, info->scene.plane[i]);
            if (t > EPSILON && t < (dist_to_light) && !isEqual(t, dist_to_light)) {
                return 0.0;  // Full shadow
            }
        }
    }

    // Check cylinders
    for (int i = 0; i < info->scene.cylinder_n; i++) {
        if (info->scene.cylinder[i]) {
            double t = intersect_cylinder(shadow_ray, info->scene.cylinder[i]);
            if (t > EPSILON && t < (dist_to_light) && !isEqual(t, dist_to_light)) {
                return 0.0;  // Full shadow
            }
        }
    }

    return 1.0;  // No shadow
}

typedef struct s_hit {
    double t;
    int type;  // 0=sphere, 1=plane, 2=cylinder
    int index;
}				t_hit;


static t_color multiply_colors(t_color a, t_color b, double factor) {
    t_color result;
    result.r = (int)(a.r * b.r * factor / 255.0);
    result.g = (int)(a.g * b.g * factor / 255.0);
    result.b = (int)(a.b * b.b * factor / 255.0);
    return result;
}

static t_color add_white_component(t_color base, double factor) {
    t_color result;
    result.r = base.r + (int)(255.0 * factor);
    result.g = base.g + (int)(255.0 * factor);
    result.b = base.b + (int)(255.0 * factor);
    return result;
}

// Helper function to trace a ray and get color
static t_color trace_ray(t_ray ray, t_info *info, int depth) 
{
    t_ambient amb = info->scene.ambient;
    t_light light = info->scene.light;
    t_vec3 light_pos = light.coordinates;
    t_color result = {0, 0, 0};
    t_hit closest = {DBL_MAX, -1, -1};

    // Base case for recursion
    if (depth >= MAX_REFLECTION_DEPTH) {
        return result;
    }

    // Find closest intersection (existing intersection code)
    // Check spheres
    for (int i = 0; i < info->scene.sphere_n; i++) {
        if (info->scene.sphere[i]) {
            double t = intersect_sphere(ray, info->scene.sphere[i]);
            if (t > EPSILON && t < closest.t) {
                closest.t = t;
                closest.type = 0;
                closest.index = i;
            }
        }
    }

    // Check planes
    for (int i = 0; i < info->scene.plane_n; i++) {
        if (info->scene.plane[i]) {
            double t = intersect_plane(ray, info->scene.plane[i]);
            if (t > EPSILON && t < closest.t) {
                closest.t = t;
                closest.type = 1;
                closest.index = i;
            }
        }
    }

    // Check cylinders
    for (int i = 0; i < info->scene.cylinder_n; i++) {
        if (info->scene.cylinder[i]) {
            double t = intersect_cylinder(ray, info->scene.cylinder[i]);
            if (t > EPSILON && t < closest.t) {
                closest.t = t;
                closest.type = 2;
                closest.index = i;
            }
        }
    }

    if (closest.t < DBL_MAX) {
        t_vec3 hit_point = vec3_add(ray.origin, vec3_mul(ray.direction, closest.t));
        t_vec3 normal;
		t_color	base_color;
        double shininess;
        double spec_intensity;
        double diffuse_strength;
        double reflectivity = 0.0;  // Default reflectivity

        // Get object properties (existing code plus reflectivity)
        if (closest.type == 0) {  // Sphere
            t_sphere *sphere = info->scene.sphere[closest.index];
            normal = vec3_normalize(vec3_sub(hit_point, sphere->coordinates));
			base_color.r = sphere->color.r;
			base_color.g = sphere->color.g;
			base_color.b = sphere->color.b;
            shininess = 50.0;
            spec_intensity = 0.4;
            diffuse_strength = 0.6;
            reflectivity = 0.5;  // Make spheres reflective
        }
        else if (closest.type == 1) {  // Plane
            t_plane *plane = info->scene.plane[closest.index];
            normal = vec3_normalize(plane->normal_vector);
            base_color.r = plane->color.r;
			base_color.g = plane->color.g;
			base_color.b = plane->color.b;
            shininess = 1.0;
            spec_intensity = 0.1;
            diffuse_strength = 0.8;
            reflectivity = 0.0;  // Slight reflection for planes
        }
        else {  // Cylinder
        	t_cylinder *cyl = info->scene.cylinder[closest.index];
			t_vec3 axis = vec3_normalize(cyl->axis_vector);
			t_vec3 center = cyl->coordinates;
			t_vec3 cp = vec3_sub(hit_point, center);
			double height = vec3_dot(cp, axis);
			t_vec3 axis_point = vec3_add(center, vec3_mul(axis, height));
			normal = vec3_normalize(vec3_sub(hit_point, axis_point));
			base_color.r = cyl->color.r;
			base_color.g = cyl->color.g;
			base_color.b = cyl->color.b;
			shininess = 30.0;       // Medium shine
			spec_intensity = 0.3;    // Moderate specular
			diffuse_strength = 0.7;  // Good diffuse for cylinder
            reflectivity = 0.5;  // Medium reflection for cylinders
        }

        // Calculate direct lighting (existing lighting code)
        t_vec3 light_dir = vec3_normalize(vec3_sub(light_pos, hit_point));
        t_vec3 view_dir = vec3_normalize(vec3_sub(ray.origin, hit_point));
        t_vec3 reflect_dir = vec3_reflect(vec3_mul(light_dir, -1.0), normal);

        double shadow = check_shadow(info, vec3_add(hit_point, vec3_mul(normal, EPSILON)), light_pos);

        // // Calculate base lighting
        // double ambient = amb.a_ratio;
        // double n_dot_l = fmax(0.0, vec3_dot(normal, light_dir));
        // double diffuse = n_dot_l * diffuse_strength * light.l_brightness * shadow;
        // double spec = pow(fmax(0.0, vec3_dot(view_dir, reflect_dir)), shininess) * spec_intensity * shadow;

        // // Set base color
        // result.r = base_color.r * (ambient + diffuse) + 255.0 * spec;
        // result.g = base_color.g * (ambient + diffuse) + 255.0 * spec;
        // result.b = base_color.b * (ambient + diffuse) + 255.0 * spec;

		// Calculate base lighting
		double ambient = amb.a_ratio;
		double n_dot_l = fmax(0.0, vec3_dot(normal, light_dir));
		double diffuse = n_dot_l * diffuse_strength * light.l_brightness * shadow;
		double spec = pow(fmax(0.0, vec3_dot(view_dir, reflect_dir)), shininess) * spec_intensity * shadow;

		// Calculate ambient component with ambient light color
		t_color ambient_color = multiply_colors(base_color, amb.color, ambient);

		// Calculate diffuse component with light color
		t_color diffuse_color = multiply_colors(base_color, light.color, diffuse);

		// Add specular highlight (white)
		t_color specular_color = add_white_component(
			(t_color){0, 0, 0},  // Start with black
			spec * light.l_brightness
		);

		// Combine all components
		result.r = fmin(255, ambient_color.r + diffuse_color.r + specular_color.r);
		result.g = fmin(255, ambient_color.g + diffuse_color.g + specular_color.g);
		result.b = fmin(255, ambient_color.b + diffuse_color.b + specular_color.b);

        // Add reflection if surface is reflective
        if (reflectivity > 0.0 && depth < MAX_REFLECTION_DEPTH) {
            // Calculate reflection ray
            t_ray reflection_ray;
            reflection_ray.origin = vec3_add(hit_point, vec3_mul(normal, EPSILON));
            reflection_ray.direction = vec3_reflect(ray.direction, normal);

            // Get reflected color
            t_color reflected_color = trace_ray(reflection_ray, info, depth + 1);

            // Blend reflected color with surface color
            result.r = result.r * (1 - reflectivity) + reflected_color.r * reflectivity;
            result.g = result.g * (1 - reflectivity) + reflected_color.g * reflectivity;
            result.b = result.b * (1 - reflectivity) + reflected_color.b * reflectivity;
        }
    }

    return result;
}

//this is not allowed!
long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void put_pixels_to_image(t_info *info, int y, int x, t_color pixel_color)
{
	unsigned int	color;
	int				i;
	int				j;
	int				scale;

	i = 0;
	scale = 1;
    if (info->render_type == LOW_RENDER)
        scale = 8;
	color = (pixel_color.r << 16) | (pixel_color.g << 8) | pixel_color.b;
	while (i < scale && (y + i) < SCREEN_HEIGHT) {
		j = 0;
		while (j < scale && (x + j) < SCREEN_WIDTH) {
			char *dst = info->img->addr + ((y + i) * info->img->line_length +
						(x + j) * (info->img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void render_scene(t_info *info)
{
    int		scale;
	t_color pixel_color;
	int		y;
	int		x;
	t_ray	ray;

    scale = 1;
    if (info->render_type == LOW_RENDER)
        scale = 8;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
            ray = get_ray(x + 0.5, y + 0.5, info);
            pixel_color = trace_ray(ray, info, 0);
            pixel_color.r = (int)fmin(255, fmax(0, pixel_color.r));
            pixel_color.g = (int)fmin(255, fmax(0, pixel_color.g));
            pixel_color.b = (int)fmin(255, fmax(0, pixel_color.b));

			put_pixels_to_image(info, y, x, pixel_color);
			x += scale;
		}
		y += scale;
	}
    if (info->render_type == LOW_RENDER)
        info->render_type = FULL_RENDER;
    else if (info->render_type != NO_RENDER)
        info->render_type = NO_RENDER;
}
