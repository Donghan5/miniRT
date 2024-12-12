/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:13:29 by donghank          #+#    #+#             */
/*   Updated: 2024/12/12 12:40:30 by donghank         ###   ########.fr       */
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
// 	if (ft_strncmp(map_name, ".rt", 3))
// 		return (0);
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
		if (!is_empty_or_comment(map_line))
		{
			if (ft_strncmp(map_line, "sp", 2) == 0)
				scene->sphere_n++;
			else if (ft_strncmp(map_line, "pl", 2) == 0)
				scene->plane_n++;
			else if (ft_strncmp(map_line, "cy", 2) == 0)
				scene->cylinder_n++;
			else if (ft_strncmp(map_line, "co", 2) == 0)
				scene->cone_n++;
			else if (ft_strncmp(map_line, "L", 1) == 0 || ft_strncmp(map_line, "l", 1) == 0)
				scene->light_n++;
		}
		free(map_line);
		map_line = get_next_line(fd);
	}
	close(fd);
}
