/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:08:25 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:08:25 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/minirt.h"

static void	read_error(t_app *app, char *str, int ret)
{
	free(str);
	str = NULL;
	if (ret == 1)
		free_exit(app, "reading file allocation failed", 1);
	if (ret == 2)
		free_exit(app, "failed to read file", 1);
}

char	*readfile(t_app *app, char *str, int fd)
{
	char	buff[BUFF_SIZE + 1];
	char	*ptr;
	int		ret;

	if (!str)
		str = ft_strdup("");
	ret = read(fd, buff, BUFF_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		ptr = str;
		str = ft_strjoin(str, buff);
		if (!str)
			read_error(app, ptr, 1);
		free (ptr);
		ret = read(fd, buff, BUFF_SIZE);
	}
	if (ret < 0)
		read_error(app, str, 2);
	return (str);
}
/*
Elle lit tout le contenu d’un fichier pointé par fd 
et le stocke dans une chaîne de caractères.
*/

int	ft_iscolor(int color)
{
	if (color >= 0 && color <= 255)
		return (1);
	return (0);
}

void	replace_tabs(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= 9 && line[i] < 13)
			line[i] = ' ';
		i++;
	}
}

char	*is_numb(t_app *app, char *str, int type)
{
	int	i;
	int	n_type;

	i = 0;
	n_type = 2;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != 0 && ft_isdigit(str[i]) != 0)
	{
		i++;
		n_type = 0;
	}
	if (str[i] != 0 && str[i] == '.')
	{
		i++;
		if (n_type >= 1)
			n_type = 2;
		else
			n_type = 1;
	}
	while (str[i] != 0 && ft_isdigit(str[i]) != 0)
		i++;
	if (str[i] != 0 || n_type > type || n_type == 2)
		free_exit (app, "wrong format number recorded in file", 1);
	return (str);
}
