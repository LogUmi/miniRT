/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:56 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:07:56 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/minirt.h"

void	free_split(char **line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		free(line[i]);
		line[i] = NULL;
		i++;
	}
	free(line);
	line = NULL;
}

void	free_scene(t_scene *scene)
{
	t_obj	*obj;
	t_obj	*tmp;
	t_light	*light;
	t_light	*ltmp;

	obj = scene->objs;
	while (obj)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
	light = scene->lights;
	while (light)
	{
		ltmp = light->next;
		free(light);
		light = ltmp;
	}
}
