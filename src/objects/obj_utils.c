/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:46:05 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/20 12:50:46 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Get the min object, return the minimum float value
 *
 * @param t1
 * @param t2
 * @param t3
 * @param t4
 * @return float, skip INFINITY values except if every value is INFINITY then
 * return INFINITY
 */
float	get_min(float t1, float t2, float t3, float t4)
{
	const int	size = 4;
	float		t[size];
	int			i;
	float		min;

	t[0] = t1;
	t[1] = t2;
	t[2] = t3;
	t[3] = t4;
	min = INFINITY;
	i = -1;
	while (++i < size)
		if (t[i] != INFINITY)
			min = t[i];
	i = -1;
	while (++i < size)
		if (t[i] < min && t[i] != INFINITY)
			min = t[i];
	return (min);
}

/**
 * @brief Check if the hit point hits top or bottom plane of a cylinder.
 *
 * @param t The distance to the hit point.
 * @param cyl The current cylinder.
 * @param ray The current ray.
 * @return int 1 if the hit point is in the height, 0 otherwise.
 */
static double	hit_top_bot(t_object *obj, t_ray *ray, const double radius)
{
	double	t;
	t_vector3	*p;
	t_vector3	*v;
	double	d2;

	t = ft_plane_hit(obj, ray);
	if (t < 0)
		return (INFINITY);
	p = ft_v3_add(ray->origin, ft_v3_scalar(ray->direction, t));
	v = ft_v3_sub(p, &obj->pos);
	d2 = ft_v3_len(v);
	if (d2 <= radius)
		return (t);
	return (INFINITY);
}
