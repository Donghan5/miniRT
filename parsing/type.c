/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:43:21 by donghank          #+#    #+#             */
/*   Updated: 2024/12/11 16:07:37 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	check int
	@param
		map_info: information of the map
		i: index of the main check validity
*/
void	check_int(char *map_info, size_t *i)
{
	while (ft_isspace(map_info[*i]))
		(*i)++;
	if ((!ft_isdigit(map_info[*i]) && map_info[*i] != '-')
		|| (map_info[*i] == '-' && !ft_isdigit(map_info[*i + 1])))
		handle_error("Incorrect number format, wrong symbol");
	if (map_info[*i] == '-')
		(*i)++;
	while (ft_isdigit(map_info[*i]))
		(*i)++;
}

/*
	check double
	@param
		map_info: information of the map
		i: index of the main check validity
*/
void	check_doub(char *map_info, size_t *i)
{
	check_int(map_info, i);
	if (map_info[*i] == '.')
	{
		(*i)++;
		if (!ft_isdigit(map_info[*i]))
			handle_error("Error in double format, wrong symbol");
		while (ft_isdigit(map_info[*i]))
			(*i)++;
	}
}

/*
	check three element
	@param
		map_info: information of the map
		i: index if the main check validity
		type: type like A, C, L, sp, ...
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
				handle_error("Missing number data, sequence of \
three is not complete");
			while (ft_isspace(map_info[*i]))
				(*i)++;
			if (map_info[*i] != ',')
				handle_error("Incorrect sequence of three");
			(*i)++;
			while (ft_isspace(map_info[*i]))
				(*i)++;
		}
		j++;
	}
}

/*
	check "A    double    int, int, int"
	@param
		map_info: information of the map
		i: index of the check main validity
*/
static void	validity_type_one(char *map_info, size_t *i)
{
	check_doub(map_info, i);
	check_three(map_info, i, "int");
}

/*
	check "C    int, int, int    double, double, double    int"
	@param
		map_info: information of the map
		i: index of the check main validity
*/
static void	validity_type_two(char *map_info, size_t *i)
{
	check_three(map_info, i, "int");
	check_three(map_info, i, "double");
	check_int(map_info, i);
}

/*
	check "[L, sp]   double, double, double    double    int, int, int"
	@param
		map_info: information of the map
		i: index of the check main validity
*/
static void	validity_type_three(char *map_info, size_t *i)
{
	check_three(map_info, i, "double");
	check_doub(map_info, i);
	check_three(map_info, i, "int");
}

/*
	check "pl    double, double, double    double, double, double    int, int, int"
	@param
		map_info: information of the map
		i: index of the check map validity
*/
static void	validity_type_four(char *map_info, size_t *i)
{
	check_three(map_info, i, "double");
	check_three(map_info, i, "double");
	check_three(map_info, i, "int");
}

/*
	check [cy, co]    double, double, double    double, double, double
			   double    double    int, int, int
	@param
		map_info: information of the map
		i: index of the checking map validity
*/
static void	validity_type_five(char *map_info, size_t *i)
{
	check_three(map_info, i, "double");
	check_three(map_info, i, "double");
	check_doub(map_info, i);
	check_doub(map_info, i);
	check_three(map_info, i, "int");
}

static void	check_validity(char *map_info)
{
	size_t	i;

	i = 0;
	while (ft_isalpha(map_info[i]))
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
		handle_error("This type is not supported");
	while (map_info[i] && map_info[i] != '\n')
	{
		if (map_info[i] == '#')
			return ;
		if (!ft_isspace(map_info[i]))
			handle_error("Extra symbols");
		i++;
	}
}

/*
	check multiple declaration of the type
	@param
		sep: separated map info which want to check
		i: index
		count: structure of count which contain a, c, l etc...
*/
static void	check_double(char **sep)
{
	int		i;
	t_count	count;

	i = 0;
	init_count(&count);
	while (sep[i] != NULL)
	{
		if (ft_strchr(sep[i], '\n'))
			sep[i] = ft_strtrim(sep[i], "\n");
		if (sep[i][0] == 'A' && sep[i][1] == '\0')
			count.a_count++;
		else if (sep[i][0] == 'C' && sep[i][1] == '\0')
			count.c_count++;
		else if (sep[i][0] == 'L' && sep[i][1] == '\0' || sep[i][0] == 'l' && sep[i][1] == '\0')
			count.l_count++;
		else if (sep[i][0] == 'p' && sep[i][1] == 'l' && sep[i][2] == '\0')
			count.pl_count++;
		else if (sep[i][0] == 's' && sep[i][1] == 'p' && sep[i][2] == '\0')
			count.sp_count++;
		else if (sep[i][0] == 'c' && sep[i][1] == 'y' && sep[i][2] == '\0')
			count.cy_count++;
		else if (sep[i][0] == 'c' && sep[i][1] == 'o' && sep[i][2] == '\0')
			count.co_count++;
		i++;
	}
	if (count.a_count > 1 || count.c_count > 1 || count.l_count > 1 \
		|| count.pl_count > 1 || count.sp_count > 1 || count.cy_count > 1 \
		|| count.co_count > 1)
	{
		free_doub_array(sep);
		handle_error("Multiple declaration of type in single line");
	}
}

/*
	set the type
	@param
		sep: separated information of the map_info
	@return
		type: type value which correspond with char
*/
static int	set_type(char **sep)
{
	int	type;

	if (sep[0][0] == 'A' && sep[0][1] == '\0')
		type = 1;
	else if (sep[0][0] == 'C' && sep[0][1] == '\0')
		type = 2;
	else if (sep[0][0] == 'L' && sep[0][1] == '\0' || sep[0][0] == 'l' && sep[0][1] == '\0')
		type = 3;
	else if (sep[0][0] == 'p' && sep[0][1] == 'l' && sep[0][2] == '\0')
		type = 4;
	else if (sep[0][0] == 's' && sep[0][1] == 'p' && sep[0][2] == '\0')
		type = 5;
	else if (sep[0][0] == 'c' && sep[0][1] == 'y' && sep[0][2] == '\0')
		type = 6;
	else if (sep[0][0] == 'c' && sep[0][1] == 'o' && sep[0][2] == '\0')
		type = 7;
	else
		return (0);
	return (type);
}

/*
	get the type value
	@param
		map_info: information of the map
	@return
		type (1 ~ 7): each type value
		0: fail
*/
int	get_type(char *map_info)
{
	char	**sep;
	int		type;

	type = 0;
	check_validity(map_info);
	sep = ft_split(map_info, ' ');
	if (sep == NULL)
		return (printf("%s\n", PARSE_ERR), 0);
	if (sep[0] == NULL)
		return (free_doub_array(sep), printf("Missing type"), 0);
	check_double(sep);
	type = set_type(sep);
	printf("type is %d\n", type);
	if (type == 0)
	{
		free_doub_array(sep);
		handle_error("Invalid type!");
	}
	free_doub_array(sep);
	return (type);
}
