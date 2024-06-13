/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_phong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:32:05 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 13:18:51 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	ft_is_shadow(t_vector3 *light_dir, const t_hit *hit, t_program *program)
{
	t_ray		ray;
	t_hit		tmp_hit;
	int			i;
	t_vector3	shifted_hit_point;
	t_vector3	offset;

	ft_v3_init(&offset, light_dir->x * 0.001, light_dir->y * 0.001, light_dir->z
		* 0.001);
	ft_v3_init(&shifted_hit_point, hit->p.x + offset.x, hit->p.y + offset.y,
		hit->p.z + offset.z);
	ft_ray_init(&ray, &shifted_hit_point, light_dir);
	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type != LIGHT)
		{
			if (ft_hit(&ray, &program->objs[i], &tmp_hit))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_color	ft_compute_phong(t_color *color, const t_object *light,
		const t_hit *hit, t_program *program)
{
	t_vector3	light_dir;
	t_color		color;
	t_color		spec_color;
	static int	i = 0;

	ft_v3_init(&light_dir, light->pos.x, light->pos.y, light->pos.z);
	ft_v3_sub_ip(&light_dir, &hit->p);
	ft_v3_normal_ip(&light_dir);
	if (ft_is_shadow(&light_dir, hit, program))
		return ((t_color){0, 0, 0});
	ft_compute_diffuse(&color, hit, light, &light_dir);
	if (i++ < 10)
		printf("color: %f %f %f\n", color.r, color.g, color.b);
	spec_color = ft_compute_specular(hit, light, &light_dir);
	color = ft_color_color_add(color, spec_color);
	return (color);
}

t_color	ft_compute_lights(const t_hit *hit, t_program *program)
{
	int		i;
	t_color	color;

	i = 0;
	color = (t_color){0, 0, 0};
	color = ft_compute_ambient(hit->obj->color_f);
	while (i < program->objs_len)
	{
		if (program->objs[i].type == LIGHT)
		{
			color = ft_color_color_add(color,
					ft_compute_phong(&program->objs[i], hit, program));
		}
		i++;
	}
	return (color);
}
