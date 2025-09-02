/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:50 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:07:51 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/minirt.h"

int	free_exit(t_app *app, char *msg, int ret)
{
	if (ret == 1)
		ft_printf("Error\n");
	if (*msg)
		ft_printf("%s\n", msg);
	if (app->str != NULL)
		free(app->str);
	free_split(app->line);
	free_split(app->token);
	free_split(app->split);
	free_scene(&app->scene);
	if (app->window.img_ptr && app->window.mlx_ptr)
		mlx_destroy_image(app->window.mlx_ptr, app->window.img_ptr);
	if (app->image.img_ptr && app->window.mlx_ptr)
		mlx_destroy_image(app->window.mlx_ptr, app->image.img_ptr);
	if (app->window.win_ptr && app->window.mlx_ptr)
		mlx_destroy_window(app->window.mlx_ptr, app->window.win_ptr);
	if (app->window.mlx_ptr)
	{
		mlx_destroy_display(app->window.mlx_ptr);
		free(app->window.mlx_ptr);
	}
	exit (ret);
}

int	control_key(int keycode, t_app *app)
{
	if (keycode == 65307)
		free_exit(app, "Regular end of session on esc key press", 0);
	return (0);
}
