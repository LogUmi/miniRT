/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:53:57 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/18 11:53:57 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_BONUS_H
# define MINIRT_STRUCT_BONUS_H

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
	int		mode;
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
	int		mode;
}			t_plane;

typedef struct s_cylinder
{
	t_vec	centre;
	t_vec	axe;
	double	diametre;
	double	height;
	t_color	color;
	int		who_inter;
	int		mode;
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

typedef struct s_cone
{
	t_vec	apex;
	t_vec	axe;
	double	angle;
	double	height;
	t_color	color;
	int		who_inter;
	int		mode;
}				t_cone;

typedef struct s_arg_co
{
	double		k;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t0;
	double		t1;
}				t_arg_co;

//Struct générique pour un objet
typedef struct s_obj
{
	t_type_obj		type;
	int				mode;
	union u_obj
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
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
	void		*culight;
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
	double		r;
	double		angle_max;
	double		angle_azim;
	t_vec		forward;
	t_vec		right;
	t_vec		up;
	t_vec		pixel_dir;
}				t_arg_ray;

typedef struct s_dam_sphere
{
	t_vec	n;
	double	theta;
	double	phi;
	double	u;
	double	v;
	int		iu;
	int		iv;
}				t_dam1;

typedef struct s_dam_cone
{
	t_vec	u;
	t_vec	v;
	t_vec	rel;
	double	ux;
	double	vx;
}				t_dam2;

typedef struct s_texture
{
	t_vec	normal;
	t_vec	n;
	t_vec	tangent;
	t_vec	bitangent;
	t_vec	tn;
	t_vec	local_pos;
	t_vec	dir;
	t_vec	p;
	t_vec	flat;
	t_vec	up;
	t_vec	right;
	t_vec	cent;
	t_vec	axis;
	double	r;
	double	h;
	double	u;
	double	v;
	double	x;
	double	y;
	double	theta;
	double	phi;
	int		iu;
	int		iv;
}			t_textu;

//Stocker les informations d'une intersection lors du raytracing
typedef struct s_hit
{
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
	int		hit;
}				t_hit;

typedef struct s_bump
{
	int			l;
	int			h;
	int			n_color;
	int			n_byte;
	int			**color;
	int			*point;
}				t_bump;

typedef struct s_app
{
	t_scene		scene;
	t_window	window;
	t_image		image;
	t_bump		*bump[5];
	t_obj		*obj;
	int			fd;
	char		*str;
	char		**line;
	char		**token;
	char		**split;
	int			fish;
}				t_app;

#endif