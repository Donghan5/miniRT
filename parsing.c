#include "minirt.h"

// have to move to minirt.h
#define PARSE_ERR "Fail to parse"
#define PARSE_RGB_ERR "Fail to parse RGB"
#define COOR_ERR "Fail to coordinate parse"
#define ORI_ERR "Fail to orientation parse"

void	handle_error(char *msg);

/*
	initailze all element of scene
	have to separate several functions
	@param
		scene: want to init
*/
void	init_scene(t_scene *scene)
{
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
	scene->sphere = malloc(sizeof(t_sphere *));
	if (!scene->sphere)
		handle_error("Fail dynamic allocate t_sphere");
	*scene->sphere = malloc(sizeof(t_sphere));
	if (!*scene->sphere)
		handle_error("Fail dynamic allocate t_sphere");
	(*scene->sphere)->color.r = 0;
	(*scene->sphere)->color.g = 0;
	(*scene->sphere)->color.b = 0;
	(*scene->sphere)->coordinates.x = 0.0;
	(*scene->sphere)->coordinates.y = 0.0;
	(*scene->sphere)->coordinates.z = 0.0;
	(*scene->sphere)->sp_diameter = 0;

	//plane part
	scene->plane = malloc(sizeof(t_plane *));
	if (!scene->plane)
		handle_error("Fail dynamic allocate t_plane");
	*scene->plane = malloc(sizeof(t_plane));
	if (!*scene->plane)
		handle_error("Fail dynamic allocate t_plane");
	(*scene->plane)->color.r = 0;
	(*scene->plane)->color.g = 0;
	(*scene->plane)->color.b = 0;
	(*scene->plane)->coordinates.x = 0.0;
	(*scene->plane)->coordinates.y = 0.0;
	(*scene->plane)->coordinates.z = 0.0;
	(*scene->plane)->normal_vector.x = 0.0;

	// cylinder part
	scene->cylinder = malloc(sizeof(t_cylinder *));
	if (!scene->cylinder)
		handle_error("Fail to dynamic allocate t_cylinder");
	*scene->cylinder = malloc(sizeof(t_cylinder));
	if (!*scene->cylinder)
		handle_error("Fail dynamic allocate t_cylinder");
	(*scene->cylinder)->axis_vector.y = 0.0;
	(*scene->cylinder)->axis_vector.z = 0.0;
	(*scene->cylinder)->color.r = 0;
	(*scene->cylinder)->color.g = 0;
	(*scene->cylinder)->color.b = 0;
	(*scene->cylinder)->coordinates.x = 0.0;
	(*scene->cylinder)->coordinates.y = 0.0;
	(*scene->cylinder)->coordinates.z = 0.0;
	(*scene->cylinder)->cy_diameter = 0.0;
	(*scene->cylinder)->cy_height = 0.0;
}

/*
	free all allocation of the scene
	@param
		scene: want to deallocation
*/
void	free_scene(t_scene *scene)
{
	free(scene->sphere);
	free(scene->plane);
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
	@return
		1: success
		0: fail
*/
int	stock_ambient(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	scene->ambient.a_ratio = ft_atod(sep_info[1]);
	rgb_infos = ft_split((char *)sep_info[2], ',');
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), 0);
	scene->ambient.color.r = ft_atoi(rgb_infos[0]);
	scene->ambient.color.g = ft_atoi(rgb_infos[1]);
	scene->ambient.color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
	return (1);
}

/*
	stock the informations of camera
	@param
		scene: same with stock_ambient
		info_map: same with stock_ambient
		sep_info: same with stock_ambient
		coord_info: coordination information of camera
		orient_info: orientation vector information of camera
	@return
		1: success
		0: fail
*/
int	stock_cam(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), 0);
	scene->camera.coordinates.x = ft_atod(coord_info[0]);
	scene->camera.coordinates.y = ft_atoi(coord_info[1]);
	scene->camera.coordinates.z = ft_atoi(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		return (printf("%s\n", ORI_ERR), 0);
	scene->camera.orientation.x = ft_atod(orient_info[0]);
	scene->camera.orientation.y = ft_atod(orient_info[1]);
	scene->camera.orientation.z = ft_atod(orient_info[2]);
	scene->camera.c_view = ft_atod(sep_info[3]);
	free_doub_array(orient_info);
	free_doub_array(sep_info);
	return (1);
}

/*
	stock function
	@param
		scene: same with function stock_ambient
		info_map: same with function stock_ambient
		sep_info: same with function stock_ambient
		coord_info: coordinate information of light
		rgb_infos: RGB information of light
	@return
		1: success
		0: fail
*/
int	stock_light(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), 0);
	scene->light.coordinates.x = ft_atod(coord_info[0]);
	scene->light.coordinates.y = ft_atod(coord_info[1]);
	scene->light.coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	scene->light.l_brightness = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), 0);
	scene->light.color.r = ft_atoi(rgb_infos[0]);
	scene->light.color.g = ft_atoi(rgb_infos[1]);
	scene->light.color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
	return (1);
}

/*
	stock element of the plane
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		coord_info: coordination information of plane
		orient_info: normal vector information of plane
		rgb_infos: RGB information of plane
	@return
		1: success
		0: fail
*/
int	stock_plane(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	coord_info = ft_split(sep_info[1], ',');
	(*scene->plane)->coordinates.x = ft_atod(coord_info[0]);
	(*scene->plane)->coordinates.y = ft_atod(coord_info[1]);
	(*scene->plane)->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ',');
	if (orient_info == NULL)
		return (printf("%s\n", ORI_ERR), 0);
	(*scene->plane)->normal_vector.x = ft_atod(orient_info[0]);
	(*scene->plane)->normal_vector.y = ft_atod(orient_info[1]);
	(*scene->plane)->normal_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	rgb_infos = ft_split(sep_info[3], ',');
	(*scene->plane)->color.r = ft_atoi(rgb_infos[0]);
	(*scene->plane)->color.g = ft_atoi(rgb_infos[1]);
	(*scene->plane)->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
	return (1);
}

/*
	stock element of stack
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		sep_info: same with stock_ambient()
		coord_info: coordination information of sphere
		rgb_infos: RGB information of sphere
	@return
		1: success
		0: fail
*/
int	stock_sphere(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), 0);
	(*scene->sphere)->coordinates.x = ft_atod(coord_info[0]);
	(*scene->sphere)->coordinates.y = ft_atod(coord_info[1]);
	(*scene->sphere)->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	(*scene->sphere)->sp_diameter = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), 0);
	(*scene->sphere)->color.r = ft_atoi(rgb_infos[0]);
	(*scene->sphere)->color.g = ft_atoi(rgb_infos[1]);
	(*scene->sphere)->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
	return (1);
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
	@return
		1: success
		0: fail
*/
int	stock_cylinder(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), 0);
	(*scene->cylinder)->coordinates.x = ft_atod(coord_info[0]);
	(*scene->cylinder)->coordinates.y = ft_atod(coord_info[1]);
	(*scene->cylinder)->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		return (printf("%s\n", ORI_ERR), 0);
	(*scene->cylinder)->axis_vector.x = ft_atod(orient_info[0]);
	(*scene->cylinder)->axis_vector.y = ft_atod(orient_info[1]);
	(*scene->cylinder)->axis_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	(*scene->cylinder)->cy_diameter = ft_atod(sep_info[3]);
	(*scene->cylinder)->cy_height = ft_atod(sep_info[4]);
	rgb_infos = ft_split(sep_info[5], ',');
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), 0);
	(*scene->cylinder)->color.r = ft_atoi(rgb_infos[0]);
	(*scene->cylinder)->color.g = ft_atoi(rgb_infos[1]);
	(*scene->cylinder)->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
	return (1);
}

/*
	@param
		type: type of the map_infos[1]
		scene: structure to stock the infos
		info_map: numeric information of the map
	@return
		1: success
		0: fail
*/
int	stock_infos(int type, t_scene *scene, char *info_map)
{
	if (type == 1)
		return (stock_ambient(scene, info_map), 1);
	else if (type == 2)
		return (stock_cam(scene, info_map), 1);
	else if (type == 3)
		return (stock_light(scene, info_map), 1);
	else if (type == 4)
		return (stock_plane(scene, info_map), 1);
	else if (type == 5)
		return (stock_sphere(scene, info_map), 1);
	else if (type == 6)
		return (stock_cylinder(scene, info_map), 1);
	else
		return (0);
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
	int		i;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Fail to open the file");
	init_scene(scene);
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		printf("Processing line: %s\n", map_line);
		type = get_type(map_line);
		if (type == 0)
		{
			free(map_line);
			handle_error("Invalid type number");
		}
		if (stock_infos(type, scene, map_line) == 0)
		{
			free(map_line);
			handle_error("Failure inside of parsing part");
		}
		free(map_line);
		map_line = get_next_line(fd);
	}
	printf("Processing ended. Terminate the parsing session\n");
	close(fd);
}
