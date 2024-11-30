/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:39:31 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/30 01:08:34 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// have to move to minirt.h
#define PARSE_ERR "Fail to parse"
#define PARSE_RGB_ERR "Fail to parse RGB"
#define COOR_ERR "Fail to coordinate parse"
#define ORI_ERR "Fail to orientation parse"

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}
/*
	check the all case of the empty and comment
	@param
		line: to verify line read by gnl
	@return
		1: success
		0: fail (there's comment or line)
*/
int is_empty_or_comment(char *line)
{
	if (line == NULL || *line == '\0')
		return (1);
	while (*line)
	{
		if (!ft_isspace(*line))
		{
			if (*line == '#')
				return (1);
			return (0);
		}
		line++;
	}
	return (1);
}

/*
	free all allocation of the scene
	@param
		scene: want to deallocation
*/
void free_scene(t_scene *scene)
{
	for (int i = 0; i < scene->plane_n; i++)
		free(scene->plane[i]);
	free(scene->plane);

	for (int i = 0; i < scene->sphere_n; i++)
		free(scene->sphere[i]);
	free(scene->sphere);

	for (int i = 0; i < scene->cylinder_n; i++)
		free(scene->cylinder[i]);
	free(scene->cylinder);
}
/*
	@param
		msg: error msg
*/
void	handle_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/*
	@param
		strs: double array which want to free
*/
void	free_doub_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/*
	to check the name of the map
	@param
		map_name: map name of the av[1]
	@return
		1: success
		0: fail
*/
// int	check_map(char *map_name)
// {
// 	if (ft_strncmp(map_name, ".rt", 2))
// 		return (printf("Invaild map name, verify once again\n"), 0);
// 	return (1);
// }

/*
	check the amount of sp, pl and cy
	@param
		path: path of the map(.rt)
		scene: structure information
		fd: file descriptor of path
*/
void	count_objs(char *path, t_scene *scene)
{
	int		fd;
	char	*map_line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Fail to open map");
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		if (is_empty_or_comment(map_line))
		{
			free(map_line);
			map_line = get_next_line(fd);
			continue ;
		}
		if (ft_strncmp(map_line, "sp", 2) == 0)
			scene->sphere_n++, printf("Count sphere_n: %d\n", scene->sphere_n);
		else if (ft_strncmp(map_line, "pl", 2) == 0)
			scene->plane_n++, printf("Count plane_n: %d\n", scene->plane_n);
		else if (ft_strncmp(map_line, "cy", 2) == 0)
			scene->cylinder_n++, printf("Count cylinder_n: %d\n", scene->cylinder_n);
		free(map_line);
		map_line = get_next_line(fd);
	}
	close(fd);
}

/*
	initailze all element of scene
	have to separate several functions
	@param
		scene: want to init
*/
void	init_scene(char *path, t_scene *scene)
{
	scene->plane_n = 0;
	scene->sphere_n = 0;
	scene->cylinder_n = 0;
	count_objs(path, scene);
	// default scene --> ambient camera and light
	scene->ambient.a_ratio = 0.0;
	scene->ambient.color.r = 0;
	scene->ambient.color.g = 0;
	scene->ambient.color.b = 0;
	scene->camera.c_view = 0.0;
	scene->camera.coordinates.x = 0.0;
	scene->camera.coordinates.y = 0.0;
	scene->camera.coordinates.z = 0.0;
	scene->camera.orientation.x = 0.0;
	scene->camera.orientation.y = 0.0;
	scene->camera.orientation.z = 0.0;
	scene->light.color.r = 0;
	scene->light.color.g = 0;
	scene->light.color.b = 0;
	scene->light.coordinates.x = 0.0;
	scene->light.coordinates.y = 0.0;
	scene->light.coordinates.z = 0.0;
	scene->light.l_brightness = 0.0;

	// sphere part
	int	sp_idx;
	sp_idx = 0;
	scene->sphere = malloc(scene->sphere_n * sizeof(t_sphere *));
	if (!scene->sphere)
		handle_error("Fail dynamic allocate t_sphere scope all");
	while (sp_idx < scene->sphere_n)
	{
		scene->sphere[sp_idx] = ft_calloc(1, sizeof(t_sphere));
		if (!scene->sphere[sp_idx])
			handle_error("Fail dynamic allocate t_sphere scope index");
		scene->sphere[sp_idx]->color.r = 0;
		scene->sphere[sp_idx]->color.g = 0;
		scene->sphere[sp_idx]->color.b = 0;
		scene->sphere[sp_idx]->coordinates.x = 0.0;
		scene->sphere[sp_idx]->coordinates.y = 0.0;
		scene->sphere[sp_idx]->coordinates.z = 0.0;
		scene->sphere[sp_idx]->sp_diameter = 0;
		sp_idx++;
	}

	//plane part
	int	pl_idx;
	pl_idx = 0;
	scene->plane = malloc(scene->plane_n * sizeof(t_plane *));
	if (!scene->plane)
		handle_error("Fail dynamic allocate t_plane");
	while (pl_idx < scene->plane_n)
	{
		scene->plane[pl_idx] = ft_calloc(1, sizeof(t_plane));
		if (!scene->plane[pl_idx])
			handle_error("Fail dynamic allocate t_plane");
		scene->plane[pl_idx]->color.r = 0;
		scene->plane[pl_idx]->color.g = 0;
		scene->plane[pl_idx]->color.b = 0;
		scene->plane[pl_idx]->coordinates.x = 0.0;
		scene->plane[pl_idx]->coordinates.y = 0.0;
		scene->plane[pl_idx]->coordinates.z = 0.0;
		scene->plane[pl_idx]->normal_vector.x = 0.0;
		pl_idx++;
	}

	// cylinder part
	int	cy_idx;
	cy_idx = 0;
	scene->cylinder = malloc(scene->cylinder_n * sizeof(t_cylinder *));
	if (!scene->cylinder)
		handle_error("Fail to dynamic allocate t_cylinder");
	while (cy_idx < scene->cylinder_n)
	{
		scene->cylinder[cy_idx] = ft_calloc(1, sizeof(t_cylinder));
		if (!scene->cylinder[cy_idx])
			handle_error("Fail dynamic allocate t_cylinder");
		scene->cylinder[cy_idx]->axis_vector.y = 0.0;
		scene->cylinder[cy_idx]->axis_vector.z = 0.0;
		scene->cylinder[cy_idx]->color.r = 0;
		scene->cylinder[cy_idx]->color.g = 0;
		scene->cylinder[cy_idx]->color.b = 0;
		scene->cylinder[cy_idx]->coordinates.x = 0.0;
		scene->cylinder[cy_idx]->coordinates.y = 0.0;
		scene->cylinder[cy_idx]->coordinates.z = 0.0;
		scene->cylinder[cy_idx]->cy_diameter = 0.0;
		scene->cylinder[cy_idx]->cy_height = 0.0;
		cy_idx++;
	}
}

/*
	@param
		sep_info:
		type: the number which correspond (A, C, L, pl, sp, cy)
	@return
		type: success
		0: fail
*/
int	get_type(char *map_info)
{
	char	**sep_info;

	sep_info = ft_split(map_info, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	// if (!sep_info || !ft_isalpha(sep_info[0]))
	// 	return (0);
	if ((ft_strncmp("A", sep_info[0], 1) == 0))
		return (1);
	else if ((ft_strncmp("C", sep_info[0], 1) == 0))
		return (2);
	else if ((ft_strncmp("L", sep_info[0], 1) == 0))
		return (3);
	else if ((ft_strncmp("pl", sep_info[0], 2) == 0))
		return (4);
	else if ((ft_strncmp("sp", sep_info[0], 2) == 0))
		return (5);
	else if ((ft_strncmp("cy", sep_info[0], 2) == 0))
		return (6);
	return (0);
}

/*
	stock functions
	using ft_atod convert
	@param
		scene: structure of scene (to print with mlx)
		info_map: information of the map which read by gnl
		sep_info: separate information of info_map
		rgb_infos: RGB information

*/
void	stock_ambient(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	scene->ambient.a_ratio = ft_atod(sep_info[1]);
	rgb_infos = ft_split((char *)sep_info[2], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->ambient.color.r = ft_atoi(rgb_infos[0]);
	scene->ambient.color.g = ft_atoi(rgb_infos[1]);
	scene->ambient.color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock the informations of camera
	@param
		scene: same with stock_ambient
		info_map: same with stock_ambient
		sep_info: same with stock_ambient
		coord_info: coordination information of camera
		orient_info: orientation vector information of camera

*/
void	stock_cam(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->camera.coordinates.x = ft_atod(coord_info[0]);
	scene->camera.coordinates.y = ft_atoi(coord_info[1]);
	scene->camera.coordinates.z = ft_atoi(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	scene->camera.orientation.x = ft_atod(orient_info[0]);
	scene->camera.orientation.y = ft_atod(orient_info[1]);
	scene->camera.orientation.z = ft_atod(orient_info[2]);
	scene->camera.c_view = ft_atod(sep_info[3]);
	free_doub_array(orient_info);
	free_doub_array(sep_info);
}

/*
	stock function
	@param
		scene: same with function stock_ambient
		info_map: same with function stock_ambient
		sep_info: same with function stock_ambient
		coord_info: coordinate information of light
		rgb_infos: RGB information of light

*/
void	stock_light(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->light.coordinates.x = ft_atod(coord_info[0]);
	scene->light.coordinates.y = ft_atod(coord_info[1]);
	scene->light.coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	scene->light.l_brightness = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->light.color.r = ft_atoi(rgb_infos[0]);
	scene->light.color.g = ft_atoi(rgb_infos[1]);
	scene->light.color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock element of the plane
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		coord_info: coordination information of plane
		orient_info: normal vector information of plane
		rgb_infos: RGB information of plane

*/
void	stock_plane(t_scene *scene, char *info_map, int pl_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->plane[pl_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->plane[pl_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->plane[pl_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	scene->plane[pl_idx]->normal_vector.x = ft_atod(orient_info[0]);
	scene->plane[pl_idx]->normal_vector.y = ft_atod(orient_info[1]);
	scene->plane[pl_idx]->normal_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	rgb_infos = ft_split(sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->plane[pl_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->plane[pl_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->plane[pl_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock element of stack
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		sep_info: same with stock_ambient()
		coord_info: coordination information of sphere
		rgb_infos: RGB information of sphere
*/
void	stock_sphere(t_scene *scene, char *info_map, int sp_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->sphere[sp_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->sphere[sp_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->sphere[sp_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	scene->sphere[sp_idx]->sp_diameter = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->sphere[sp_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->sphere[sp_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->sphere[sp_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock information of cylinder
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		sep_info: same with stock_ambient()
		coord_info: coordinate information of cylinder
		orient_info: normal vector information of cylinder
		rgb_infos: RGB information of cylinder
*/
void	stock_cylinder(t_scene *scene, char *info_map, int cy_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->cylinder[cy_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->cylinder[cy_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->cylinder[cy_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	scene->cylinder[cy_idx]->axis_vector.x = ft_atod(orient_info[0]);
	scene->cylinder[cy_idx]->axis_vector.y = ft_atod(orient_info[1]);
	scene->cylinder[cy_idx]->axis_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	scene->cylinder[cy_idx]->cy_diameter = ft_atod(sep_info[3]);
	scene->cylinder[cy_idx]->cy_height = ft_atod(sep_info[4]);
	rgb_infos = ft_split(sep_info[5], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->cylinder[cy_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->cylinder[cy_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->cylinder[cy_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	part of ambient, camera and light
	@param
		type: type of the map_infos[1]
		scene: structure to stock the infos
		info_map: numeric information of the map
*/
void	stock_infos(int type, t_scene *scene, char *info_map)
{
	if (type == 1)
		stock_ambient(scene, info_map);
	else if (type == 2)
		stock_cam(scene, info_map);
	else if (type == 3)
		stock_light(scene, info_map);
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
	int		pl_idx = 0, sp_idx = 0, cy_idx = 0;

	init_scene(path, scene);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Fail to open the file");
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		if (is_empty_or_comment(map_line))
		{
			free(map_line);
			map_line = get_next_line(fd);
			continue ;
		}
		printf("Processing line: %s\n", map_line);
		type = get_type(map_line);
		if (type == 0)
		{
			free(map_line);
			handle_error("Invalid type number");
		}
		if (type == 1 || type == 2 || type == 3)
			stock_infos(type, scene, map_line);
		else if (type == 4)
		{
			if (pl_idx >= scene->plane_n)
				handle_error("Index is out of range in plane");
			stock_plane(scene, map_line, pl_idx++);
		}
		else if (type == 5)
		{
			if (sp_idx >= scene->sphere_n)
				handle_error("Index is out of range in sphere");
			stock_sphere(scene, map_line, sp_idx++);
		}
		else if (type == 6)
		{
			if (cy_idx >= scene->cylinder_n)
				handle_error("Index is out of range in cylinder");
			stock_cylinder(scene, map_line, cy_idx++);
		}
		free(map_line);
		map_line = get_next_line(fd);
	}
	printf("Processing ended. Terminate the parsing session\n");
	close(fd);
}
