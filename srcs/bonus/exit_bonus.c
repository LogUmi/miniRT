/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:04:19 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:41:17 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

static void	free_exit0(t_app *app)
{
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
}

int	free_exit(t_app *app, char *msg, int ret)
{
	if (ret == 1)
		ft_printf("Error\n");
	if (*msg)
		ft_printf("%s\n", msg);
	if (app->str != NULL)
		free(app->str);
	if (app->fd >= 0)
		close(app->fd);
	free_split(app->line);
	free_split(app->token);
	free_split(app->split);
	free_scene(&app->scene);
	free_bump(app, 0, 0);
	free_exit0(app);
	exit (ret);
}

int	control_key(int keycode, t_app *app)
{
	if (keycode == 65307)
		free_exit(app, "Regular end of session on esc key press", 0);
	return (0);
}
