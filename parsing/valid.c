/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:12:43 by donghank          #+#    #+#             */
/*   Updated: 2024/12/10 15:53:05 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	to check the validity of the information form
	@param
		sep_info: separated information
*/
void	valid_form(int type, char **sep_info)
{
	int	i;

	i = 0;
	while (sep_info[i])
		i++;
	if (type == 1 && i > 3)
		handle_error("error syntax");
	else if ((type >= 2 && type <= 5) && i > 4)
		handle_error("error syntax");
	else if ((type == 6 || type == 7) && i > 6)
		handle_error("error syntax");
}
