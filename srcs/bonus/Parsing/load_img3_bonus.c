/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:00:47 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:00:48 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

void	get_img_rgb(t_app *app, t_bump *bump, char *s, int i)
{
	bump->color[i] = (int *)ft_calloc(3, sizeof(int));
	if (!bump->color[i])
		free_exit(app, "image palette rgb component allocation failed", 1);
	s[6] = 0;
	bump->color[i][2] = ft_atoi_base_unsi(&s[4], "0123456789abcdef");
	s[4] = 0;
	bump->color[i][1] = ft_atoi_base_unsi(&s[2], "0123456789abcdef");
	s[2] = 0;
	bump->color[i][0] = ft_atoi_base_unsi(&s[0], "0123456789abcdef");
}
/* conversion des données des couleurs et intégration associée 
au même numéro d'ordre que l'identifiant palette de app->line*/

static void	test_format2(t_app *app, char *s, int l)
{
	if (s[l] != 0 && s[l] != '\"')
		free_exit(app, "missing closing quote after image line", 1);
	l++;
	if (!(s[l] != 0 && ((s[l] == ',' && s[l + 1] != 0 && s[l + 1] == '\n')
				|| (s[l] == '}' && s[l + 1] != 0 && s[l + 1] == ';'
					&& s[l + 2] != 0 && s[l + 2] == '\n'))))
		free_exit(app, "unexpected end line format in image section", 1);
}
/* Vérifie que lq fin de ligne ou de fichier attendue est bien présente*/

static void	set_pcolor(t_app *app, t_bump *bump, char *s, int np)
{
	int	m;
	int	hit;

	m = 0;
	hit = -1;
	while (m < bump->n_color)
	{
		if (ft_strncmp(app->line[m], s, bump->n_byte + 1) == 0)
		{
			hit = m;
			break ;
		}
		m++;
	}
	if (hit == -1)
		free_exit(app, "palette identifier not found to set image point", 1);
	bump->point[np] = hit;
}
/* Cherche l'identifiant palette trouvé dans la section image dans la liste 
des palettes temporairement enregistrée dans la 1ère partie de la lecture
et affecte la couleur du tableau dump->color associée au point cas échéant*/

static void	treat_pline(t_app *app, char *s, t_bump *bump, int i)
{
	int		j;
	int		k;
	int		l;
	char	p[255];

	j = 0;
	l = 1;
	if (s[0] != '\"')
		free_exit(app, "missing opening quote before image points", 1);
	while (j < bump->l)
	{
		k = 0;
		while (k < bump->n_byte)
		{
			if (s[l] == 0 || (s[l] != 0 && s[l] == '\"'))
				free_exit(app, "unexpected end of line in image points", 1);
			p[k++] = s[l++];
		}
		p[k] = 0;
		set_pcolor(app, bump, &p[0], j + i * bump->l);
		j++;
	}
	test_format2(app, s, l);
}
/* Récupére les identifiants palette pour chaque point 
et lance l'attribution de la couleur */

void	get_img_points(t_app *app, t_bump *bump, char *s)
{
	int		i;

	bump->point = (int *)malloc(bump->l * bump->h * sizeof(int));
	if (!bump->color)
		free_exit(app, "image points color allocation failed", 1);
	i = 0;
	while (i < bump->h)
	{
		s = get_next_lines(app->fd);
		if (!s)
			free_exit(app, "unexpected end of file in screen section", 1);
		treat_pline(app, s, bump, i);
		i++;
	}
	free_split(app->line);
	app->line = NULL;
	close (app->fd);
	app->fd = -1;
}
/*lis chaque ligne de l'écran et lance le traitement des points
exécute les libération nécessaire en fin y compris fermeture fichier */
