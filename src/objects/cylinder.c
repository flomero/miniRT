/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:39:55 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/17 11:53:41 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	in_height(float t, t_object *cyl, t_ray *ray);
static		t_vector3 *vector_normalize(t_vector3 *v);

float	ft_cylinder_hit(t_object *cyl, t_ray *ray)
{
	float		r;
	t_vector3	*oc;
	t_vector3	*temp1;
	t_vector3	*temp2;
	float		a,b,c;
	float		discriminant;
	float		t[2];

	ray->direction = vector_normalize(ray->direction);
	cyl->s_cylinder.normal = *vector_normalize(&cyl->s_cylinder.normal);
	r = cyl->s_cylinder.diameter / 2;
	oc = ft_v3_sub(ray->origin, &cyl->pos);
	temp1 = ft_v3_sub(ray->direction, ft_v3_scalar(&cyl->s_cylinder.normal, ft_v3_dotprod(ray->direction, &cyl->s_cylinder.normal)));
	temp2 = ft_v3_sub(oc, ft_v3_scalar(&cyl->s_cylinder.normal, ft_v3_dotprod(oc, &cyl->s_cylinder.normal)));
	a = ft_v3_dotprod(temp1, temp1);
	b = 2 * ft_v3_dotprod(temp1, temp2);
	c = ft_v3_dotprod(temp2, temp2) - (r * r);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	t[0] = (-b + sqrt(discriminant)) / (2 * a);
	t[1] = (-b - sqrt(discriminant)) / (2 * a);
	if (!in_height(t[0], cyl, ray) && !in_height(t[1], cyl, ray))
		return (INFINITY);
	if (in_height(t[0], cyl, ray) && in_height(t[1], cyl, ray))
	{
		if (t[0] < t[1])
			return (t[0]);
		return (t[1]);
	}
	if (in_height(t[0], cyl, ray))
		return (t[0]);
	return (t[1]);
}

static int	in_height(float t, t_object *cyl, t_ray *ray)
{
	t_vector3	*temp2;
	float		height_pos;

	if (t < 0)
		return (0);
	temp2 = ft_v3_add(ray->origin, ft_v3_scalar(ray->direction, t));
	height_pos = ft_v3_dotprod(ft_v3_sub(temp2, &cyl->pos), &cyl->s_cylinder.normal);
	if (height_pos >= 0 && height_pos <= cyl->s_cylinder.height)
		return (1);
	return (0);
}

static t_vector3	*vector_normalize(t_vector3 *v)
{
	float	length;

	length = ft_v3_len(v);
	if (length != 0)
		return (ft_v3_scalar(v, 1.0f / length));
	return (v);
}
