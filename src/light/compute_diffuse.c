/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_diffuse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:02 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 12:49:57 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ft_compute_diffuse(const t_hit *rec, const t_object *light,
		const t_vector3 *light_dir)
{
	float		angle;
	t_vector3	tmp;
	t_color		color;

	ft_v3_init(&tmp, rec->n.x, rec->n.y, rec->n.z);
	ft_v3_normal_ip(&tmp);
	angle = ft_v3_dotprod(&tmp, light_dir);
	if (angle < 0)
		return ((t_color){0, 0, 0});
	color = ft_color_float_mult(light->color_f, angle);
	color = ft_color_float_mult(color, light->s_light.brightness);
	color = ft_color_color_mult(rec->obj->color_f, color);
	return (color);
}
