/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_specular.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:43:35 by flfische          #+#    #+#             */
/*   Updated: 2024/07/10 10:48:32 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_v3_reflect(t_vector3 *v, const t_vector3 *n, t_vector3 *result)
{
	t_vector3	tmp;
	t_vector3	normal;

	ft_v3_init(&normal, n->x, n->y, n->z);
	ft_v3_scalar_ip(&normal, 2 * ft_v3_dotprod(v, n));
	ft_v3_init(&tmp, v->x, v->y, v->z);
	ft_v3_sub_ip(&tmp, &normal);
	ft_v3_init(result, tmp.x, tmp.y, tmp.z);
}

t_color	*ft_compute_reflection(t_color *refl_col, const t_hit *rec, int depth)
{
	t_ray		refl_ray;
	t_vector3	origin;
	t_vector3	direction;
	t_color		tmp_col;

	*refl_col = (t_color){0, 0, 0};
	if (depth <= 0 || rec->obj->material->s_mat.reflectivness <= 0)
		return (refl_col);
	ft_v3_init(&origin, rec->p.x, rec->p.y, rec->p.z);
	ft_v3_init(&direction, rec->ray->dir->x, rec->ray->dir->y,
		rec->ray->dir->z);
	ft_v3_reflect(&direction, &rec->n, &direction);
	ft_v3_normal_ip(&direction);
	ft_v3_scalar_ip(&direction, 1 + EPSILON);
	ft_v3_add_ip(&origin, &direction);
	ft_ray_init(&refl_ray, &origin, &direction);
	refl_ray.depth = depth;
	ft_color_to_float(ft_trace_ray(&refl_ray), &tmp_col);
	ft_color_float_mult(tmp_col, rec->obj->material->s_mat.reflectivness,
		refl_col);
	return (refl_col);
}

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
	double		l_n;
	double		r_v;
	double		power;

	*spec_col = (t_color){0, 0, 0};
	if (rec->obj->material->s_mat.specular <= 0)
		return (spec_col);
	l_n = ft_v3_dotprod(light_dir, &rec->n);
	ft_v3_init(&tmp, rec->n.x, rec->n.y, rec->n.z);
	ft_v3_scalar_ip(&tmp, 2 * l_n);
	ft_v3_sub_ip(&tmp, light_dir);
	ft_v3_init(&rev_ray, rec->ray->dir->x, rec->ray->dir->y, rec->ray->dir->z);
	ft_v3_scalar_ip(&rev_ray, -1);
	r_v = ft_v3_dotprod(&rev_ray, &tmp);
	if (r_v < 0)
		return (spec_col);
	power = pow(r_v, rec->obj->material->s_mat.shininess);
	ft_color_float_mult(light->color_f, power, spec_col);
	ft_color_float_mult(*spec_col, light->s_light.brightness, spec_col);
	return (spec_col);
}
