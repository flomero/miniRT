/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:36:37 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 17:34:14 by klamprak         ###   ########.fr       */
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

/**
 * @brief prints both msg1 and msg2
 *
 * @param msg1
 * @param msg2
 * @param i
 */
void	print_err_extend(const char *msg1, const char *msg2)
{
	char	*line;

	line = ft_strjoin(msg1, msg2);
	ft_print_error(line);
	free(line);
}
