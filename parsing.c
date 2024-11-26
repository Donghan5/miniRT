#include "minirt.h"

// have to move to minirt.h
#define PARSE_ERR "Fail to parse"
#define PARSE_RGB_ERR "Fail to parse RGB"
#define COOR_ERR "Fail to coordinate parse"
#define ORI_ERR "Fail to orientation parse"

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
int	check_map(char *map_name)
{
	if(ft_strcmp(map_name, ".rt"))
		return (printf("Invaild map name, verify once again\n"), 0);
	return (1);
}

int	check_vaild_char(char *info_map)
{
	if ()
}

/*
	@param
		info_map: first element of array info_map
		type: the number which correspond (A, C, L, pl, sp, cy)
	@return
		type: success
		0: fail
*/
int	get_type(char *info_map)
{
	int	type;

	type = 0;
	if (!info_map || !ft_isalpha(info_map))
		return (0);
	if ((ft_strncmp("A", info_map, 1) == 0) && !ft_isalpha(info_map))
		type = 1;
	else if ((ft_strncmp("C", info_map, 1) == 0) && !ft_isalpha(info_map))
		type = 2;
	else if ((ft_strncmp("L", info_map, 1) == 0) && !ft_isalpha(info_map))
		type = 3;
	else if ((ft_strncmp("pl", info_map, 2) == 0) && !ft_isalpha(info_map))
		type = 4;
	else if ((ft_strncmp("sp", info_map, 2) == 0) && !ft_isalpha(info_map))
		type = 5;
	else if ((ft_strncmp("cy", info_map, 2) == 0) && !ft_isalpha(info_map))
		type = 6;
	return (type);
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

	sep_info = ft_split(info_map, " ");
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), (void *)0);
	scene->ambient.a_ratio = ft_atod(sep_info[1]);
	rgb_infos = ft_split(sep_info[2], ",");
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), (void *)0);
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

	sep_info = ft_split(info_map, " ");
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), (void *)0);
	coord_info = ft_split(sep_info[1], ",");
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), (void *)0);
	scene->camera.coordinates.x = ft_atod(coord_info[0]);
	scene->camera.coordinates.y = ft_atoi(coord_info[1]);
	scene->camera.coordinates.z = ft_atoi(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ",");
	if (orient_info == NULL)
		return (printf("%s\n", ORI_ERR), (void *)0);
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

	sep_info = ft_split(info_map, " ");
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), (void *)0);
	coord_info = ft_split(sep_info[1], ",");
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), (void *)0);
	scene->light.coordinates.x = ft_atod(coord_info[0]);
	scene->light.coordinates.y = ft_atod(coord_info[1]);
	scene->light.coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	scene->light.l_brightness = ft_atod(sep_info[2]);
	rgb_infos = ft_split(sep_info[3], ",");
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), (void *)0);
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
void	stock_plane(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ",");
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), (void *)0);
	coord_info = ft_split(sep_info[1], ",");
	(*scene->plane)->coordinates.x = ft_atod(coord_info[0]);
	(*scene->plane)->coordinates.y = ft_atod(coord_info[1]);
	(*scene->plane)->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ",");
	(*scene->plane)->normal_vector.x = ft_atod(orient_info[0]);
	(*scene->plane)->normal_vector.y = ft_atod(orient_info[1]);
	(*scene->plane)->normal_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	rgb_infos = ft_split(sep_info[3], ",");
	(*scene->plane)->color.r = ft_atoi(rgb_infos[0]);
	(*scene->plane)->color.g = ft_atoi(rgb_infos[1]);
	(*scene->plane)->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock element of stack
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
*/
void	stock_sphere(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, " ");
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), (void *)0);
	coord_info = ft_split(sep_info[1], ",");
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), (void *)0);
	(*scene->sphere)->coordinates.x = ft_atod(coord_info[0]);
	(*scene->sphere)->coordinates.y = ft_atod(coord_info[1]);
	(*scene->sphere)->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	(*scene->sphere)->sp_diameter = ft_atod(sep_info[2]);
	rgb_infos = ft_split(sep_info[3], ",");
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), (void *)0);
	(*scene->sphere)->color.r = ft_atoi(rgb_infos[0]);
	(*scene->sphere)->color.g = ft_atoi(rgb_infos[1]);
	(*scene->sphere)->color.b = ft_atoi(rgb_infos[2]);
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
void	stock_cylinder(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, " ");
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), (void *)0);
	coord_info = ft_split(sep_info[1], ",");
	if (coord_info == NULL)
		return (printf("%s\n", COOR_ERR), (void *)0);
	(*scene->cylinder)->coordinates.x = ft_atod(coord_info[0]);
	(*scene->cylinder)->coordinates.y = ft_atod(coord_info[1]);
	(*scene->cylinder)->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ",");
	if (orient_info == NULL)
		return (printf("%s\n", ORI_ERR), (void *)0);
	(*scene->cylinder)->axis_vector.x = ft_atod(orient_info[0]);
	(*scene->cylinder)->axis_vector.y = ft_atod(orient_info[1]);
	(*scene->cylinder)->axis_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	(*scene->cylinder)->cy_diameter = ft_atod(sep_info[3]);
	(*scene->cylinder)->cy_height = ft_atod(sep_info[4]);
	rgb_infos = ft_split(sep_info[5], ",");
	if (rgb_infos == NULL)
		return (printf("%s\n", PARSE_RGB_ERR), (void *)0);
	(*scene->cylinder)->color.r = ft_atoi(rgb_infos[0]);
	(*scene->cylinder)->color.g = ft_atoi(rgb_infos[1]);
	(*scene->cylinder)->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
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
		return (stock_ambient(scene), 1);
	else if (type == 2)
		return (stock_cam(scene), 1);
	else if (type == 3)
		return (stock_light(scene), 1);
	else if (type == 4)
		return (stock_plane(scene), 1);
	else if (type == 5)
		return (stock_sphere(scene), 1);
	else if (type == 6)
		return (stock_cylinder(scene), 1);
	else if (type == 0)
		return (printf("Fail to stock\n"), 0);
	return (0);
}
/*
	think more this function
	idea of this function
	1. parsing the map_line (read by gnl) by separating white-space
	2. verify element (map_infos[0] is char) the other have just , and num
	3. separate the case --> stock each structs
*/
void	parsing_map(int fd, )
{
	char	*map_line;
	char	**map_infos;
	int		i;

	map_line = get_next_line(fd);
	map_infos = ft_split(map_infos, ' ');
	while (map_infos)
	// ...
	free(map_line);
}
