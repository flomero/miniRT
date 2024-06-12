/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_phong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:32:05 by flfische          #+#    #+#             */
/*   Updated: 2024/06/12 11:55:08 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_reflect_phong(t_vector3 *ref_v, t_vector3 *light_dir, t_vector3 *n)
{
	t_vector3	tmp;
	int			dot;

	dot = ft_v3_dotprod(light_dir, n);
	tmp.x = 2 * dot * n->x;
	tmp.y = 2 * dot * n->y;
	tmp.z = 2 * dot * n->z;
	ft_v3_init(ref_v, light_dir->x - tmp.x, light_dir->y - tmp.y, light_dir->z
		- tmp.z);
	ft_v3_normal_ip(ref_v);
}

uint32_t	ft_compute_phong(t_object *obj, t_object *light, t_hit *hit)
{
	uint32_t	color;
	uint32_t	ambient_color;
	uint32_t	diffuse_color;
	uint32_t	specular_color;
	int			light_dot_normal;
	int			ref_dot_origin;
	t_vector3	light_dir;
	t_vector3	ref_v;
	int			factor;

	color = ft_color_float_mult(ft_color_color_mult(obj->color, light->color),
			light->s_light.brightness);
	ambient_color = ft_compute_ambient(color);
	ft_v3_init(&light_dir, light->pos.x, light->pos.y, light->pos.z);
	ft_v3_sub_ip(&light_dir, &hit->p);
	ft_v3_normal_ip(&light_dir);
	light_dot_normal = ft_v3_dotprod(&light_dir, &hit->n);
	if (light_dot_normal < 0)
	{
		diffuse_color = 0x000000FF;
		specular_color = 0x000000FF;
	}
	else
	{
		diffuse_color = ft_color_float_mult(color, light_dot_normal);
		ft_reflect_phong(&ref_v, &light_dir, &hit->n);
		ref_dot_origin = ft_v3_dotprod(&ref_v, &hit->e);
		if (ref_dot_origin < 0)
			specular_color = 0x000000FF;
		else
		{
			factor = pow(ref_dot_origin, obj->material.shininess);
			specular_color = ft_color_float_mult(light->color, factor);
			specular_color = ft_color_float_mult(specular_color,
					obj->material.specular);
		}
	}
	return (ft_color_color_add(ambient_color, ft_color_color_add(diffuse_color,
				specular_color)));
}
