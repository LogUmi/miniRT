/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_fonctions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:54:25 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:45:50 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FONCTIONS_H
# define MINIRT_FONCTIONS_H

# include "minirt_struct.h"

//PARSING
void	pars_sphere(t_app *app, t_obj **objs);
void	pars_plane(t_app *app, t_obj **objs);
void	pars_cylinder(t_app *app, t_obj **objs);

void	pars_amb(t_app *app);
t_color	pars_color(t_app *app, const char *str);
t_vec	pars_vec(t_app *app, const char *str);

void	pars_cam(t_app *app);
void	pars_light(t_app *app, t_light **lights);
void	check_scene(t_app *app);

void	pars_elems(t_app *app);
void	pars_line(t_app *app, char *line);
void	pars_obj(t_app *app);
void	pars_scene(t_app *app, char **av);

//RAYTRACING
void	hit_sphere(t_hit *hit, double *t, t_ray ray, t_obj *obj);
void	hit_plane(t_hit *hit, double *t, t_ray ray, t_obj *obj);
void	hit_cyl(t_hit *hit, double *t, t_ray ray, t_obj *obj);

int		intersection_sphere(t_ray ray, t_sphere *sphere, double *t);
int		intersection_plane(t_ray ray, t_plane *plane, double *t);
int		intersection_cylinder(t_ray ray, t_cylinder *cyl, double *t);

t_ray	generate_ray(int i, int j, t_cam *cam, t_window *win);
t_color	trace_ray(t_ray ray, t_scene *scene);

void	put_pixel(t_image *img, int x, int y, t_color color);
void	render_scene(t_app *app, t_scene *scene, t_window *win);

t_color	the_color(t_color final);
int		in_shadow(t_scene *scene, t_vec point, t_vec light_dir,
			double light_dist);
void	ft_paint(t_light *light, t_hit *hit, t_color *final, t_vec light_dir);
t_color	shade(t_scene *scene, t_hit *hit);

double	vec_dot(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
void	ft_type(t_obj *obj, t_ray ray, double *t, t_hit *hit);
int		inter_cyl(t_vec oc, t_vec dir, t_cylinder *cyl, double *t);

int		base_cylinder(t_ray ray, t_cylinder *cyl, double *t, int labase);
int		inter_disk_cyl(t_ray ray, t_vec centre, t_cylinder cyl, double *t);
void	inter_plus(t_arg_inter *arg, t_cylinder *cyl);

//SRC
void	error(char *s1);
void	*ptr_malloc(t_app *app, int from, unsigned int size);

int		free_exit(t_app *app, char *msg, int ret);
int		control_key(int keycode, t_app *app);

void	free_split(char **line);
void	free_scene(t_scene *scene);

void	init(t_app *app);
void	init_window(t_app *app, int width, int height);
void	init_image(t_app *app, int width, int height);

t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, double s);
t_vec	vec_cross(t_vec a, t_vec b);
double	vec_length(t_vec v);
t_vec	vec_normalize(t_vec v);

char	*readfile(t_app *app, char *str, int fd);
int		ft_iscolor(int color);
void	replace_tabs(char *line);
char	*is_numb(t_app *app, char *str, int type);

double	ft_atof(const char *nptr);

#endif