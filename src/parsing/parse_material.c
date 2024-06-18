/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:10:43 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 18:42:15 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_assign_own_tm(t_object *obj)
{
	obj->material = obj;
	obj->texture = obj;
}

void	ft_default_material(t_object *material)
{
	material->s_mat.specular = DEFAULT_SPECULAR;
	material->s_mat.shininess = DEFAULT_SHININESS;
	material->s_mat.diffuse = DEFAULT_DIFFUSE;
	material->s_mat.reflectivness = DEFAULT_REFLECTIVNESS;
}

void	ft_compute_if_reflective(t_object *material)
{
	if (material->s_mat.reflectivness > 0)
	{
		material->s_mat.diffuse = (1 - material->s_mat.reflectivness)
			* DEFAULT_DIFFUSE;
		material->s_mat.specular = material->s_mat.reflectivness
			* DEFAULT_SPECULAR;
	}
}

t_bool	get_basic_mat(char **tokens, t_object *obj)
{
	obj->type = MATERIAL;
	if (get_arr_len(tokens) != 4)
		return (FALSE);
	obj->s_mat.name = ft_strdup(tokens[1]);
	if (!get_color(tokens[2], &obj->color))
		return (FALSE);
	ft_color_to_float(obj->color, &obj->color_f);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (FALSE);
	ft_default_material(obj);
	obj->s_mat.reflectivness = (float)ft_atod(tokens[3]);
	ft_compute_if_reflective(obj);
	return (TRUE);
}

t_bool	get_adv_mat(char **tokens, t_object *obj)
{
	obj->type = MATERIAL;
	if (get_arr_len(tokens) != 7)
		return (FALSE);
	obj->s_mat.name = ft_strdup(tokens[1]);
	if (!get_color(tokens[2], &obj->color))
		return (FALSE);
	ft_color_to_float(obj->color, &obj->color_f);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (FALSE);
	if (!is_float(tokens[4]) && !is_int(tokens[4]))
		return (FALSE);
	if (!is_float(tokens[5]) && !is_int(tokens[5]))
		return (FALSE);
	if (!is_float(tokens[6]) && !is_int(tokens[6]))
		return (FALSE);
	obj->s_mat.reflectivness = (float)ft_atod(tokens[3]);
	obj->s_mat.diffuse = (float)ft_atod(tokens[4]);
	obj->s_mat.specular = (float)ft_atod(tokens[5]);
	obj->s_mat.shininess = (float)ft_atod(tokens[6]);
	return (TRUE);
}
