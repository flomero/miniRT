/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_specular.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:43:35 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 15:08:17 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes the specular light of the scene.
 *
 * @param spec_col The color to store the result in.
 * @param rec The hit record.
 * @param light The light object.
 * @param light_dir The light direction.
 * @return t_color* The computed color.
 */
t_color	*ft_compute_specular(t_color *spec_col, const t_hit *rec,
		const t_object *light, const t_vector3 *light_dir)
{
	t_vector3	tmp;
	t_vector3	rev_ray;
	float		l_n;
	float		r_v;
	float		power;

	*spec_col = (t_color){0, 0, 0};
	if (rec->obj->material.specular <= 0)
		return (spec_col);
	l_n = ft_v3_dotprod(light_dir, &rec->n);
	ft_v3_init(&tmp, rec->n.x, rec->n.y, rec->n.z);
	ft_v3_scalar_ip(&tmp, 2 * l_n);
	ft_v3_sub_ip(&tmp, light_dir);
	ft_v3_init(&rev_ray, rec->ray->direction->x, rec->ray->direction->y,
		rec->ray->direction->z);
	ft_v3_scalar_ip(&rev_ray, -1);
	r_v = ft_v3_dotprod(&rev_ray, &tmp);
	if (r_v < 0)
		return (spec_col);
	power = pow(r_v / (ft_v3_len(&rev_ray) * ft_v3_len(&tmp)),
			rec->obj->material.specular);
	ft_color_float_mult(light->color_f, power, spec_col);
	ft_color_float_mult(*spec_col, light->s_light.brightness, spec_col);
	return (spec_col);
}
