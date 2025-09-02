/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:04:10 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:04:10 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

void	error(char *s1)
{
	ft_printf("Error %s\n", s1);
	exit (1);
}

void	*ptr_malloc(t_app *app, int from, unsigned int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		if (from == 0)
			free_exit(app, "memory allocation of light pointer failed", 1);
		if (from == 1)
			free_exit(app, "memory allocation of sphere pointer failed", 1);
		if (from == 2)
			free_exit(app, "memory allocation of plane pointer failed", 1);
		if (from == 3)
			free_exit(app, "memory allocation of cylinder pointer failed", 1);
		if (from == 4)
			free_exit(app, "memory allocation of cone pointer failed", 1);
	}
	return (ptr);
}

int	count_token(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}
