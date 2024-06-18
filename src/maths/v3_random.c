/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:46 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 16:14:03 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector3	*ft_v3_rand(void)
{
	t_vector3	*rand;

	rand = ft_v3_new(ft_randf(), ft_randf(), ft_randf());
	return (rand);
}

t_vector3	*ft_v3_rand_ip(t_vector3 *vec)
{
	vec->x = ft_randf();
	vec->y = ft_randf();
	vec->z = ft_randf();
	return (vec);
}

t_vector3	*ft_v3_rand_range(float min, float max)
{
	t_vector3	*rand;

	rand = ft_v3_new(ft_randf_range(min, max), ft_randf_range(min, max),
			ft_randf_range(min, max));
	return (rand);
}

t_vector3	*ft_v3_rand_range_ip(t_vector3 *vec, float min, float max)
{
	vec->x = ft_randf_range(min, max);
	vec->y = ft_randf_range(min, max);
	vec->z = ft_randf_range(min, max);
	return (vec);
}

t_vector3	*ft_v3_rand_unit(t_vector3 *vec)
{
	float	len;

	while (1)
	{
		ft_v3_rand_ip(vec);
		len = ft_v3_len(vec);
		if (len * len < 1)
			break ;
	}
	return (vec);
}
