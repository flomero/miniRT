/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:24:49 by flfische          #+#    #+#             */
/*   Updated: 2024/06/09 17:52:02 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vector3	*calc_lower_left_corner(t_object *camera)
{
	t_vector3	*lower_left_corner;
	t_vector3	temp;
	t_vector3	*horizontal;
	t_vector3	*vertical;

	horizontal = ft_v3_div(camera->s_camera.horizontal, 2.0);
	vertical = ft_v3_div(camera->s_camera.vertical, 2.0);
	temp = (t_vector3){0.0, 0.0, camera->s_camera.focal_length};
	lower_left_corner = ft_v3_sub(camera->pos, horizontal);
	lower_left_corner = ft_v3_sub_ip(lower_left_corner, vertical);
	lower_left_corner = ft_v3_sub_ip(lower_left_corner, &temp);
	free(horizontal);
	free(vertical);
	return (lower_left_corner);
}

/**
 * Calculates the viewport of the camera.
 *
 * @param camera The camera object.
 */
void	ft_calculate_viewport(t_object *camera)
{
	float	aspect_ratio;
	float	theta;

	aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	theta = camera->s_camera.fov * M_PI / 180.0;
	camera->s_camera.viewport_height = 2.0 * tan(theta / 2.0);
	camera->s_camera.viewport_width = aspect_ratio
		* camera->s_camera.viewport_height;
	camera->s_camera.horizontal = ft_v3_new(camera->s_camera.viewport_width,
			0.0, 0.0);
	camera->s_camera.vertical = ft_v3_new(0.0, camera->s_camera.viewport_height,
			0.0);
	camera->s_camera.lower_left_corner = calc_lower_left_corner(camera);
}
