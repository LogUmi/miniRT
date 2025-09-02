/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:00:31 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:00:32 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/minirt_bonus.h"

static void	test_format1(t_app *app, char *s, int j)
{
	int	k;

	k = j;
	while (s[j] != 0 && ((s[j] > 47 && s[j] < 58) || (s[j] > 64 && s[j] < 71)
			|| (s[j] > 96 && s[j] < 103)))
	{
		if (s[j] > 64 && s[j] < 71)
			s[j] = s[j] + 32;
		j++;
	}
	if ((j - k) != 6)
		free_exit(app, "unexpected/unsupported color format in palette", 1);
	if (s[j] != 0 && s[j] != '\"')
		free_exit(app, "missing closing quote after color", 1);
	j++;
	if (!(s[j] != 0 && s[j] == ',' && s[j + 1] != 0 && s[j + 1] == '\n'))
		free_exit(app, "unexpected/unsupported end line format in palette", 1);
}

/* Vérifie la validité des caractères (hexadécimal) des codes couleurs rgb
ainsi que de la fin de ligne.
Passe les caractères alpha en minuscule cas échéant*/

static void	test_format0(t_app *app, char *s, int *j, char c)
{
	int	k;

	k = (*j);
	while (s[(*j)] != 0 && (s[(*j)] == 32 || (s[(*j)] > 8 && s[(*j)] < 14)))
		(*j)++;
	if ((*j) == k || ((*j) > k && s[(*j)] != c))
		free_exit(app, "unexpected/unsupported format in palette section", 1);
	(*j)++;
}
/* Vérifie les l'existence des séparateurs et la validité attendue
 du caractère suivant 'c' en milieu de ligne et '#' devant les données rgb*/

static void	treat_palette(t_app *app, char *s, t_bump *bump, int i)
{
	int	j;
	int	k;

	j = 1;
	k = 0;
	if (s[0] != '\"')
		free_exit(app, "missing opening quote before color", 1);
	app->line[i] = (char *)ft_calloc(bump->n_byte + 1, sizeof(char));
	if (!app->line[i])
		free_exit(app, "image palette identifier item allocation failed", 1);
	while (j < (bump->n_byte + 1))
		app->line[i][k++] = s[j++];
	test_format0(app, s, &j, 'c');
	test_format0(app, s, &j, '#');
	test_format1(app, s, j);
	get_img_rgb(app, bump, &s[j], i);
}
/* traite la ligne de palette: extrait l'identifiant palette et la couleur*/

void	get_img_palette(t_app *app, t_bump *bump, char *s)
{
	int		i;

	app->line = (char **)ft_calloc(bump->n_color + 1, sizeof(char *));
	if (!app->line)
		free_exit(app, "image palette identifier header allocation failed", 1);
	bump->color = (int **)ft_calloc(bump->n_color + 1, sizeof(int *));
	if (!bump->color)
		free_exit(app, "image palette rgb header allocation failed", 1);
	i = 0;
	while (i < bump->n_color)
	{
		s = get_next_lines(app->fd);
		if (!s)
			free_exit(app, "unexpected end of file in palette section", 1);
		treat_palette(app, s, bump, i);
		i++;
	}
}
/* charge les n couleurs de la palette défini dans le header*/
