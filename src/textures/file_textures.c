/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:26:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/21 15:30:30 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_get_pixel_color(mlx_texture_t *texture, int x, int y,
		t_color *result)
{
	uint32_t	color;
	uint8_t		*pixel;

	if (x < 0 || (uint32_t)x >= texture->width || y < 0
		|| (uint32_t)y >= texture->height)
		return (0);
	y = texture->height - y - 1;
	pixel = texture->pixels + (y * texture->width + x)
		* texture->bytes_per_pixel;
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	if (result)
		ft_color_to_float(color, result);
	return (color);
}

uint32_t	ft_texture_file(t_object *obj, t_hit *hit, t_color *result)
{
	t_vector2	uv;
	t_uv_func	*uv_func;
	t_object	*texture;

	texture = obj->texture;
	uv_func = ft_get_uv_func();
	if (texture->s_tex.s_custom.img == NULL)
		return (0);
	if (uv_func[obj->type] == NULL)
	{
		uv.x = 0;
		uv.y = 0;
	}
	else
		uv_func[obj->type](hit, &uv);
	uv.x = uv.x * texture->s_tex.s_custom.img->width;
	uv.y = uv.y * texture->s_tex.s_custom.img->height;
	return (ft_get_pixel_color(texture->s_tex.s_custom.img, uv.x, uv.y,
			result));
}
