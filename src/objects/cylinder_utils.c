/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:33:39 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/28 17:43:32 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	in_radius(float *t, t_ray *ray, t_object *disk_pl, float radius)
{
	t_vector3	pos;
	t_vector3	sub;
	float		len;

	ft_v3_init(&pos, ray->origin->x + ray->direction->x * *t,
		ray->origin->y + ray->direction->y * *t, ray->origin->z
		+ ray->direction->z * *t);
	ft_v3_init(&sub, disk_pl->pos.x - pos.x, disk_pl->pos.y - pos.y,
		disk_pl->pos.z - pos.z);
	len = sqrt(ft_v3_dotprod(&sub, &sub));
	if (len >= radius)
		return (false);
	return (true);
}

bool	inter_disk(t_ray *ray, t_object *disk_pl, float *t, float radius)
{
	float		d;
	t_vector3	po;
	float		tmp;

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
	center = cylinder->pos;
	if (is_top == true)
	{
		ft_v3_init(&center, normal.x * cylinder->s_cylinder.height,
			normal.y * cylinder->s_cylinder.height,
			normal.z * cylinder->s_cylinder.height);
		center = *ft_v3_add_ip(&center, &cylinder->pos);
	}
	*to_init_pl = (t_object){
		.pos = center,
		.s_plane.normal = normal,
		.color = cylinder->color,
	};
}

bool	is_sol_equation(float *abc, float *t0, float *t1)
{
	float	d;
	float	sqrt_disc;
	float	a;
	float	b;
	float	c;

	a = abc[0];
	b = abc[1];
	c = abc[2];
	d = b * b - 4 * a * c;
	if (d < 0)
		return (false);
	sqrt_disc = sqrtf(d);
	if (a == 0)
		return (false);
	*t0 = (-b - sqrt_disc) / (2 * a);
	*t1 = (-b + sqrt_disc) / (2 * a);
	return (true);
}
