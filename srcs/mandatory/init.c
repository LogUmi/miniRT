/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:08:07 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:08:07 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/minirt.h"

void	init(t_app *app)
{
	app->scene.amb.ratio = 0.0;
	app->scene.amb.color = (t_color){0, 0, 0};
	app->scene.cam.pos = (t_vec){0.0, 0.0, 0.0};
	app->scene.cam.dir = (t_vec){0.0, 0.0, 1.0};
	app->scene.cam.fov = 60.0;
	app->scene.lights = NULL;
	app->scene.objs = NULL;
	app->scene.cam_set = 0;
	app->scene.amb_set = 0;
	app->scene.light_set = 0;
	app->window.width = 800;
	app->window.height = 600;
	app->window.mlx_ptr = NULL;
	app->window.win_ptr = NULL;
	app->window.img_ptr = NULL;
	app->image.img_ptr = NULL;
	app->image.addr = NULL;
	app->image.bits_pixel = 0;
	app->image.line_length = 0;
	app->image.endian = 0;
	app->str = NULL;
	app->line = NULL;
	app->token = NULL;
	app->split = NULL;
}
/*
Pour garantir que tous les pointeurs et structures sont bien définis,
éviter les comportements indéterminés,
et préparer un état de base propre avant l’analyse de la scène.
*/

void	init_window(t_app *app, int width, int height)
{
	app->window.mlx_ptr = mlx_init();
	if (!app->window.mlx_ptr)
		free_exit(app, "mlx_init failed", 1);
	ft_printf("Minilibx library initialized\n");
	if (mlx_get_screen_size(app->window.mlx_ptr, &app->window.swidth,
			&app->window.sheight) != 0)
		free_exit(app, "mlx was unable to detect a screen", 1);
	ft_printf("Screen %dx%d detected\n", app->window.swidth,
		app->window.sheight);
	if (width > app->window.swidth || height > app->window.sheight)
	{
		ft_printf("Window %dx%d out of screen range\n", width, height);
		width = app->window.swidth;
		height = app->window.sheight;
	}
	app->window.win_ptr = mlx_new_window(app->window.mlx_ptr,
			width, height, "miniRT");
	if (!app->window.win_ptr)
		free_exit(app, "mlx_new_window failed", 1);
	ft_printf("New window %dx%d opened\n", width, height);
	app->window.width = width;
	app->window.height = height;
}
/*
Pour créer un espace où l’image calculée sera affichée,
et détecter les erreurs critiques de configuration graphique dès le début.
*/

void	init_image(t_app *app, int width, int height)
{
	if (width > app->window.width || height > app->window.height)
	{
		ft_printf("Image %dx%d out of window range\n", width, height);
		width = app->window.width;
		height = app->window.height;
	}
	app->image.img_ptr = mlx_new_image(app->window.mlx_ptr, width, height);
	if (!app->image.img_ptr)
		free_exit(app, "mlx_new_image failed", 1);
	ft_printf("New image %dx%d created\n", width, height);
	app->image.addr = mlx_get_data_addr(app->image.img_ptr,
			&app->image.bits_pixel, &app->image.line_length,
			&app->image.endian);
}
/*
Pour disposer d'une zone de dessin mémoire dans laquelle
la scène 3D sera calculée avant d’être affichée dans la fenêtre.
*/
