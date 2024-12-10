/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:43:21 by donghank          #+#    #+#             */
/*   Updated: 2024/12/10 15:38:15 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		else if (sep[i][0] == 'L' && sep[i][1] == '\0')
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
	else if (sep[0][0] == 'L' && sep[0][1] == '\0')
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
	this one is test prototype
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
	check_double(sep);
	type = set_type(sep);
	if (type == 0)
		return (free_doub_array(sep), 0);
	return (free_doub_array(sep), type);
}
