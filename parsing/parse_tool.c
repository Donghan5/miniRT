/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:13:29 by donghank          #+#    #+#             */
/*   Updated: 2024/12/05 23:04:34 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	check the logic once again
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
// 		return (0);
// 	return (1);
// }


/*
	set the number of type information
	@param
		sep: information separated by ft_split (like rgb, coordinate etc...)
		type: the number which correspond (A, C, L, pl, sp, cy)
	@return
		type (1 to 6): success
		0: fail
*/
int	get_type(char *map_info)
{
	char	**sep_info;

	sep_info = ft_split(map_info, ' ');
	if (sep_info == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
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
			scene->sphere_n++;
		else if (ft_strncmp(map_line, "pl", 2) == 0)
			scene->plane_n++;
		else if (ft_strncmp(map_line, "cy", 2) == 0)
			scene->cylinder_n++;
		else if (ft_strncmp(map_line, "L", 1) == 0)
			scene->light_n++;
		free(map_line);
		map_line = get_next_line(fd);
	}
	close(fd);
}
