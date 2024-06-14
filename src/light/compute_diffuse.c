/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_diffuse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:02 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 19:22:06 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes the diffuse light of the scene.
 *
 * @param diffuse_col The color to store the result in.
 * @param rec The hit record.
 * @param light The light object.
 * @param light_dir The light direction.
 * @return t_color* The computed color.
 */
t_color	*ft_compute_diffuse(t_color *diffuse_col, const t_hit *rec,
		const t_object *light, const t_vector3 *light_dir)
{
	float		angle;
	t_vector3	tmp;

	*diffuse_col = (t_color){0, 0, 0};
	ft_v3_init(&tmp, rec->n.x, rec->n.y, rec->n.z);
	ft_v3_normal_ip(&tmp);
	angle = ft_v3_dotprod(&tmp, light_dir);
	if (angle < 0)
		return (diffuse_col);
	if (rec->obj->material.reflectivness > 0)
	{
		ft_color_float_mult(rec->obj->color_f, 1
			- rec->obj->material.reflectivness, diffuse_col);
		return (diffuse_col);
	}
	ft_color_float_mult(light->color_f, angle, diffuse_col);
	ft_color_float_mult(*diffuse_col, light->s_light.brightness, diffuse_col);
	ft_color_color_mult(rec->obj->color_f, *diffuse_col, diffuse_col);
	return (diffuse_col);
}
