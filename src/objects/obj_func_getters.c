/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_func_getters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:15:54 by flfische          #+#    #+#             */
/*   Updated: 2024/06/19 15:52:07 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit_func	*ft_get_hit_func(void)
{
	static const t_hit_func	hit_functions[OBJECT_COUNT] = {
	[SPHERE] = ft_sphere_hit,
	[PLANE] = ft_plane_hit,
	[CYLINDER] = ft_cylinder_hit,
	[CONE] = ft_cone_hit};

	return ((t_hit_func *)hit_functions);
}

t_normal_func	*ft_get_normal_func(void)
{
	static const t_normal_func	normal_functions[OBJECT_COUNT] = {
	[SPHERE] = ft_sphere_normal,
	[PLANE] = ft_plane_normal,
	[CYLINDER] = ft_cylinder_normal,
	[CONE] = ft_cone_normal};

	return ((t_normal_func *)normal_functions);
}

t_uv_func	*ft_get_uv_func(void)
{
	static const t_uv_func	uv_functions[OBJECT_COUNT] = {
	[SPHERE] = ft_sphere_uv};

	return ((t_uv_func *)uv_functions);
}
