/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:03:31 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 22:54:02 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

t_color	texture_sphere(t_hit *hit, t_bump *bump, int mode)
{
	t_textu	sp;
	t_color	color;

	sp.n = vec_normalize(hit->normal);
	sp.theta = atan2(sp.n.z, sp.n.x);
	sp.phi = acos(fmax(-1.0, fmin(1.0, sp.n.y)));
	sp.u = (sp.theta + M_PI) / (2.0 * M_PI);
	sp.v = sp.phi / M_PI;
	sp.iu = (int)(sp.u * bump->l);
	sp.iv = (int)(sp.v * bump->h);
	color = get_pixel_color(bump, sp.iu, sp.iv, mode);
	return (color);
}

t_color	texture_plane(t_hit *hit, t_bump *bump, int mode, double scale)
{
	t_textu	pl;

	pl.normal = hit->normal;
	if (fabs(pl.normal.y) < 0.999)
		pl.tangent = vec_cross(pl.normal, (t_vec){0, 1, 0});
	else
		pl.tangent = vec_cross(pl.normal, (t_vec){1, 0, 0});
	pl.tangent = vec_normalize(pl.tangent);
	pl.bitangent = vec_cross(pl.normal, pl.tangent);
	pl.local_pos = hit->point;
	pl.u = vec_dot(pl.local_pos, pl.tangent);
	pl.v = vec_dot(pl.local_pos, pl.bitangent);
	pl.iu = ((int)(pl.u * scale) % bump->l + bump->l) % bump->l;
	pl.iv = ((int)(pl.v * scale) % bump->h + bump->h) % bump->h;
	return (get_pixel_color(bump, pl.iu, pl.iv, mode));
}

t_color	texture_cone_side(t_hit *hit, t_bump *bump, t_cone *cone, double scl)
{
	t_textu	co;

	co.dir = vec_sub(hit->point, cone->apex);
	co.h = vec_dot(co.dir, cone->axe);
	co.h = fmax(0.0, fmin(cone->height, co.h));
	co.cent = vec_add(cone->apex, vec_scale(cone->axe, co.h));
	co.local_pos = vec_sub(hit->point, co.cent);
	co.local_pos = co.local_pos;
	co.theta = atan2(co.local_pos.z, co.local_pos.x);
	co.u = (co.theta + M_PI) / (2.0 * M_PI);
	co.v = co.h / cone->height;
	co.iu = ((int)(co.u * bump->l * scl) % bump->l + bump->l) % bump->l;
	co.iv = ((int)((1.0 - co.v) * bump->h * scl) % bump->h + bump->h) % bump->h;
	return (get_pixel_color(bump, co.iu, co.iv, cone->mode));
}

t_color	texture_cone_base(t_hit *hit, t_bump *bump, t_cone *cone, double scl)
{
	t_textu	co;

	co.cent = vec_add(cone->apex, vec_scale(cone->axe, cone->height));
	co.local_pos = vec_sub(hit->point, co.cent);
	co.h = cone->height * tan(cone->angle);
	if (fabs(cone->axe.y) < 0.99)
		co.up = (t_vec){0, 1, 0};
	else
		co.up = (t_vec){1, 0, 0};
	co.right = vec_normalize(vec_cross(co.up, cone->axe));
	co.up = vec_cross(cone->axe, co.right);
	co.r = cone->height * tan(cone->angle);
	co.u = vec_dot(co.local_pos, co.right) / (2.0 * co.r) + 0.5;
	co.v = vec_dot(co.local_pos, co.up) / (2.0 * co.r) + 0.5;
	co.iu = ((int)(co.u * bump->l * scl) % bump->l + bump->l) % bump->l;
	co.iv = ((int)((1.0 - co.v) * bump->h * scl) % bump->h
			+ bump->h) % bump->h;
	return (get_pixel_color(bump, co.iu, co.iv, cone->mode));
}

t_color	texture_cone(t_hit *hit, t_bump *bump, t_cone *cone, double scale)
{
	if (cone->who_inter == 0)
		return (texture_cone_side(hit, bump, cone, scale));
	else if (cone->who_inter == 1)
		return (texture_cone_base(hit, bump, cone, scale));
	else
		return ((t_color){255, 0, 255});
}
