/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:33 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:02:33 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

t_color	base_color(const t_obj *obj)
{
	if (obj->type == SPHERE)
		return (obj->data.sphere.color);
	else if (obj->type == PLANE)
		return (obj->data.plane.color);
	else if (obj->type == CYLINDER)
		return (obj->data.cylinder.color);
	else if (obj->type == CONE)
		return (obj->data.cone.color);
	return ((t_color){0, 0, 0});
}

t_color	color_by_mode(t_hit *hit, t_obj *obj, t_app *app)
{
	if (obj->mode < 0)
		return (base_color(obj));
	else if (obj->mode == 0)
		return (checker_color(hit, obj));
	else if (obj->mode > 0 && obj->mode <= MAX_TEXTURE)
		return (texture_color(hit, obj, obj->mode, app));
	free_exit(app, "invalid mode in color_by_mode", 1);
	return (base_color(obj));
}

t_color	checker_color(t_hit *hit, t_obj *obj)
{
	t_dam1	arg1;
	t_dam2	arg2;

	hit->color = base_color(obj);
	if (obj->type == SPHERE)
		return (dam_sphere(hit, 20.0, &arg1));
	else if (obj->type == PLANE)
		return (dam_plan(hit, 0.5));
	else if (obj->type == CYLINDER)
		return (dam_cyl(hit, &obj->data.cylinder, 1, &arg2));
	else if (obj->type == CONE)
		return (dam_cone(hit, &obj->data.cone, 1, &arg2));
	return (base_color(obj));
}

t_color	texture_color(t_hit *hit, t_obj *obj, int mod, t_app *app)
{
	t_bump	*img;

	img = app->bump[mod - 1];
	if (!img)
		free_exit(app, "image texture not loaded", 1);
	if (obj->type == SPHERE)
		return (texture_sphere(hit, img, mod));
	else if (obj->type == PLANE)
		return (texture_plane(hit, img, mod, 12.5));
	else if (obj->type == CYLINDER)
		return (texture_cylinder(hit, img, &obj->data.cylinder, 1));
	else if (obj->type == CONE)
		return (texture_cone(hit, img, &obj->data.cone, 1));
	return (base_color(obj));
}
