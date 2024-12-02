/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:01:06 by donghank          #+#    #+#             */
/*   Updated: 2024/12/02 15:02:14 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
	helper function to save the line
	basically, free the map_line and exit the loop
	@param
		map_line: to free
		msg: error message (user input)
*/
static void	handle_error_free(char *map_line, char *msg)
{
	free(map_line);
	handle_error(msg);
}

/*
	helper function of process_parse()
	@param
		type: the type of information
		map_line: information of the map which read by gnl
		scene: information to render
		indices: the structure index
*/
static void	process_parse_obj(int type, char *map_line, t_scene *scene, t_indices *indices)
{
	if (type == 3)
	{
		if (indices->l_idx >= scene->cylinder_n)
			handle_error("Index is out of range in light");
		stock_light(scene, map_line, indices->l_idx++);
	}
	else if (type == 4)
	{
		if (indices->pl_idx >= scene->plane_n)
			handle_error("Index is out of range in plane");
		stock_plane(scene, map_line, indices->pl_idx++);
	}
	else if (type == 5)
	{
		if (indices->sp_idx >= scene->sphere_n)
			handle_error("Index is out of range in sphere");
		stock_sphere(scene, map_line, indices->sp_idx++);
	}
	else if (type == 6)
	{
		if (indices->cy_idx >= scene->cylinder_n)
			handle_error("Index is out of range in cylinder");
		stock_cylinder(scene, map_line, indices->cy_idx++);
	}
}

/*
	process of the stock all element in structure (helper function)
	@param
		map_line: information of the map which read by gnl
		scene: information to render
		indices: structure which contain all index of sp, pl and cy
		type: the type of the information (ambient, cam, light etc)
*/
static void	process_parse(char *map_line, t_scene *scene, t_indices *indices)
{
	int	type;

	type = get_type(map_line);
	if (type == 1 || type == 2)
		stock_infos(type, scene, map_line);
	else if (type >= 3 && type <= 6)
		process_parse_obj(type, map_line, scene, indices);
	else if (type == 0)
		handle_error_free(map_line, "Invalid type!!");
}
/*
	checking validity of the map and contain the process of stock
	@param
		map_line: same as process_parse()
		scene: same as process_parse()
		indices: same as process_parse()
*/
void	handle_map_check(char *map_line, t_scene *scene, t_indices *indices)
{
	if (is_empty_or_comment(map_line))
	{
		// free(map_line); // i'm not sure it free is good place this was the problem
		return ;
	}
	printf("Processing line: %s\n", map_line);
	process_parse(map_line, scene, indices);
}
