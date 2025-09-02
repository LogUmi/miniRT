/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:54:36 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 11:54:36 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

//vecteur 3D
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

//Couleur avec des composant RGB
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

//Lumiere d'ambiance
typedef struct s_amb
{
	double	ratio;
	t_color	color;
}			t_amb;

//Caméra
typedef struct s_cam
{
	t_vec	pos;
	t_vec	dir;
	double	fov;//(Field Of View)
}			t_cam;

//Lumière (possible multiple)
typedef struct s_light
{
	t_vec			pos;
	double			ratio;
	t_color			color;
	struct s_light	*next;
}				t_light;

//Enumeration pour les objets
typedef enum e_type_obj
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}				t_type_obj;

typedef struct s_sphere
{
	t_vec	centre;
	double	diametre;
	t_color	color;
}			t_sphere;

typedef struct s_sphere_arg
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	neg;
	double	t0;
	double	t1;
}			t_sphere_arg;

typedef struct s_plane
{
	t_vec	point;
	t_vec	normal;
	t_color	color;
}			t_plane;

typedef struct s_cylinder
{
	t_vec	centre;
	t_vec	axe;
	double	diametre;
	double	height;
	t_color	color;
	int		who_inter;
}			t_cylinder;

typedef struct s_arg_cyl
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t0;
	double	t1;
}			t_arg_cyl;

typedef struct s_arg_base_cyl
{
	double	t1;
	double	t2;
	int		hit;
	double	min;
	t_vec	base1;
	t_vec	base2;
}			t_arg_base_cyl;

//Struct générique pour un objet
typedef struct s_obj
{
	t_type_obj		type;
	union u_obj
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	} data;
	struct s_obj	*next;
}				t_obj;

typedef struct s_arg_inter
{
	double		side;
	double		base;
	double		min;
	double		m;
	int			hit_side;
	int			hit_base;
	t_vec		p;
}				t_arg_inter;

//Fenetre et environnement graphique
typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		width;
	int		height;
	int		swidth;
	int		sheight;
}				t_window;

//Image (buffer pixel par pixel)
typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_scene
{
	t_amb		amb;
	t_cam		cam;
	t_light		*lights;
	t_obj		*objs;
	int			cam_set;
	int			amb_set;
	int			light_set;
}				t_scene;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}			t_ray;

typedef struct s_arg_ray
{
	t_ray		ray;
	double		aspect;
	double		px;
	double		py;
	double		scale;
	t_vec		forward;
	t_vec		right;
	t_vec		up;
	t_vec		pixel_dir;
}				t_arg_ray;

//Stocker les informations d'une intersection lors du raytracing
typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
	int		hit;
}				t_hit;

typedef struct s_app
{
	t_scene		scene;
	t_window	window;
	t_image		image;
	char		*str;
	char		**line;
	char		**token;
	char		**split;
}				t_app;

#endif