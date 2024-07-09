/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:39:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/09 12:55:32 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calculate_coefficients(t_ray *ray, t_object *cone, double *coeffs)
{
	t_vector3	delta_p;
	double	radius;
	double	tsq;
	double	ray_cn;
	double	p_cn;

	ft_v3_init(&delta_p, ray->origin->x - cone->pos.x, ray->origin->y - cone->pos.y, ray->origin->z - cone->pos.z);
	radius = cone->s_cone.radius;
	tsq = 1 + ((radius / cone->s_cone.height) * (radius / cone->s_cone.height));
	ray_cn = ft_v3_dotprod(ray->direction, &cone->s_cone.normal);
	p_cn = ft_v3_dotprod(&delta_p, &cone->s_cone.normal);
	coeffs[0] = ft_v3_dotprod(ray->direction, ray->direction) - tsq * powf(ray_cn, 2);
	coeffs[1] = 2 * (ft_v3_dotprod(ray->direction, &delta_p) - tsq * ray_cn * p_cn);
	coeffs[2] = ft_v3_dotprod(&delta_p, &delta_p) - tsq * powf(p_cn, 2);
}

static bool	calc_hit(t_ray *ray, t_object *cone, double dist, double *t)
{
	t_vector3	hit_point;
	double	dist_to_base;

	ft_v3_init(&hit_point, ray->origin->x + ray->direction->x * dist,
		ray->origin->y + ray->direction->y * dist, ray->origin->z
		+ ray->direction->z * dist);
	ft_v3_sub_ip(&hit_point, &cone->pos);
	dist_to_base = ft_v3_dotprod(&hit_point, &cone->s_cone.normal);
	if (dist_to_base >= 0 && dist_to_base <= cone->s_cone.height)
	{
		if (dist < *t)
			*t = dist;
		return (true);
	}
	return (false);
}

static bool	check_cone_body(t_ray *ray, t_object *cone, double *coeffs, double *t)
{
	bool	hit0_valid;
	bool	hit1_valid;
	double	tmp;
	double	t0;
	double	t1;

	tmp = INFINITY;
	if (!is_sol_equation(coeffs, &t0, &t1))
		return (false);
	hit0_valid = calc_hit(ray, cone, t0, &tmp);
	hit1_valid = calc_hit(ray, cone, t1, &tmp);
	if (hit0_valid || hit1_valid)
	{
		*t = tmp;
		return (true);
	}
	return (false);
}

void	get_cone_plane(t_object *cone, t_object *to_init_pl)
{
	t_vector3	center;
	t_vector3	normal;
	t_vector3	middle_offset;

	ft_v3_init(&normal, cone->s_cone.normal.x,
		cone->s_cone.normal.y, cone->s_cone.normal.z);
	ft_v3_init(&center, cone->pos.x, cone->pos.y, cone->pos.z);
	ft_v3_init(&middle_offset, normal.x * cone->s_cone.height,
		normal.y * cone->s_cone.height, normal.z
		* cone->s_cone.height);
	ft_v3_scalar_ip(&center, 1 + EPSILON);
	ft_v3_add_ip(&center, &middle_offset);
	ft_v3_init(&to_init_pl->pos, center.x, center.y, center.z);
	ft_v3_init(&to_init_pl->s_plane.normal, normal.x, normal.y, normal.z);
	ft_v3_normal_ip(&to_init_pl->s_plane.normal);
}

double	ft_cone_hit(t_object *cone, t_ray *ray)
{
	t_object	tmp_cone;
	double	coefficients[3];
	t_object	bot_pl;
	bool	hit_body;
	bool	hit_cap;
	double	t;

	t = INFINITY;
	ft_v3_init(&tmp_cone.pos, cone->pos.x, cone->pos.y, cone->pos.z);
	ft_v3_init(&tmp_cone.s_cone.normal, cone->s_cone.normal.x, cone->s_cone.normal.y, cone->s_cone.normal.z);
	tmp_cone.s_cone.height = cone->s_cone.height;
	tmp_cone.s_cone.radius = cone->s_cone.radius;
	ft_v3_init(&tmp_cone.s_cone.normal, cone->s_cone.normal.x, cone->s_cone.normal.y, cone->s_cone.normal.z);
	ft_v3_div_ip(&tmp_cone.s_cone.normal, sqrt(ft_v3_dotprod(&tmp_cone.s_cone.normal, &tmp_cone.s_cone.normal)));
	get_cone_plane(&tmp_cone, &bot_pl);
	calculate_coefficients(ray, &tmp_cone, coefficients);
	hit_body = check_cone_body(ray, &tmp_cone, coefficients, &t);
	hit_cap = inter_disk(ray, &bot_pl, &t, cone->s_cone.radius);
	if (hit_body || hit_cap)
		return (t);
	return (INFINITY);
}

int	ft_cone_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	height_component;
	t_vector3	radial_component;
	double	radius;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&radial_component, hit->p.x - hit->obj->pos.x, hit->p.y - hit->obj->pos.y, hit->p.z - hit->obj->pos.z);
	ft_v3_init(&height_component, hit->obj->s_cone.normal.x, hit->obj->s_cone.normal.y, hit->obj->s_cone.normal.z);
	ft_v3_scalar_ip(&height_component, ft_v3_dotprod(&radial_component, &hit->obj->s_cone.normal));
	ft_v3_sub_ip(&radial_component, &height_component);
	radius = hit->obj->s_cone.radius;
	ft_v3_scalar_ip(&radial_component, 1.0 / (radius / hit->obj->s_cone.height));
	ft_v3_add_ip(&height_component, &radial_component);
	ft_v3_init(&hit->n, height_component.x, height_component.y, height_component.z);
	return (1);
}

// int	ft_cone_normal(t_hit *hit, t_ray *ray)
// {
// 	t_vector3tor3	tmp;
// 	double		projec;
// 	double		magnitude;
// 	double		angle;
// 	double		n_dot_n;

// 	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
// 		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
// 		+ ray->direction->z * hit->t);
// 	ft_v3_init(&hit->n, hit->p.x, hit->p.y, hit->p.z);
// 	ft_v3_sub_ip(&hit->n, &hit->obj->pos);
// 	projec = ft_v3_dotprod(&hit->n, &hit->obj->s_cone.normal);
// 	n_dot_n = ft_v3_dotprod(&hit->n, &hit->n);
// 	if (n_dot_n < projec * projec)
// 		return (handle_projec_zero(hit, ray));
// 	magnitude = sqrt(ft_v3_dotprod(&hit->n, &hit->n) - (projec * projec));
// 	if (projec == 0)
// 		return (handle_projec_zero(hit, ray));
// 	angle = atan(magnitude / projec);
// 	ft_v3_init(&tmp, hit->obj->s_cone.normal.x, hit->obj->s_cone.normal.y,
// 		hit->obj->s_cone.normal.z);
// 	ft_v3_scalar_ip(&tmp, projec * (1 + (tan(angle) * tan(angle))));
// 	ft_v3_sub_ip(&hit->n, &tmp);
// 	ft_v3_normal_ip(&hit->n);
// 	return (1);
// }
