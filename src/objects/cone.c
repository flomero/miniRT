
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
	t_vector3	tmp;
	float		projec;
	float		magnitude;
	float		angle;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&hit->n, hit->p.x, hit->p.y, hit->p.z);
	ft_v3_sub_ip(&hit->n, &hit->obj->pos);
	projec = ft_v3_dotprod(&hit->n, &hit->obj->s_cone.normal);
	magnitude = sqrt(ft_v3_dotprod(&hit->n, &hit->n) - (projec * projec));
	angle = atan(magnitude / projec);
	ft_v3_init(&tmp, hit->obj->s_cone.normal.x, hit->obj->s_cone.normal.y, \
	hit->obj->s_cone.normal.z);
	ft_v3_scalar_ip(&tmp, projec * (1 + (tan(angle) * tan(angle))));
	ft_v3_sub_ip(&hit->n, &tmp);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
