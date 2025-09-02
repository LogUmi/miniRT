/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:03:07 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:03:08 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static t_ray	generate_ray_fisheye_0(t_arg_ray *arg)
{
	if (arg->r > 1.0)
	{
		arg->ray.dir = (t_vec){0, 0, 0};
		return (arg->ray);
	}
	arg->pixel_dir = vec_add(vec_add(vec_scale(arg->right,
					cos(arg->angle_azim) * sin(arg->angle_max)),
				vec_scale(arg->up, sin(arg->angle_azim) * sin(arg->angle_max))),
			vec_scale(arg->forward, cos(arg->angle_max)));
	arg->ray.dir = vec_normalize(arg->pixel_dir);
	return (arg->ray);
}

t_ray	generate_ray_fisheye(int i, int j, t_cam *cam, t_window *win)
{
	t_arg_ray	arg;
	t_vec		xy_ref;

	xy_ref = (t_vec){0.0, 1.0, 0.0};
	arg.aspect = 1.0;
	arg.scale = 1.0;
	arg.forward = cam->dir;
	if (fabs(arg.forward.x) < 1e-6 && fabs(arg.forward.z) < 1e-6)
		xy_ref = (t_vec){0.0, 0.0, 1.0};
	arg.right = vec_normalize(vec_cross(arg.forward, xy_ref));
	if (vec_dot(arg.right, (t_vec){1, 0, 0}) < 0)
		arg.right = vec_normalize(vec_scale(arg.right, -1));
	arg.up = vec_cross(arg.right, arg.forward);
	if (vec_dot(arg.up, (t_vec){0, 1, 0}) > 0)
		arg.up = vec_scale(arg.up, -1);
	arg.px = (2.0 * i / (double)(win->width) - 1.0);
	arg.py = (2.0 * j / (double)(win->height) - 1.0);
	arg.r = sqrt(arg.px * arg.px + arg.py * arg.py);
	arg.ray.origin = cam->pos;
	arg.angle_max = arg.r * (cam->fov / 2.0);
	arg.angle_azim = atan2(arg.py, arg.px);
	return (generate_ray_fisheye_0(&arg));
}

t_ray	generate_ray(int i, int j, t_cam *cam, t_window *win)
{
	t_arg_ray	arg;
	t_vec		xy_ref;

	xy_ref = (t_vec){0.0, 1.0, 0.0};
	arg.scale = tan(cam->fov * 0.5);
	arg.aspect = (double)win->width / (double)win->height;
	arg.forward = cam->dir;
	if (fabs(arg.forward.x) < 1e-6 && fabs(arg.forward.z) < 1e-6)
		xy_ref = (t_vec){0.0, 0.0, 1.0};
	arg.right = vec_normalize(vec_cross(arg.forward, xy_ref));
	if (vec_dot(arg.right, (t_vec){1, 0, 0}) < 0)
		arg.right = vec_normalize(vec_scale(arg.right, -1));
	arg.up = vec_cross(arg.right, arg.forward);
	if (vec_dot(arg.up, (t_vec){0, 1, 0}) < 0)
		arg.up = vec_scale(arg.up, -1);
	arg.px = (2 * ((i + 0.5) / (double)win->width) - 1) * arg.aspect
		* arg.scale;
	arg.py = (1 - 2 * ((j + 0.5) / (double)win->height)) * arg.scale;
	arg.pixel_dir = vec_add(vec_add(vec_scale(arg.right, arg.px),
				vec_scale(arg.up, arg.py)), arg.forward);
	arg.ray.origin = cam->pos;
	arg.ray.dir = vec_normalize(arg.pixel_dir);
	return (arg.ray);
}
/*
Que fait-elle ? Elle crée un rayon 3D correspondant à un pixel
(i, j) de l'écran, selon la caméra.
Comment ?
Elle calcule les coordonnées du pixel dans le plan image en les normalisant.
Utilise les vecteurs forward, right et up issus de l’orientation caméra.
Construit un vecteur de direction pointant vers ce pixel.
Retourne un rayon (t_ray) partant de la position de la caméra
et dirigé vers ce point, normalisé.
Où ? Appelée dans la boucle de rendu, pour chaque pixel.
Pourquoi ? Pour tracer un rayon optique par pixel, base du
rendu par lancer de rayons.
*/

t_color	trace_ray(t_app *app, t_ray ray, t_scene *scene)
{
	t_hit	closest;
	t_hit	hit;
	double	t;

	closest.t = 1e30;
	closest.hit = 0;
	app->obj = scene->objs;
	while (app->obj)
	{
		hit.hit = 0;
		ft_type(app, ray, &t, &hit);
		if (hit.hit && hit.t < closest.t)
			closest = hit;
		app->obj = app->obj->next;
	}
	if (closest.hit)
		return (shade(app, scene, &closest));
	return ((t_color){0, 0, 0});
}
/*
Que fait-elle ? Elle détermine la couleur perçue par un
rayon lancé dans la scène.
Comment ?
Parcourt tous les objets.
Utilise ft_type pour détecter s’il y a intersection avec chacun.
Retient l’intersection la plus proche (closest).
Si une intersection a lieu, elle retourne la couleur calculée via shade.
Sinon, retourne la couleur du fond (ici noir).
Où ? Appelée pour chaque rayon dans render_scene.
Pourquoi ? Pour calculer la couleur associée à un pixel,
en fonction des objets et de la lumière rencontrés.
*/
