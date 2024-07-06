/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:52 by flfische          #+#    #+#             */
/*   Updated: 2024/07/06 14:21:51 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Checks if a ray hits a sphere.
 *
 * @param sphere The sphere to check.
 * @param ray The ray to check.
 * @return The distance to the hit point or INFINITY if no hit.
 */
double	ft_sphere_hit(t_object *sphere, t_ray *ray)
{
	t_vector3	oc;
	t_vector3	tmp;
	double		discriminant;

	ft_v3_init(&oc, ray->origin->x, ray->origin->y, ray->origin->z);
	ft_v3_sub_ip(&oc, &sphere->pos);
	tmp.x = ft_v3_dotprod(ray->direction, ray->direction);
	tmp.y = 2.0 * ft_v3_dotprod(&oc, ray->direction);
	tmp.z = ft_v3_dotprod(&oc, &oc) - (sphere->s_sphere.diameter / 2.0)
		* (sphere->s_sphere.diameter / 2.0);
	discriminant = tmp.y * tmp.y - 4.0 * tmp.x * tmp.z;
	if (discriminant < 0)
		return (INFINITY);
	return ((-tmp.y - sqrt(discriminant)) / (2.0 * tmp.x));
}

static int	ft_sphere_bump(t_hit *hit)
{
	mlx_texture_t	*tex;
	t_vector2		uv;
	t_vector2		uv_r;
	t_vector2		uv_d;
	t_vector3		height_pert[2];

	ft_sphere_uv(hit, &uv);
	tex = hit->obj->bump->s_bump.img;
	uv.x = fmod(uv.x * tex->width, tex->width);
	uv.y = fmod(uv.y * tex->height, tex->height);
	if (uv.x < 0)
		uv.x += tex->width;
	if (uv.y < 0)
		uv.y += tex->height;
	uv_r = (t_vector2){fmod(uv.x + 1, tex->width), uv.y};
	uv_d = (t_vector2){uv.x, fmod(uv.y + 1, tex->height)};
	height_pert[0] = (t_vector3){((ft_pixcol(tex, (int)uv.x, (int)uv.y,
					NULL) >> 24) & 0xFF) / 255.0, ((ft_pixcol(tex, (int)uv_r.x,
					(int)uv_r.y, NULL) >> 24) & 0xFF) / 255.0, ((ft_pixcol(tex,
					(int)uv_d.x, (int)uv_d.y, NULL) >> 24) & 0xFF) / 255.0};
	height_pert[1].x = (height_pert[0].y - height_pert[0].x) * BUMP_SCALE;
	height_pert[1].y = (height_pert[0].z - height_pert[0].x) * BUMP_SCALE;
	hit->n = (t_vector3){hit->n.x + height_pert[1].x, hit->n.y
		+ height_pert[1].y, hit->n.z};
	return (ft_v3_normal_ip(&hit->n), 1);
}

int	ft_sphere_normal(t_hit *hit, t_ray *ray)
{
	ft_v3_init(&hit->p, ray->origin->x + ray->direction->x * hit->t,
		ray->origin->y + ray->direction->y * hit->t, ray->origin->z
		+ ray->direction->z * hit->t);
	ft_v3_init(&hit->n, hit->p.x - hit->obj->pos.x, hit->p.y - hit->obj->pos.y,
		hit->p.z - hit->obj->pos.z);
	ft_v3_normal_ip(&hit->n);
	ft_v3_init(&hit->uvn, hit->n.x, hit->n.y, hit->n.z);
	if (hit->obj->bump_name[0])
		return (ft_sphere_bump(hit));
	return (1);
}

int	ft_sphere_uv(t_hit *hit, t_vector2 *uv)
{
	double		phi;
	double		theta;
	t_vector3	*normal;

	normal = &hit->uvn;
	phi = atan2(normal->z, normal->x);
	theta = asin(normal->y);
	uv->x = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	uv->y = (theta + M_PI / 2.0) / M_PI;
	return (1);
}
