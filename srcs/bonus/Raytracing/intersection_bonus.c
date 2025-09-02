/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:42 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:02:43 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

int	intersection_sphere(t_ray ray, t_sphere *sphere, double *t)
{
	t_sphere_arg	arg;

	arg.oc = vec_sub(ray.origin, sphere->centre);
	arg.a = vec_dot(ray.dir, ray.dir);
	arg.b = 2.0 * vec_dot(arg.oc, ray.dir);
	arg.c = vec_dot(arg.oc, arg.oc) - (sphere->diametre * 0.5)
		* (sphere->diametre * 0.5);
	arg.neg = arg.b * arg.b - 4 * arg.a * arg.c;
	if (arg.neg < 0)
		return (0);
	arg.t0 = (-arg.b - sqrt(arg.neg)) / (2.0 * arg.a);
	arg.t1 = (-arg.b + sqrt(arg.neg)) / (2.0 * arg.a);
	if (arg.t0 > 1e-4)
		*t = arg.t0;
	else if (arg.t1 > 1e-4)
		*t = arg.t1;
	else
		return (0);
	return (1);
}
/*
Que fait-elle ? Elle détermine si un rayon coupe une sphère,
et à quelle distance (t).
Comment ?
Elle résout une équation quadratique avec discriminant.
Si le discriminant est négatif → aucune intersection.
Sinon, elle teste les deux racines t0 et t1.
Retourne la plus petite racine strictement positive.
Pourquoi ? Pour identifier les points d’impact potentiels
avec les sphères dans la scène.
C’est une opération de base en ray tracing.
*/

int	intersection_plane(t_ray ray, t_plane *plane, double *t)
{
	double	num;
	double	denom;
	t_vec	p0;

	denom = vec_dot(plane->normal, ray.dir);
	if (fabs(denom) < 1e-6)
		return (0);
	p0 = vec_sub(plane->point, ray.origin);
	num = vec_dot(p0, plane->normal);
	*t = num / denom;
	if (*t > 1e-4)
		return (1);
	return (0);
}
/*
Que fait-elle ? Teste si un rayon intersecte un plan infini.
Comment ?
Vérifie si le rayon est parallèle au plan (produit scalaire ≈ 0).
Sinon, calcule la distance via projection.
Retourne vrai si l’intersection est en avant du rayon.
Pourquoi ?
Permet de détecter collisions avec des surfaces planes,
comme des murs, sols, ou plafonds.
*/

int	intersection_cylinder(t_ray ray, t_cylinder *cyl, double *t)
{
	t_arg_inter	arg;

	arg.min = 1e30;
	arg.hit_base = 0;
	arg.hit_side = 0;
	cyl->who_inter = 0;
	if (inter_cyl(vec_sub(ray.origin, cyl->centre), ray.dir, cyl, &arg.side))
	{
		arg.p = vec_add(ray.origin, vec_scale(ray.dir, arg.side));
		arg.m = vec_dot(vec_sub(arg.p, cyl->centre), cyl->axe);
		if (fabs(arg.m) <= cyl->height / 2.0 && arg.side > 1e-4)
		{
			arg.min = arg.side;
			arg.hit_side = 1;
		}
	}
	arg.hit_base = base_cylinder(ray, cyl, &arg.base, 1);
	if (arg.hit_base && arg.base < arg.min)
		inter_plus(&arg, cyl, NULL);
	if (arg.hit_side || arg.hit_base)
	{
		*t = arg.min;
		return (1);
	}
	return (0);
}
/*
Que fait-elle ? Elle vérifie si un rayon touche un cylindre (latéral ou base).
Comment ?
Appelle inter_cyl pour la surface latérale.
Calcule si l’impact se situe bien entre les deux extrémités (hauteur).
Appelle aussi base_cylinder pour tester les deux disques d’extrémité.
Retient la collision la plus proche.
Pourquoi ? Permet une modélisation réaliste de tubes, colonnes,
tuyaux et objets cylindriques fermés.
*/

int	base_cylinder(t_ray ray, t_cylinder *cyl, double *t, int labase)
{
	t_arg_base_cyl	arg;

	arg.min = 1e30;
	arg.hit = 0;
	arg.base1 = vec_add(cyl->centre, vec_scale(cyl->axe, -cyl->height / 2.0));
	if (inter_disk_cyl(ray, arg.base1, *cyl, &arg.t1)
		&& arg.t1 > 1e-4 && arg.t1 < arg.min)
	{
		arg.min = arg.t1;
		arg.hit = 1;
	}
	arg.base2 = vec_add(cyl->centre, vec_scale(cyl->axe, cyl->height / 2.0));
	if (inter_disk_cyl(ray, arg.base2, *cyl, &arg.t2) && arg.t2 > 1e-4
		&& arg.t2 < arg.min)
	{
		arg.min = arg.t2;
		arg.hit = 1;
		labase = 2;
	}
	if (arg.hit)
	{
		*t = arg.min;
		return (labase);
	}
	return (0);
}
/*
Que fait-elle ? Teste l’intersection entre le rayon et les
deux disques fermant le cylindre.
Comment ?
Détermine les centres des deux bases.
Utilise inter_disk_cyl pour chacun.
Retient la plus proche.
Pourquoi ? Un cylindre sans bases serait visuellement creux.
Cette fonction complète sa détection.
*/

int	inter_disk_cyl(t_ray ray, t_vec centre, t_cylinder cyl, double *t)
{
	double	denom;
	double	hit;
	t_vec	p;

	denom = vec_dot(ray.dir, cyl.axe);
	if (fabs(denom) < 1e-6)
		return (0);
	hit = vec_dot(vec_sub(centre, ray.origin), cyl.axe) / denom;
	if (hit < 1e-4)
		return (0);
	p = vec_add(ray.origin, vec_scale(ray.dir, hit));
	if (vec_length(vec_sub(p, centre)) > cyl.diametre * 0.5)
		return (0);
	*t = hit;
	return (1);
}
/*
Que fait-elle ? Teste si le rayon intersecte un disque circulaire
(la base du cylindre).
Comment ?
Calcule l’intersection avec le plan.
Vérifie si le point se situe à l’intérieur du rayon du disque.
Pourquoi ? Essentiel pour que la base du cylindre ne soit pas « invisible ».
*/
