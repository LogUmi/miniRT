/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:03:14 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:03:15 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

void	put_pixel(t_image *img, int x, int y, t_color color)
{
	unsigned int	pixel;
	char			*dst;

	pixel = ((color.r & 0xFF) << 16) | ((color.g & 0xFF) << 8)
		| (color.b & 0xFF);
	dst = img->addr + (y * img->line_length + x
			* (img->bits_pixel / 8));
	*(unsigned int *)dst = pixel;
}
/*
Elle écrit un pixel coloré dans le buffer mémoire
de l’image à la position (x, y).
Comment ?
Convertit la couleur RGB en entier codé sur 24 bits (format 0xRRGGBB).
Calcule l’adresse mémoire exacte du pixel à modifier dans le buffer.
Écrit la valeur de couleur directement à cet emplacement.
*/

void	render_scene(t_app *app, t_scene *scene, t_window *win)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;

	if (!app->image.addr)
		free_exit(app, "image buffer non initialized", 1);
	y = 0;
	while (y < win->height)
	{
		if (y % 50 == 0)
			printf("Ligne générer %d/%d\n", y, win->height);
		x = 0;
		while (x < win->width)
		{
			if (app->fish == 1)
				ray = generate_ray_fisheye(x, y, &scene->cam, win);
			else
				ray = generate_ray(x, y, &scene->cam, win);
			color = trace_ray(app, ray, scene);
			put_pixel(&app->image, x, y, color);
			x++;
		}
		y++;
	}
}
/*
Que fait-elle ? Elle génère l’image complète de la scène 3D
en traçant un rayon pour chaque pixel de l’écran.
Comment ?
Parcourt chaque pixel de la fenêtre (double boucle y, puis x).
Pour chaque pixel :
Génère un rayon (generate_ray) en fonction de la caméra.
Calcule la couleur vue dans cette direction via trace_ray.
Place la couleur dans l’image avec put_pixel.
Affiche une progression toutes les 50 lignes.
*/
