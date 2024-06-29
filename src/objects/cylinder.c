/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/28 18:22:14 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calc_abc(t_ray *ray, t_object *cy, float *coeffs)
{
	t_vector3	delta_p;
	float		dp_norm;
	float		rd_norm;
	float		radius;

	radius = cy->s_cylinder.diameter / 2;
	ft_v3_init(&delta_p, ray->origin->x - cy->pos.x, ray->origin->y
		- cy->pos.y, ray->origin->z - cy->pos.z);
	dp_norm = ft_v3_dotprod(&delta_p, &cy->s_cylinder.normal);
	rd_norm = ft_v3_dotprod(ray->direction, &cy->s_cylinder.normal);
	coeffs[0] = ft_v3_dotprod(ray->direction, ray->direction) - powf(rd_norm,
			2);
	coeffs[1] = 2 * (ft_v3_dotprod(ray->direction, &delta_p) - rd_norm
			* dp_norm);
	coeffs[2] = ft_v3_dotprod(&delta_p, &delta_p) - powf(dp_norm, 2)
		- powf(radius, 2);
}

static bool	calc_hit(t_ray *ray, t_object *cy, float dist, float *t)
{
	t_vector3	p;
	t_vector3	tmp;
	float		dist_to_cap;

	ft_v3_init(&p, ray->origin->x + ray->direction->x * dist,
		ray->origin->y + ray->direction->y * dist, ray->origin->z
		+ ray->direction->z * dist);
	ft_v3_init(&tmp, p.x - cy->pos.x, p.y - cy->pos.y, p.z - cy->pos.z);
	dist_to_cap = ft_v3_dotprod(&tmp, &cy->s_cylinder.normal);
	if (dist_to_cap >= 0 && dist_to_cap <= cy->s_cylinder.height)
	{
		if (dist < *t)
			*t = dist;
		return (true);
	}
	return (false);
}

static bool	is_hit_wall_cy(t_ray *ray, t_object *cy, float *coeffs, float *t)
{
	float	t0;
	float	t1;
	float	tmp;
	bool	hit[2];

	tmp = INFINITY;
	hit[0] = false;
	hit[1] = false;
	if (!is_sol_equation(coeffs, &t0, &t1))
		return (false);
	hit[0] = calc_hit(ray, cy, t0, &tmp);
	hit[1] = calc_hit(ray, cy, t1, &tmp);
	if (hit[0] || hit[1])
	{
		*t = tmp;
		return (true);
	}
	return (false);
}

double	ft_cylinder_hit(t_object *cyl, t_ray *ray)
{
	float		t;
	float		abc[3];
	t_object	tmp;
	t_object	top_bot[2];
	bool		hit;

	tmp = *cyl;
	ft_v3_init(&tmp.s_cylinder.normal, cyl->s_cylinder.normal.x,
		cyl->s_cylinder.normal.y, cyl->s_cylinder.normal.z);
	ft_v3_normal_ip(&tmp.s_cylinder.normal);
	get_plane(&tmp, &top_bot[1], false);
	get_plane(&tmp, &top_bot[0], true);
	calc_abc(ray, &tmp, abc);
	hit = is_hit_wall_cy(ray, &tmp, abc, &t);
	hit = hit || inter_disk(ray, &top_bot[1], &t, cyl->s_cylinder.diameter / 2);
	hit = hit || inter_disk(ray, &top_bot[0], &t, cyl->s_cylinder.diameter / 2);
	if (hit)
		return (t);
	return (INFINITY);
}

int	ft_cylinder_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	norm;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&hit->n, hit->p.x, hit->p.y, hit->p.z);
	ft_v3_sub_ip(&hit->n, &hit->obj->pos);
	ft_v3_init(&norm, hit->obj->s_cylinder.normal.x,
		hit->obj->s_cylinder.normal.y, hit->obj->s_cylinder.normal.z);
	ft_v3_scalar_ip(&norm, ft_v3_dotprod(&hit->n,
			&hit->obj->s_cylinder.normal));
	ft_v3_sub_ip(&hit->n, &norm);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
