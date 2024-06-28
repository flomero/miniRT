/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:08:43 by flfische          #+#    #+#             */
/*   Updated: 2024/06/28 18:34:59 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_triangle_hit(t_object *triangle, t_ray *ray)
{
	t_vector3	h;
	t_vector3	s;
	t_vector3	q;
	double		afuvt[5];

	ft_v3_init(&h, ray->direction->x, ray->direction->y, ray->direction->z);
	ft_v3_crossprod_ip(&h, &triangle->s_triangle.edge2);
	afuvt[0] = ft_v3_dotprod(&triangle->s_triangle.edge1, &h);
	if (afuvt[0] > -EPSILON && afuvt[0] < EPSILON)
		return (INFINITY);
	afuvt[1] = 1 / afuvt[0];
	ft_v3_init(&s, ray->origin->x - triangle->s_triangle.points[0].x,
		ray->origin->y - triangle->s_triangle.points[0].y, ray->origin->z
		- triangle->s_triangle.points[0].z);
	afuvt[2] = afuvt[1] * ft_v3_dotprod(&s, &h);
	if (afuvt[2] < 0.0 || afuvt[2] > 1.0)
		return (INFINITY);
	ft_v3_init(&q, s.x, s.y, s.z);
	ft_v3_crossprod_ip(&q, &triangle->s_triangle.edge1);
	afuvt[3] = afuvt[1] * ft_v3_dotprod(ray->direction, &q);
	if (afuvt[3] < 0.0 || afuvt[2] + afuvt[3] > 1.0)
		return (INFINITY);
	if (afuvt[1] * ft_v3_dotprod(&triangle->s_triangle.edge2, &q) > EPSILON)
		return (afuvt[1] * ft_v3_dotprod(&triangle->s_triangle.edge2, &q));
	return (INFINITY);
}

int	ft_triangle_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	normal;

	ft_v3_init(&normal, hit->obj->s_triangle.edge1.x,
		hit->obj->s_triangle.edge1.y, hit->obj->s_triangle.edge1.z);
	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_crossprod_ip(&normal, &hit->obj->s_triangle.edge2);
	ft_v3_normal_ip(&normal);
	if (ft_v3_dotprod(&normal, ray->direction) > 0)
		ft_v3_scalar_ip(&normal, -1);
	hit->n = normal;
	return (1);
}
