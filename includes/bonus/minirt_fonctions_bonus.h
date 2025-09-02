/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_fonctions_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:53:48 by lgerard           #+#    #+#             */
/*   Updated: 2025/07/19 20:45:25 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FONCTIONS_BONUS_H
# define MINIRT_FONCTIONS_BONUS_H

# include "minirt_struct_bonus.h"

//PARSING
void	pars_sphere(t_app *app, t_obj **objs, int mode);
void	pars_plane(t_app *app, t_obj **objs, int mode);
void	pars_cylinder(t_app *app, t_obj **objs, int mode);
void	pars_cone(t_app *app, t_obj **objs, int mode);
void	pars_sphere(t_app *app, t_obj **objs, int mode);
void	pars_plane(t_app *app, t_obj **objs, int mode);
void	pars_cylinder(t_app *app, t_obj **objs, int mode);
void	pars_cone(t_app *app, t_obj **objs, int mode);

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

void	check_mode_img(t_app *app);

void	get_img_palette(t_app *app, t_bump *bump, char *s);

void	get_img_rgb(t_app *app, t_bump *bump, char *s, int i);
void	get_img_points(t_app *app, t_bump *bump, char *s);

//RAYTRACING
void	hit_sphere(t_hit *hit, double *t, t_ray ray, t_app *app);
void	hit_plane(t_hit *hit, double *t, t_ray ray, t_app *app);
void	hit_cyl(t_hit *hit, double *t, t_ray ray, t_app *app);
void	hit_cone(t_hit *hit, double *t, t_ray ray, t_app *app);

t_color	base_color(const t_obj *obj);
t_color	color_by_mode(t_hit *hit, t_obj *obj, t_app *app);
t_color	checker_color(t_hit *hit, t_obj *obj);
t_color	texture_color(t_hit *hit, t_obj *obj, int mod, t_app *app);

t_color	dam_plan(t_hit *hit, double scale);
t_color	dam_sphere(const t_hit *hit, double scale, t_dam1 *arg);
t_color	dam_cyl(const t_hit *hit, const t_cylinder *cyl,
			double scale, t_dam2 *arg);
t_color	dam_cone(const t_hit *hit, const t_cone *cone, double scale,
			t_dam2 *arg);

int		intersection_sphere(t_ray ray, t_sphere *sphere, double *t);
int		intersection_plane(t_ray ray, t_plane *plane, double *t);
int		intersection_cylinder(t_ray ray, t_cylinder *cyl, double *t);
int		intersection_cone(t_ray ray, t_cone *cone, double *t);

t_ray	generate_ray(int i, int j, t_cam *cam, t_window *win);
t_color	trace_ray(t_app *app, t_ray ray, t_scene *scene);
t_ray	generate_ray_fisheye(int i, int j, t_cam *cam, t_window *win);

void	put_pixel(t_image *img, int x, int y, t_color color);
void	render_scene(t_app *app, t_scene *scene, t_window *win);

t_color	the_color(t_color final);
int		in_shadow(t_app *app, t_hit *hit, t_vec light_dir,
			double light_dist);
void	pt_lambert(t_light *light, t_hit *hit, t_color *final, t_vec light_dir);
void	pt_ambient(t_color *final, t_color *base, t_amb amb);
t_color	shade(t_app *app, t_scene *scene, t_hit *hit);

void	init_light(t_light *light, t_hit *hit, t_vec *dir, double *dist);
void	pt_phong(t_scene *scene, t_hit *hit, t_vec light_dir, t_color *final);

double	vec_dot(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
void	ft_type(t_app *app, t_ray ray, double *t, t_hit *hit);
int		inter_cyl(t_vec oc, t_vec dir, t_cylinder *cyl, double *t);
int		inter_cone(t_vec oc, t_vec dir, t_cone *cone, double *t);

int		base_cylinder(t_ray ray, t_cylinder *cyl, double *t, int labase);
int		base_cone(t_ray ray, t_cone *cone, double *t);
int		inter_disk_cyl(t_ray ray, t_vec centre, t_cylinder cyl, double *t);
int		inter_disk_cone(t_ray ray, t_vec centre, t_cone *cone, double *t);
void	inter_plus(t_arg_inter *arg, t_cylinder *cyl, t_cone *cone);

t_color	get_pixel_color(t_bump *bump, int x, int y, int mode);
t_color	texture_sphere(t_hit *hit, t_bump *bump, int mode);
t_color	texture_plane(t_hit *hit, t_bump *bump, int mode, double scale);
t_color	texture_cone(t_hit *hit, t_bump *bump, t_cone *cone, double scale);
t_color	texture_cylinder(t_hit *hit, t_bump *bump, t_cylinder *cylinder,
			double scl);

//SRC
void	error(char *s1);
void	*ptr_malloc(t_app *app, int from, unsigned int size);

int		free_exit(t_app *app, char *msg, int ret);
int		control_key(int keycode, t_app *app);

void	free_split(char **line);
void	free_scene(t_scene *scene);
void	free_bump(t_app *app, int i, int j);

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
int		count_token(char **tokens);

#endif