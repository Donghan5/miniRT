/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:55:24 by donghank          #+#    #+#             */
/*   Updated: 2024/12/17 12:58:50 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	check int type
	@param
		map_info: information of the map
		i: index pointer
*/
void	check_int(char *map_info, size_t *i)
{
	while (ft_isspace(map_info[*i]))
		(*i)++;
	if ((!ft_isdigit(map_info[*i]) && map_info[*i] != '-')
		|| (map_info[*i] == '-' && !ft_isdigit(map_info[*i + 1])))
		handle_error_free(map_info, "Incorrect number format, wrong symbol");
	if (map_info[*i] == '-')
		(*i)++;
	while (ft_isdigit(map_info[*i]))
		(*i)++;
}

/*
	check double type
	@param
		map_info: information
		i: index pointer
*/
void	check_doub(char *map_info, size_t *i)
{
	check_int(map_info, i);
	if (map_info[*i] == '.')
	{
		(*i)++;
		if (!ft_isdigit(map_info[*i]))
			handle_error_free(map_info, "Error in double format, wrong symbol");
		while (ft_isdigit(map_info[*i]))
			(*i)++;
	}
}

/*
	check RGB and vector value
	@param
		map_info: information of the map
		i: index pointer
		type: type of the value
*/
void	check_three(char *map_info, size_t *i, char *type)
{
	int	j;

	j = 0;
	while (j < 3)
	{
		if (!ft_strncmp(type, "int", 3))
			check_int(map_info, i);
		else
			check_doub(map_info, i);
		if (j != 2)
		{
			if (!map_info[*i])
				handle_error_free(map_info, "Missing number data, sequence of \
three is not complete");
			while (ft_isspace(map_info[*i]))
				(*i)++;
			if (map_info[*i] != ',')
				handle_error_free(map_info, "Incorrect sequence of three");
			(*i)++;
			while (ft_isspace(map_info[*i]))
				(*i)++;
		}
		j++;
	}
}

/*
	check the validity of information
	RGB, vector etc...
	@param
		map_info: information of the map
*/
void	check_validity(char *map_info)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(map_info[i]))
		i++;
	if (!ft_strncmp(map_info, "A ", 2))
		validity_type_one(map_info, &i);
	else if (!ft_strncmp(map_info, "C ", 2))
		validity_type_two(map_info, &i);
	else if (!ft_strncmp(map_info, "l ", 2) || !ft_strncmp(map_info, "L ", 2)
		|| !ft_strncmp(map_info, "sp ", 3))
		validity_type_three(map_info, &i);
	else if (!ft_strncmp(map_info, "pl ", 3))
		validity_type_four(map_info, &i);
	else if (!ft_strncmp(map_info, "cy ", 3) || !ft_strncmp(map_info, "co ", 3))
		validity_type_five(map_info, &i);
	else if (map_info[0] != '#')
		handle_error_free(map_info, "This type is not supported");
	while (map_info[i] && map_info[i] != '\n')
	{
		if (map_info[i] == '#')
			return ;
		if (!ft_isspace(map_info[i++]))
			handle_error_free(map_info, "Extra symbols");
	}
}
