/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:03:41 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 22:47:48 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static void	set_offset(int *x, int *y, int mode)
{
	if (mode == 1)
		(*x) = (*x) + IMAGE1_OFFSET_X;
	if (mode == 1)
		(*y) = (*y) + IMAGE1_OFFSET_Y;
	if (mode == 2)
		(*x) = (*x) + IMAGE2_OFFSET_X;
	if (mode == 2)
		(*y) = (*y) + IMAGE2_OFFSET_Y;
	if (mode == 3)
		(*x) = (*x) + IMAGE3_OFFSET_X;
	if (mode == 3)
		(*y) = (*y) + IMAGE3_OFFSET_Y;
	if (mode == 4)
		(*x) = (*x) + IMAGE4_OFFSET_X;
	if (mode == 4)
		(*y) = (*y) + IMAGE4_OFFSET_Y;
	if (mode == 5)
		(*x) = (*x) + IMAGE5_OFFSET_X;
	if (mode == 5)
		(*y) = (*y) + IMAGE5_OFFSET_Y;
}

t_color	get_pixel_color(t_bump *bump, int x, int y, int mode)
{
	int		pixel;
	t_color	color;

	set_offset(&x, &y, mode);
	while (x < 0)
		x = bump->l + x;
	while (x > bump->l)
		x = x - bump->l;
	while (y < 0)
		y = bump->h + y;
	while (y > bump->h)
		y = y - bump->l;
	pixel = x + y * bump->l;
	color.r = bump->color[bump->point[pixel]][0];
	color.g = bump->color[bump->point[pixel]][1];
	color.b = bump->color[bump->point[pixel]][2];
	return (color);
}

static t_color	texture_cyl_side(t_hit *hit, t_bump *bump, t_cylinder *cyl,
								int scl)
{
	t_textu		cy;

	(void)scl;
	cy.dir = vec_sub(hit->point, cyl->centre);
	cy.axis = vec_normalize(cyl->axe);
	if (fabs(cy.axis.y) < 0.99)
		cy.up = (t_vec){0, 1, 0};
	else
		cy.up = (t_vec){1, 0, 0};
	cy.tangent = vec_normalize(vec_cross(cy.up, cy.axis));
	cy.bitangent = vec_cross(cy.axis, cy.tangent);
	cy.x = vec_dot(cy.dir, cy.tangent);
	cy.y = vec_dot(cy.dir, cy.bitangent);
	cy.theta = atan2(cy.y, cy.x);
	cy.u = (cy.theta + M_PI) / (2.0 * M_PI);
	cy.h = vec_dot(cy.dir, cy.axis);
	cy.v = (cy.h + cyl->height / 2.0) / cyl->height;
	cy.iu = ((int)(cy.u * bump->l * scl) % bump->l + bump->l) % bump->l;
	cy.iv = ((int)((1.0 - cy.v) * bump->h * scl) % bump->h + bump->h) % bump->h;
	return (get_pixel_color(bump, cy.iu, cy.iv, cyl->mode));
}

static t_color	texture_disk(t_hit *hit, t_bump *bump, t_cylinder *cyl,
								int scl)
{
	t_textu	cy;

	(void)scl;
	if (cyl->who_inter == BASE_INF)
		cy.cent = vec_sub(cyl->centre, vec_scale(cyl->axe, cyl->height / 2.0));
	else
		cy.cent = vec_add(cyl->centre, vec_scale(cyl->axe, cyl->height / 2.0));
	cy.r = cyl->diametre / 2.0;
	cy.dir = vec_sub(hit->point, cy.cent);
	if (fabs(cyl->axe.y) < 0.99)
		cy.up = (t_vec){0, 1, 0};
	else
		cy.up = (t_vec){1, 0, 0};
	cy.right = vec_normalize(vec_cross(cy.up, cyl->axe));
	cy.up = vec_cross(cyl->axe, cy.right);
	cy.u = vec_dot(cy.dir, cy.right) / (2.0 * cy.r) + 0.5;
	cy.v = vec_dot(cy.dir, cy.up) / (2.0 * cy.r) + 0.5;
	cy.iu = ((int)(cy.u * bump->l) % bump->l + bump->l) % bump->l;
	cy.iv = ((int)((1.0 - cy.v) * bump->h) % bump->h + bump->h) % bump->h;
	return (get_pixel_color(bump, cy.iu, cy.iv, cyl->mode));
}

t_color	texture_cylinder(t_hit *hit, t_bump *bump, t_cylinder *cyl, double scl)
{
	if (cyl->who_inter == 0)
		return (texture_cyl_side(hit, bump, cyl, scl));
	else if (cyl->who_inter == BASE_INF || cyl->who_inter == BASE_SUP)
		return (texture_disk(hit, bump, cyl, scl));
	else
		return ((t_color){255, 0, 255});
}
