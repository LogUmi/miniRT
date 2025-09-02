/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_unsi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:17:34 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/15 19:23:36 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	in_base(char *bs, char c)
{
	int	i;

	i = 0;
	while (bs[i] != 0)
	{
		if (bs[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoi_base_unsi(const char *nptr, char *bs)
{
	int	i;
	int	nb;
	int	val;

	i = 0;
	val = 0;
	nb = ft_strlen(bs);
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	while (nptr[i] != 0 && in_base(bs, nptr[i]) != -1)
	{
		val = (val * nb);
		val = val + in_base(bs, (nptr[i]));
		i++;
	}
	return (val);
}
/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void	ft_print(char *s1)
{
	printf("chaine: %s\n", s1);
	printf("fct originale: %d\n", atoi(s1));
	printf("Ta fonction  : %d\n\n", ft_atoi(s1));
}

int	main(void)
{
	char s1[] ="      4568654";
	
	s1[0] = 9;
	s1[1] = 10;
	s1[2] = 11;
	s1[3] = 12;
	s1[4] = 13;
	ft_print(s1);
	ft_print(" +012345[]]");
	ft_print("- 012345dsd");
	ft_print(" -012345dsd");
	ft_print("-2147483648");
	ft_print("--2147483648");
	ft_print("+-2147483648");
	ft_print("2147483648");
	ft_print("-42147483648");
	ft_print("25644147483648");
	ft_print("0x147483648");
	ft_print("");
	return (0);
} */