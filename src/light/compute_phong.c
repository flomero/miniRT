/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_phong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:32:05 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 18:29:59 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Checks if the hit point is in shadow.
 *
 * @param light_dir The direction of the light.
 * @param hit The hit point.
 * @param program The program.
 * @return t_bool TRUE if the hit point is in shadow, FALSE otherwise.
 */
t_bool	ft_is_shadow(t_vector3 *light_dir, const t_hit *hit, t_program *program)
{
	t_ray	ray;
	t_hit	tmp_hit;
	int		i;

	ray.origin = &(t_vector3){hit->p.x, hit->p.y, hit->p.z};
	ray.direction = light_dir;
	i = 0;
	while (i < program->objs_len)
	{
		if (program->objs[i].type > LIGHT)
		{
			tmp_hit.t = INFINITY;
			if (ft_hit(&ray, &program->objs[i], &tmp_hit))
			{
				if (tmp_hit.t < -0.0001 && tmp_hit.t > -0.9999)
					return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}

/**
 * @brief Computes the phong light of the scene.
 *
 * @param phong_color The color to store the result in.
 * @param light The light object.
 * @param hit The hit record.
 * @param program The program.
 * @return t_color* The computed color.
 */
t_color	*ft_compute_phong(t_color *phong_color, const t_object *light,
		const t_hit *hit, t_program *program)
{
	t_vector3	light_dir;
	t_color		color;
	t_color		spec_color;
	t_color		refl_col;

	*phong_color = (t_color){0, 0, 0};
	ft_v3_init(&light_dir, light->pos.x, light->pos.y, light->pos.z);
	ft_v3_sub_ip(&light_dir, &hit->p);
	if (ft_is_shadow(&light_dir, hit, program))
		return (phong_color);
	ft_v3_normal_ip(&light_dir);
	ft_compute_diffuse(&color, hit, light, &light_dir);
	if (hit->ray->depth > 0 && hit->obj->material->s_mat.reflectivness > 0)
	{
		ft_compute_reflection(&refl_col, hit, --hit->ray->depth);
		ft_color_float_mult(*phong_color, 1
			- hit->obj->material->s_mat.reflectivness, phong_color);
		ft_color_color_add(*phong_color, refl_col, phong_color);
	}
	ft_compute_specular(&spec_color, hit, light, &light_dir);
	ft_color_color_add(*phong_color, spec_color, phong_color);
	return (phong_color);
}

/**
 * @brief Computes the lights of the scene.
 *
 * @param light_col The color to store the result in.
 * @param hit The hit record.
 * @param program The program.
 * @return The computed color.
 */
t_color	*ft_compute_lights(t_color *light_col, t_hit *hit, t_program *program)
{
	int		i;
	t_color	ambient;
	t_color	phong_color;

	i = 0;
	*light_col = (t_color){0, 0, 0};
	hit->local_color = (t_color){hit->obj->material->color_f.r,
		hit->obj->material->color_f.g, hit->obj->material->color_f.b};
	if (hit->obj->texture->s_tex.type == CHECKER)
		ft_checkerboard(hit->obj->material, &hit->p,
			(t_color *)&hit->local_color);
	else if (hit->obj->texture->s_tex.type == UVCHECKER)
		ft_checkerboard_uv(hit->obj->material, (t_color *)&hit->local_color,
			hit);
	ft_compute_ambient(&ambient, hit->local_color);
	while (i < program->objs_len)
	{
		if (program->objs[i].type == LIGHT)
		{
			ft_compute_phong(&phong_color, &program->objs[i], hit, program);
			ft_color_color_add(*light_col, phong_color, light_col);
		}
		i++;
	}
	ft_color_color_add(*light_col, ambient, light_col);
	return (light_col);
}
