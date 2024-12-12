/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:39:04 by donghank          #+#    #+#             */
/*   Updated: 2024/12/12 16:22:27 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// char *mutiple_single(char *str)
// {
// 	while (*str == ' ' || *str == '\t')
// 		str++;
// 	size_t len = ft_strlen(str);
// 	char *result = (char *)malloc(len + 1);
// 	if (!result)
// 		return NULL;

// 	bool first_word_printed = false;
// 	size_t idx = 0;

// 	while (*str)
// 	{
// 		if (*str == ' ' || *str == '\t')
// 		{
// 			while (*str == ' ' || *str == '\t')
// 				str++;
// 			if (*str != '\0' && first_word_printed)
// 			{
// 				result[idx++] = ' ';
// 			}
// 		}
// 		else
// 		{
// 			result[idx++] = *str;
// 			first_word_printed = true;
// 			str++;
// 		}
// 	}
// 	result[idx] = '\0';

// 	char *trimmed_result = ft_realloc(result, len,idx + 1);
// 	if (trimmed_result)
// 		result = trimmed_result;
// 	return (trimmed_result);
// }

/*
	checking the range of the RGB value
	@param
		rgb_infos: rgb information to free
	@return
		0: out of value (fail)
		1: success
*/
static int	check_range(char **rgb_infos)
{
	if (ft_atoi(rgb_infos[0]) > 255 || \
	ft_atoi(rgb_infos[1]) > 255 || ft_atoi(rgb_infos[2]) > 255)
	{
		return (0);
	}
	return (1);
}

/*
	helper function of stock coordinate
	helper function of stock axis vector
	@param
		scene: scene to render
		coord_info: information of the coordinate (x, y, z)
		orient_info: information of axis vector
		cy_idx: index of cylinder
*/
static void	stock_coord_orient(t_scene *scene, char **coord_info, char **orient_info, int cy_idx)
{
	scene->cylinder[cy_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->cylinder[cy_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->cylinder[cy_idx]->coordinates.z = ft_atod(coord_info[2]);
	scene->cylinder[cy_idx]->axis_vector.x = ft_atod(orient_info[0]);
	scene->cylinder[cy_idx]->axis_vector.y = ft_atod(orient_info[1]);
	scene->cylinder[cy_idx]->axis_vector.z = ft_atod(orient_info[2]);
}

/*
	helper funtion to stock rgb value
	helper function of diameter and height
	@param
		scene: scene to render
		rgb_infos: information of RGB value
		cy_idx: index of the cylinder
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int cy_idx)
{
	char	*r_info;
	char	*g_info;
	char	*b_info;

	r_info = rgb_infos[0];
	g_info = rgb_infos[1];
	b_info = rgb_infos[2];

	if (ft_strchr(rgb_infos[0], '.')
		|| ft_strchr(rgb_infos[1], '.')
		|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "bad RGB type");
	}
	if (!check_range(rgb_infos))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "bad RGB out of range");
	}
	scene->cylinder[cy_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->cylinder[cy_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->cylinder[cy_idx]->color.b = ft_atoi(rgb_infos[2]);
}

/*
	helper function of diameter and height
	@param
		scene: to render
		sep_info: separated information
		cy_idx: index of the cylinder
*/
static void	stock_dia_hei(t_scene *scene, char **sep_info, int cy_idx)
{
	scene->cylinder[cy_idx]->cy_diameter = ft_atod(sep_info[3]);
	scene->cylinder[cy_idx]->cy_height = ft_atod(sep_info[4]);
}

/*
	stock information of cylinder
	@param
		scene: scene to render
		info_map: information of the map which read by gnl
		sep_info: separated information
		coord_info: coordinate information of cylinder
		orient_info: normal vector information of cylinder
		rgb_infos: RGB information of cylinder
*/
void	stock_cylinder(t_scene *scene, char *line, int cy_idx)
{
	char	**sep;
	char	**coord;
	char	**orient_info;
	char	**rgb_infos;

	sep = ft_split(line, ' ');
	if (sep == NULL)
		exit_error(line, scene, PARSE_ERR);
	print_double_array(sep);
	coord = ft_split(sep[1], ',');
	if (coord == NULL)
		return (free_doub_array(sep), exit_error(line, scene, COOR_ERR));
	orient_info = ft_split((char *)sep[2], ',');
	if (orient_info == NULL)
		return (free_doub_array(coord),
			free_doub_array(sep), exit_error(line, scene, ORI_ERR));
	stock_coord_orient(scene, coord, orient_info, cy_idx);
	free_doub_array(coord);
	free_doub_array(orient_info);
	stock_dia_hei(scene, sep, cy_idx);
	rgb_infos = ft_split(sep[5], ',');
	printf("sep[5]: %s\n", sep[5]);
	printf("rgb_infos[0]: %s\n", rgb_infos[0]);
	printf("rgb_infos[1]: %s\n", rgb_infos[1]);
	printf("rgb_infos[2]: %s\n", rgb_infos[2]);
	if (rgb_infos[0] == NULL || rgb_infos[1] == NULL || rgb_infos[2] == NULL)
		return (free_doub_array(sep), exit_error(line, scene, PARSE_RGB_ERR));
	stock_rgb(scene, rgb_infos, cy_idx);
	return (free_doub_array(rgb_infos), free_doub_array(sep));
}
