/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 16:52:22 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// distance = math.sqrt((x - x_c)**2 + (y - y_c)**2 + (z - z_c)**2)
// b = 2 * (D[0] * (O[0] - C[0]) + D[1] * (O[1] - C[1]) + D[2] * (O[2] - C[2]))
// c = (O[0] - C[0])**2 + (O[1] - C[1])**2 + (O[2] - C[2])**2 - r**2
// O = ray_origin
// D = ray_direction
// C = sphere_center
// r = sphere_radius
// if discriminant < 0 -> No intersection
/**
 * Checks if a ray hits a sphere.
 *
 * @param sphere The sphere to check.
 * @param ray The ray to check.
 * @return The distance to the hit point or INFINITY if no hit.
 */
float	ft_sphere_hit(t_object *sphere, t_ray *ray)
{
	float		distance;
	float		discriminant;
	t_vector3	*temp;
	float		a;
	float		b;
	float		c;

	a = ft_v3_dotprod(ray->direction, ray->direction);
	temp = ft_v3_sub(ray->origin, &sphere->pos);
	b = 2 * ft_v3_dotprod(temp, ray->direction);
	c = ft_v3_dotprod(temp, temp) - (sphere->s_sphere.diameter / 2.0) * (sphere->s_sphere.diameter / 2.0);
	discriminant = (b * b) - (4*a*c);
	if (discriminant >= 0)
	{
		distance = sqrt(pow(ray->origin->x - sphere->pos.x, 2)
			+ pow(ray->origin->y - sphere->pos.y, 2)
			+ pow(ray->origin->z - sphere->pos.z, 2));
		return (distance);
	}
	else
		return (INFINITY);
}

// float	ft_sphere_hit(t_object *sphere, t_ray *ray)
// {
// 	t_vector3	oc;
// 	t_vector3	tmp;
// 	float		discriminant;

// 	ft_v3_init(&oc, ray->origin->x, ray->origin->y, ray->origin->z);
// 	ft_v3_sub_ip(&oc, &sphere->pos);
// 	tmp.x = ft_v3_dotprod(ray->direction, ray->direction);
// 	tmp.y = 2.0 * ft_v3_dotprod(&oc, ray->direction);
// 	tmp.z = ft_v3_dotprod(&oc, &oc) - (sphere->s_sphere.diameter / 2.0)
// 		* (sphere->s_sphere.diameter / 2.0);
// 	discriminant = tmp.y * tmp.y - 4.0 * tmp.x * tmp.z;
// 	if (discriminant < 0)
// 		return (INFINITY);
// 	return ((-tmp.y - sqrt(discriminant)) / (2.0 * tmp.x));
// }
