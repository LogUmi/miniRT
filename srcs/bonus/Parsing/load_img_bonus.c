/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:00:15 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:00:16 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static int	img_head(t_app *app, char *s, int *i, int *j)
{
	int		k;
	char	c[255];

	k = 0;
	while (s[(*i)] != 0 && (s[(*i)] < 48 || s[(*i)] > 57))
		(*i)++;
	(*j) = (*i);
	while (s[(*i)] != 0 && s[(*i)] > 47 && s[(*i)] < 58)
		c[k++] = s[(*i)++];
	c[k] = 0;
	if (s[(*i)] != 0 && (s[(*i)] == 32 || (s[(*i)] > 8
				&& s[(*i)] < 13) || s[(*i)] == '\"'))
		k = ft_atoi(&c[0]);
	else
		free_exit(app, "invalid header format detected in file", 1);
	return (k);
}
/* Extrait une à une les valeurs du header au format "l h n_color nbyte", */

static void	get_data_img(t_app *app, int mode, char *s)
{
	t_bump	*bump;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = get_next_lines(app->fd);
	if (!s)
		free_exit(app, "unexpected end of file", 1);
	bump = (t_bump *)malloc(sizeof(t_bump));
	if (!bump)
		free_exit(app, "image texture allocation failed", 1);
	app->bump[mode] = bump;
	bump->point = 0;
	bump->color = 0;
	app->bump[mode]->l = img_head(app, s, &i, &j);
	app->bump[mode]->h = img_head(app, s, &i, &j);
	app->bump[mode]->n_color = img_head(app, s, &i, &j);
	app->bump[mode]->n_byte = img_head(app, s, &i, &j);
	ft_printf(" loading ... %ix%i %i colors %i bytes per pixel file\n",
		app->bump[mode]->l, app->bump[mode]->h,
		app->bump[mode]->n_color, app->bump[mode]->n_byte);
	get_img_palette(app, bump, s);
	get_img_points(app, bump, s);
}
/* charge la 3ème ligne du fichier image
et en extraut les données caractéristiques puis enchaîne */

static void	dfile_name(char *str, int mode)
{
	if (mode == 1)
		ft_strlcpy(str, IMAGE1, ft_strlen(IMAGE1) + 1);
	else if (mode == 2)
		ft_strlcpy(str, IMAGE2, ft_strlen(IMAGE2) + 1);
	else if (mode == 3)
		ft_strlcpy(str, IMAGE3, ft_strlen(IMAGE3) + 1);
	else if (mode == 4)
		ft_strlcpy(str, IMAGE4, ft_strlen(IMAGE4) + 1);
	else if (mode == 5)
		ft_strlcpy(str, IMAGE5, ft_strlen(IMAGE5) + 1);
}
/* affecte à str le chemin et nom de fichier image associé au numéro de mode */

static void	load_img_xpm(t_app *app, int mode, char *s)
{
	char	msg[100];
	char	dname[255];

	dfile_name(&dname[0], mode);
	ft_strlcpy(&msg[0], "Image ", 7);
	ft_strlcat(&msg[0], &dname[0], ft_strlen(&dname[0]) + 7);
	app->fd = open(&dname[0], 0);
	if (app->fd == -1)
	{
		ft_strlcat(&msg[0], ": can't open file", ft_strlen(&dname[0]) + 24);
		free_exit(app, &msg[0], 1);
	}
	ft_strlcat(&msg[0], ": file opened\n", ft_strlen(&dname[0]) + 21);
	ft_printf("%s", &msg[0]);
	s = get_next_lines(app->fd);
	if (!s)
		free_exit(app, "empty file", 1);
	if (ft_strncmp(s, "/* XPM */\n", 10) != 0)
		free_exit(app, "xpm file format expected", 1);
	s = get_next_lines(app->fd);
	if (!s)
		free_exit(app, "unexpected end of file", 1);
	if (ft_strncmp(s, "static char", 12) != 0 && ft_strrstr(s, "{\n") != 0)
		free_exit(app, "unsupported xpm file format", 1);
	get_data_img(app, mode - 1, s);
}
/* ouvre le fichier image associé au mode détecté 
et charge 2 premières lignes de déclaration pour vérification du format*/

void	check_mode_img(t_app *app)
{
	t_obj	*obj;

	obj = app->scene.objs;
	while (obj)
	{
		if (obj->mode > 0 && app->bump[obj->mode - 1] == NULL)
			load_img_xpm(app, obj->mode, 0);
		obj = obj->next;
	}
}

/* Balaye les objets pour en fonction des modes (>= 1) éventuellement 
charger le fichier associé si ce n'est pas déjà fait pour un autre objet*/