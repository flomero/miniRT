/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:29:22 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 10:31:26 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define WIN_TITLE "miniRT"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define BACKGROUND_COLOR 0x000000FF
# define SAMPLES 100

// VIEWPORT
# define VIEWPORT_WIDTH 2.0
# define FOCAL_LENGTH 1.0

// COLORS
# define RESET "\033[0m"
# define RED "\033[31m"
# define BOLD "\033[1m"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define ALLOC_ERR "Memory allocation failed"

#endif
