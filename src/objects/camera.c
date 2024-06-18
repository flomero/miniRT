/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:24:49 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 15:16:23 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Calculates the lower left corner of the camera.
 *
 * @param camera The camera object.
 * @return The lower left corner.
 */
static t_vector3	*calc_lower_left_corner(t_object *camera)
{
	t_vector3	*ll_corner;
	t_vector3	u;
	t_vector3	v;
	t_vector3	w;

	ft_v3_init(&w, camera->pos.x - camera->s_camera.look_at->x, camera->pos.y
		- camera->s_camera.look_at->y, camera->pos.z
		- camera->s_camera.look_at->z);
	ft_v3_normal_ip(&w);
	if (fabs(w.y) == 1.0)
		ft_v3_init(&u, 0.0, 0.0, 1.0);
	else
		ft_v3_init(&u, 0.0, 1.0, 0.0);
	ft_v3_crossprod_ip(&u, &w);
	ft_v3_normal_ip(&u);
	ft_v3_init(&v, w.x, w.y, w.z);
	ft_v3_crossprod_ip(&v, &u);
	ll_corner = ft_v3_new(camera->pos.x, camera->pos.y, camera->pos.z);
	camera->s_camera.horizontal = ft_v3_scalar(&u, camera->s_camera.vp_width);
	camera->s_camera.vertical = ft_v3_scalar(&v, camera->s_camera.vp_height);
	ft_v3_scalar_ip(&u, camera->s_camera.vp_width / 2.0);
	ft_v3_scalar_ip(&v, camera->s_camera.vp_height / 2.0);
	ft_v3_sub_ip(ft_v3_sub_ip(ft_v3_sub_ip(ll_corner, &u), &v), &w);
	return (ll_corner);
}

/**
 * Calculates the viewport of the camera.
 *
 * @param camera The camera object.
 */
void	ft_calculate_viewport(t_object *camera)
{
	float		aspect_ratio;
	float		theta;
	t_vector3	temp_vec;

	camera->s_camera.focal_length = FOCAL_LENGTH;
	aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	camera->s_camera.look_at = ft_v3_new(camera->pos.x, camera->pos.y,
			camera->pos.z);
	ft_v3_init(&temp_vec, camera->s_camera.normal.x, camera->s_camera.normal.y,
		camera->s_camera.normal.z);
	ft_v3_scalar_ip(&temp_vec, camera->s_camera.focal_length);
	ft_v3_add_ip(camera->s_camera.look_at, &temp_vec);
	theta = camera->s_camera.fov * M_PI / 180.0;
	camera->s_camera.vp_height = 2.0 * tan(theta / 2.0);
	camera->s_camera.vp_width = aspect_ratio * camera->s_camera.vp_height;
	camera->s_camera.ll_corner = calc_lower_left_corner(camera);
}
