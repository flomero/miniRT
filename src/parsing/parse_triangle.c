/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:04:39 by flfische          #+#    #+#             */
/*   Updated: 2024/06/28 16:19:47 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_tr(char **tokens, t_object *obj)
{
	if (get_arr_len(tokens) != 5)
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
	return (1);
}
