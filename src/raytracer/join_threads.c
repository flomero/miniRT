/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:59:13 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 12:59:34 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->thread_count)
	{
		pthread_join(program->threads[i], NULL);
		i++;
	}
}
