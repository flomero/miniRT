/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_specular.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:43:35 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 12:57:38 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ft_compute_specular(const t_hit *rec, const t_object *light,
		const t_vector3 *light_dir)
{
	t_vector3	tmp;
	t_vector3	rev_ray;
	float		l_n;
	float		r_v;
	float		power;
	t_color		color;

	if (rec->obj->material.specular <= 0)
		return ((t_color){0, 0, 0});
	l_n = ft_v3_dotprod(light_dir, &rec->n);
	ft_v3_init(&tmp, rec->n.x, rec->n.y, rec->n.z);
	ft_v3_scalar_ip(&tmp, 2 * l_n);
	ft_v3_sub_ip(&tmp, light_dir);
	ft_v3_init(&rev_ray, rec->ray->direction->x, rec->ray->direction->y,
		rec->ray->direction->z);
	ft_v3_scalar_ip(&rev_ray, -1);
	r_v = ft_v3_dotprod(&rev_ray, &tmp);
	if (r_v < 0)
		return ((t_color){0, 0, 0});
	power = pow(r_v / (ft_v3_len(&rev_ray) * ft_v3_len(&tmp)),
			rec->obj->material.specular);
	color = ft_color_float_mult(light->color_f, power);
	color = ft_color_float_mult(color, light->s_light.brightness);
	return (color);
}
