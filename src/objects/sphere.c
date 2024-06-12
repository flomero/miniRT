/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/12 11:56:48 by flfische         ###   ########.fr       */
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

int	ft_sphere_normal(t_object *sphere, t_ray *ray, t_vector3 *normal, float t)
{
	t_vector3	oc;

	ft_v3_init(&oc, ray->origin->x, ray->origin->y, ray->origin->z);
	ft_v3_sub_ip(&oc, &sphere->pos);
	ft_v3_scalar_ip(ray->direction, t);
	ft_v3_add_ip(&oc, ray->direction);
	ft_v3_sub_ip(&oc, &sphere->pos);
	ft_v3_normal_ip(&oc);
	ft_v3_init(normal, oc.x, oc.y, oc.z);
	return (1);
}
