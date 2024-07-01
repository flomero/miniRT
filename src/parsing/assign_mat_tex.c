/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_mat_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:05:37 by flfische          #+#    #+#             */
/*   Updated: 2024/07/01 15:28:24 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_bool	ft_assign_mat(t_object *obj, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type == MATERIAL && !ft_strcmp(obj->material_name,
				program->objs[i].s_mat.name))
		{
			obj->material = &program->objs[i];
			if (DEBUG)
				printf("Assigned material %s to object %d\n",
					obj->material_name, i);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	ft_assign_tex(t_object *obj, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type == TEXTURE && !ft_strcmp(obj->texture_name,
				program->objs[i].s_tex.name))
		{
			obj->texture = &program->objs[i];
			if (DEBUG)
				printf("Assigned texture %s to object %d\n", obj->texture_name,
					i);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	ft_assign_bump(t_object *obj, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type == BUMP && !ft_strcmp(obj->bump_name,
				program->objs[i].s_bump.name))
		{
			obj->bump = &program->objs[i];
			if (DEBUG)
				printf("Assigned bump %s to object %d\n", obj->bump_name, i);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/**
 * @brief assigns the material and texture to the objects
 * @return t_bool - checks if the assignment was successful
 */
t_bool	ft_assign_mat_tex(void)
{
	t_program	*program;
	int			i;

	program = ft_get_program();
	i = 0;
	if (ft_check_dup_mat() || ft_check_dup_tex() || ft_check_dup_bump())
		return (ft_print_error("Duplicate material, texture or bump."), FALSE);
	while (i < program->objs_len)
	{
		if (program->objs[i].type > LIGHT)
		{
			if (program->objs[i].material_name[0]
				&& !ft_assign_mat(&program->objs[i], program))
				return (ft_print_error("Failed to assign material."), FALSE);
			if (program->objs[i].texture_name[0]
				&& !ft_assign_tex(&program->objs[i], program))
				return (ft_print_error("Failed to assign texture."), FALSE);
			if (program->objs[i].bump_name[0]
				&& !ft_assign_bump(&program->objs[i], program))
				return (ft_print_error("Failed to assign bump."), FALSE);
		}
		i++;
	}
	return (TRUE);
}
