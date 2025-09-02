/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:06:21 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:48:23 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/minirt.h"

void	hit_sphere(t_hit *hit, double *t, t_ray ray, t_obj *obj)
{
	hit->t = (*t);
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, (*t)));
	hit->normal = vec_normalize(vec_sub(hit->point, obj->data.sphere.centre));
	hit->color = obj->data.sphere.color;
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}
/*
Calcule le point d’impact avec la sphère.
Déduit la normale en soustrayant le centre du point d’impact (vecteur radial).
Normalise la normale et vérifie son sens par rapport au rayon
(elle doit pointer vers l’extérieur de l’objet visible).
*/

void	hit_plane(t_hit *hit, double *t, t_ray ray, t_obj *obj)
{
	hit->t = (*t);
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, (*t)));
	hit->normal = obj->data.plane.normal;
	hit->color = obj->data.plane.color;
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}
/*
Le point d’intersection est simplement calculé.
La normale est fixée d’emblée (plan infini : direction constante).
Le test vec_dot(...) > 0 inverse la normale
si elle pointe dans la mauvaise direction (face cachée).
*/

void	hit_cyl(t_hit *hit, double *t, t_ray ray, t_obj *obj)
{
	double	m;
	t_vec	oc;

	hit->t = (*t);
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, (*t)));
	if (obj->data.cylinder.who_inter == 1)
		hit->normal = vec_scale(obj->data.cylinder.axe, -1);
	else if (obj->data.cylinder.who_inter == 2)
		hit->normal = obj->data.cylinder.axe;
	else
	{
		oc = vec_sub(hit->point, obj->data.cylinder.centre);
		m = vec_dot(ray.dir, obj->data.cylinder.axe) * (*t)
			+ vec_dot(vec_sub(ray.origin, obj->data.cylinder.centre),
				obj->data.cylinder.axe);
		hit->normal = vec_normalize(vec_sub(oc,
					vec_scale(obj->data.cylinder.axe, m)));
	}
	hit->color = obj->data.cylinder.color;
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}
/*
Déduit la position d’impact (point) comme d’habitude.
Calcule m, la projection du rayon sur l’axe du cylindre,
pour localiser où sur le corps du cylindre l’impact a lieu.
Déduit la normale à la surface latérale du cylindre par projection orthogonale.
Corrige l’orientation si nécessaire.
*/
