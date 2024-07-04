/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:24:49 by flfische          #+#    #+#             */
/*   Updated: 2024/07/04 15:29:23 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Calculates the lower left corner of the camera.
 *
 * @param cam The camera object.
 * @return The lower left corner.
 */
static t_vector3	*calc_lower_left_corner(t_object *cam)
{
	t_vector3	u;
	t_vector3	v;
	t_vector3	w;

	ft_v3_normal_ip(ft_v3_init(&w, cam->pos.x - cam->s_camera.look_at.x,
			cam->pos.y - cam->s_camera.look_at.y, cam->pos.z
			- cam->s_camera.look_at.z));
	if (fabs(w.y) == 1.0)
		ft_v3_init(&u, 0.0, 0.0, 1.0);
	else
		ft_v3_init(&u, 0.0, 1.0, 0.0);
	ft_v3_crossprod_ip(&u, &w);
	ft_v3_normal_ip(&u);
	ft_v3_init(&v, w.x, w.y, w.z);
	ft_v3_crossprod_ip(&v, &u);
	ft_v3_init(&cam->s_camera.ll_corner, cam->pos.x, cam->pos.y, cam->pos.z);
	ft_v3_init(&cam->s_camera.hor, u.x, u.y, u.z);
	ft_v3_scalar_ip(&cam->s_camera.hor, cam->s_camera.vp_width);
	ft_v3_init(&cam->s_camera.ver, v.x, v.y, v.z);
	ft_v3_scalar_ip(&cam->s_camera.ver, cam->s_camera.vp_height);
	ft_v3_scalar_ip(&u, cam->s_camera.vp_width / 2.0);
	ft_v3_scalar_ip(&v, cam->s_camera.vp_height / 2.0);
	ft_v3_sub_ip(ft_v3_sub_ip(ft_v3_sub_ip(&cam->s_camera.ll_corner, &u), &v),
		&w);
	return (&cam->s_camera.ll_corner);
}

/**
 * Calculates the viewport of the camera.
 *
 * @param camera The camera object.
 */
void	ft_calculate_viewport(t_object *camera)
{
	double		aspect_ratio;
	double		theta;
	t_vector3	temp_vec;

	camera->s_camera.focal_length = FOCAL_LENGTH;
	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	ft_v3_init(&camera->s_camera.look_at, camera->pos.x, camera->pos.y,
		camera->pos.z);
	ft_v3_init(&temp_vec, camera->s_camera.normal.x, camera->s_camera.normal.y,
		camera->s_camera.normal.z);
	ft_v3_scalar_ip(&temp_vec, camera->s_camera.focal_length);
	ft_v3_add_ip(&camera->s_camera.look_at, &temp_vec);
	theta = camera->s_camera.fov * M_PI / 180.0;
	camera->s_camera.vp_height = 2.0 * tan(theta / 2.0);
	camera->s_camera.vp_width = aspect_ratio * camera->s_camera.vp_height;
	calc_lower_left_corner(camera);
}
