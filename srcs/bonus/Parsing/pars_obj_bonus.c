/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:01:16 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:01:16 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

void	pars_sphere(t_app *app, t_obj **objs, int mode)
{
	t_sphere	sph;
	t_obj		*new;

	sph.mode = mode;
	sph.mode = mode;
	if (count_token(app->token) < 3 || count_token(app->token) > 4)
		free_exit(app, "wrong number of sphere arguments", 1);
	sph.centre = pars_vec(app, app->token[1]);
	sph.diametre = ft_atof(is_numb(app, app->token[2], 1));
	if (sph.diametre <= 0)
		free_exit(app, "invalid sphere diameter", 1);
	if (app->token[3])
		sph.color = pars_color(app, app->token[3]);
	else
		sph.color = (t_color){255, 255, 255};
	new = ptr_malloc(app, 1, sizeof(t_obj));
	new->type = SPHERE;
	new->mode = mode;
	new->data.sphere = sph;
	new->next = *objs;
	*objs = new;
}
/*
Lit et convertit le centre, le diamètre, et la couleur (si présente).
Vérifie la validité du diamètre.
Alloue dynamiquement un nouvel objet, assigne 
le type SPHERE et l’ajoute en tête de liste.
*/

void	pars_plane(t_app *app, t_obj **objs, int mode)
{
	t_plane	pl;
	t_obj	*new;

	pl.mode = mode;
	if (count_token(app->token) < 3 || count_token(app->token) > 4)
		free_exit(app, "wrong number of plan arguments", 1);
	pl.point = pars_vec(app, app->token[1]);
	pl.normal = vec_normalize(pars_vec(app, app->token[2]));
	if (app->token[3])
		pl.color = pars_color(app, app->token[3]);
	else
		pl.color = (t_color){255, 255, 255};
	new = ptr_malloc(app, 2, sizeof(t_obj));
	new->type = PLANE;
	new->mode = mode;
	new->data.plane = pl;
	new->next = *objs;
	*objs = new;
}
/*
Lit la position (point), la normale (direction), et une couleur éventuelle.
Normalise la normale pour assurer un comportement correct en shading.
*/

void	pars_cylinder(t_app *app, t_obj **objs, int mode)
{
	t_cylinder	cy;
	t_obj		*new;

	cy.mode = mode;
	if (count_token(app->token) < 5 || count_token(app->token) > 6)
		free_exit(app, "wrong number of cylinder arguments", 1);
	cy.centre = pars_vec(app, app->token[1]);
	cy.axe = vec_normalize(pars_vec(app, app->token[2]));
	cy.diametre = ft_atof(is_numb(app, app->token[3], 1));
	cy.height = ft_atof(is_numb(app, app->token[4], 1));
	if (cy.diametre <= 0 || cy.height <= 0)
		free_exit(app, "invalid cylinder dimensions", 1);
	if (app->token[5])
		cy.color = pars_color(app, app->token[5]);
	else
		cy.color = (t_color){255, 255, 255};
	new = ptr_malloc(app, 3, sizeof(t_obj));
	new->type = CYLINDER;
	new->mode = mode;
	new->data.cylinder = cy;
	new->next = *objs;
	*objs = new;
}
/*
Lit centre, direction (axe), diamètre, hauteur et couleur.
Vérifie que les dimensions sont strictement positives.
Ajoute un t_obj typé CYLINDER à la liste.
*/

static void	pars_cone0(t_app *app, t_obj **objs, int mode, t_cone co)
{
	t_obj	*new;

	new = ptr_malloc(app, 5, sizeof(t_obj));
	new->type = CONE;
	new->mode = mode;
	new->data.cone = co;
	new->next = *objs;
	*objs = new;
}

void	pars_cone(t_app *app, t_obj **objs, int mode)
{
	t_cone	co;

	co.mode = mode;
	if (count_token(app->token) < 5 || count_token(app->token) > 6)
		free_exit(app, "wrong number of cone arguments", 1);
	co.apex = pars_vec(app, app->token[1]);
	co.axe = vec_normalize(pars_vec(app, app->token[2]));
	co.angle = ft_atof(is_numb(app, app->token[3], 1));
	co.height = ft_atof(is_numb(app, app->token[4], 1));
	if (co.height <= 0)
		free_exit(app, "invalid cone height", 1);
	if (app->token[5])
		co.color = pars_color(app, app->token[5]);
	else
		co.color = (t_color){255, 255, 255};
	if (co.angle < 0.0 || co.angle > 180.0)
		free_exit(app, "invalid cone angle", 1);
	co.angle = co.angle * M_PI / 180.0;
	pars_cone0(app, objs, mode, co);
}
/*Lit les paramètres, vérifie la hauteur.
Normalise l’axe pour assurer les calculs d’intersection corrects.
Ajoute à la scène via un objet de type CONE.
*/
