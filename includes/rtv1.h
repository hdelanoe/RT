/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 22:53:25 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:52:46 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../ft_printf/printf.h"
# include "../minilibx_macos/mlx.h"
# include "json_parser.h"
# include "color.h"
# include "vector.h"
# include "matrix.h"
# include <math.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# define A printf("File = [%s]\nLine = [%d]\nFunction = [%s]\n", __FILE__, __LINE__, __FUNCTION__);

# define WIN_X 1000
# define WIN_Y 1000
# define RANDOM (double)rand()/RAND_MAX

# define R_VOID 1.0
# define R_AIR 1.000272
# define R_ICE 1.31
# define R_WATER 1.32612
# define R_PMMA 1.4917
# define R_GLASS 1.524
# define R_DIAM 2.4175

typedef struct s_env	t_env;
typedef struct s_mlx	t_mlx;
typedef struct s_camera	t_camera;
typedef struct s_grid	t_grid;
typedef struct s_object	t_object;
typedef struct s_light	t_light;
typedef struct s_rayon	t_rayon;



typedef struct s_poly	t_poly;
typedef struct s_inter	t_inter;

typedef struct s_pixel	t_pixel;
typedef struct s_anti_a	t_anti_a;

struct          s_pixel 
{ 
  int          x; 
  int          y; 
  int          tmpx; 
  int          tmpy; 
  t_vector      viewplane_point; 
  t_vector      tmp_vp_pointx; 
  t_vector      tmp_vp_pointy; 
}; 
 
struct          s_anti_a 
{ 
  int          x; 
  int          y; 
  int          sample; 
  double        x1; 
  double        y1; 
  t_color        aaclr; 
  t_vector      viewplane_point; 
  t_vector      tmp_vp_pointx; 
  t_vector      tmp_vp_pointy; 
}; 

struct					s_object
{
	char 		*type;
	int			id;
	t_vector	point;
	t_vector 	center;
	t_vector	vertex;
	t_vector	normal;
	double		radius;
	double		lenght_max;
	double		tangent;
	t_vector	axis;
	t_vector	node;
	t_vector	node_normal;
	t_color		color;
	double 		ambient;
	double 		diffuse;
	double 		specular;
	int 		reflect;
	int 		refract;
	double 		absorbtion;

	t_object	*next;
};

struct					s_light
{
	int 		id;
	t_vector	origin;
	t_vector	rayon;
	double		angle;
	t_color		color;
	t_light		*next;
};

struct  				s_rayon
{
	t_vector 	origin;
	t_vector 	rayon;
	t_vector 	node;
	t_vector 	normal;
};

struct 					s_node
{
	t_vector 	node;
	t_vector 	normal;
};

struct					s_camera
{
	t_vector		origin;
	t_vector		rayon;
	t_vector		lookat;
	t_vector		up;
	t_vector		x_vector;
	t_vector		y_vector;
	t_vector		z_vector;
	double			viewplane_width;
	double			viewplane_height;
	double			viewplane_distance;
	double			*matrix;
};

typedef struct			s_mlx
{
	void			*win_ptr;
	void			*mlx_ptr;
	void			*img_ptr;
	unsigned char	*data;
	int				l_size;
	int				bpp;
	int				endian;
}						t_mlx;

struct 					s_env
{
	t_mlx			mlx;
	t_object	*object;
	t_light		*light;
	t_camera	camera;
	t_vector	current_origin;
	t_vector	current_rayon;
	t_vector	current_node;
	t_vector	current_node_normal;
	t_color		current_color;
	double 		width;
	double 		height;
	int			id_object;
	double		distance_light_object;
	double		distance;
	double		solution;
	int 		in_out;
	int 		bump;
	double 		ambient;
	double 		diffuse;
	double 		specular;
	int 		reflect;
	int 		refract;
	double 		absorbtion;
	int 		intersect;
	t_vector		viewplane_point_up_left;
	t_matrix4x4		rotation_matrix;
	t_matrix4x4		translation_matrix;
	t_matrix4x4		matrix_camera_system;
	t_matrix4x1		matrix_camera_origin;
	double			move_x;
	double			move_y;
	double			move_z;
	double			rotate_x;
	double			rotate_y;
	double			rotate_z;
	double			x1;
	double			y1;
	double			z1;
	int				pixelize;
	int				aa_flag;
	int 			recursion;

};

struct 					s_grid
{
	double 		x;
	double 		y;
	double 		x1;
	double 		y1;
};

typedef struct 					s_physics
{
		double 		ior;
		double 		cos1;
		double 		cos2;
		double 		teta;
		t_vector 	tmp1;
		t_vector 	tmp2;
		t_vector	r;
		t_vector	t;
}								t_physics;

struct							s_poly
{
	double						tmp1;
	double						tmp2;
	double						tmp3;
	double						a;
	double						b;
	double						c;
	double						d;
	double						e;
	double						f;
	double						p;
	double						q;
	double						r;
	double						x;
	double						y;
	double						z;
	double						ad;
	double						bd;
	double						s1;
	double						s2;
	double						s3;
	double						s4;
	double						discriminant;
	double						len;
	double						radian_x;
	double						radian_y;
	double						radian_z;
};

struct							s_inter
{
	t_vector					object_rayon;
	t_vector					tmp_node;
	t_vector					tmp_node_normal1;
	t_vector					tmp_node_normal2;
};

int p[512];

/*
CAMERA/MATRIX
*/
void							init_camera(t_env *e);
void							camera_transformation(t_env *e);
void							viewplane_transformation(t_env *e);
void							matrix_4x4_to_vectors(t_vector *a, t_vector *b, t_vector *c, t_matrix4x4 *matrix);
void							rotation_matrix(t_matrix4x4 *rotation, t_poly *p);
t_matrix4x4						matrix_camera_system(t_vector *a, t_vector *b, t_vector *c);
void							matrix_4x1_to_vectors(t_vector *a, t_matrix4x1 *matrix);
void							update_system_translation(t_env *e, t_matrix4x4 *rot);
t_matrix4x4						translation(t_env *e, t_matrix4x4 *rot);
t_matrix4x1						matrix_camera_origin(t_vector *a);
/*PARSING
*/
int								parsing(t_env *e, char *str);
void							create_tree(t_env *e, char **str);
void							get_light(t_env *e);
void							get_object(t_env *e, t_json *json);
void							init_material(t_object *object);
void							parse_scene(t_env *e, t_json *json);
void							parse_material(t_json *material, t_object *object);
void							create_sphere(t_env *e, t_json *json, int *id);
void							create_cone(t_env *e, t_json *json, int *id);
void							create_cylinder(t_env *e, t_json *json, int *id);
void							create_plane(t_env *e, t_json *json, int *id);
void							create_torus(t_env *e, t_json *json, int *id);
void							create_light(t_env *e, t_json *json, int *id);
void 							create_paraboloid(t_object *object, t_json *json);
t_vector 						parse_point(t_json *membre);
t_color 						parse_color(t_json *membre);
t_vector 						parse_normal(t_json *membre);
void							add_new_object(t_object **list, t_object *object);
void							add_new_light(t_light **list, t_light *new_light);
void							exit_parser(int flag);
/*
RAYTRACER
*/
void							ray_tracer(t_env *e);
int								cast_ray(t_env *e, t_vector rayon, t_vector origin);
void							check_intersection(t_env *e, t_object *object);
int								check_if_light_is_blocked(t_env *e);
int								plane_intersection(t_env *e, t_object *plane);
int								cone_intersection(t_env *e, t_object *cone);
int								sphere_intersection(t_env *e, t_object *sphere);
int								cylinder_intersection(t_env *e, t_object *cylinder);
int								torus_intersection(t_env *e, t_object *torus);
t_color							get_color(t_env *e);
int 							cast_reflect_ray(t_env *e, t_rayon origin);
int 							cast_refract_ray(t_env *e, t_rayon origin);
void							print_color(t_color *color, t_env *e, int x, int y);
/*
RENDER
*/
void							display_window(t_env *e);
int								key_functions(int keycode, t_env *e);
void							anti_aliasing_clr_merge(t_color *anti, t_color *clr);
t_anti_a						antialias_loop_init(t_anti_a *anti, t_env *e, int sample);
void							aa_tracer(t_env *e, int sample);
t_color							c_double_div(t_color *a, double b);
t_pixel							pixel_vp_init(t_pixel *pxl, t_env *e);
void							pxl_tracer(t_env *e, int sample);
t_color							ambient_occlusion(t_env *e);
/*
ERROR
*/
void							ft_print_err(int argc);
void							ft_help(void);
void							ft_kill(char *text);
void							exit_rt(int flag);
int								proper_exit(t_env *e);
/*
PERLIN_NOIZE
*/
double 							fade(double t);
double 							lerp(double t, double a, double b);
double 							grad(int hash, double x, double y, double z);
double 							noise(double x, double y, double z);
void 							loadPermutation(void);

#endif
