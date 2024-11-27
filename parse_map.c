/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:05:39 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/27 12:18:25 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static int	*line_to_ints(char *line, int size)
// {
// 	int	*new_arr;
// 	int	arr_i;
// 	int	i;

// 	i = 0;
// 	arr_i = 0;
// 	new_arr = malloc(size * sizeof (int));
// 	if (!new_arr)
// 		return (NULL);
// 	while (line[i] != '\0' && line[i] != '\n')
// 	{
// 		while (line[i] == ' ')
// 			i++;
// 		if (((line[i] >= '0') && (line[i] <= '9'))
// 			|| line[i] == '-' || line[i] == '+')
// 		{
// 			new_arr[arr_i] = atoi(line + i);
// 			arr_i++;
// 			i++;
// 		}
// 		while ((line[i] >= '0') && (line[i] <= '9'))
// 			i++;
// 	}
// 	return (new_arr);
// }

// static int	get_type(char *line)
// {
// 	int	type;

// 	type = 0;
// 	if (!line || !line[0] || !ft_isalpha(line[0]))
// 		return (0);
// 	if ((ft_strncmp("A", line, 1) == 0) && !ft_isalpha(line[1]))
// 		type = 1;
// 	else if ((ft_strncmp("C", line, 1) == 0) && !ft_isalpha(line[1]))
// 		type = 2;
// 	else if ((ft_strncmp("L", line, 1) == 0) && !ft_isalpha(line[1]))
// 		type = 3;
// 	else if ((ft_strncmp("pl", line, 2) == 0) && !ft_isalpha(line[2]))
// 		type = 4;
// 	else if ((ft_strncmp("sp", line, 2) == 0) && !ft_isalpha(line[2]))
// 		type = 5;
// 	else if ((ft_strncmp("cy", line, 2) == 0) && !ft_isalpha(line[2]))
// 		type = 6;
// 	return (type);
// }

// static int	check_line(char	*line)
// {
// 	int	i;
// 	int	width;

// 	i = 0;
// 	width = 0;
// 	while (line[i] && line[i] != '\n')
// 	{
// 		while (line[i] == ' ')
// 			i++;
// 		if (!line[i] || line[i] == '\n')
// 			break ;
// 		if (!(line[i] >= 'a' && line[i] <= 'z'))
// 		if (((line[i] >= '0') && (line[i] <= '9'))
// 			|| (line[i] == '-') || (line[i] == '+'))
// 		{
// 			width++;
// 			i++;
// 		}
// 		while ((line[i] >= '0') && (line[i] <= '9'))
// 			i++;
// 		if (line[i] && ((line[i] != ' ') && (line[i] != '\n')))
// 			return (0);
// 		if (line[i])
// 			i++;
// 	}
// 	return (width);
// }

// static int	check_map(int fd, t_view *map)
// {
// 	int		result;
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		result = check_line(line);
// 		free(line);
// 		if (!result)
// 			return (0);
// 		line = get_next_line(fd);
// 	}
// 	return (1);
// }

// static void	set_min_max(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	map->min_height = FLT_MAX;
// 	map->max_height = FLT_MIN;
// 	i = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			if ((float)map->map[i][j] < map->min_height)
// 				map->min_height = (float)map->map[i][j];
// 			if ((float)map->map[i][j] > map->max_height)
// 				map->max_height = (float)map->map[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	parse_scene(char *path, t_scene *scene)
// {
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	// fd = open(path, O_RDONLY);
	// if (fd < 0 || !check_map(fd, scene))
	// 	return (close(fd), exit_error(NULL, 0, "Map error"));
	// close(fd);
	// map->map = malloc(map->height * sizeof (int *));
	// if (!map->map)
	// 	return (exit_error(NULL, 0, "Memory error"));
	// fd = open(path, O_RDONLY);
	// line = get_next_line(fd);
	// i = 0;
	// while (line)
	// {
	// 	map->map[i] = line_to_ints(line, map->width);
	// 	if (!map->map[i])
	// 		exit_error(map, i, "Map translation failure");
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	i++;
	// }
	// set_min_max(map);
// }
