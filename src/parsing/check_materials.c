/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_materials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:50:49 by flfische          #+#    #+#             */
/*   Updated: 2024/06/21 14:59:22 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief checks if there are duplicate materials
 * @return t_bool - TRUE if there are duplicates, FALSE otherwise
 */
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

/**
 * @brief checks if there are duplicate textures
 * @return t_bool - TRUE if there are duplicates, FALSE otherwise
 */
t_bool	ft_check_dup_tex(void)
{
	t_program	*program;
	int			i;
	int			j;

	program = ft_get_program();
	i = 0;
	while (i < program->objs_len)
	{
		j = i + 1;
		if (program->objs[i].type == TEXTURE)
		{
			while (j < program->objs_len)
			{
				if (program->objs[j].type == TEXTURE
					&& !ft_strcmp(program->objs[i].s_tex.name,
						program->objs[j].s_tex.name))
					return (TRUE);
				j++;
			}
		}
		i++;
	}
	return (FALSE);
}

/**
 * @brief checks if there are duplicate bumps
 * @return t_bool - TRUE if there are duplicates, FALSE otherwise
 */
t_bool	ft_check_dup_bump(void)
{
	t_program	*program;
	int			i;
	int			j;

	program = ft_get_program();
	i = 0;
	while (i < program->objs_len)
	{
		j = i + 1;
		if (program->objs[i].type == BUMP)
		{
			while (j < program->objs_len)
			{
				if (program->objs[j].type == BUMP
					&& !ft_strcmp(program->objs[i].s_bump.name,
						program->objs[j].s_bump.name))
					return (TRUE);
				j++;
			}
		}
		i++;
	}
	return (FALSE);
}
