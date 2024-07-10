/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:06:48 by flfische          #+#    #+#             */
/*   Updated: 2024/07/10 10:59:36 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	assign_cone_mat(char **tokens, t_object *obj, int i)
{
	if (get_arr_len(tokens) >= i + 1)
		ft_strlcpy(obj->material_name, tokens[i], ft_strlen(tokens[i]) + 1);
	if (get_arr_len(tokens) >= i + 2)
		ft_strlcpy(obj->texture_name, tokens[i + 1], ft_strlen(tokens[i + 1])
			+ 2);
	return (1);
}

int	get_co(char **tokens, t_object *obj)
{
	obj->type = CONE;
	if (get_arr_len(tokens) < 6 && get_arr_len(tokens) > 8)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (0);
	if (!get_vector(&obj->s_cone.normal, tokens[2]))
		return (0);
	if (!in_range(&obj->s_cone.normal, -1, 1))
		return (0);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (0);
	obj->s_cone.radius = (double)ft_atod(tokens[3]);
	if (!is_float(tokens[4]) && !is_int(tokens[4]))
		return (0);
	obj->s_cone.height = (double)ft_atod(tokens[4]);
	if (!get_color(tokens[5], &obj->color))
		return (0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_cone.angle = atan(obj->s_cone.radius / obj->s_cone.height) * 2;
	obj->s_cone.min = 0;
	ft_default_material(obj);
	ft_assign_own_tm(obj);
	ft_v3_normal_ip(&obj->s_cone.normal);
	return (assign_cone_mat(tokens, obj, 6));
}
