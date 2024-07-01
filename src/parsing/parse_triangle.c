/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:39 by flfische          #+#    #+#             */
/*   Updated: 2024/06/30 12:22:02 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	assign_triangle_mat(char **tokens, t_object *obj, int i)
{
	if (get_arr_len(tokens) >= i + 1)
		ft_strlcpy(obj->material_name, tokens[i], ft_strlen(tokens[i]) + 1);
	return (1);
}

/**
 * @brief Get the tr object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_tr(char **tokens, t_object *obj)
{
	if (get_arr_len(tokens) != 5 && get_arr_len(tokens) != 6)
		return (0);
	if (!get_vector(&obj->s_triangle.points[0], tokens[1]))
		return (0);
	if (!get_vector(&obj->s_triangle.points[1], tokens[2]))
		return (0);
	if (!get_vector(&obj->s_triangle.points[2], tokens[3]))
		return (0);
	if (!get_color(tokens[4], &obj->color))
		return (0);
	ft_color_to_float(obj->color, &obj->color_f);
	ft_default_material(obj);
	ft_assign_own_tm(obj);
	obj->type = TRIANGLE;
	ft_v3_init(&obj->s_triangle.edge1, obj->s_triangle.points[1].x
		- obj->s_triangle.points[0].x, obj->s_triangle.points[1].y
		- obj->s_triangle.points[0].y, obj->s_triangle.points[1].z
		- obj->s_triangle.points[0].z);
	ft_v3_init(&obj->s_triangle.edge2, obj->s_triangle.points[2].x
		- obj->s_triangle.points[0].x, obj->s_triangle.points[2].y
		- obj->s_triangle.points[0].y, obj->s_triangle.points[2].z
		- obj->s_triangle.points[0].z);
	return (assign_triangle_mat(tokens, obj, 5));
}
