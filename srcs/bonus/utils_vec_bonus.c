/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:12:07 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 12:12:07 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}
/*
Que fait-elle ? Additionne deux vecteurs, composante par composante.
Comment ? Retourne un nouveau vecteur résultant de a + b.
Pourquoi ? Pour déplacer des objets, additionner des directions, etc.
Exemple : Additionner deux vecteurs de déplacement.
Si un objet se déplace de (1, 2, 3) puis de (4, -1, 2),
le déplacement total est (5, 1, 5)
*/

t_vec	vec_scale(t_vec v, double s)
{
	return ((t_vec){v.x * s, v.y * s, v.z * s});
}
/*
Que fait-elle ? Multiplie un vecteur par un scalaire.
Comment ? Chaque composante du vecteur est multipliée par s.
Pourquoi ? Utile pour étirer, réduire ou moduler une direction.
*/

t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}
/*
Que fait-elle ? Calcule le produit vectoriel entre a et b. 
Comment ? Applique la formule mathématique du produit vectoriel.
Pourquoi ? Sert à trouver un vecteur perpendiculaire,
notamment pour définir des plans ou construire des bases orthogonales.
*/

double	vec_length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
/*
Que fait-elle ? Retourne la norme (longueur) du vecteur.
Comment ? Utilise la racine carrée de la somme des carrés des composantes. 
Pourquoi ? Nécessaire pour évaluer des distances, 
des forces, ou normaliser un vecteur.
*/

t_vec	vec_normalize(t_vec v)
{
	double	len;

	len = vec_length(v);
	if (len == 0)
		return ((t_vec){0, 0, 0});
	return ((t_vec){v.x / len, v.y / len, v.z / len});
}
/*
Que fait-elle ? Convertit un vecteur en un vecteur unitaire (de longueur 1).
Comment ? Divise chaque composante par la norme du vecteur.
Cas particulier : Si la norme est 0 → renvoie un vecteur nul.
Pourquoi ? Indispensable pour manipuler des directions, notamment en ray tracing.
*/
