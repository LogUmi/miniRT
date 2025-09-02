/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:02:37 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/03 13:22:09 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strrstr(const char *s0, const char *s1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s0[i] != 0)
		i++;
	while (s1[j] != 0)
		j++;
	if (i-- < j-- || i == -1 || j == -1)
		return (1);
	while (i > -1 && j > -1)
	{
		if (s0[i--] != s1[j--])
			return (1);
	}
	return (0);
}
/* #include <stdio.h>
#include <string.h>
#include <ctype.h>

int	main(void)
{
	char	array [] = "012345c6789012345c6789";
	char	arraybis [] = "000000000000000000000";
	char	test = 'c';
	
	printf("array : %s ... cherche : %c\n", array, test);
	printf("Pas tienne : %p ... %s\n", strrchr(array, test), 
	strrchr(array, test));
	printf("Tienne     : %p ... %s\n", ft_strrchr(array, test), 
		ft_strrchr(array, test));
	printf("array : %s ... cherche : %c\n", arraybis, test);
	printf("Pas tienne : %p ... %s\n", strrchr(arraybis, test), 
		strrchr(arraybis, test));
	printf("Tienne     : %p ... %s\n", ft_strrchr(arraybis, test), 
		ft_strrchr(arraybis, test));
	test = 0;
	printf("array : %s ... cherche : %c\n", array, test);
	printf("Pas tienne : %p ... %s\n", strrchr(array, test), 
	strrchr(array, test));
	printf("Tienne     : %p ... %s\n", ft_strrchr(array, test), 
		ft_strrchr(array, test));
	test = 'c';
	printf("array : %s ... cherche : %c\n", "", test);
	printf("Pas tienne : %p ... %s\n", strrchr("", test), strrchr("", test));
	printf("Tienne     : %p ... %s\n", ft_strrchr("", test),
	nb ft_strrchr("", test));

	return (0);
} */