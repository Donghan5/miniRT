/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:13:29 by donghank          #+#    #+#             */
/*   Updated: 2024/12/05 12:24:29 by donghank         ###   ########.fr       */
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
	char	**sep;
	int		type;

	type = 0;
	sep = ft_split(map_info, ' ');
	if (sep == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	if (sep[0] == NULL)
		return (free_doub_array(sep), printf("Missing type"), 0);
	if (sep[0][0] == 'A' && sep[0][1] == ' ')
		type = 1;
	else if (sep[0][0] == 'C' && sep[0][1] == ' ')
		type = 2;
	else if (sep[0][0] == 'L' && sep[0][1] == ' ')
		type = 3;
	else if (sep[0][0] == 'p' && sep[0][1] == 'l' && sep[0][2] == ' ')
		type = 4;
	else if (sep[0][0] == 's' && sep[0][1] == 'p' && sep[0][2] == ' ')
		type = 5;
	else if (sep[0][0] == 'c' && sep[0][1] == 'y' && sep[0][2] == ' ')
		type = 6;
	else
		return (free_doub_array(sep), 0);
	return (free_doub_array(sep), type);
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
