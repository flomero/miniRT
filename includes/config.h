/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:29:22 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 12:21:09 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# ifndef DEBUG
#  define DEBUG 0
# endif

// IMAGE
# define WIN_TITLE "miniRT"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define BACKGROUND_COLOR 0x000000FF

// VIEWPORT
# define VIEWPORT_WIDTH 2.0
# define FOCAL_LENGTH 1.0
# define SAMPLES 100

// LIGHT
# define BOUNCES 2

// TERMINAL COLORS
# define RESET "\033[0m"
# define RED "\033[31m"
# define BOLD "\033[1m"

// ERRORS
# define ALLOC_ERR "Memory allocation failed"

#endif
