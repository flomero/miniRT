/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:29:22 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 17:07:44 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define WIN_TITLE "miniRT"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// COLORS
# define RESET "\033[0m"
# define RED "\033[31m"
# define BOLD "\033[1m"

#ifndef DEBUG
# define DEBUG 0
#endif

# define ALLOC_ERR "Memory allocation failed"

#endif
