/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_phong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:32:05 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 15:04:16 by flfische         ###   ########.fr       */
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

	ft_v3_init(&offset, light_dir->x * 0.01, light_dir->y * 0.01, light_dir->z
		* 0.01);
	ft_v3_init(&shifted_hit_point, hit->p.x + offset.x, hit->p.y + offset.y,
		hit->p.z + offset.z);
	ray.origin = &shifted_hit_point;
	ray.direction = light_dir;
	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type != LIGHT)
		{
			tmp_hit.t = INFINITY;
			if (ft_hit(&ray, &program->objs[i], &tmp_hit))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_color	*ft_compute_phong(t_color *phong_color, const t_object *light,
		const t_hit *hit, t_program *program)
{
	t_vector3	light_dir;
	t_color		color;
	t_color		spec_color;
	static int	i = 0;

	*phong_color = (t_color){0, 0, 0};
	ft_v3_init(&light_dir, light->pos.x, light->pos.y, light->pos.z);
	ft_v3_sub_ip(&light_dir, &hit->p);
	ft_v3_normal_ip(&light_dir);
	if (ft_is_shadow(&light_dir, hit, program))
		return (phong_color);
	ft_compute_diffuse(&color, hit, light, &light_dir);
	if (i++ < 10)
		printf("color: %f %f %f\n", color.r, color.g, color.b);
	ft_compute_specular(&spec_color, hit, light, &light_dir);
	ft_color_color_add(color, spec_color, phong_color);
	return (phong_color);
}

t_color	*ft_compute_lights(t_color *light_col, const t_hit *hit,
		t_program *program)
{
	int		i;
	t_color	ambient;
	t_color	phong_color;

	i = 0;
	*light_col = (t_color){0, 0, 0};
	ft_compute_ambient(&ambient, hit->obj->color_f);
	while (i < program->objs_len)
	{
		if (program->objs[i].type == LIGHT)
		{
			ft_compute_phong(&phong_color, &program->objs[i], hit, program);
			ft_color_color_add(ambient, phong_color, light_col);
		}
		i++;
	}
	return (light_col);
}
