/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/08 15:36:37 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calc_abc(t_ray *ray, t_object *cy, double *coeffs)
{
	t_vector3	delta_p;
	double		dp_norm;
	double		rd_norm;
	double		radius_squared;

	radius_squared = pow(cy->s_cylinder.diameter / 2, 2);
	ft_v3_init(&delta_p, ray->origin->x - cy->pos.x, ray->origin->y - cy->pos.y,
		ray->origin->z - cy->pos.z);
	dp_norm = ft_v3_dotprod(&delta_p, &cy->s_cylinder.normal);
	rd_norm = ft_v3_dotprod(ray->direction, &cy->s_cylinder.normal);
	coeffs[0] = ft_v3_dotprod(ray->direction, ray->direction) - pow(rd_norm, 2);
	coeffs[1] = 2 * (ft_v3_dotprod(ray->direction, &delta_p) - rd_norm
			* dp_norm);
	coeffs[2] = ft_v3_dotprod(&delta_p, &delta_p) - pow(dp_norm, 2)
		- radius_squared;
}

static bool	calc_hit(t_ray *ray, t_object *cy, double dist, double *t)
{
	t_vector3	p;
	t_vector3	tmp;
	double		projection_on_axis;

	ft_v3_init(&p, ray->origin->x + ray->direction->x * dist, ray->origin->y
		+ ray->direction->y * dist, ray->origin->z + ray->direction->z * dist);
	ft_v3_init(&tmp, p.x - cy->pos.x, p.y - cy->pos.y, p.z - cy->pos.z);
	projection_on_axis = ft_v3_dotprod(&tmp, &cy->s_cylinder.normal);
	if (projection_on_axis >= -cy->s_cylinder.height / 2
		&& projection_on_axis <= cy->s_cylinder.height / 2)
	{
		if (dist < *t)
			*t = dist;
		return (true);
	}
	return (false);
}

static bool	is_hit_wall_cy(t_ray *ray, t_object *cy, double *coeffs, double *t)
{
	double	t0;
	double	t1;
	double	tmp;
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
	double		t;
	double		abc[3];
	t_object	tmp;
	t_object	top_bot[2];
	bool		hit;

	tmp = *cyl;
	t = INFINITY;
	ft_v3_init(&tmp.s_cylinder.normal, cyl->s_cylinder.normal.x,
		cyl->s_cylinder.normal.y, cyl->s_cylinder.normal.z);
	ft_v3_normal_ip(&tmp.s_cylinder.normal);
	get_plane(&tmp, &top_bot[1], false);
	get_plane(&tmp, &top_bot[0], true);
	calc_abc(ray, &tmp, abc);
	hit = is_hit_wall_cy(ray, &tmp, abc, &t);
	hit = inter_disk(ray, &top_bot[1], &t, cyl->s_cylinder.diameter / 2) || hit;
	hit = inter_disk(ray, &top_bot[0], &t, cyl->s_cylinder.diameter / 2) || hit;
	if (hit)
		return (t);
	return (INFINITY);
}
