/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:33:50 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/10 10:48:32 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
	Maths for plane:
	Plane equation: Ax + By + Cz + D = 0
		- A, B and C are s_plane.normal.x,y,z
		- We calculate D by using by replacing x, y, z and A, B, C
		- x, y, z is the position of the random point in the plane
		plane->pos.x,y,z
	Ray equation:
		- P = R + t⋅d
		- P is the point on ray
		- R is the origin of the ray(camera.pos = ray.origin, identical)
		- t is the distance from the origin to the point(random positive number)
		- d is the direction of the ray, ray.direction like (4, 2, 1)
	For intersaction:
		- we take plane equation and replace x, y, z with ray equation
		- if we find solution for that, that means the point is on both ray and
		plane
		- so we calculate t, if t < 0 -> no solution, if t > 0 -> solution
		and if t == 0 -> the ray is on the plane's border
		- at the end if there is solution, we calculate the distance from
		origin to the hit point because at the very end only the obj with
		minimum distance for this ray does matter
		- if divisor == 0, means plane is parallel to ray, no hit
*/
/**
 * Checks if a ray hits a plane.
 *
 * @param plane The plane to check.
 * @param ray The ray to check.
 * @return The distance to the hit point or INFINITY if no hit.
 */
double	ft_plane_hit(t_object *plane, t_ray *ray)
{
	double	d_plane;
	double	t;
	double	divisor;

	d_plane = -(plane->pos.x * plane->s_plane.normal.x + plane->pos.y
			* plane->s_plane.normal.y + plane->pos.z * plane->s_plane.normal.z);
	divisor = (plane->s_plane.normal.x * ray->dir->x
			+ plane->s_plane.normal.y * ray->dir->y
			+ plane->s_plane.normal.z * ray->dir->z);
	if (fabs(divisor) < EPSILON)
		return (INFINITY);
	t = -(plane->s_plane.normal.x * ray->origin->x + plane->s_plane.normal.y
			* ray->origin->y + plane->s_plane.normal.z * ray->origin->z
			+ d_plane) / divisor;
	if (t < 0)
		return (INFINITY);
	return (t);
}

int	ft_plane_normal(t_hit *hit, t_ray *ray)
{
	ft_v3_init(&hit->p, ray->origin->x + ray->dir->x * hit->t,
		ray->origin->y + ray->dir->y * hit->t, ray->origin->z
		+ ray->dir->z * hit->t);
	ft_v3_init(&hit->n, hit->obj->s_plane.normal.x, hit->obj->s_plane.normal.y,
		hit->obj->s_plane.normal.z);
	ft_v3_normal_ip(&hit->n);
	if (ft_v3_dotprod(&hit->n, ray->dir) > 0)
		ft_v3_scalar_ip(&hit->n, -1);
	return (1);
}
