/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:53:19 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 11:53:19 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include "minirt_struct_bonus.h"
# include "minirt_fonctions_bonus.h"
# include "../libft/includes/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define BUFF_SIZE 4096
# define MAX_TEXTURE 5
# define BASE_INF 1
# define BASE_SUP 2

# define IMAGE1 "scenes/images/earth_daymap_1024x512.xpm"
# define IMAGE2 "scenes/images/sun_1024x512.xpm"
# define IMAGE3 "scenes/images/moon_1024x512.xpm"
# define IMAGE4 "scenes/images/mars_1024x512.xpm"
# define IMAGE5 "scenes/images/jupiter_1024x512.xpm"

# define IMAGE1_OFFSET_X 250
# define IMAGE1_OFFSET_Y -50
# define IMAGE2_OFFSET_X 0
# define IMAGE2_OFFSET_Y 0
# define IMAGE3_OFFSET_X 400
# define IMAGE3_OFFSET_Y 0
# define IMAGE4_OFFSET_X 300
# define IMAGE4_OFFSET_Y 0
# define IMAGE5_OFFSET_X 100
# define IMAGE5_OFFSET_Y 0

# define XK_ESCAPE 0xff1b
# define XK_PLUS   0xffab
# define XK_MINUS  0xffad
# define XK_UP     0xff52
# define XK_DOWN   0xff54
# define XK_RIGHT  0xff53
# define XK_LEFT   0xff51
# define XK_SPACE  0x0020
# define XK_KP7    65429
# define XK_KP4    65430
# define XK_KP8    65431
# define XK_KP5    65437
# define XK_KP9    65434
# define XK_KP6    65432
# define XK_KP1    65436
# define XK_KP2    65433
# define XK_KP3	   65435
# define XK_KP0    65438

#endif