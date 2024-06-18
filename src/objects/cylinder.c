/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/18 15:26:50 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		in_height(float t, t_object *cyl, t_ray *ray);
// static t_vector3	*vector_normalize(t_vector3 *v);
static void		get_t(float t[2], t_object *cyl, t_ray *ray);
static float	handle_zero(float b, float c, t_ray *ray, t_object *cyl);

float	ft_cylinder_hit(t_object *cyl, t_ray *ray)
{
	float	t[2];

	t[0] = INFINITY;
	t[1] = INFINITY;
	get_t(t, cyl, ray);
	if (!in_height(t[0], cyl, ray) && !in_height(t[1], cyl, ray))
		return (INFINITY);
	if (in_height(t[0], cyl, ray) && in_height(t[1], cyl, ray) && t[0] > t[1])
		t[0] = t[1];
	if (in_height(t[0], cyl, ray))
		return (t[0]);
	return (t[1]);
}

static void	get_t(float t[2], t_object *cyl, t_ray *ray)
{
	t_vector3	*temp1;
	t_vector3	*temp2;
	t_vector3	normalized_raydir;
	float		a;
	float		b;
	float		c;

	ft_v3_init(&normalized_raydir, ray->direction->x, ray->direction->y,
		ray->direction->z);
	ft_v3_normal_ip(&normalized_raydir);
	ft_v3_normal_ip(&cyl->s_cylinder.normal);
	temp1 = ft_v3_sub(&normalized_raydir, ft_v3_scalar(&cyl->s_cylinder.normal,
				ft_v3_dotprod(&normalized_raydir, &cyl->s_cylinder.normal)));
	temp2 = ft_v3_sub(ft_v3_sub(ray->origin, &cyl->pos),
			ft_v3_scalar(&cyl->s_cylinder.normal,
				ft_v3_dotprod(ft_v3_sub(ray->origin, &cyl->pos),
					&cyl->s_cylinder.normal)));
	a = ft_v3_dotprod(temp1, temp1);
	b = 2 * ft_v3_dotprod(temp1, temp2);
	c = (ft_v3_dotprod(temp2, temp2) - ((cyl->s_cylinder.diameter / 2)
				* (cyl->s_cylinder.diameter / 2)));
	if (a == 0)
		t[0] = handle_zero(b, c, ray, cyl);
	c = b * b - 4 * a * c;
	if (c < 0 || a < 0)
		return ;
	t[0] = (-b + sqrt(c)) / (2 * a);
	t[1] = (-b - sqrt(c)) / (2 * a);
}

static float	handle_zero(float b, float c, t_ray *ray, t_object *cyl)
{
	float		t[2];
	t_vector3	*temp1;

	if (b == 0)
		return (INFINITY);
	else
	{
		t[0] = -c / b;
		if (t < 0)
			return (INFINITY);
		temp1 = ft_v3_add(ray->origin, ft_v3_scalar(ray->direction, t[0]));
		t[1] = ft_v3_dotprod(ft_v3_sub(temp1, &cyl->pos),
				&cyl->s_cylinder.normal);
		if (t[1] >= 0 && t[1] <= cyl->s_cylinder.height)
			return (t[0]);
	}
	return (INFINITY);
}

static int	in_height(float t, t_object *cyl, t_ray *ray)
{
	t_vector3	*temp2;
	float		hei_p;

	if (t < 0)
		return (0);
	temp2 = ft_v3_add(ray->origin, ft_v3_scalar(ray->direction, t));
	hei_p = ft_v3_dotprod(ft_v3_sub(temp2, &cyl->pos), &cyl->s_cylinder.normal);
	if (hei_p >= 0 && hei_p <= cyl->s_cylinder.height)
		return (1);
	return (0);
}

// static t_vector3	*vector_normalize(t_vector3 *v)
// {
// 	float	length;

// 	length = ft_v3_len(v);
// 	if (length != 0)
// 		return (ft_v3_scalar(v, 1.0f / length));
// 	return (v);
// }

int	ft_cylinder_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	hit_point;
	t_vector3	object_center_to_hit;

	ft_v3_init(&hit_point, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&object_center_to_hit, hit_point.x - hit->obj->pos.x, 0,
		hit_point.z - hit->obj->pos.z);
	ft_v3_normal_ip(&object_center_to_hit);
	ft_v3_init(&hit->n, object_center_to_hit.x, 0, object_center_to_hit.z);
	return (1);
}
