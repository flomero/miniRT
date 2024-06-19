/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/19 14:27:03 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int		in_height(float t, t_object *cyl, t_ray *ray);
static void		get_t(float t[2], t_object *cyl, t_ray *ray);
static float	handle_zero(float abc[3], t_ray *ray, t_object *cyl);

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
	t_vector3	*v1;
	t_vector3	n_rd;
	t_vector3	*n_cy;
	float		abc[3];

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
	abc[0] = ft_v3_dotprod(&n_rd, &n_rd);
	abc[1] = 2 * ft_v3_dotprod(&n_rd, v1);
	abc[2] = (ft_v3_dotprod(v1, v1) - pow((cyl->s_cylinder.diameter / 2), 2));
	t[0] = handle_zero(abc, ray, cyl);
	if ((abc[1] * abc[1] - 4 * abc[0] * abc[2]) < 0 || abc[0] <= 0)
		return ;
	t[0] = (-abc[1] + sqrt(abc[1] * abc[1] - 4 * abc[0] * abc[2]))
	/ (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(abc[1] * abc[1] - 4 * abc[0] * abc[2]))
	/ (2 * abc[0]);
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
	t_vector3	*oc;
	t_vector3	*projection;
	t_vector3	*normal;

	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	oc = ft_v3_sub(&hit->p, &hit->obj->pos);
	projection = ft_v3_scalar(&hit->obj->s_cylinder.normal, ft_v3_dotprod(oc,
				&hit->obj->s_cylinder.normal));
	normal = ft_v3_sub(oc, projection);
	hit->n = *ft_v3_normal(normal);
	free(oc);
	free(projection);
	free(normal);
	return (1);
}
