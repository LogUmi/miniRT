/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:01:26 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:01:27 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

void	pars_cam(t_app *app)
{
	double	norm;

	if (app->scene.cam_set)
		free_exit(app, "more than one cam in the scene", 1);
	app->scene.cam_set = 1;
	if (count_token(app->token) < 3 || count_token(app->token) > 4)
		free_exit (app, "wrong number of cam arguments", 1);
	app->scene.cam.pos = pars_vec(app, app->token[1]);
	app->scene.cam.dir = pars_vec(app, app->token[2]);
	norm = sqrt(app->scene.cam.dir.x * app->scene.cam.dir.x
			+ app->scene.cam.dir.y * app->scene.cam.dir.y
			+ app->scene.cam.dir.z * app->scene.cam.dir.z);
	if (norm < 1e-6)
		free_exit(app, "cam direction out of normalization", 1);
	app->scene.cam.dir.x /= norm;
	app->scene.cam.dir.y /= norm;
	app->scene.cam.dir.z /= norm;
	app->scene.cam.fov = ft_atof(is_numb(app, app->token[3], 1));
	if (app->fish == 0 && (app->scene.cam.fov < 0.0
			|| app->scene.cam.fov > 180.0))
		free_exit(app, "non fisheye invalid FOV", 1);
	else if (app->fish == 1 && (app->scene.cam.fov < 0.0))
		free_exit(app, "fisheye invalid FOV", 1);
	app->scene.cam.fov = app->scene.cam.fov * M_PI / 180.0;
}
/*
Vérifie qu’une seule caméra est définie (via cam_set).
Lit la position, la direction et le champ de vision (FOV).
Vérifie et normalise la direction.
Convertit le FOV de degrés vers radians.
*/

void	pars_light(t_app *app, t_light **lights)
{
	t_light	*new;

	if (count_token(app->token) < 3 || count_token(app->token) > 4)
		free_exit(app, "wrong number of light arguments", 1);
	new = ptr_malloc(app, 0, sizeof(t_light));
	new->pos = pars_vec(app, app->token[1]);
	new->ratio = ft_atof(is_numb(app, app->token[2], 1));
	if (new->ratio < 0.0 || new->ratio > 1.0)
		free_exit(app, "invalid light ratio", 1);
	if (app->token[3])
		new->color = pars_color(app, app->token[3]);
	else
		new->color = (t_color){255, 255, 255};
	new->next = *lights;
	*lights = new;
}
/*
Lit la position (vec), le ratio d’intensité (entre 0 et 1), 
et la couleur (optionnelle).
Si aucun token[3], utilise une couleur blanche par défaut.
Alloue dynamiquement la lumière et l’ajoute à la liste chaînée.
*/

void	check_scene(t_app *app)
{
	if (!app->scene.cam_set)
		free_exit(app, "no camera in the scene", 1);
	if (!app->scene.amb_set)
		free_exit(app, "no ambient lighting in the scene", 1);
	if (!app->scene.lights)
		free_exit(app, "no spot light in the scene", 1);
	if (!app->scene.objs)
		free_exit(app, "no object in the scene", 1);
	check_mode_img(app);
}
/*
Refuse la scène si elle ne contient pas au moins :
une caméra,
une lumière ambiante,
une source de lumière,
un objet.
*/
