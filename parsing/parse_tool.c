/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:13:29 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 23:13:26 by donghank         ###   ########.fr       */
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
	to update the object count
	@param
		map_line: information of the map
		scene: to render
		ambient: to check the number of A
		camera: to check the number of C
		capital_light: to check the number of L
*/
static t_bool	update_count(char *map_line, t_scene *scene)
{
	static int	ambient;
	static int	camera;
	static int	capital_light;

	if (ft_strncmp(map_line, "sp", 2) == 0)
		scene->sphere_n++;
	else if (ft_strncmp(map_line, "pl", 2) == 0)
		scene->plane_n++;
	else if (ft_strncmp(map_line, "cy", 2) == 0)
		scene->cylinder_n++;
	else if (ft_strncmp(map_line, "co", 2) == 0)
		scene->cone_n++;
	else if (ft_strncmp(map_line, "L", 1) == 0
		|| ft_strncmp(map_line, "l", 1) == 0)
		scene->light_n++;
	else if (ft_strncmp(map_line, "A", 1) == 0)
		ambient++;
	else if (ft_strncmp(map_line, "C", 1) == 0)
		camera++;
	if (ft_strncmp(map_line, "L", 1) == 0)
		capital_light++;
	if (ambient > 1 || camera > 1 || capital_light > 1)
		return (0);
	return (1);
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
		if (!is_empty_or_comment(map_line) && !update_count(map_line, scene))
		{
			close(fd);
			handle_error_free(map_line,
				"Multiple definitions with capital letter");
		}
		free(map_line);
		map_line = get_next_line(fd);
	}
	close(fd);
}
