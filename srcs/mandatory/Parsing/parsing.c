/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:05:59 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:05:59 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/minirt.h"

void	pars_elems(t_app *app)
{
	int		i;

	i = 0;
	app->line = ft_split(app->str, '\n');
	if (!app->line)
		free_exit(app, "line split allocation failed", 1);
	while (app->line[i])
	{
		pars_line(app, app->line[i]);
		i++;
	}
	free_split(app->line);
	app->line = NULL;
}
/*
Coupe les lignes avec ft_split(str, '\n').
Appelle pars_line sur chaque entrée.
Libère la mémoire.
*/

void	pars_line(t_app *app, char *line)
{
	if (!line || !*line || line[0] == '#')
		return ;
	replace_tabs(line);
	app->token = ft_split(line, ' ');
	if (!app->token || !app->token[0])
		return ;
	if (ft_strncmp(app->token[0], "A", 2) == 0)
		pars_amb(app);
	else if (ft_strncmp(app->token[0], "C", 2) == 0)
		pars_cam(app);
	else if (ft_strncmp(app->token[0], "L", 2) == 0)
		pars_light(app, &app->scene.lights);
	else
		pars_obj(app);
	free_split(app->token);
	app->token = NULL;
}
/*
Ignore les commentaires (#) et lignes vides.
Remplace les tabulations par des espaces.
Coupe la ligne en tokens (mots séparés).
Redirige vers la fonction adaptée :
"A" : lumière ambiante
"C" : caméra
"L" : lumière
autre : objet 3D (pars_obj)
*/

void	pars_obj(t_app *app)
{
	char	msg[100];

	msg[0] = 0;
	if (ft_strncmp(app->token[0], "sp", 3) == 0)
		pars_sphere(app, &app->scene.objs);
	else if (ft_strncmp(app->token[0], "pl", 3) == 0)
		pars_plane(app, &app->scene.objs);
	else if (ft_strncmp(app->token[0], "cy", 3) == 0)
		pars_cylinder(app, &app->scene.objs);
	else
	{
		ft_strlcpy(&msg[0], "invalid identifier ", 20);
		ft_strlcat(&msg[0], app->token[0], ft_strlen(app->token[0]) + 20);
		ft_strlcat(&msg[0], " found in file", ft_strlen(app->token[0]) + 34);
		free_exit(app, &msg[0], 1);
	}
}
/*
"sp" → sphère
"pl" → plan
"cy" → cylindre
"co" → cône
Sinon : erreur de format
*/

void	pars_scene(t_app *app, char **av)
{
	int		fd;
	char	msg[100];

	ft_strlcpy(&msg[0], "Scene ", 7);
	ft_strlcat(&msg[0], av[1], ft_strlen(av[1]) + 7);
	fd = open(av[1], 0);
	if (fd == -1)
	{
		ft_strlcat(&msg[0], ": can't open file", ft_strlen(av[1]) + 24);
		free_exit(app, &msg[0], 1);
	}
	ft_strlcat(&msg[0], ": file opened\n", ft_strlen(av[1]) + 21);
	ft_printf("%s", &msg[0]);
	app->str = readfile(app, app->str, fd);
	close (fd);
	if (app->str[0] == 0)
		free_exit(app, "empty file", 1);
	pars_elems(app);
	free (app->str);
	app->str = NULL;
}
/*
Utilise readfile pour charger tout le fichier en mémoire.
Appelle ensuite pars_elems pour traiter chaque ligne.
*/
//Lire → Découper → Identifier → Parsr → Vérifier →
//  Ajouter à la scène → Libérer la mémoire.
