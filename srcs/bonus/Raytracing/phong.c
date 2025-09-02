/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:02:59 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:02:59 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

void	init_light(t_light *light, t_hit *hit, t_vec *dir, double *dist)
{
	*dir = vec_sub(light->pos, hit->point);
	*dist = vec_length(*dir);
	if (*dist > 1e-8)
		*dir = vec_scale(*dir, 1.0 / *dist);
	else
		*dir = (t_vec){0, 0, 0};
}

void	pt_phong(t_scene *scene, t_hit *hit, t_vec light_dir, t_color *final)
{
	t_vec	view_dir;
	t_vec	reflect;
	double	spec;
	t_light	*light;

	light = scene->lights;
	view_dir = vec_normalize(vec_sub(scene->cam.pos, hit->point));
	reflect = vec_normalize(vec_sub(vec_scale(hit->normal, 2.0
					* vec_dot(hit->normal, light_dir)), light_dir));
	spec = pow(fmax(vec_dot(view_dir, reflect), 0.0), 20.0);
	final->r += light->ratio * spec * light->color.r;
	final->g += light->ratio * spec * light->color.g;
	final->b += light->ratio * spec * light->color.b;
}

/*
changement de ft_paint en pt_lambert(paint_lambert)
mise a jour de shade diviser en plusieur fonctions
shade, pt_amb,  init_light
ajout fonction pt_phong
a faire trouve pourquoi il y a des petit grains dans les base du
cylindre et du cone qui ne sont pas présent dans le mandatory
du coup sa viens d'un problème de thread, 
*/