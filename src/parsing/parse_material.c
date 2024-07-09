/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:10:43 by flfische          #+#    #+#             */
/*   Updated: 2024/07/08 15:54:05 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief assigns the object to its own material and texture
 * @note each object is also a material and texture
 * @param obj the object to assign
 */
void	ft_assign_own_tm(t_object *obj)
{
	obj->material = obj;
	ft_bzero(obj->material_name, MAX_NAME_LEN);
	obj->texture = obj;
	obj->s_tex.type = TEX_DEFAULT;
	ft_bzero(obj->texture_name, MAX_NAME_LEN);
	obj->bump = obj;
	ft_bzero(obj->bump_name, MAX_NAME_LEN);
}

/**
 * @brief assigns the default material values to the object
 * @param material the object to assign the default material values
 */
void	ft_default_material(t_object *material)
{
	material->s_mat.specular = DEFAULT_SPECULAR;
	material->s_mat.shininess = DEFAULT_SHININESS;
	material->s_mat.diffuse = DEFAULT_DIFFUSE;
	material->s_mat.reflectivness = DEFAULT_REFLECTIVNESS;
}

/**
 * @brief computes the material values if the object is reflective
 * @param material the object to compute the values
 */
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
	ft_strlcpy(obj->s_mat.name, tokens[1], MAX_NAME_LEN);
	if (!get_color(tokens[2], &obj->color))
		return (FALSE);
	ft_color_to_float(obj->color, &obj->color_f);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (FALSE);
	ft_default_material(obj);
	obj->s_mat.reflectivness = (double)ft_atod(tokens[3]);
	ft_compute_if_reflective(obj);
	return (TRUE);
}

t_bool	get_adv_mat(char **tokens, t_object *obj)
{
	obj->type = MATERIAL;
	if (get_arr_len(tokens) != 7)
		return (FALSE);
	ft_bzero(obj->s_mat.name, MAX_NAME_LEN);
	ft_strlcpy(obj->s_mat.name, tokens[1], MAX_NAME_LEN);
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
	obj->s_mat.reflectivness = (double)ft_atod(tokens[3]);
	obj->s_mat.diffuse = (double)ft_atod(tokens[4]);
	obj->s_mat.specular = (double)ft_atod(tokens[5]);
	obj->s_mat.shininess = (double)ft_atod(tokens[6]);
	return (TRUE);
}
