/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 15:19:36 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Checks if a ray hits a sphere.
 *
 * @param sphere The sphere to check.
 * @param ray The ray to check.
 * @return The distance to the hit point or INFINITY if no hit.
 */
float	ft_sphere_hit(t_object *sphere, t_ray *ray)
{
	t_vector3	oc;
	t_vector3	tmp;
	float		discriminant;

	ft_v3_init(&oc, ray->origin->x, ray->origin->y, ray->origin->z);
	ft_v3_sub_ip(&oc, &sphere->pos);
	tmp.x = ft_v3_dotprod(ray->direction, ray->direction);
	tmp.y = 2.0 * ft_v3_dotprod(&oc, ray->direction);
	tmp.z = ft_v3_dotprod(&oc, &oc) - (sphere->s_sphere.diameter / 2.0)
		* (sphere->s_sphere.diameter / 2.0);
	discriminant = tmp.y * tmp.y - 4.0 * tmp.x * tmp.z;
	if (discriminant < 0)
		return (INFINITY);
	return ((-tmp.y - sqrt(discriminant)) / (2.0 * tmp.x));
}

int	ft_sphere_normal(t_hit *hit, t_ray *ray)
{
	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&hit->n, hit->p.x - hit->obj->pos.x, hit->p.y - hit->obj->pos.y,
		hit->p.z - hit->obj->pos.z);
	ft_v3_normal_ip(&hit->n);
	return (1);
}

int	ft_sphere_uv(t_hit *hit, t_vector2 *uv)
{
	float		phi;
	float		theta;
	t_vector3	*normal;

	normal = &hit->n;
	phi = atan2(normal->z, normal->x);
	theta = asin(normal->y);
	uv->x = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	uv->y = (theta + M_PI / 2.0) / M_PI;
	return (1);
}
