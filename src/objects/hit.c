/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:11:15 by flfische          #+#    #+#             */
/*   Updated: 2024/06/27 16:36:43 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	ft_hit(t_ray *ray, t_object *obj, t_hit *hit)
{
	double	t;

	t = INFINITY;
	if (obj->type > LIGHT)
		t = ft_get_hit_func()[obj->type](obj, ray);
	if (t <= 0 || t == INFINITY)
		return (FALSE);
	if (t > hit->t)
		return (FALSE);
	hit->t = t;
	hit->obj = obj;
	t = ft_get_normal_func()[obj->type](hit, ray);
	hit->ray = ray;
	return (TRUE);
}
