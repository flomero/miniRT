/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:45:48 by flfische          #+#    #+#             */
/*   Updated: 2024/07/10 10:49:24 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	handle_projec_zero(t_hit *hit, t_ray *ray)
{
	t_vector3	tmp;
	t_vector3	perp;

	ft_v3_init(&perp, 1, 0, 0);
	if (fabs(hit->obj->s_cone.normal.x) > 0.9)
		perp = (t_vector3){0, 1, 0};
	ft_v3_init(&tmp, hit->obj->s_cone.normal.x, hit->obj->s_cone.normal.y,
		hit->obj->s_cone.normal.z);
	ft_v3_crossprod_ip(&tmp, &perp);
	ft_v3_normal_ip(&tmp);
	ft_v3_init(&hit->n, tmp.x, tmp.y, tmp.z);
	ft_v3_crossprod_ip(&hit->n, &hit->obj->s_cone.normal);
	ft_v3_normal_ip(&hit->n);
	(void)ray;
	return (1);
}

static int	hit_cone_cap(t_ray *ray, t_object *cone, double t, t_hit *hit)
{
	t_object	cap_plane;
	double		t_tmp;
	t_vector3	norm;
	int			cap_hit;
	double		cap_radius;

	cap_hit = 0;
	get_cone_plane(cone, &cap_plane);
	t_tmp = INFINITY;
	cap_radius = cone->s_cone.radius;
	if (inter_disk(ray, &cap_plane, &t_tmp, cap_radius))
		if (t_tmp >= t - EPSILON && t_tmp <= t + EPSILON)
			cap_hit = 1;
	if (!cap_hit)
		return (0);
	ft_v3_init(&norm, cone->s_cone.normal.x, cone->s_cone.normal.y,
		cone->s_cone.normal.z);
	ft_v3_normal_ip(&norm);
	ft_v3_init(&hit->n, norm.x, norm.y, norm.z);
	ft_v3_scalar_ip(&hit->n, -1);
	return (1);
}

int	ft_cone_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	tmp;
	double		projec;
	double		magnitude;
	double		angle;
	double		n_dot_n;

	ft_v3_init(&hit->p, ray->origin->x + ray->dir->x * hit->t, ray->origin->y
		+ ray->dir->y * hit->t, ray->origin->z + ray->dir->z * hit->t);
	if (hit_cone_cap(ray, hit->obj, hit->t, hit))
		return (1);
	ft_v3_init(&hit->n, hit->p.x, hit->p.y, hit->p.z);
	ft_v3_sub_ip(&hit->n, &hit->obj->pos);
	projec = ft_v3_dotprod(&hit->n, &hit->obj->s_cone.normal);
	n_dot_n = ft_v3_dotprod(&hit->n, &hit->n);
	if (n_dot_n < projec * projec)
		return (handle_projec_zero(hit, ray));
	magnitude = sqrt(ft_v3_dotprod(&hit->n, &hit->n) - (projec * projec));
	if (projec == 0)
		return (handle_projec_zero(hit, ray));
	angle = atan(magnitude / projec);
	ft_v3_init(&tmp, hit->obj->s_cone.normal.x, hit->obj->s_cone.normal.y,
		hit->obj->s_cone.normal.z);
	ft_v3_scalar_ip(&tmp, projec * (1 + (tan(angle) * tan(angle))));
	ft_v3_normal_ip(ft_v3_sub_ip(&hit->n, &tmp));
	return (1);
}
