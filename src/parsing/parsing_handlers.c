/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:41:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/30 12:22:26 by flfische         ###   ########.fr       */
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
	double	ratio;

	if (get_arr_len(tokens) != 3)
		return (0);
	if (!is_float(tokens[1]) && !is_int(tokens[1]))
		return (free(obj), 0);
	ratio = (double)ft_atod(tokens[1]);
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
	double	brightness;

	obj->type = LIGHT;
	if (get_arr_len(tokens) != 4)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (0);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (free(obj), 0);
	brightness = (double)ft_atod(tokens[2]);
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
	double	diameter;

	obj->type = SPHERE;
	if (get_arr_len(tokens) < 4 || get_arr_len(tokens) > 7)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (0);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (0);
	diameter = (double)ft_atod(tokens[2]);
	if (!get_color(tokens[3], &obj->color))
		return (0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_sphere.diameter = diameter;
	ft_default_material(obj);
	ft_assign_own_tm(obj);
	if (get_arr_len(tokens) >= 5)
		ft_strlcpy(obj->material_name, tokens[4], ft_strlen(tokens[4]) + 1);
	if (get_arr_len(tokens) >= 6)
		ft_strlcpy(obj->texture_name, tokens[5], ft_strlen(tokens[5]) + 1);
	if (get_arr_len(tokens) == 7)
		ft_strlcpy(obj->bump_name, tokens[6], ft_strlen(tokens[6]) + 1);
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
	if (get_arr_len(tokens) != 4 && get_arr_len(tokens) != 5)
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
	if (get_arr_len(tokens) >= 5)
		ft_strlcpy(obj->material_name, tokens[4], ft_strlen(tokens[4]) + 1);
	return (1);
}
