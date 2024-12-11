/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:39:31 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 15:21:35 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	to stock the all element in the .rt maps
	@param
		fd: file discriptor of the map
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
	free(map_line);
}

/*
	parse and stock all informations
	idea of this function
	1. parsing the map_line (read by gnl) by separating white-space
	2. verify element (map_infos[0] is char) the other have just , and num
	3. separate the case --> stock each structures
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
