/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/25 15:57:25 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		in_height(float t, t_object *cyl, t_ray *ray);
static void		get_t(float t[2], t_object *cyl, t_ray *ray);
static float	handle_zero(float abc[3], t_ray *ray, t_object *cyl);

float	ft_cylinder_hit(t_object *cyl, t_ray *ray)
{
	float		t[4];
	t_object	plane;
	t_vector3	tmp;
	int			i;

	i = -1;
	while (++i < 4)
		t[i] = INFINITY;
	get_t(t, cyl, ray);
	ft_v3_init(&plane.s_plane.normal, cyl->s_cylinder.normal.x, \
	cyl->s_cylinder.normal.y, cyl->s_cylinder.normal.z);
	ft_v3_init(&tmp, cyl->s_cylinder.normal.x, cyl->s_cylinder.normal.y, \
	cyl->s_cylinder.normal.z);
	ft_v3_scalar_ip(&tmp, cyl->s_cylinder.height);
	ft_v3_init(&plane.pos, tmp.x, tmp.y, tmp.z);
	ft_v3_add_ip(&plane.pos, &cyl->pos);
	t[2] = hit_top_bot(&plane, ray, cyl->s_cylinder.diameter / 2);
	ft_v3_scalar_ip(&plane.s_plane.normal, -1);
	plane.pos = cyl->pos;
	t[3] = hit_top_bot(&plane, ray, cyl->s_cylinder.diameter / 2);
	i = -1;
	while (++i < 4)
		if (!in_height(t[i], cyl, ray))
			t[i] = INFINITY;
	return (get_min(t[0], t[1], t[2], t[3]));
}

static void	get_t(float t[3], t_object *cyl, t_ray *ray)
{
	t_vector3	t1;
	t_vector3	t2;
	t_vector3	n_rd;
	float		ac[3];

	ft_v3_init(&n_rd, ray->direction->x, ray->direction->y, ray->direction->z);
	ft_v3_normal_ip(&n_rd);
	ft_v3_init(&t1, cyl->s_cylinder.normal.x, cyl->s_cylinder.normal.y, \
	cyl->s_cylinder.normal.z);
	ft_v3_normal_ip(&t1);
	ft_v3_init(&t2, t1.x, t1.y, t1.z);
	ft_v3_scalar_ip(&t2, ft_v3_dotprod(&n_rd, &t1));
	ft_v3_sub_ip(&n_rd, &t2);
	ft_v3_init(&t2, ray->origin->x, ray->origin->y, ray->origin->z);
	ft_v3_sub_ip(&t2, &cyl->pos);
	ft_v3_scalar_ip(&t1, ft_v3_dotprod(&t2, &t1));
	ft_v3_sub_ip(&t2, &t1);
	ac[0] = ft_v3_dotprod(&n_rd, &n_rd);
	ac[1] = 2 * ft_v3_dotprod(&n_rd, &t2);
	ac[2] = (ft_v3_dotprod(&t2, &t2) - pow((cyl->s_cylinder.diameter / 2), 2));
	t[0] = handle_zero(ac, ray, cyl);
	if ((ac[1] * ac[1] - 4 * ac[0] * ac[2]) < 0 || ac[0] <= 0)
		return ;
	t[0] = (-ac[1] + sqrt(ac[1] * ac[1] - 4 * ac[0] * ac[2])) / (2 * ac[0]);
	t[1] = (-ac[1] - sqrt(ac[1] * ac[1] - 4 * ac[0] * ac[2])) / (2 * ac[0]);
}

static float	handle_zero(float abc[3], t_ray *ray, t_object *cyl)
{
	float		t[2];
	t_vector3	temp;
	t_vector3	temp2;

	if (abc[0] != 0 || abc[1] == 0)
		return (INFINITY);
	t[0] = -abc[2] / abc[1];
	if (t[0] < 0)
		return (INFINITY);
	ft_v3_init(&temp, ray->origin->x + ray->direction->x * t[0],
		ray->origin->y + ray->direction->y * t[0], ray->origin->z
		+ ray->direction->z * t[0]);
	ft_v3_sub_ip(&temp, &cyl->pos);
	ft_v3_init(&temp2, cyl->s_cylinder.normal.x, cyl->s_cylinder.normal.y, \
	cyl->s_cylinder.normal.z);
	ft_v3_normal_ip(&temp2);
	t[1] = ft_v3_dotprod(&temp, &temp2);
	if (t[1] >= 0 && t[1] <= cyl->s_cylinder.height)
		return (t[0]);
	return (INFINITY);
}

static int	in_height(float t, t_object *cyl, t_ray *ray)
{
	t_vector3	temp;
	t_vector3	temp2;
	float		hei_p;

	if (t < 0)
		return (0);
	ft_v3_init(&temp, ray->direction->x * t + ray->origin->x, \
	ray->direction->y * t + ray->origin->y, \
	ray->direction->z * t + ray->origin->z);
	ft_v3_sub_ip(&temp, &cyl->pos);
	ft_v3_init(&temp2, cyl->s_cylinder.normal.x, cyl->s_cylinder.normal.y, \
	cyl->s_cylinder.normal.z);
	ft_v3_normal_ip(&temp2);
	hei_p = ft_v3_dotprod(&temp, &temp2);
	if (hei_p >= 0 && hei_p <= cyl->s_cylinder.height)
		return (1);
	return (0);
}

int	ft_cylinder_normal(t_hit *hit, t_ray *ray)
{
	t_vector3	norm;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&hit->n, hit->p.x, hit->p.y, hit->p.z);
	ft_v3_sub_ip(&hit->n, &hit->obj->pos);
	ft_v3_init(&norm, hit->obj->s_cylinder.normal.x,
		hit->obj->s_cylinder.normal.y, hit->obj->s_cylinder.normal.z);
	ft_v3_scalar_ip(&norm, \
	ft_v3_dotprod(&hit->n, &hit->obj->s_cylinder.normal));
	ft_v3_sub_ip(&hit->n, &norm);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
