/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:33:50 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/13 11:13:33 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Checks if a ray hits a plane.
 *
 * @param plane The plane to check.
 * @param ray The ray to check.
 * @return The distance to the hit point or INFINITY if no hit.
 */
float	ft_plane_hit(t_object *plane, t_ray *ray)
{
	int		d_plane;
	float	t;
	float	distance;

	d_plane = -1 * (plane->pos.x * plane->s_plane.normal.x
			+ plane->pos.y * plane->s_plane.normal.y
			+ plane->pos.z * plane->s_plane.normal.z);
	t = -1 * (plane->pos.x * ray->origin->x
			+ plane->pos.y * ray->origin->y
			+ plane->pos.z * ray->origin->z + d_plane)
		/ (plane->s_plane.normal.x * ray->direction->x
			+ plane->s_plane.normal.y * ray->direction->y
			+ plane->s_plane.normal.z * ray->direction->z);
	if (t < 0)
		return (INFINITY);
	distance = sqrt(ray->direction->x * ray->direction->x
			+ ray->direction->y * ray->direction->y
			+ ray->direction->z * ray->direction->z) * t;
	// printf ("\nT is: %f, x: %f, y: %f, z: %f\n", t, ray->direction->x, ray->direction->y, ray->direction->z);
	return (fabs(distance));
}
