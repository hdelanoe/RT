/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 22:53:25 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 22:53:27 by dguy-caz         ###   ########.fr       */
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
# define A printf("LOL\n");

# define WIN_X 1600
# define WIN_Y 1300

typedef struct s_vector			t_vector;
typedef struct s_color			t_color;
typedef struct s_camera			t_camera;
typedef struct s_plane			t_plane;
typedef struct s_cone			t_cone;
typedef struct s_cylinder		t_cylinder;
typedef struct s_sphere			t_sphere;
typedef struct s_torus			t_torus;
typedef struct s_light			t_light;
typedef struct s_object			t_object;
typedef struct s_datas			t_datas;
typedef struct s_mlx			t_mlx;
typedef struct s_poly			t_poly;
typedef struct s_inter			t_inter;

struct							s_vector
{
	double						x;
	double						y;
	double						z;
};

struct							s_color
{
	double						b;
	double						g;
	double						r;
};

struct							s_camera
{
	t_vector					origin;
	t_vector					rayon;
};

struct							s_plane
{
	t_vector					point;
	t_vector					normal;
	t_color						color;
	t_vector					node;
	t_vector					node_normal;
	int							id;
	struct s_plane				*next;
};

struct							s_cone
{
	t_vector					vertex;
	t_vector					axis;
	double						tangent;
	double						lenght_max;
	t_color						color;
	t_vector					node;
	t_vector					node_normal;
	int							id;
	struct s_cone				*next;
};

struct							s_cylinder
{
	t_vector					center;
	double						radius;
	t_vector					axis;
	double						lenght_max;
	t_color						color;
	t_vector					node;
	t_vector					node_normal;
	int							id;
	struct s_cylinder			*next;
};

struct							s_sphere
{
	t_vector					center;
	double						radius;
	t_color						color;
	t_vector					node;
	t_vector					node_normal;
	int							id;
	struct s_sphere				*next;
};

struct							s_torus
{
	int							un;
	t_vector					center;
	double						big_radius;
	double						small_radius;
	t_vector					axis;
	t_color						color;
	t_vector					node;
	t_vector					node_normal;
	int							id;
	struct s_torus				*next;
};

struct							s_light
{
	t_vector					origin;
	t_vector					rayon;
	double						angle;
	t_color						color;
	struct s_light				*next;
};

struct							s_object
{
	t_sphere					*start_sphere;
	t_cylinder					*start_cylinder;
	t_plane						*start_plane;
	t_cone						*start_cone;
	t_light						*start_light;
	t_torus						*start_torus;
	char						**tab_line;
};

struct							s_datas
{
	t_camera					camera;
	t_vector					current_origin;
	t_vector					current_rayon;
	t_color						current_color;
	t_vector					current_node;
	t_vector					current_node_normal;
	t_color						color_finale;
	int							number_sphere;
	int							number_plane;
	int							id_sphere;
	int							id_cylinder;
	int							id_cone;
	int							id_plane;
	int							id_torus;
	double						distance_light_object;
	double						distance;
	double						solution;
};

struct							s_mlx
{
	void						*win_ptr;
	void						*mlx_ptr;
	void						*img_ptr;
	unsigned char				*data;
	int							l_size;
	int							bpp;
	int							endian;
};

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
	double						p;
	double						q;
	double						r;
	double						x;
	double						y;
	double						z;
	double						s1;
	double						s2;
	double						s3;
	double						s4;
	double						discriminant;
	double						len;
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
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_json			t_json;
typedef struct s_parsing		t_parsing;

struct							s_json
{
	char						*name;
	char						*content;
	struct s_json				*member;
	struct s_json				*next;
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


void							exit_parser(int flag);
void							parse(t_object *object, char **str);
void							char_is_valid(char a, char b);
void							add(t_json **current, t_json *new);
t_json							*new_object(void);
void							display_window(t_object *object);
int								plane_intersection(t_datas *d, t_plane *plane);
int								cone_intersection(t_datas *d, t_cone *cone);
int								sphere_intersection(t_datas *d, t_sphere *sphere);
int								cylinder_intersection(t_datas *d, t_cylinder *cylinder);
int								torus_intersection(t_datas *d, t_torus *torus);
void							draw(t_datas *d, t_mlx *mlx, t_object *object);
int								key_functions(int keycode, t_mlx *mlx);
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
void							print_color(t_color *color, t_mlx *mlx, int x, int y);
t_color							c_c_mult(t_color *a, t_color *b);
t_color							c_c_add(t_color *a, t_color *b);
t_color							c_double_add(t_color *a, double b);
t_color							c_double_pow(t_color *a, double b);
t_color							c_double_mult(t_color *a, double b);
void							get_light(t_datas *d, t_object *object);
void							get_intersection(t_datas *d, t_mlx *mlx, int x, int y, t_object *object);
int								check_if_light_is_blocked(t_datas *d, int *light_blocked, t_object *object);
void							blocked_by_a_plane(t_datas *d, int *light_blocked, t_object *object);
void							blocked_by_a_cylinder(t_datas *d, int *light_blocked, t_object *object);
void							blocked_by_a_sphere(t_datas *d, int *light_blocked, t_object *object);
void							blocked_by_a_cone(t_datas *d, int *light_blocked, t_object *object);
t_sphere						*add_new_sphere(t_object *object, t_sphere *new_sphere);
t_cone							*add_new_cone(t_object *object, t_cone *new_cone);
t_cylinder						*add_new_cylinder(t_object *object, t_cylinder *new_cylinder);
t_plane							*add_new_plane(t_object *object, t_plane *new_plane);
t_torus							*add_new_torus(t_object *object, t_torus *new_torus);
t_light							*add_new_light(t_object *object, t_light *new_light);
void							create_sphere(t_object *object, t_json *sphere);
void							create_cone(t_object *object, t_json *json);
void							create_cylinder(t_object *object, t_json *json);
void							create_plane(t_object *object, t_json *json);
void							create_torus(t_object *object, char *line);
void							create_light(t_object *object, t_json *json);
int								parsing(t_object *object, char *str);
int								poly_2nd_degree(t_datas **d, t_poly *p);
int								poly_2nd_degree_sphere(t_datas *d, t_poly *p);
void							get_object(t_object *object, t_json *json);
int								create_object(t_json *object, char *str, int i);
void							ft_print_err(int argc);
void							ft_help(void);
void							ft_kill(char *text);


/// test titi
t_vector parse_point(t_json *membre);
t_color  parse_color(t_json *membre);
t_vector parse_normal(t_json *membre);
double get_content_from_member(char *name, t_json **membre);
void create_paraboloid(t_object *object, t_json *json);

#endif
