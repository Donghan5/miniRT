/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:39:31 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/12 16:59:39 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// char	*normalize_line(char *line)
// {
// 	char	*new_line;
// 	char	*new_start;
// 	char	*line_start;

// 	line_start = line;
// 	new_line = malloc(ft_strlen(line) + 1);
// 	if (!new_line)
// 		return (free(line), line = NULL, NULL);
// 	new_start = new_line;
// 	while (*line)
// 	{
// 		while (*line && !ft_isspace(*line))
// 			*new_line++ = *line++;
// 		if (ft_isspace(*line))
// 			*new_line = ' ';
// 		while (ft_isspace(*line))
// 			line++;
// 		if (*line != ',' && new_line != new_start && *(new_line - 1) != ',')
// 			new_line++;
// 	}
// 	*new_line = '\0';
// 	free(line_start);
// 	line_start = new_start;
// 	return (line_start);
// }

char	*normalize_line(char *line)
{
	int		i;
	int		j;
	char	*new_line;


	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	new_line = malloc(ft_strlen(line) + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	while (line[i])
	{
		while (line[i] && !ft_isspace(line[i]))
			new_line[j++] = line[i++];
		if (line[i] && ft_isspace(line[i]))
		{
			new_line[j] = ' ';
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (line[i] != ',' && (j == 0 || new_line[j - 1] != ','))
				j++;
		}
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

/*
	to stock the all element in the .rt maps
	@param
		fd: file discriptor of the map
		scene: structure which want to stock it
*/
static int	do_stock(int fd, t_scene *scene)
{
	char		*map_line;
	t_indices	indices;

	init_indices(&indices);
	map_line = get_next_line(fd);
	if (!map_line)
		return (0);
	while (map_line != NULL)
	{
		if (!is_empty_or_comment(map_line))
		{
			map_line = normalize_line(map_line);
			if (!map_line)
				return (0);
			printf("~%s~\n", map_line);
			process_parse(map_line, scene, &indices);
		}
		free(map_line);
		map_line = get_next_line(fd);
	}
	return (1);
}

static int	validate(int fd, t_scene *scene)
{
	char	*map_line;

	map_line = get_next_line(fd);
	if (!map_line)
		return (0);
	while (map_line != NULL)
	{
		if (!is_empty_or_comment(map_line))
			check_validity(map_line);
		free(map_line);
		map_line = get_next_line(fd);
	}
	return (1);
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

	fd = open(path, O_RDONLY);
	if (fd < 0 || !validate(fd, scene))
	{
		close(fd);
		handle_error("Fail to open the file");
	}
	close(fd);
	init_scene(path, scene);
	fd = open(path, O_RDONLY);
	if (fd < 0 || !do_stock(fd, scene))
	{
		close(fd);
		exit_error(NULL, scene, "Fail to open the file");
	}
	close(fd);
	printf("Processing ended. Terminate the parsing session\n");
}
