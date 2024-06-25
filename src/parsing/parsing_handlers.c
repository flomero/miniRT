/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:41:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/21 15:15:39 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Get the a object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_a(char **tokens, t_object *obj)
{
	float	ratio;

	if (get_arr_len(tokens) != 3)
		return (0);
	if (!is_float(tokens[1]) && !is_int(tokens[1]))
		return (free(obj), 0);
	ratio = (float)ft_atod(tokens[1]);
	if (ratio < 0 || ratio > 1)
		return (0);
	if (!get_color(tokens[2], &obj->color))
		return (free(obj), 0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_ambient_light.ratio = ratio;
	obj->type = AMBIENT_LIGHT;
	return (1);
}

/**
 * @brief Get the l object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_l(char **tokens, t_object *obj)
{
	float	brightness;

	obj->type = LIGHT;
	if (get_arr_len(tokens) != 4)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (0);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (free(obj), 0);
	brightness = (float)ft_atod(tokens[2]);
	if (brightness < 0 || brightness > 1)
		return (0);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), 0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_light.brightness = brightness;
	return (1);
}

/**
 * @brief Get the sp object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_sp(char **tokens, t_object *obj)
{
	float	diameter;

	obj->type = SPHERE;
	if (get_arr_len(tokens) < 4 || get_arr_len(tokens) > 7)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (0);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (0);
	diameter = (float)ft_atod(tokens[2]);
	if (!get_color(tokens[3], &obj->color))
		return (0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_sphere.diameter = diameter;
	ft_default_material(obj);
	ft_assign_own_tm(obj);
	if (get_arr_len(tokens) >= 5)
		obj->material_name = ft_strdup(tokens[4]);
	if (get_arr_len(tokens) >= 6)
		obj->texture_name = ft_strdup(tokens[5]);
	if (get_arr_len(tokens) == 7)
		obj->bump_name = ft_strdup(tokens[6]);
	return (1);
}

/**
 * @brief Get the pl object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_pl(char **tokens, t_object *obj)
{
	obj->type = PLANE;
	if (get_arr_len(tokens) != 4)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(&obj), 0);
	if (!get_vector(&obj->s_plane.normal, tokens[2]))
		return (0);
	if (!in_range(&obj->s_plane.normal, -1, 1))
		return (0);
	if (!get_color(tokens[3], &obj->color))
		return (0);
	ft_color_to_float(obj->color, &obj->color_f);
	ft_default_material(obj);
	ft_assign_own_tm(obj);
	return (1);
}

/*
int	get_cy(char **tokens, t_object	*obj): This implementation is on
parsing_utils3.c in order for norminette to aprove it.
 */
