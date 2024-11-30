/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:06:16 by donghank          #+#    #+#             */
/*   Updated: 2024/11/30 16:11:05 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	check the space
	@param
		c: checking char
*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

/*
	check the all case of the empty and comment
	@param
		line: to verify line read by gnl
	@return
		1: success
		0: fail (there's comment or line)
*/
int	is_empty_or_comment(char *line)
{
	if (line == NULL || *line == '\0')
		return (1);
	while (*line)
	{
		if (!ft_isspace(*line))
		{
			if (*line == '#')
				return (1);
			return (0);
		}
		line++;
	}
	return (1);
}

/*
	free all allocation of the scene
	@param
		scene: want to deallocation
*/
void	free_scene(t_scene *scene)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < scene->plane_n)
		free(scene->plane[i++]);
	free(scene->plane);
	j = 0;
	while (j < scene->sphere_n)
		free(scene->sphere[j++]);
	free(scene->sphere);
	k = 0;
	while (k < scene->cylinder_n)
		free(scene->cylinder[k]);
	free(scene->cylinder);
}

/*
	@param
		msg: error msg
*/
void	handle_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

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
