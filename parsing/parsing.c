/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:39:31 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/30 16:31:14 by donghank         ###   ########.fr       */
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
	process of the stock all element in structure
	@param
		map_line: information of the map which read by gnl
		scene: information to render
		indices: structure which contain all index of sp, pl and cy
		type: the type of the information
*/
static void	process_parse(char *map_line, t_scene *scene, t_indices *indices)
{
	int	type;

	type = get_type(map_line);
	if (type == 1 || type == 2 || type == 3)
		stock_infos(type, scene, map_line);
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
static void	handle_map_check(char *map_line, t_scene *scene, t_indices *indices)
{
	if (is_empty_or_comment(map_line))
	{
		// free(map_line); // i'm not sure it free is good place this was the problem
		return ;
	}
	printf("Processing line: %s\n", map_line);
	process_parse(map_line, scene, indices);
}

/*
	to stock the all element in the .rt maps
	@param
		fd: file discriptor of .rt
		scene: structure which want to stock it
*/
static void	do_stock(int fd, t_scene *scene)
{
	int			type;
	char		*map_line;
	t_indices	indices;

	init_indices(&indices);
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		handle_map_check(map_line, scene, &indices);
		free(map_line);
		map_line = get_next_line(fd);
	}
}

/*
	parse and stock all informations
	idea of this function
	1. parsing the map_line (read by gnl) by separating white-space
	2. verify element (map_infos[0] is char) the other have just , and num
	3. separate the case --> stock each structs
	@param
		path: path of the file
		scene: struct information
		map_line: all of information (separate by) in a single line
		type: type of information
		i: index
		fd: file descriptor of path
*/
void	parse_scene(char *path, t_scene *scene)
{
	char	*map_line;
	int		type;
	int		fd;

	init_scene(path, scene);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Fail to open the file");
	do_stock(fd, scene);
	printf("Processing ended. Terminate the parsing session\n");
	close(fd);
}
