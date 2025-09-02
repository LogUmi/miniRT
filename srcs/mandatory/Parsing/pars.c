/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:05:34 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:05:34 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/minirt.h"

void	pars_amb(t_app *app)
{
	if (app->scene.amb_set)
		free_exit(app, "several ambient lightings in the scene", 1);
	app->scene.amb_set = 1;
	if (!app->token[1] || app->token[3])
		free_exit(app, "wrong number of ambient lighting arguments", 1);
	app->scene.amb.ratio = ft_atof(is_numb(app, app->token[1], 1));
	if (app->scene.amb.ratio < 0.0 || app->scene.amb.ratio > 1.0)
		free_exit(app, "invalid ratio of ambient lighting", 1);
	app->scene.amb.color = pars_color(app, app->token[2]);
	if (app->token[2])
		app->scene.amb.color = pars_color(app, app->token[2]);
	else
		app->scene.amb.color = (t_color){255, 255, 255};
}
/*
Vérifie qu’il n’y a qu’une seule ambiance (via amb_set).
Lit le ratio d’intensité (token[1]) et vérifie qu’il est bien entre 0 et 1.
Convertit token[2] en couleur avec pars_color, ou utilise du blanc si absent.
Stocke le tout dans scene->amb.
*/

t_color	pars_color(t_app *app, const char *str)
{
	t_color	color;

	app->split = ft_split(str, ',');
	if (!app->split[0] || !app->split[1] || !app->split[2] || app->split[3])
		free_exit(app, "wrong number of color arguments", 1);
	color.r = ft_atoi(is_numb(app, app->split[0], 0));
	color.g = ft_atoi(is_numb(app, app->split[1], 0));
	color.b = ft_atoi(is_numb(app, app->split[2], 0));
	free_split(app->split);
	app->split = NULL;
	if (!ft_iscolor(color.r) || !ft_iscolor(color.g)
		|| !ft_iscolor(color.b))
		free_exit(app, "invalid color value", 1);
	return (color);
}
/*
Coupe la chaîne en trois parties avec , comme séparateur.
Convertit chaque partie en entier (r, g, b).
Vérifie que les valeurs sont valides (entre 0 et 255).
Retourne une structure t_color.
*/

t_vec	pars_vec(t_app *app, const char *str)
{
	t_vec	vec;

	app->split = ft_split(str, ',');
	if (!app->split || !app->split[0] || !app->split[1] || !app->split[2]
		|| app->split[3])
		free_exit(app, "wrong number of vector arguments", 1);
	vec.x = ft_atof(is_numb(app, app->split[0], 1));
	vec.y = ft_atof(is_numb(app, app->split[1], 1));
	vec.z = ft_atof(is_numb(app, app->split[2], 1));
	free_split(app->split);
	app->split = NULL;
	return (vec);
}
/*
Sépare la chaîne en trois parties.
Convertit chaque nombre en double.
Remplit la structure t_vec.
*/
