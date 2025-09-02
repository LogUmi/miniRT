/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:03:52 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:44:03 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
/*
Que fait-elle ? Calcule le produit scalaire entre deux vecteurs.
Comment ? Somme des produits des composantes.
Pourquoi ? Mesure l’angle entre deux vecteurs
(utile pour déterminer les ombres, la luminosité ou des projections).
*/

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
/*
Que fait-elle ? Soustrait deux vecteurs.
Comment ? Composante par composante.
Pourquoi ? Pour calculer un vecteur directionnel entre deux points
(ex. rayon - position d’origine).
*/

void	ft_type(t_app *app, t_ray ray, double *t, t_hit *hit)
{
	t_obj	*obj;

	obj = app->obj;
	if (obj->type == SPHERE && intersection_sphere(ray, &obj->data.sphere, t))
		hit_sphere(hit, t, ray, app);
	else if (obj->type == PLANE
		&& intersection_plane(ray, &obj->data.plane, t))
		hit_plane(hit, t, ray, app);
	else if (obj->type == CYLINDER
		&& intersection_cylinder(ray, &obj->data.cylinder, t))
		hit_cyl(hit, t, ray, app);
	else if (obj->type == CONE && intersection_cone(ray, &obj->data.cone, t))
		hit_cone(hit, t, ray, app);
}

int	inter_cyl(t_vec oc, t_vec dir, t_cylinder *cyl, double *t)
{
	t_arg_cyl	arg;
	double		r;

	r = cyl->diametre * 0.5;
	arg.a = vec_dot(dir, dir) - pow(vec_dot(dir, cyl->axe), 2);
	arg.b = 2 * (vec_dot(dir, oc) - vec_dot(dir, cyl->axe)
			* vec_dot(oc, cyl->axe));
	arg.c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl->axe), 2) - r * r;
	arg.disc = arg.b * arg.b - 4 * arg.a * arg.c;
	if (arg.disc < 0)
		return (0);
	arg.t0 = (-arg.b - sqrt(arg.disc)) / (2 * arg.a);
	arg.t1 = (-arg.b + sqrt(arg.disc)) / (2 * arg.a);
	if (arg.t0 > 1e-4)
		*t = arg.t0;
	else if (arg.t1 > 1e-4)
		*t = arg.t1;
	else
		return (0);
	return (1);
}
/*
Détermine si un rayon intersecte un cylindre infini, et calcule la distance
*/

int	inter_cone(t_vec oc, t_vec dir, t_cone *cone, double *t)
{
	t_arg_co	arg;

	arg.k = tan(cone->angle);
	arg.a = vec_dot(dir, dir) - (1 + arg.k * arg.k)
		* pow(vec_dot(dir, cone->axe), 2);
	arg.b = 2 * (vec_dot(dir, oc) - (1 + arg.k * arg.k)
			* vec_dot(dir, cone->axe) * vec_dot(oc, cone->axe));
	arg.c = vec_dot(oc, oc) - (1 + arg.k * arg.k)
		* pow(vec_dot(oc, cone->axe), 2);
	arg.disc = arg.b * arg.b - 4 * arg.a * arg.c;
	if (arg.disc < 0)
		return (0);
	arg.t0 = (-arg.b - sqrt(arg.disc)) / (2 * arg.a);
	arg.t1 = (-arg.b + sqrt(arg.disc)) / (2 * arg.a);
	if (arg.t0 > 1e-4)
		*t = arg.t0;
	else if (arg.t1 > 1e-4)
		*t = arg.t1;
	else
		return (0);
	return (1);
}
/*
Même logique que inter_cyl, mais pour un cône infini.
*/
