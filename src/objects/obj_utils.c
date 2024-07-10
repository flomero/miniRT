/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:46:05 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/10 10:48:32 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Get the min object, return the minimum double value
 *
 * @param t1
 * @param t2
 * @param t3
 * @param t4
 * @return double, skip INFINITY values except if every value is INFINITY then
 * return INFINITY
 */
double	get_min(double t1, double t2, double t3, double t4)
{
	double		t[4];
	int			i;
	double		min;

	t[0] = t1;
	t[1] = t2;
	t[2] = t3;
	t[3] = t4;
	min = INFINITY;
	i = -1;
	while (++i < 4)
		if (t[i] != INFINITY)
			min = t[i];
	i = -1;
	while (++i < 4)
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
double	hit_top_bot(t_object *plane, t_ray *ray, const double radius, t_object \
*cyl)
{
	double		t;
	t_vector3	tmp;
	double		tmp_z;
	double		d2;

	tmp_z = ray->origin->z;
	if (cyl->s_cylinder.normal.x == 0 && cyl->s_cylinder.normal.y == 0)
		ray->origin->z = 0;
	t = ft_plane_hit(plane, ray);
	if (t < 0)
	{
		ray->origin->z = tmp_z;
		return (INFINITY);
	}
	ft_v3_init(&tmp, ray->dir->x, ray->dir->y, ray->dir->z);
	ft_v3_scalar_ip(&tmp, t);
	ft_v3_add_ip(&tmp, ray->origin);
	ft_v3_sub_ip(&tmp, &plane->pos);
	ray->origin->z = tmp_z;
	d2 = ft_v3_len(&tmp);
	if (d2 <= radius)
		return (t);
	return (INFINITY);
}
