/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:31 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:40:14 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/minirt.h"

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

int	in_shadow(t_scene *scene, t_vec point, t_vec light_dir, double light_dist)
{
	t_ray	shadow_ray;
	t_hit	hit;
	t_obj	*obj;
	double	t;

	t = 0.0;
	shadow_ray.origin = vec_add(point, vec_scale(light_dir, 1e-4));
	shadow_ray.dir = light_dir;
	obj = scene->objs;
	while (obj)
	{
		hit.hit = 0;
		ft_type(obj, shadow_ray, &t, &hit);
		if (hit.hit && t > 1e-4 && t < light_dist)
			return (1);
		obj = obj->next;
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

void	ft_paint(t_light *light, t_hit *hit, t_color *final, t_vec light_dir)
{
	double	diffu;

	diffu = fmax(0.0, vec_dot(hit->normal, light_dir));
	final->r += hit->color.r * light->ratio * diffu * light->color.r / 255.0;
	final->g += hit->color.g * light->ratio * diffu * light->color.g / 255.0;
	final->b += hit->color.b * light->ratio * diffu * light->color.b / 255.0;
}
/*
Calcule la contribution lumineuse directe d’une lumière
sur un point éclairé (modèle Lambertien, diffus).
Comment ?
Produit scalaire entre la normale du point et la direction
de la lumière → intensité (diffu).
Pondère la couleur du point en fonction de celle de la lumière,
du ratio lumineux et du produit scalaire.
Ajoute au final.
Pourquoi ? Pour appliquer un éclairage réaliste par source
lumineuse en tenant compte de la surface et de l’intensité.
*/

t_color	shade(t_scene *scene, t_hit *hit)
{
	t_color	final;
	t_light	*light;
	t_vec	light_dir;
	double	light_dist;

	final = (t_color){0, 0, 0};
	light = scene->lights;
	final.r += hit->color.r * scene->amb.ratio * scene->amb.color.r / 255.0;
	final.g += hit->color.g * scene->amb.ratio * scene->amb.color.g / 255.0;
	final.b += hit->color.b * scene->amb.ratio * scene->amb.color.b / 255.0;
	while (light)
	{
		light_dir = vec_sub(light->pos, hit->point);
		light_dist = vec_length(light_dir);
		light_dir = vec_normalize(light_dir);
		if (in_shadow(scene, hit->point, light_dir, light_dist))
		{
			light = light->next;
			continue ;
		}
		ft_paint(light, hit, &final, light_dir);
		light = light->next;
	}
	final = the_color(final);
	return (final);
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
