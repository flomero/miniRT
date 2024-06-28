/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:45:47 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/28 16:56:00 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_radius(float *t, t_ray *ray, t_object *disk_pl, float radius)
{
	t_vector3	pos;
	float	len;

	pos = *ft_v3_add(ray->origin, ft_v3_scalar(ray->direction, *t));
	len = sqrt(ft_v3_dotprod(ft_v3_sub(&disk_pl->pos, &pos), ft_v3_sub(&disk_pl->pos, &pos)));
	if (len >= radius)
		return (false);
	return (true);
}

bool	intersect_disk(t_ray *ray, t_object *disk_pl, float *t, float radius)
{
	float	denominator;
	t_vector3	point_to_origin;
	float	tmp;

	denominator = ft_v3_dotprod(&disk_pl->s_plane.normal, ray->direction);
	if (fabs(denominator) < 1e-16)
		return (false);
	point_to_origin = *ft_v3_sub(&disk_pl->pos, ray->origin);
	tmp = ft_v3_dotprod(&point_to_origin, &disk_pl->s_plane.normal) / denominator;
	if (tmp >= 0 && check_radius(&tmp, ray, disk_pl, radius))
	{
		if (tmp < *t)
			*t = tmp;
		return (true);
	}
	return (false);
}

void	make_helper_plane(t_object *cylinder, t_object *to_init_pl, bool is_top)
{
	t_vector3	center;
	t_vector3	normal;

	normal = cylinder->s_cylinder.normal;
	center = cylinder->pos;
	if (is_top == true)
		center = *ft_v3_add(&cylinder->pos, ft_v3_scalar(&normal,
					cylinder->s_cylinder.height));
	*to_init_pl = (t_object){
		.pos = center,
		.s_plane.normal = normal,
		.color = cylinder->color,
	};
}

bool	intersect_plane(t_ray *ray, t_object *plane, float *t)
{
	float		denominator;
	t_vector3	point_to_origin;

	denominator = ft_v3_dotprod(&plane->s_plane.normal, ray->direction);
	if (fabs(denominator) < 1e-16)
		return (false);
	point_to_origin = *ft_v3_sub(&plane->pos, ray->origin);
	*t = ft_v3_dotprod(&point_to_origin, &plane->s_plane.normal) / denominator;
	if (*t < 0)
		return (false);
	return (true);
}

float	vec_len(t_vector3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector3	vec_unit(t_vector3 a)
{
	float		length;
	t_vector3	res;

	length = vec_len(a);
	if (length == 0)
	{
		return ((t_vector3){0.f, 0.f, 0.f});
	}
	res.x = a.x / length;
	res.y = a.y / length;
	res.z = a.z / length;
	return (res);
}

static bool	solve_quadratic_siuuu(float *coefficients, float *t0, float *t1)
{
	float	discriminant;
	float	sqrt_disc;
	float	a;
	float	b;
	float	c;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrtf(discriminant);
	*t0 = (-b - sqrt_disc) / (2 * a);
	*t1 = (-b + sqrt_disc) / (2 * a);
	return (true);
}

static void	calculate_coefficients(t_ray *ray, t_object *cy, float *coeffs)
{
	t_vector3	delta_p;
	float		dp_axis;
	float		rd_axis;
	float		radius;

	radius = cy->s_cylinder.diameter / 2;
	delta_p = *ft_v3_sub(ray->origin, &cy->pos);
	dp_axis = ft_v3_dotprod(&delta_p, &cy->s_cylinder.normal);
	rd_axis = ft_v3_dotprod(ray->direction, &cy->s_cylinder.normal);
	coeffs[0] = ft_v3_dotprod(ray->direction, ray->direction) - powf(rd_axis,
			2);
	coeffs[1] = 2 * (ft_v3_dotprod(ray->direction, &delta_p) - rd_axis
			* dp_axis);
	coeffs[2] = ft_v3_dotprod(&delta_p, &delta_p) - powf(dp_axis, 2)
		- powf(radius, 2);
}

static bool	calc_hit(t_ray *ray, t_object *cy, float dist, float *t)
{
	t_vector3	hit_point;
	float		dist_to_cap;

	hit_point = *ft_v3_add(ray->origin, ft_v3_scalar(ray->direction, dist));
	dist_to_cap = ft_v3_dotprod(ft_v3_sub(&hit_point, &cy->pos),
			&cy->s_cylinder.normal);
	if (dist_to_cap >= 0 && dist_to_cap <= cy->s_cylinder.height)
	{
		if (dist < *t)
			*t = dist;
		return (true);
	}
	return (false);
}

static bool	check_cy_body(t_ray *ray, t_object *cy, float *coeffs, float *t)
{
	float	t0;
	float	t1;
	float	tmp;
	bool	hit0_valid;
	bool	hit1_valid;

	tmp = INFINITY;
	hit0_valid = false;
	hit1_valid = false;
	if (!solve_quadratic_siuuu(coeffs, &t0, &t1))
		return (false);
	hit0_valid = calc_hit(ray, cy, t0, &tmp);
	hit1_valid = calc_hit(ray, cy, t1, &tmp);
	if (hit0_valid || hit1_valid)
	{
		*t = tmp;
		return (true);
	}
	return (false);
}

bool	intersect_object(t_ray *ray, t_object *cylinder, float *t)
{
	float		coefficients[3];
	t_object	tmp;
	t_object	bottom_pl;
	t_object	top_pl;
	bool		hits[3];

	tmp = *cylinder;
	tmp.s_cylinder.normal = vec_unit(cylinder->s_cylinder.normal);
	make_helper_plane(&tmp, &bottom_pl, false);
	make_helper_plane(&tmp, &top_pl, true);
	calculate_coefficients(ray, &tmp, coefficients);
	hits[0] = check_cy_body(ray, &tmp, coefficients, t);
	hits[1] = intersect_disk(ray, &bottom_pl, t, cylinder->s_cylinder.diameter
			/ 2);
	hits[2] = intersect_disk(ray, &top_pl, t, cylinder->s_cylinder.diameter
			/ 2);
	return (hits[0] || hits[1] || hits[2]);
}

double	ft_cylinder_hit(t_object *cyl, t_ray *ray)
{
	float	t;

	if (intersect_object(ray, cyl, &t))
		return (t);
	return (INFINITY);
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
	ft_v3_scalar_ip(&norm, ft_v3_dotprod(&hit->n,
			&hit->obj->s_cylinder.normal));
	ft_v3_sub_ip(&hit->n, &norm);
	ft_v3_normal_ip(&hit->n);
	return (1);
}
