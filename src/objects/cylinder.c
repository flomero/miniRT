/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/21 09:45:03 by klamprak         ###   ########.fr       */
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
	t_vector3	*tmp[2];
	int			i;

	i = -1;
	while (++i < 4)
		t[i] = INFINITY;
	get_t(t, cyl, ray);
	plane.type = PLANE;
	ft_v3_init(&plane.s_plane.normal, cyl->s_cylinder.normal.x, \
	cyl->s_cylinder.normal.y, cyl->s_cylinder.normal.z);
	tmp[0] = ft_v3_scalar(&cyl->s_cylinder.normal, cyl->s_cylinder.height);
	tmp[1] = ft_v3_add(&cyl->pos, tmp[0]);
	plane.pos = *tmp[1];
	t[2] = hit_top_bot(&plane, ray, cyl->s_cylinder.diameter / 2);
	ft_v3_scalar_ip(&plane.s_plane.normal, -1);
	plane.pos = cyl->pos;
	t[3] = hit_top_bot(&plane, ray, cyl->s_cylinder.diameter / 2);
	i = -1;
	while (++i < 4)
		if (!in_height(t[i], cyl, ray))
			t[i] = INFINITY;
	return (free(tmp[0]), free(tmp[1]), get_min(t[0], t[1], t[2], t[3]));
}

static void	get_t(float t[3], t_object *cyl, t_ray *ray)
{
	t_vector3	*v1;
	t_vector3	n_rd;
	t_vector3	*n_cy;
	float		ac[3];

	ft_v3_init(&n_rd, ray->direction->x, ray->direction->y, ray->direction->z);
	ft_v3_normal_ip(&n_rd);
	n_cy = ft_v3_normal(&cyl->s_cylinder.normal);
	v1 = ft_v3_scalar(n_cy, ft_v3_dotprod(&n_rd, n_cy));
	ft_v3_sub_ip(&n_rd, v1);
	free(v1);
	v1 = ft_v3_sub(ray->origin, &cyl->pos);
	ft_v3_scalar_ip(n_cy, ft_v3_dotprod(v1, n_cy));
	ft_v3_sub_ip(v1, n_cy);
	free(n_cy);
	ac[0] = ft_v3_dotprod(&n_rd, &n_rd);
	ac[1] = 2 * ft_v3_dotprod(&n_rd, v1);
	ac[2] = (ft_v3_dotprod(v1, v1) - pow((cyl->s_cylinder.diameter / 2), 2));
	free(v1);
	t[0] = handle_zero(ac, ray, cyl);
	if ((ac[1] * ac[1] - 4 * ac[0] * ac[2]) < 0 || ac[0] <= 0)
		return ;
	t[0] = (-ac[1] + sqrt(ac[1] * ac[1] - 4 * ac[0] * ac[2])) / (2 * ac[0]);
	t[1] = (-ac[1] - sqrt(ac[1] * ac[1] - 4 * ac[0] * ac[2])) / (2 * ac[0]);
}

static float	handle_zero(float abc[3], t_ray *ray, t_object *cyl)
{
	float		t[2];
	t_vector3	*temp1;
	t_vector3	*temp2;

	if (abc[0] != 0 || abc[1] == 0)
		return (INFINITY);
	t[0] = -abc[2] / abc[1];
	if (t[0] < 0)
		return (INFINITY);
	temp2 = ft_v3_scalar(ray->direction, t[0]);
	temp1 = ft_v3_add(ray->origin, temp2);
	ft_v3_sub_ip(temp1, &cyl->pos);
	free(temp2);
	temp2 = ft_v3_normal(&cyl->s_cylinder.normal);
	t[1] = ft_v3_dotprod(temp1, temp2);
	free(temp1);
	free(temp2);
	if (t[1] >= 0 && t[1] <= cyl->s_cylinder.height)
		return (t[0]);
	return (INFINITY);
}

static int	in_height(float t, t_object *cyl, t_ray *ray)
{
	t_vector3	*temp1;
	t_vector3	*temp2;
	float		hei_p;

	if (t < 0)
		return (0);
	temp1 = ft_v3_scalar(ray->direction, t);
	temp2 = ft_v3_add(ray->origin, temp1);
	free(temp1);
	ft_v3_sub_ip(temp2, &cyl->pos);
	temp1 = ft_v3_normal(&cyl->s_cylinder.normal);
	hei_p = ft_v3_dotprod(temp2, temp1);
	free(temp1);
	free(temp2);
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
	ft_v3_scalar_ip(&norm, ft_v3_dotprod(&hit->n, &hit->obj->s_cylinder.normal));
	ft_v3_sub_ip(&hit->n, &norm);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
