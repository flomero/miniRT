/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_mat_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:05:37 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 18:36:22 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	ft_assign_mat(t_object *obj, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type == MATERIAL && !ft_strcmp(obj->material_name,
				program->objs[i].s_mat.name))
		{
			obj->material = &program->objs[i];
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	ft_assign_tex(t_object *obj, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type == TEXTURE && !ft_strcmp(obj->texture_name,
				program->objs[i].s_tex.name))
		{
			obj->texture = &program->objs[i];
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	ft_assign_mat_tex(void)
{
	t_program	*program;
	int			i;

	program = ft_get_program();
	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type > LIGHT)
		{
			if (program->objs[i].material_name != NULL
				&& !ft_assign_mat(&program->objs[i], program))
				return (FALSE);
			if (program->objs[i].texture_name != NULL
				&& !ft_assign_tex(&program->objs[i], program))
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
