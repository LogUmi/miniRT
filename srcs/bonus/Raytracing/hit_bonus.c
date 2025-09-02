/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:11 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:54:50 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

void	hit_sphere(t_hit *hit, double *t, t_ray ray, t_app *app)
{
	t_obj	*obj;

	obj = app->obj;
	hit->t = (*t);
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, (*t)));
	hit->normal = vec_normalize(vec_sub(hit->point, obj->data.sphere.centre));
	hit->color = color_by_mode(hit, obj, app);
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}

void	hit_plane(t_hit *hit, double *t, t_ray ray, t_app *app)
{
	t_obj	*obj;

	obj = app->obj;
	hit->t = (*t);
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, (*t)));
	hit->normal = obj->data.plane.normal;
	hit->color = color_by_mode(hit, obj, app);
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}

void	hit_cyl(t_hit *hit, double *t, t_ray ray, t_app *app)
{
	double	m;
	t_vec	oc;
	t_obj	*obj;

	obj = app->obj;
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
	hit->color = color_by_mode(hit, obj, app);
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}

void	hit_cone(t_hit *hit, double *t, t_ray ray, t_app *app)
{
	t_vec	oc;
	double	m;
	double	k;
	t_obj	*obj;

	obj = app->obj;
	k = tan(obj->data.cone.angle);
	hit->t = (*t);
	hit->point = vec_add(ray.origin, vec_scale(ray.dir, (*t)));
	if (obj->data.cone.who_inter == 1)
		hit->normal = obj->data.cone.axe;
	else
	{
		oc = vec_sub(hit->point, obj->data.cone.apex);
		m = vec_dot(ray.dir, obj->data.cone.axe) * (*t)
			+ vec_dot(vec_sub(ray.origin, obj->data.cone.apex),
				obj->data.cone.axe);
		hit->normal = vec_normalize(vec_sub(oc, vec_scale(obj->data.cone.axe,
						(1 + k * k) * m)));
	}
	hit->color = color_by_mode(hit, obj, app);
	hit->hit = 1;
	if (vec_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec_scale(hit->normal, -1);
}
