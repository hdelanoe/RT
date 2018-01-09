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

//# include "xml_parser.h"
# include "../minilibx_macos/mlx.h"
# include "../libft/includes/libft.h"
# include <math.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# define A printf("File = [%s]\nLine = [%d]\nFunction = [%s]\n", __FILE__, __LINE__, __FUNCTION__);

# define WIN_X 1000
# define WIN_Y 1000

#define MAX_RECURSION 1
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
typedef struct s_color	t_color;
typedef struct s_vector	t_vector;
typedef struct s_node	t_node;
typedef struct s_poly	t_poly;
typedef struct s_inter	t_inter;
typedef struct s_wave 	t_wave;

struct					s_vector
{
	double	x;
	double	y;
	double	z;
};


struct					s_color
{
	double	b;
	double	g;
	double	r;
};

struct 					s_wave
{
	t_color	issued;
	t_color	diffuse;
	t_color	add;
	double 	specular;
};

typedef struct		s_matrix4x4
{
	double			m[4][4];
}					t_matrix4x4;

typedef struct		s_matrix4x1
{
	double			m[4][1];
}					t_matrix4x1;

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
	t_vector	origin;
	t_vector	rayon;
	double		angle;
	t_color		color;
	t_light		*next;
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
	t_color		current_color;
	t_vector	current_node;
	t_vector	current_node_normal;
	t_color		color_finale;
	t_color 	refract_color;
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

typedef struct 		s_paraboloid
{
	int 			id;
	t_vector		origin;
	t_vector		normal;
	double 			distance;
	t_color			color;
	struct s_paraboloid *next;
}					t_paraboloid;

struct							s_inter
{
	t_vector					object_rayon;
	t_vector					tmp_node;
	t_vector					tmp_node_normal1;
	t_vector					tmp_node_normal2;
};

# define BUF_SIZ 2
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_json			t_json;
typedef struct s_parsing		t_parsing;

struct							s_json
{
	char						*name;
	char						*content;
	t_json						*member;
	t_json						*next;
};

struct							s_parsing
{
	int							fd;
	int							i;
	int							j;
	char						buff[BUF_SIZ + 1];
	char						*stock;
	char						*tmp;
}; 

int p[512];

int								proper_exit(t_env *e);
void							aa_tracer(t_env *e);
void							pxl_tracer(t_env *e);

void							add_new_object(t_object **list, t_object *object);
void							exit_parser(int flag);
void							create_tree(t_env *e, char **str);
void							char_is_valid(char a, char b, char *str);
void							add(t_json **current, t_json *new);
int								get_content(char **content, char *str, int i);
t_json							*new_object(void);
void							display_window(t_env *e);
int								plane_intersection(t_env *e, t_object *plane);
int								cone_intersection(t_env *e, t_object *cone);
int								sphere_intersection(t_env *e, t_object *sphere);
int								cylinder_intersection(t_env *e, t_object *cylinder);
int								torus_intersection(t_env *e, t_object *torus);
void							ray_tracer(t_env *e);
int								key_functions(int keycode, t_env *e);
t_vector						set_vector(double x, double y, double z);
double							magnitude(t_vector *a);
t_vector						normalize(t_vector *a);
double							dot_product(t_vector *a, t_vector *b);
t_vector						v_v_add(t_vector *a, t_vector *b);
t_vector						v_v_subs(t_vector *a, t_vector *b);
t_vector						v_v_mult(t_vector *a, t_vector *b);
t_vector						v_double_add(t_vector *a, double b);
t_vector						v_double_subs(t_vector *a, double b);
t_vector						v_double_mult(t_vector *a, double b);
t_vector						v_double_div(t_vector *a, double b);
t_color							set_color(double b, double g, double r);
void							print_color(t_color *color, t_env *e, int x, int y);
t_color							c_c_mult(t_color *a, t_color *b);
t_color							c_c_add(t_color *a, t_color *b);
t_color							c_double_add(t_color *a, double b);
t_color							c_double_pow(t_color *a, double b);
t_color							c_double_mult(t_color *a, double b);
t_color							get_color(t_env *e);
void							get_light(t_env *e);
void							parse_material(t_json *material, t_object *object);
t_color							cast_ray(t_env *e, t_vector rayon, t_vector origin);
void							check_intersection(t_env *e, t_object *object);
int								check_if_light_is_blocked(t_env *e);
void							blocked_by_a_plane(t_env *e, int *light_blocked);
void							blocked_by_a_cylinder(t_env *e, int *light_blocked);
void							blocked_by_a_sphere(t_env *e, int *light_blocked);
void							blocked_by_a_cone(t_env *e, int *light_blocked);
void							add_new_light(t_light **list, t_light *new_light);
void							create_sphere(t_env *e, t_json *json, int *id);
void							create_cone(t_env *e, t_json *json, int *id);
void							create_cylinder(t_env *e, t_json *json, int *id);
void							create_plane(t_env *e, t_json *json, int *id);
void							create_torus(t_env *e, t_json *json, int *id);
void							create_light(t_env *e, t_json *json);
int								parsing(t_env *e, char *str);
int								poly_2nd_degree(t_env *e, t_poly *p);
int								poly_2nd_degree_sphere(t_env *e, t_poly *p);
void							get_object(t_env *e, t_json *json);
int								create_object(t_json *object, char *str, int i);
void							ft_print_err(int argc);
void							ft_help(void);
void							ft_kill(char *text);
void							exit_rt(int flag);
double 							fade(double t);
double 							lerp(double t, double a, double b);
double 							grad(int hash, double x, double y, double z);
double 							noise(double x, double y, double z);
void							init_material(t_object *object);
void 							loadPermutation(void);
void							free_json(t_json *json);
void							init_camera(t_env *e);
void							camera_transformation(t_env *e);
void							viewplane_transformation(t_env *e);
void							matrix_4x4_to_vectors(t_vector *a, t_vector *b, t_vector *c, t_matrix4x4 *matrix);
double							degree_to_radian(double degree_angle);
t_matrix4x4						rotation(double degree_x, double degree_y, double degree_z);
void							rotation_matrix(t_matrix4x4 *rotation, t_poly *p);
t_matrix4x4						matrix_camera_system(t_vector *a, t_vector *b, t_vector *c);
t_matrix4x4						m4x4_m4x4_mult(t_matrix4x4 *camera_matrix, t_matrix4x4 *rotation);
void							matrix_4x1_to_vectors(t_vector *a, t_matrix4x1 *matrix);
void							update_system_translation(t_env *e, t_matrix4x4 *rot);
t_matrix4x4						translation(t_env *e, t_matrix4x4 *rot);
t_matrix4x1						matrix_camera_origin(t_vector *a);
t_matrix4x1						m4x4_m4x1_mult_reduced(t_matrix4x4 *translation, t_matrix4x1 *matrix);


/// test titi
t_vector parse_point(t_json *membre);
t_color  parse_color(t_json *membre);
t_vector parse_normal(t_json *membre);
double get_content_from_member(char *name, t_json **membre);
void create_paraboloid(t_object *object, t_json *json);

#endif
