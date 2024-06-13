/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:11:15 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 10:44:11 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	ft_hit(t_ray *ray, t_object *obj, t_hit *hit)
{
	float	t;

	t = INFINITY;
	if (obj->type == SPHERE)
		t = ft_sphere_hit(obj, ray);
	if (t <= 0 || t == INFINITY)
		return (FALSE);
	if (t > hit->t)
		return (FALSE);
	hit->t = t;
	hit->obj = obj;
	hit->obj->color = obj->color;
	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * t, ray->origin->y
		+ ray->direction->y * t, ray->origin->z + ray->direction->z * t);
	ft_v3_init(&hit->n, hit->p.x - obj->pos.x, hit->p.y - obj->pos.y, hit->p.z
		- obj->pos.z);
	ft_v3_normal_ip(&hit->n);
	hit->ray = ray;
	return (TRUE);
}
