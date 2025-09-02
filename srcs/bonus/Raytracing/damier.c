/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:02 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:02:02 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static t_color	xor_color(t_color c1)
{
	t_color	c2;

	c2.r = c1.r ^ 0xFF;
	c2.g = c1.g ^ 0xFF;
	c2.b = c1.b ^ 0xFF;
	return (c2);
}

t_color	dam_plan(t_hit *hit, double scale)
{
	t_textu	pl;
	t_color	c1;
	t_color	c2;

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
	pl.iu = (int)floor((pl.u + 0.5 / scale) * scale);
	pl.iv = (int)floor((pl.v + 0.5 / scale) * scale);
	c1 = hit->color;
	c2 = xor_color(c1);
	if ((pl.iu + pl.iv) % 2 == 0)
		return (c1);
	else
		return (c2);
}

t_color	dam_sphere(const t_hit *hit, double scale, t_dam1 *arg)
{
	int		iu;
	int		iv;
	t_color	c1;
	t_color	c2;

	arg->n = hit->normal;
	arg->theta = atan2(arg->n.z, arg->n.x);
	arg->phi = acos(fmax(-1.0, fmin(1.0, arg->n.y)));
	arg->u = (arg->theta + M_PI) / (2.0 * M_PI);
	arg->v = arg->phi / M_PI;
	c1 = hit->color;
	c2 = xor_color(c1);
	iu = (int)floor(arg->u * scale);
	iv = (int)floor(arg->v * scale / 2);
	if ((iu + iv) % 2 == 0)
		return (c1);
	else
		return (c2);
}

t_color	dam_cyl(const t_hit *hit, const t_cylinder *cyl,
	double scale, t_dam2 *arg)
{
	int		iu;
	int		iv;
	t_color	c1;
	t_color	c2;
	t_vec	up;

	c1 = hit->color;
	c2 = xor_color(c1);
	up = (t_vec){0, 1, 0};
	if (fabs(vec_dot(cyl->axe, up)) > 0.99)
		up = (t_vec){1, 0, 0};
	arg->u = vec_normalize(vec_cross(cyl->axe, up));
	arg->v = vec_cross(cyl->axe, arg->u);
	arg->rel = vec_sub(hit->point, cyl->centre);
	arg->ux = vec_dot(arg->rel, arg->u) * scale;
	arg->vx = vec_dot(arg->rel, arg->v) * scale;
	iu = (int)floor(arg->ux);
	iv = (int)floor(arg->vx);
	if ((iu + iv) % 2 == 0)
		return (c1);
	else
		return (c2);
}

t_color	dam_cone(const t_hit *hit, const t_cone *cone, double scale,
				t_dam2 *arg)
{
	int		iu;
	int		iv;
	t_color	c1;
	t_color	c2;

	c1 = hit->color;
	c2 = xor_color(c1);
	arg->u = vec_normalize(vec_cross(cone->axe, (t_vec){0, 1, 0}));
	arg->v = vec_cross(cone->axe, arg->u);
	arg->rel = vec_sub(hit->point, cone->apex);
	arg->ux = vec_dot(arg->rel, arg->u) * scale;
	arg->vx = vec_dot(arg->rel, arg->v) * scale;
	iu = (int)floor(arg->ux);
	iv = (int)floor(arg->vx);
	if ((iu + iv) % 2 == 0)
		return (c1);
	else
		return (c2);
}
