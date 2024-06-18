/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_materials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:50:49 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 17:55:53 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	ft_check_dup_mat(void)
{
	t_program	*program;
	int			i;
	int			j;

	program = ft_get_program();
	i = 0;
	while (i < program->objs_len)
	{
		j = i + 1;
		if (program->objs[i].type == MATERIAL)
		{
			while (j < program->objs_len)
			{
				if (program->objs[j].type == MATERIAL
					&& !ft_strcmp(program->objs[i].s_mat.name,
						program->objs[j].s_mat.name))
					return (TRUE);
				j++;
			}
		}
		i++;
	}
	return (FALSE);
}
