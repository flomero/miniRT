/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:06:39 by flfische          #+#    #+#             */
/*   Updated: 2024/07/06 16:08:33 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Prints a debug message.
 *
 * @param message The message to print.
 */
void	ft_debug_message(char *message)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(CYAN BOLD "DEBUG:\t" RESET, 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}
