/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:51 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:02:52 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static void	init_arg(t_arg_inter *arg)
{
	arg->hit_side = 0;
	arg->hit_base = 0;
	arg->min = 1e30;
}

int	base_cone(t_ray ray, t_cone *cone, double *t)
{
	double	t_base;
	t_vec	base_center;

	base_center = vec_add(cone->apex, vec_scale(cone->axe, cone->height));
	if (inter_disk_cone(ray, base_center, cone, &t_base)
		&& t_base > 1e-4)
	{
		*t = t_base;
		return (1);
	}
	return (0);
}
/*
Que fait-elle ? Teste si un rayon touche la base circulaire d’un cône.
Comment ?
Calcule le centre de la base à partir de l’apex et de l’axe.
Appelle inter_disk_cone pour vérifier s’il y a intersection avec ce disque.
Si oui, renvoie l’intersection via t.
Pourquoi ? Un cône visuellement complet nécessite
une base plate en plus de ses flancs.
*/

void	inter_plus(t_arg_inter *arg, t_cylinder *cyl, t_cone *cone)
{
	arg->min = arg->base;
	arg->hit_side = 0;
	if (cyl)
		cyl->who_inter = arg->hit_base;
	else if (cone)
		cone->who_inter = arg->hit_base;
}

/*
Que fait-elle ? Met à jour les données d’intersection si 
la base est touchée avant le flanc du cône.
Comment ?
Met à jour min avec la distance trouvée pour la base.
Réinitialise le drapeau de hit latéral.
Pourquoi ? Pour garantir que c’est bien l’intersection
la plus proche qui est retenue.
*/
int	intersection_cone(t_ray ray, t_cone *cone, double *t)
{
	t_arg_inter	arg;

	init_arg(&arg);
	cone->who_inter = 0;
	if (inter_cone(vec_sub(ray.origin, cone->apex), ray.dir,
			cone, &arg.side))
	{
		arg.p = vec_add(ray.origin, vec_scale(ray.dir, arg.side));
		arg.m = vec_dot(vec_sub(arg.p, cone->apex), cone->axe);
		if (arg.m >= 0 && arg.m <= cone->height && arg.side > 1e-4)
		{
			arg.min = arg.side;
			arg.hit_side = 1;
		}
	}
	arg.hit_base = base_cone(ray, cone, &arg.base);
	if (arg.hit_base && arg.base < arg.min)
		inter_plus(&arg, NULL, cone);
	if (arg.hit_side || arg.hit_base)
	{
		*t = arg.min;
		return (1);
	}
	return (0);
}
/*
Que fait-elle ? Teste une intersection complète
avec un cône fermé (flanc + base).
Comment ?
Teste le flanc avec inter_cone.
Vérifie que l’impact se situe entre l’apex et la base.
Teste la base avec base_cone.
Compare les deux t pour garder l’intersection la plus proche.
Pourquoi ? C’est la fonction centrale qui détermine
si et où un rayon frappe un cône.
*/

int	inter_disk_cone(t_ray ray, t_vec centre, t_cone *cone, double *t)
{
	double	denom;
	double	hit;
	double	radius;
	t_vec	p;

	denom = vec_dot(ray.dir, cone->axe);
	radius = cone->height * tan(cone->angle);
	if (fabs(denom) < 1e-6)
		return (0);
	hit = vec_dot(vec_sub(centre, ray.origin), cone->axe) / denom;
	if (hit < 1e-4)
		return (0);
	p = vec_add(ray.origin, vec_scale(ray.dir, hit));
	if (vec_length(vec_sub(p, centre)) > radius)
		return (0);
	*t = hit;
	return (1);
}
/*
Que fait-elle ? Teste l’intersection avec un disque
circulaire placé à la base du cône.
Comment ?
Vérifie que le rayon n’est pas parallèle.
Calcule le point d’impact.
Vérifie que ce point est bien dans le rayon du disque.
Pourquoi ? Complète le cône visuellement : sans ça,
on verrait à travers.
*/
