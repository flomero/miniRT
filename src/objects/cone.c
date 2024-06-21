
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:39:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/19 16:13:23 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	ft_cone_hit(t_object *cone, t_ray *ray)
{
	t_vector3	*CO;
	float		cos_theta2;
	float		D_dot_A;
	float		CO_dot_A;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t1;
	float		t2;
	float		hit_height1;
	// float		hit_height2;

	cone->s_cone.min = 0;
	cone->s_cone.max = 5;
	CO = ft_v3_sub(ray->origin, &cone->pos);
	cos_theta2 = cos(cone->s_cone.angle) * cos(cone->s_cone.angle);
	D_dot_A = ft_v3_dotprod(ray->direction, &cone->s_cone.normal);
	CO_dot_A = ft_v3_dotprod(CO, &cone->s_cone.normal);
	a = ft_v3_dotprod(ray->direction, ray->direction) - (cos_theta2 + 1)
		* (D_dot_A * D_dot_A);
	b = 2 * (ft_v3_dotprod(ray->direction, CO) - (cos_theta2 + 1) * D_dot_A
			* CO_dot_A);
	c = ft_v3_dotprod(CO, CO) - (cos_theta2 + 1) * (CO_dot_A * CO_dot_A);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);

	if (t1 > 0)
	{
		hit_height1 = CO_dot_A + t1 * D_dot_A;
		if ((hit_height1 >= cone->s_cone.min && hit_height1 <= cone->s_cone.max))
			return (t1);
	}
	// if (t2 > 0)
	// {
	// 	hit_height2 = CO_dot_A + t2 * D_dot_A;
	// 	if ((hit_height2 >= cone->s_cone.min && hit_height2 <= cone->s_cone.max))
	// 		return (t2);
	// }
	return (INFINITY);
}

int	ft_cone_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	*VP;
	t_vector3	*normal;
	float		projection;
	float		magnitude;
	float		angle;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	VP = ft_v3_sub(&hit->p, &hit->obj->pos);
	// Calculate the projection of VP onto the cone axis (normal)
	projection = ft_v3_dotprod(VP, &hit->obj->s_cone.normal);
	// Calculate magnitude of the vector from cone axis to surface
	magnitude = sqrt(ft_v3_dotprod(VP, VP) - (projection * projection));
	// Calculate angle of the cone
	angle = atan(magnitude / projection);
	// Calculate the normal at the hit point
	normal = ft_v3_sub(VP, ft_v3_scalar(&hit->obj->s_cone.normal, projection * (1 + (tan(angle) * tan(angle)))));
	ft_v3_normal_ip(normal);
	hit->n = *normal;
	return (1);
}
