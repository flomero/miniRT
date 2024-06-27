/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:39:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/27 16:36:43 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	in_height(double t[2], t_object *cone, double CO_A, double D_A);

double	ft_cone_hit(t_object *cone, t_ray *ray)
{
	t_vector3	co;
	double		k;
	double		dot_dc[2];
	double		abc[4];
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
	abc[3] = ft_v3_dotprod(&co, &co) - (1 + k) * (dot_dc[1] * dot_dc[1]);
	abc[3] = abc[1] * abc[1] - 4 * abc[0] * abc[3];
	if (abc[3] < 0 || abc[0] == 0)
		return (INFINITY);
	t[0] = (-abc[1] - sqrt(abc[3])) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(abc[3])) / (2 * abc[0]);
	return (in_height(t, cone, dot_dc[1], dot_dc[0]));
}

static double	in_height(double t[2], t_object *cone, double CO_A, double D_A)
{
	double	hit_height[2];

	if (t[0] > 0)
	{
		hit_height[0] = CO_A + t[0] * D_A;
		if ((hit_height[0] >= cone->s_cone.min
				&& hit_height[0] <= cone->s_cone.height))
			return (t[0]);
	}
	if (t[1] > 0)
	{
		hit_height[1] = CO_A + t[1] * D_A;
		if ((hit_height[1] >= cone->s_cone.min
				&& hit_height[1] <= cone->s_cone.height))
			return (t[1]);
	}
	return (INFINITY);
}

int	ft_cone_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	tmp;
	double		projec;
	double		magnitude;
	double		angle;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&hit->n, hit->p.x, hit->p.y, hit->p.z);
	ft_v3_sub_ip(&hit->n, &hit->obj->pos);
	projec = ft_v3_dotprod(&hit->n, &hit->obj->s_cone.normal);
	magnitude = sqrt(ft_v3_dotprod(&hit->n, &hit->n) - (projec * projec));
	if (projec == 0)
		return (0);
	angle = atan(magnitude / projec);
	ft_v3_init(&tmp, hit->obj->s_cone.normal.x, hit->obj->s_cone.normal.y,
		hit->obj->s_cone.normal.z);
	ft_v3_scalar_ip(&tmp, projec * (1 + (tan(angle) * tan(angle))));
	ft_v3_sub_ip(&hit->n, &tmp);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
