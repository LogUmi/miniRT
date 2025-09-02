/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:11:54 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:11:54 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

/* static void	put_img(t_app *app, int mode)
{
	int		i;
	int		pixel;
	char	*dst;
	int		n;

	i = 0;
	while (i < (app->bump[mode]->l * app->bump[mode]->h))
	{
		n = app->bump[mode]->point[i];
		pixel = ((app->bump[mode]->color[n][0] & 0xFF) << 16)
			| ((app->bump[mode]->color[n][1] & 0xFF) << 8)
			| (app->bump[mode]->color[n][2] & 0xFF);
		dst = app->image.addr + i * 4;
		*(unsigned int *)dst = pixel;
		i++;
	}
} */

static int	mouse_close(t_app *app)
{
	return (free_exit(app, "Regular end of session on mouse command", 0));
}

int	main(int ac, char **av)
{
	t_app	app;

	init(&app);
	if (ac != 2)
		free_exit(&app, "no argument ... usage: ./minirt <scene.rt>", 1);
	if (ft_strrstr(av[1], ".rt") != 0)
		free_exit(&app, "file has no .rt extension", 1);
	pars_scene(&app, av);
	check_scene(&app);
	init_window(&app, 1600, 1200);
	init_image(&app, 1600, 1200);
	render_scene(&app, &app.scene, &app.window);
	mlx_put_image_to_window(app.window.mlx_ptr, app.window.win_ptr,
		app.image.img_ptr, 0, 0);
	mlx_hook(app.window.win_ptr, 17, 0, &mouse_close, &app);
	mlx_hook(app.window.win_ptr, 2, 1L << 0, &control_key, &app);
	mlx_loop(app.window.mlx_ptr);
	return (0);
}
/*
Charger une scène 3D définie par l'utilisateur.
Initialiser les outils graphiques et les structures mémoire nécessaires.
Générer et afficher une image issue d’un moteur de ray tracing.
Permettre une interaction utilisateur simple (fermeture).
*/