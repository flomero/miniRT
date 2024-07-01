/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:39:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/01 10:36:57 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	in_height(double t[2], t_object *cone, double CO_A, double D_A);

double	ft_cone_hit(t_object *cone, t_ray *ray)
{
	t_vector3	co;
	double		k;
	double		dot_dc[2];
	double		abc[3];
	double		t[2];

	ft_v3_init(&co, ray->origin->x - cone->pos.x, ray->origin->y - cone->pos.y,
		ray->origin->z - cone->pos.z);
	k = (cone->s_cone.radius / cone->s_cone.height) * (cone->s_cone.radius
			/ cone->s_cone.height);
	dot_dc[0] = ft_v3_dotprod(ray->direction, &cone->s_cone.normal);
	dot_dc[1] = ft_v3_dotprod(&co, &cone->s_cone.normal);
	abc[0] = ft_v3_dotprod(ray->direction, ray->direction) - (1 + k)
		* (dot_dc[0] * dot_dc[0]);
	abc[1] = 2 * (ft_v3_dotprod(ray->direction, &co) - (1 + k) * dot_dc[0]
			* dot_dc[1]);
	abc[2] = ft_v3_dotprod(&co, &co) - (1 + k) * (dot_dc[1] * dot_dc[1]);
	abc[2] = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (abc[2] < 0 || abc[0] == 0)
		return (INFINITY);
	t[0] = (-abc[1] - sqrt(abc[2])) / (2 * abc[0]) - EPSILON;
	t[1] = (-abc[1] + sqrt(abc[2])) / (2 * abc[0]) - EPSILON;
	return (in_height(t, cone, dot_dc[1], dot_dc[0]));
}

static double	in_height(double t[2], t_object *cone, double CO_A, double D_A)
{
	double	hit_height;
	double	t_min;
	int		i;

	t_min = INFINITY;
	i = -1;
	while (++i < 2)
	{
		if (t[i] > 0)
		{
			hit_height = CO_A + t[i] * D_A;
			if (hit_height >= cone->s_cone.min
				&& hit_height <= cone->s_cone.height)
			{
				if (t[i] < t_min)
					t_min = t[i];
			}
		}
	}
	return (t_min);
}

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

int	ft_cone_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	tmp;
	double		projec;
	double		magnitude;
	double		angle;
	double		n_dot_n;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
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
	ft_v3_sub_ip(&hit->n, &tmp);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
