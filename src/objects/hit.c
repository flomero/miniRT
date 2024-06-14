/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:11:15 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 17:33:37 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	ft_hit(t_ray *ray, t_object *obj, t_hit *hit)
{
	float	t;

	t = INFINITY;
	if (obj->type > LIGHT)
		t = ft_get_hit_func()[obj->type](obj, ray);
	if (t <= 0 || t == INFINITY)
		return (FALSE);
	if (t > hit->t)
		return (FALSE);
	hit->t = t;
	hit->obj = obj;
	hit->obj->color = obj->color;
	t = ft_get_normal_func()[obj->type](hit, ray);
	hit->ray = ray;
	return (TRUE);
}
