/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:04:29 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:04:29 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

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

void	free_bump(t_app *app, int i, int j)
{
	while (i < 5)
	{
		if (app->bump[i] != NULL)
		{
			if (app->bump[i]->color)
			{
				j = 0;
				while (app->bump[i]->color[j])
					free(app->bump[i]->color[j++]);
				free(app->bump[i]->color);
			}
			if (app->bump[i]->point)
				free(app->bump[i]->point);
			free(app->bump[i]);
		}
		i++;
	}
}
