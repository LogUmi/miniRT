/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_mode_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:01:06 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:01:06 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static void	pars_obj1(t_app *app)
{
	char	msg[100];

	msg[0] = 0;
	if (ft_strncmp(app->token[0], "cy4", 4) == 0)
		pars_cylinder(app, &app->scene.objs, 4);
	else if (ft_strncmp(app->token[0], "co4", 4) == 0)
		pars_cone(app, &app->scene.objs, 4);
	else if (ft_strncmp(app->token[0], "sp5", 4) == 0)
		pars_sphere(app, &app->scene.objs, 5);
	else if (ft_strncmp(app->token[0], "pl5", 4) == 0)
		pars_plane(app, &app->scene.objs, 5);
	else if (ft_strncmp(app->token[0], "cy5", 4) == 0)
		pars_cylinder(app, &app->scene.objs, 5);
	else if (ft_strncmp(app->token[0], "co5", 4) == 0)
		pars_cone(app, &app->scene.objs, 5);
	else
	{
		ft_strlcpy(&msg[0], "invalid identifier ", 20);
		ft_strlcat(&msg[0], app->token[0], ft_strlen(app->token[0]) + 20);
		ft_strlcat(&msg[0], " found in file", ft_strlen(app->token[0]) + 34);
		free_exit(app, &msg[0], 1);
	}
}

static void	pars_obj0(t_app *app)
{
	if (ft_strncmp(app->token[0], "co1", 4) == 0)
		pars_cone(app, &app->scene.objs, 1);
	else if (ft_strncmp(app->token[0], "sp2", 4) == 0)
		pars_sphere(app, &app->scene.objs, 2);
	else if (ft_strncmp(app->token[0], "pl2", 4) == 0)
		pars_plane(app, &app->scene.objs, 2);
	else if (ft_strncmp(app->token[0], "cy2", 4) == 0)
		pars_cylinder(app, &app->scene.objs, 2);
	else if (ft_strncmp(app->token[0], "co2", 4) == 0)
		pars_cone(app, &app->scene.objs, 2);
	else if (ft_strncmp(app->token[0], "sp3", 4) == 0)
		pars_sphere(app, &app->scene.objs, 3);
	else if (ft_strncmp(app->token[0], "pl3", 4) == 0)
		pars_plane(app, &app->scene.objs, 3);
	else if (ft_strncmp(app->token[0], "cy3", 4) == 0)
		pars_cylinder(app, &app->scene.objs, 3);
	else if (ft_strncmp(app->token[0], "co3", 4) == 0)
		pars_cone(app, &app->scene.objs, 3);
	else if (ft_strncmp(app->token[0], "sp4", 4) == 0)
		pars_sphere(app, &app->scene.objs, 4);
	else if (ft_strncmp(app->token[0], "pl4", 4) == 0)
		pars_plane(app, &app->scene.objs, 4);
	else
		pars_obj1(app);
}

void	pars_obj(t_app *app)
{
	if (ft_strncmp(app->token[0], "sp", 3) == 0)
		pars_sphere(app, &app->scene.objs, -1);
	else if (ft_strncmp(app->token[0], "pl", 3) == 0)
		pars_plane(app, &app->scene.objs, -1);
	else if (ft_strncmp(app->token[0], "cy", 3) == 0)
		pars_cylinder(app, &app->scene.objs, -1);
	else if (ft_strncmp(app->token[0], "co", 3) == 0)
		pars_cone(app, &app->scene.objs, -1);
	else if (ft_strncmp(app->token[0], "sp0", 4) == 0)
		pars_sphere(app, &app->scene.objs, 0);
	else if (ft_strncmp(app->token[0], "pl0", 4) == 0)
		pars_plane(app, &app->scene.objs, 0);
	else if (ft_strncmp(app->token[0], "cy0", 4) == 0)
		pars_cylinder(app, &app->scene.objs, 0);
	else if (ft_strncmp(app->token[0], "co0", 4) == 0)
		pars_cone(app, &app->scene.objs, 0);
	else if (ft_strncmp(app->token[0], "sp1", 4) == 0)
		pars_sphere(app, &app->scene.objs, 1);
	else if (ft_strncmp(app->token[0], "pl1", 4) == 0)
		pars_plane(app, &app->scene.objs, 1);
	else if (ft_strncmp(app->token[0], "cy1", 4) == 0)
		pars_cylinder(app, &app->scene.objs, 1);
	else
		pars_obj0(app);
}
/*
objets en mode -1 (couleur brute unie sans transformation)
"sp" → sphère
"pl" → plan
"cy" → cylindre
"co" → cône

objets en mode 0 (disruption de couleur en damier activée)
"sp0" → sphère
"pl0" → plan
"cy0" → cylindre
"co0" → cône

objets en mode 1 (intégration du fichier IMAGE1 fixée dans miniRT_bonus.h)
"sp1" → sphère
"pl1" → plan
"cy1" → cylindre
"co1" → cône

objets en mode 2 (intégration du fichier IMAGE2 fixée dans miniRT_bonus.h)
"sp2" → sphère
"pl2" → plan
"cy2" → cylindre
"co2" → cône

etc... jusqu'à mode 5 inclus

Sinon : erreur de format
*/
