/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:33:39 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/01 11:04:15 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	in_radius(double *t, t_ray *ray, t_object *disk_pl, double radius)
{
	t_vector3	pos;
	t_vector3	sub;
	double		len;

	ft_v3_init(&pos, ray->origin->x + ray->direction->x * *t, ray->origin->y
		+ ray->direction->y * *t, ray->origin->z + ray->direction->z * *t);
	ft_v3_init(&sub, disk_pl->pos.x - pos.x, disk_pl->pos.y - pos.y,
		disk_pl->pos.z - pos.z);
	len = sqrt(ft_v3_dotprod(&sub, &sub));
	if (len >= radius)
		return (false);
	return (true);
}

bool	inter_disk(t_ray *ray, t_object *disk_pl, double *t, double radius)
{
	double		d;
	t_vector3	po;
	double		tmp;

	d = ft_v3_dotprod(&disk_pl->s_plane.normal, ray->direction);
	if (fabs(d) < 1e-16)
		return (false);
	ft_v3_init(&po, disk_pl->pos.x - ray->origin->x, disk_pl->pos.y
		- ray->origin->y, disk_pl->pos.z - ray->origin->z);
	tmp = ft_v3_dotprod(&po, &disk_pl->s_plane.normal) / d;
	if (tmp >= 0 && in_radius(&tmp, ray, disk_pl, radius))
	{
		if (tmp < *t)
			*t = tmp;
		return (true);
	}
	return (false);
}

void	get_plane(t_object *cylinder, t_object *to_init_pl, bool is_top)
{
	t_vector3	center;
	t_vector3	normal;

	normal = cylinder->s_cylinder.normal;
	if (!is_top)
		ft_v3_scalar_ip(&normal, -1);
	center = cylinder->pos;
	if (is_top == true)
	{
		ft_v3_init(&center, normal.x * cylinder->s_cylinder.height, normal.y
			* cylinder->s_cylinder.height, normal.z
			* cylinder->s_cylinder.height);
		ft_v3_add_ip(&center, &cylinder->pos);
	}
	ft_v3_init(&to_init_pl->pos, center.x, center.y, center.z);
	ft_v3_init(&to_init_pl->s_plane.normal, normal.x, normal.y, normal.z);
}

bool	is_sol_equation(double *abc, double *t0, double *t1)
{
	double	d;
	double	sqrt_disc;

	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < 0)
		return (false);
	sqrt_disc = sqrtf(d);
	if (abc[0] == 0)
		return (false);
	*t0 = (-abc[1] - sqrt_disc) / (2 * abc[0]);
	*t1 = (-abc[1] + sqrt_disc) / (2 * abc[0]);
	return (true);
}
