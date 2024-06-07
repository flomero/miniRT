/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:36:37 by flfische          #+#    #+#             */
/*   Updated: 2024/06/07 14:43:47 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_print_error(const char *error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(BOLD, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("\t", 2);
	ft_putstr_fd((char *)error, 2);
	ft_putchar_fd('\n', 2);
}
