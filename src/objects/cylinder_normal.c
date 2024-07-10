/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:53:13 by flfische          #+#    #+#             */
/*   Updated: 2024/07/10 10:48:32 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	hit_disks(t_ray *ray, t_object *cylinder, double *t, t_hit *hit)
{
	t_object	top_bot[2];
	double		t_tmp;
	t_vector3	norm;
	int			disk_hit;

	disk_hit = 0;
	get_plane(cylinder, &top_bot[1], false);
	get_plane(cylinder, &top_bot[0], true);
	t_tmp = INFINITY;
	if (inter_disk(ray, &top_bot[1], &t_tmp, cylinder->s_cylinder.diameter / 2))
		if (t_tmp >= *t - EPSILON && t_tmp <= *t + EPSILON)
			disk_hit = 2;
	if (inter_disk(ray, &top_bot[0], &t_tmp, cylinder->s_cylinder.diameter / 2))
		if (t_tmp >= *t - EPSILON && t_tmp <= *t + EPSILON)
			disk_hit = 1;
	if (!disk_hit)
		return (0);
	ft_v3_init(&norm, cylinder->s_cylinder.normal.x,
		cylinder->s_cylinder.normal.y, cylinder->s_cylinder.normal.z);
	ft_v3_normal_ip(&norm);
	ft_v3_init(&hit->n, norm.x, norm.y, norm.z);
	if (disk_hit == 2)
		ft_v3_scalar_ip(&hit->n, -1);
	return (disk_hit);
}

int	ft_cylinder_normal(t_hit *hit, t_ray *ray)
{
	int			disk_hit;
	double		len;
	t_vector3	hit_to_center;
	t_vector3	proj_hit;

	ft_v3_init(&hit->p, ray->origin->x + ray->dir->x * hit->t,
		ray->origin->y + ray->dir->y * hit->t, ray->origin->z
		+ ray->dir->z * hit->t);
	disk_hit = hit_disks(ray, hit->obj, &hit->t, hit);
	if (disk_hit)
		return (1);
	ft_v3_init(&hit_to_center, hit->p.x - hit->obj->pos.x, hit->p.y
		- hit->obj->pos.y, hit->p.z - hit->obj->pos.z);
	len = ft_v3_dotprod(&hit_to_center, &hit->obj->s_cylinder.normal);
	proj_hit.x = hit_to_center.x - len * hit->obj->s_cylinder.normal.x;
	proj_hit.y = hit_to_center.y - len * hit->obj->s_cylinder.normal.y;
	proj_hit.z = hit_to_center.z - len * hit->obj->s_cylinder.normal.z;
	ft_v3_normal_ip(&proj_hit);
	if (ft_v3_dotprod(&proj_hit, ray->dir) > 0)
		ft_v3_scalar_ip(&proj_hit, -1);
	ft_v3_init(&hit->n, proj_hit.x, proj_hit.y, proj_hit.z);
	return (1);
}
