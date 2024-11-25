#include "minirt.h"

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
	else if ((ft_strncmp("cy", info_map, 2) == 0) && !ft_isalpha(info_mapH))
		type = 6;
	return (type);
}

/*
	stock functions
	using ft_atod convert
*/
void	stock_ambient(t_scene *scene);
void	stock_cam(t_scene *scene);
void	stock_light(t_scene *scene);
void	stock_plane(t_scene *scene);
void	stock_sphere(t_scene *scene);
void	stock_cylinder(t_scene *scene);

/*
	@param
		type: type of the map_infos[1]
		scene: structure to stock the infos
	@return
		1: success
		0: fail
*/
void	stock_infos(int type, t_scene *scene)
{
	if (type == 1)
		stock_ambient(scene);
	else if (type == 2)
		stock_cam(scene);
	else if (type == 3)
		stock_light(scene);
	else if (type == 4)
		stock_plane(scene);
	else if (type == 5)
		stock_sphere(scene);
	else if (type == 6)
		stock_cylinder(scene);
	else if (type == 0)

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
