/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:06:38 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:06:39 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/minirt.h"

void	inter_plus(t_arg_inter *arg, t_cylinder *cyl)
{
	arg->min = arg->base;
	arg->hit_side = 0;
	if (cyl)
		cyl->who_inter = arg->hit_base;
}
/*
Que fait-elle ? Met à jour les données d’intersection si 
la base est touchée avant le flanc du cône.
Comment ?
Met à jour min avec la distance trouvée pour la base.
Réinitialise le drapeau de hit latéral.
Pourquoi ? Pour garantir que c’est bien l’intersection
la plus proche qui est retenue.
*/
