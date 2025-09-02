/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:04:45 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:04:45 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/minirt.h"

void	pars_sphere(t_app *app, t_obj **objs)
{
	t_sphere	sph;
	t_obj		*new;

	if (!app->token[1] || !app->token[2] || app->token[4])
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

void	pars_plane(t_app *app, t_obj **objs)
{
	t_plane	pl;
	t_obj	*new;

	if (!app->token[1] || !app->token[2])
		free_exit(app, "wrong number of plan arguments", 1);
	pl.point = pars_vec(app, app->token[1]);
	pl.normal = vec_normalize(pars_vec(app, app->token[2]));
	if (app->token[3])
		pl.color = pars_color(app, app->token[3]);
	else
		pl.color = (t_color){255, 255, 255};
	new = ptr_malloc(app, 2, sizeof(t_obj));
	new->type = PLANE;
	new->data.plane = pl;
	new->next = *objs;
	*objs = new;
}
/*
Lit la position (point), la normale (direction), et une couleur éventuelle.
Normalise la normale pour assurer un comportement correct en shading.
*/

void	pars_cylinder(t_app *app, t_obj **objs)
{
	t_cylinder	cy;
	t_obj		*new;

	if (!app->token[1] || !app->token[2] || !app->token[3]
		|| !app->token[4] || app->token[6])
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
	new->data.cylinder = cy;
	new->next = *objs;
	*objs = new;
}
/*
Lit centre, direction (axe), diamètre, hauteur et couleur.
Vérifie que les dimensions sont strictement positives.
Ajoute un t_obj typé CYLINDER à la liste.
*/
