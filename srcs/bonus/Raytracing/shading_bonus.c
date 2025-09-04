/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:03:21 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/05 00:07:34 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

t_color	the_color(t_color final)
{
	if (final.r < 0)
		final.r = 0;
	if (final.r > 255)
		final.r = 255;
	if (final.g < 0)
		final.g = 0;
	if (final.g > 255)
		final.g = 255;
	if (final.b < 0)
		final.b = 0;
	if (final.b > 255)
		final.b = 255;
	return (final);
}

int	in_shadow(t_app *app, t_hit *hit, t_vec light_dir, double light_dist)
{
	t_ray	shadow_ray;
	t_hit	hit2;
	double	t;
	t_scene	*scene;

	t = 0.0;
	scene = &app->scene;
	shadow_ray.origin = vec_add(hit->point, vec_scale(hit->normal, 1e-4));
	shadow_ray.dir = light_dir;
	app->obj = scene->objs;
	while (app->obj)
	{
		hit2.hit = 0;
		ft_type(app, shadow_ray, &t, &hit2);
		if (hit2.hit && t > 1e-4 && t < light_dist)
			return (1);
		app->obj = app->obj->next;
	}
	return (0);
}
/*
Détermine si un point est dans l’ombre par rapport à une source lumineuse.
Comment ?
Lance un rayon secondaire ("shadow ray") du point vers la lumière.
Si un objet est rencontré avant la lumière → ombre → retourne 1.
Sinon, retourne 0.
*/

void	pt_lambert(t_light *light, t_hit *hit, t_color *final, t_vec light_dir)
{
	double	diffu;

	diffu = fmax(0.0, vec_dot(hit->normal, light_dir));
	final->r += hit->color.r * light->ratio * diffu * light->color.r / 255.0;
	final->g += hit->color.g * light->ratio * diffu * light->color.g / 255.0;
	final->b += hit->color.b * light->ratio * diffu * light->color.b / 255.0;
}
/*
Calcule la contribution lumineuse directe d’une lumière
sur un point éclairé (modèle Lambert, lumière diffuse).
Comment ?
Produit scalaire entre la normale du point et la direction
de la lumière → intensité (diffu).
Pondère la couleur du point en fonction de celle de la lumière,
du ratio lumineux et du produit scalaire.
Ajoute au final.
Pourquoi ? Pour appliquer un éclairage réaliste par source
lumineuse en tenant compte de la surface et de l’intensité.
*/

void	pt_amb(t_color *final, t_color base, t_amb amb)
{
	double	factor;

	factor = amb.ratio / 255.0;
	final->r += base.r * factor * amb.color.r;
	final->g += base.g * factor * amb.color.g;
	final->b += base.b * factor * amb.color.b;
}

t_color	shade(t_app *app, t_scene *scene, t_hit *hit)
{
	t_color	final;
	t_light	*light;
	t_vec	light_dir;
	double	light_dist;

	(void)app;
	final = (t_color){0, 0, 0};
	light = scene->lights;
	pt_amb(&final, hit->color, scene->amb);
	while (light)
	{
		scene->culight = (void*)light;
		init_light(light, hit, &light_dir, &light_dist);
		if (!in_shadow(app, hit, light_dir, light_dist))
		{
			pt_lambert(light, hit, &final, light_dir);
			pt_phong(scene, hit, light_dir, &final);
		}
		light = light->next;
	}
	return (the_color(final));
}
/*
Que fait-elle ? Calcule la couleur finale d’un point
touché par un rayon (ombrage de ce point).
Comment ?
Initialise la couleur finale avec l’ambiante.
Pour chaque lumière :
Calcule direction & distance.
Vérifie l’ombre via in_shadow.
Si visible, applique ft_paint.
Clamp final via the_color.
Pourquoi ? C’est l’algorithme central du modèle d’éclairage,
qui détermine ce que « voit » la caméra à chaque pixel.
*/
