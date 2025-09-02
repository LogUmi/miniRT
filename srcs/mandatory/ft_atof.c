/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:08:01 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:08:02 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/minirt.h"

static double	finalize_double(double val, double expo)
{
	double	magnitude;

	magnitude = log10(fabs(val)) + expo;
	if (magnitude > 308.0)
	{
		if (val > 0.0)
			return (INFINITY);
		else
			return (-INFINITY);
	}
	else if (magnitude < -324.0)
		return (0.0);
	else
		return (val * pow(10.0, expo));
}

static double	get_exponent(const char *str, int *i)
{
	double	val;
	double	sign;

	val = 0.0;
	sign = 1.0;
	if (str[(*i)] == 'e' || str[(*i)] == 'E')
	{
		(*i)++;
		while ((str[(*i)] > 8 && str[(*i)] < 14) || str[(*i)] == 32)
			(*i)++;
		if (str[(*i)] == '-' || str[(*i)] == '+')
			if (str[(*i)++] == '-')
				sign = sign * -1.0;
		while (str[(*i)] > 47 && str[(*i)] < 58)
			val = (val * 10.0) + (str[(*i)++] - 48);
		val *= sign;
	}
	return (val);
}

static double	under_coma(const char *str, int *i)
{
	double	val;
	double	frac;

	val = 0.0;
	frac = 0.1;
	if (str[(*i)] == '.')
	{
		(*i)++;
		while (str[(*i)] > 47 && str[(*i)] < 58)
		{
			val += (str[(*i)] - 48) * frac;
			frac = frac * 0.1;
			(*i)++;
		}
	}
	return (val);
}

double	ft_atof(const char *nptr)
{
	int		i;
	double	expo;
	double	val;
	double	sign;

	i = 0;
	val = 0.0;
	sign = 1.0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = sign * -1.0;
	while (nptr[i] > 47 && nptr[i] < 58)
		val = (val * 10.0) + (nptr[i++] - 48);
	val = (val + under_coma(nptr, &i)) * sign;
	expo = get_exponent(nptr, &i);
	if (expo != 0)
		val = finalize_double(val, expo);
	return (val);
}
//DBL_MAX  // environ 1.7976931348623157e+308
//DBL_MIN  // environ 2.2250738585072014e-308