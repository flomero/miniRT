/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:04:06 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 17:11:37 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_checkerboard(t_object *texture, const t_vector3 *point,
		t_color *result)
{
	float	px;
	float	py;
	float	pz;

	px = floor(point->x / texture->s_tex.s_checker.size);
	py = floor(point->y / texture->s_tex.s_checker.size);
	pz = floor(point->z / texture->s_tex.s_checker.size);
	if ((int)(px + py + pz) % 2 == 0)
	{
		ft_color_to_float(texture->s_tex.s_checker.color1, result);
		return (texture->s_tex.s_checker.color1);
	}
	else
	{
		ft_color_to_float(texture->s_tex.s_checker.color2, result);
		return (texture->s_tex.s_checker.color2);
	}
}

uint32_t	ft_checkerboard_uv(t_object *texture, t_color *result, t_hit *hit)
{
	t_vector2	uv;
	t_uv_func	*uv_func;

	uv_func = ft_get_uv_func();
	if (uv_func[hit->obj->type] == NULL)
		return (ft_checkerboard(texture, &hit->p, result));
	uv_func[hit->obj->type](hit, &uv);
	uv.x *= (float)texture->s_tex.s_checker.size;
	uv.y *= texture->s_tex.s_checker.size;
	if ((int)(floor(uv.x) + floor(uv.y)) % 2 == 0)
	{
		ft_color_to_float(texture->s_tex.s_checker.color1, result);
		return (texture->s_tex.s_checker.color1);
	}
	ft_color_to_float(texture->s_tex.s_checker.color2, result);
	return (texture->s_tex.s_checker.color2);
}
