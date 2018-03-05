/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobila <nobila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 22:53:25 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/12/23 18:52:46 by nobila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIN_X 1000
# define WIN_Y 1000
# define RANDOM (double)rand()/RAND_MAX
# define R_VOID 1.0
# define R_AIR 1.000272
# define R_TEST 1.21
# define R_ICE 1.31
# define R_WATER 1.32612
# define R_PMMA 1.4917
# define R_GLASS 1.524
# define R_DIAM 2.4175
# define PI 3.1415

# include <math.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <float.h>
# include <stdlib.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../ft_printf/printf.h"
# include "../minilibx_macos/mlx.h"
# include "vector.h"
# include "color.h"
# include "json_parser.h"
# include "matrix.h"
# include "perlin.h"
# include "bitmap.h"
# include "mlx_key_macos.h"
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_env	t_env;
typedef struct s_mlx	t_mlx;
typedef struct s_camera	t_camera;
typedef struct s_grid	t_grid;
typedef struct s_object	t_object;
typedef struct s_cube	t_cube;
typedef struct s_light	t_light;
typedef struct s_rayon	t_rayon;
typedef struct s_flag	t_flag;
typedef struct s_poly	t_poly;
typedef struct s_inter	t_inter;
typedef struct s_anti_a	t_anti_a;
typedef struct s_physic	t_physic;

struct					s_object
{
	char				*type;
	int					id;
	t_vector			point;
	t_vector			point_2;
	t_vector			point_3;
	t_vector			point_4;
	t_vector			center;
	t_vector			vertex;
	t_vector			normal;
	double				radius;
	double				lenght_max;
	double				range_max;
	double				tangent;
	t_vector			axis;
	t_vector			node;
	t_vector			node_normal;
	t_color				color;
	int					cap;
	double				ambient;
	double				diffuse;
	double				specular;
	int					reflect;
	int					refract;
	double				emit;
	double				absorbtion;
	t_object			*sub_object;
	double				indice;
	int					bump;
	int					texture;
	int					skybox;
	int					sun;
	t_object			*next;
	int					damier;
};

struct					s_light
{
	char				*type;
	int					id;
	t_vector			origin;
	t_vector			point;
	t_vector			point_2;
	t_vector			point_3;
	t_vector			point_4;
	t_vector			rayon;
	double				angle;
	t_color				color;
	t_vector			length;
	t_vector			length_div;
	t_vector			width;
	t_vector			width_div;
	t_light				*next;
};

struct					s_cube
{
	t_object			*carre_1;
	t_object			*carre_2;
	t_object			*carre_3;
	t_object			*carre_4;
	t_object			*carre_5;
	t_object			*carre_6;
};

struct					s_camera
{
	t_vector			origin;
	t_vector			rayon;
	t_vector			lookat;
	t_vector			up;
	t_vector			x_vector;
	t_vector			y_vector;
	t_vector			z_vector;
	double				width;
	double				height;
	double				distance;
	double				*matrix;
};

struct					s_grid
{
	double				x;
	double				y;
	double				xx;
	double				yy;
	t_color				ctmp;
	t_color				color;
	t_color				fblue;
	t_color				fred;
	t_color				blue;
	t_color				red;
	t_color				filter;
	t_vector			vp_point;
	t_vector			vpx;
	t_vector			vpy;
};

struct					s_rayon
{
	t_vector			origin;
	t_vector			rayon;
	t_vector			node;
	t_vector			normal;
	int					refract;
	double				absorbtion;
	int					bump;
};

struct					s_mlx
{
	void				*win_ptr;
	void				*mlx_ptr;
	void				*img_ptr;
	void				*pen;
	unsigned char		*data;
	int					l_size;
	int					bpp;
	int					endian;
};

struct					s_flag
{
	int					edit;
	int					help;
	int					aa;
	int					am;
	int					pixelize;
	int					render_mode;
	int					cel_shade;
	int					stereo;
	int					filter;
	int					begin;
	int					fin;
	int					is_copy;
	int					is_past;
	int					is_delete;
	int					delete_id;
	int					recursion;
	int					lookat;
	int					deep;
};

struct					s_env
{
	t_mlx				mlx;
	t_object			*object;
	t_light				*light;
	t_camera			camera;
	t_camera			lstereo;
	t_camera			rstereo;
	int					area_light_on;
	t_vector			current_origin;
	t_vector			current_rayon;
	t_vector			current_node;
	t_vector			current_node_normal;
	t_vector			object_node;
	t_vector			object_normal;
	t_color				current_color;
	t_vector			light_rayon;
	char				*stock;
	double				width;
	double				height;
	int					id_object;
	double				distance_light_object;
	double				distance;
	double				solution;
	int					bump;
	double				ambient;
	double				diffuse;
	double				specular;
	int					reflect;
	int					refract;
	double				absorbtion;
	int					intersect;
	int					skybox;
	t_vector			viewplane_point_up_left;
	t_vector			lviewplane;
	t_vector			rviewplane;
	t_matrix4x4			rotation_matrix;
	t_matrix4x4			translation_matrix;
	t_matrix4x4			matrix_camera_system;
	t_matrix4x1			matrix_camera_origin;
	double				move_x;
	double				move_y;
	double				move_z;
	double				rotate_x;
	double				rotate_y;
	double				rotate_z;
	double				x1;
	double				y1;
	double				z1;
	int					pixelize;
	int					aa_flag;
	int					recursion;
	int					rebound;
	int					begin;
	int					fin;
	int					am_flag;
	t_object			*copy;
	int					is_copy;
	int					is_delete;
	int					stereo_flag;
	int					filter_flag;
	int					edit_flag;
	t_vector			lookat;
	t_matrix4x4			matrix_lstereo_system;
	t_matrix4x1			matrix_lstereo_origin;
	t_matrix4x4			matrix_rstereo_system;
	t_matrix4x1			matrix_rstereo_origin;
	int					pet;
	t_color				tmp_clr;
	int					i;
	int					j;
	double				u;
	double				v;
	double				strechx;
	double				strechy;
	unsigned int		ti;
	int					text_flag;
	int					bpp[22];
	int					end;
	int					naz;
	void				*text_img[22];
	unsigned char		*tx_dta[22];
	int					sl[22];
	int					cel_shade;
	int					render_mode;
	int					help_flag;
	int					delete_id;
	t_flag				flag;
	double				indice;
	double				object_indice;
	int					hit;
	t_vector			rayon_length;
	t_vector			rayon_length_div;
	t_vector			rayon_width;
	t_vector			rayon_width_div;
	int					p[512];
	t_perlin			perlin;
	int					ambient_flag;
	char				*argv_cpy;
	char				*s_name;
	int					loading;
	char				*img_bat;
	char				*barre_bat;
	int					sonic;
	char				*sonic_d;
	char				*sonic_u;
	int					pars_flag;
};

struct					s_physic
{
	double				ior;
	double				cos1;
	double				cos2;
	double				sin2;
	double				etat;
	double				etai;
	double				teta;
	double				rs;
	double				rp;
	t_vector			tmp1;
	t_vector			tmp2;
	t_vector			r;
	t_vector			t;
};

struct					s_poly
{
	t_vector			object_rayon;
	t_vector			tmp_node;
	t_vector			tmp_node_normal1;
	t_vector			tmp_node_normal2;
	t_vector			v1_2;
	t_vector			v1_3;
	t_vector			v3_1;
	t_vector			v2_3;
	t_vector			v1_node;
	t_vector			v2_node;
	t_vector			v3_node;
	t_vector			cp_1;
	t_vector			cp_2;
	t_vector			cp_3;
	double				tmp1;
	double				tmp2;
	double				tmp3;
	double				tmp4;
	double				a;
	double				b;
	double				c;
	double				d;
	double				e;
	double				f;
	double				ad;
	double				bd;
	double				s1;
	double				s2;
	double				s3;
	double				s4;
	double				discriminant;
	double				len;
	double				radian_x;
	double				radian_y;
	double				radian_z;
	int					i;
	int					j;
	int					nb;
};

t_env					*init(void);
void					default_env(t_env *e);
void					display_window(t_env *e);
void					check_load(t_env *e);
int						check_argv(char *argv);
void					stereo_viewplane(t_env *e);
void					init_stereo(t_env *e);
void					init_camera(t_env *e);
void					camera_transformation(t_env *e);
void					viewplane_transformation(t_env *e);
void					reset_stereo(t_env *e);
void					reset_camera(t_env *e);
double					degree_to_radian(double degree_angle);
t_matrix4x4				m4x4_m4x4_mult(t_matrix4x4 *camera_matrix,
						t_matrix4x4 *rotation);
void					matrix_4x4_to_vectors(t_vector *a, t_vector *b,
						t_vector *c, t_matrix4x4 *matrix);
t_matrix4x4				matrix_camera_system(t_vector *a, t_vector *b,
						t_vector *c);
void					rotation_matrix(t_matrix4x4 *rotation, t_poly *p);
t_matrix4x4				rotation(double degree_x, double degree_y,
						double degree_z);
t_matrix4x1				m4x4_m4x1_mult_reduced(t_matrix4x4 *translation,
						t_matrix4x1 *matrix);
void					matrix_4x1_to_vectors(t_vector *a,
						t_matrix4x1 *matrix);
t_matrix4x1				matrix_camera_origin(t_vector *a);
void					update_system_translation(t_env *e,
						t_matrix4x4 *rot);
t_matrix4x4				translation(t_env *e, t_matrix4x4 *rot);

int						parsing(t_env *e, char *src_file);
void					get_object(t_env *e, t_json *json);
void					add_new_member(t_json **list, t_json *new_member);
void					create_tree(t_env *e, char **str);
void					add_new_object(t_object **list, t_object *new_object);

void					parse_indice(char **material, t_object *object);
void					create_cap_sphere(t_object *sphere);
void					create_child_glass(t_object *glass);
void					create_glass(t_env *e, t_json *json);
void					create_plane(t_env *e, t_json *json);
void					create_triangle(t_env *e, t_json *json);
void					create_quad(t_env *e, t_json *json);
void					create_sphere(t_env *e, t_json *json);
void					create_cap_cylinder(t_object *cylinder);
void					create_cylinder(t_env *e, t_json *json);
void					create_disk(t_env *e, t_json *json);
void					create_cap_cone(t_object *cone);
void					create_cone(t_env *e, t_json *json);
void					create_cube(t_env *e, t_json *json);
void					create_pyramide(t_env *e, t_json *json);
void					create_cap_cube(t_object *cb);
void					create_child_pyramide(t_object *pyramide);
void					create_paraboloid(t_env *e, t_json *json);
void					paraboloid_attribut(t_object *object, t_json *tmp);
void					plane_attribut(t_object *object, t_json *json);
void					sphere_attribut(t_json *json, t_object *sphere);
void					cylinder_attribut(t_object *cylinder, t_json *json);
void					cone_attribut(t_object *object, t_json *json);
void					cone_attribut_2(t_object *object);
void					cube_attribut(t_object *cb, t_json *tmp);
void					parse_scene(t_env *e, t_json *json);
t_object				*init_material(void);
void					init_copy2(t_object **copy, t_object *object);
void					parse_material(t_json *material, t_object *object);
void					check_material(t_object *object, t_json *tmp);
void					free_json_member(t_json **member);
void					choose_mirror(t_object *object);
void					choose_ice(t_object *object);
void					choose_water(t_object *object);
void					choose_glass(t_object *object);
void					choose_pmma(t_object *object);
void					choose_diam(t_object *object);
void					choose_mirror(t_object *object);
void					choose_marble(t_object *object);
void					choose_snow(t_object *object);
void					choose_paradise(t_object *object);
void					choose_metal(t_object *object);
void					choose_cave(t_object *object);
void					choose_sun(t_object *object);
void					choose_space(t_object *object);
void					choose_wood(t_object *object);
void					choose_jupiter(t_object *object);
void					choose_iron(t_object *object);
void					choose_uranus(t_object *object);
void					choose_neptune(t_object *object);
void					choose_mars(t_object *object);
void					choose_moon(t_object *object);
void					choose_cloud(t_object *object);
void					choose_venus(t_object *object);
void					choose_mercury(t_object *object);
void					choose_earth(t_object *object);
void					choose_saturn(t_object *object);
void					choose_arc(t_object *object);
void					add_new_light(t_light **list, t_light *new_light);
void					create_light(t_env *e, t_json *json);
void					fill_area_light_infos(t_json *tmp,
						t_object *al_object, t_light *al_light);
void					create_area_light(t_env *e, t_json *json);
double					get_content_from_member(char *name, t_json **membre);
void					free_content(t_json *member);
double					max(double a, double b);

int						cast_ray(t_env *e, t_vector rayon, t_vector origin);
void					init_rayon_values(t_env *e,
						t_vector rayon, t_vector origin);
int						cast_reflect_ray(t_env *e, t_rayon incident);
int						cast_refract_ray(t_env *e, t_rayon origin);
void					get_object_values(t_env *e, t_object *object,
						t_object *parent);
int						sort_type(t_env *e, t_object *object);
void					check_intersection(t_env *e, t_object *object,
						t_object *parent);
t_color					light_intersection(t_env *e, t_light *light);
void					save_node(t_object *buff, t_object *source, int *tmp);
int						plane_intersection(t_env *e, t_object *plane);
int						glass_intersection(t_env *e, t_object *parent);
int						sphere_intersection(t_env *e, t_object *sphere);
int						cylinder_intersection(t_env *e, t_object *cylinder);
int						disk_intersection(t_env *e, t_object *disk,
	t_object *parent);
int						cone_intersection(t_env *e, t_object *cone);
int						quad_intersection(t_env *e, t_object *quad);
int						cube_intersection(t_env *e, t_object *cube);
int						paraboloid_intersection(t_env *e, t_object *para);
int						paraboloid_solution(t_env *e, t_object *para, t_poly p);
int						triangle_intersection(t_env *e,
						t_object *triangle, t_object *t);
int						sphere_solution(t_env *e, t_object *sphere, t_poly p);
int						solve_solution(t_env *e, t_poly *p);
int						cylinder_solution(t_env *e,
						t_object *cylinder, t_poly p);
int						cone_solution(t_env *e, t_object *cone, t_poly p);

double					noise(t_env *e, double x, double y, double z);
t_color					choose_color(t_env *e);
double					get_specular(t_light *light,
						t_vector *view, t_vector *node);
t_color					init_ray_values(t_rayon *ray, t_env *e);
void					bump_water(t_env *e, t_rayon *ray);
void					bump_marble(t_env *e, t_color *c, t_rayon *ray);
void					bump_wood(t_env *e, t_color *c, t_rayon *ray);
t_color					add_diffuse(t_env *e,
						t_color *c, t_light *light, t_rayon *ray);
void					shoot_new_color(t_env *e, t_color *c, double coef);
void					recurse_color(t_env *e, t_rayon ray, t_color *c);
t_color					ambient_occlusion(t_env *e);
t_color					get_color(t_env *e);
t_color					apply_bump(t_env *e, t_rayon *ray, t_color c);
t_color					get_area_light_intensity(t_env *e,
						t_light *area_light, t_rayon *ray, t_color *c);
void					get_area_light_origin(t_light *area_light, int nb);
void					init_area_size(t_object	*al_object,
						t_light *area_light);
t_color					get_area_color(t_env *e);
void					load_texture(t_env *e);
void					parsing_obj(t_env *e, char ***v, char ***f);
void					wrap_sphere(t_env *e, t_object *object);
void					wrap_cylinder(t_env *e, t_object *object);
void					wrap_plane(t_env *e, t_object *object);
void					wrap_obj(t_env *e, t_object *object, t_object *parent);
t_color					get_texture_info(unsigned char *text_data,
						t_env *e, int sl);
t_color					set_filter(t_env *e, t_color c);
void					print_color(t_color *color, t_env *e, int x, int y);

t_color					vp_init(t_env *e, t_camera cam, t_vector vp, t_grid g);
void					stereo_tracer(t_env *e);
void					edit_tracer(t_env *e);
void					ray_tracer(t_env *e);
void					*aa_tracer_void(void *e);
void					anti_aliasing_clr_merge(t_color *anti, t_color *clr);
void					antialias_loop_init(t_grid *aa, t_env *e, int sample);
void					aa_tracer(t_env *e, int sample);
t_color					get_render_mode(t_env *e);
t_color					cel_shading(t_vector *light, t_env *e, t_color *clr);
t_color					cel_shade_color(t_env *e);
void					*ray_tracer_void(void *e);
void					ft_pthread(t_env *e, void *(*f)(void *param));
void					*stereo_tracer_void(void *e);
void					*pxl_tracer_void(void *e);
void					*aa_tracer_void(void *e);
void					pixel_vp_init(t_grid *g, t_env *e);
void					pxl_tracer(t_env *e, int sample);
void					pxl_edit_tracer(t_env *e, int sample);

int						proper_exit(t_env *e);
void					inputs2(int keycode, t_env *e);
int						inputs4(int keycode, t_env *e);
void					choose_display_mode(t_env *e);
void					print_info(t_env *e);
void					reset_mov_rotate(t_env *e);
int						key_functions(int keycode, t_env *e);
int						check_keycode(int keycode, t_env *e);
int						inputs(int keycode, t_env *e);
void					print_help(t_env *e);
void					ft_object_remove_if(t_object **beg_obj,
						int data_ref, int (*cmp)());
int						set_lookat(t_env *e, int x, int y);
void					create_obj_to_add(t_object **copy);
int						copy_object(t_env *e, int x, int y);
void					copy_cplx(t_object *copy, t_vector center);
int						mouse(int button, int x, int y, t_env *e);
int						obj_lst_size(t_object **lst);
void					init_copy(t_object **copy, t_object *object);
int						cmp(int a, int b);
void					add_object(t_env *e, int x, int y);
int						copy_object(t_env *e, int x, int y);
int						delete_object(t_env *e, int x, int y);
void					save_image(t_env *e);
void					save_scene(t_env *e);
int						print_list_scenes(char *file, char *path);
int						print_list_obj(char *file, char *path);
char					*get_time_to_str(int bl);
int						read_scene_files(t_env *e);
int						read_obj_files(t_env *e);
int						check_existance(char *text, t_env *e);
t_object				*ft_remove_begin(t_object **prev, t_object **ptr);
void					ft_delete_obj_lst(t_object **beg_obj);
t_rayon					init_ray(t_env *e);
void					reset_diffuse_ambiant(t_env *e);
void					put_axis(char *name, t_vector *point, int fd);
void					put_int(char *name, int i, int fd);
void					put_coord(char *name, t_vector *point, int fd);
void					put_cylinder_file(t_object *cylinder, int fd);
void					put_cube_file(t_object *cube, int fd);
void					put_axis(char *name, t_vector *point, int fd);
void					put_plane_file(t_object *plane, int fd);
void					put_light_file(t_light *light, int fd);
void					put_cone_file(t_object *cone, int fd);
void					put_quad_file(t_object *quad, int fd);
void					put_sphere_file(t_object *sphere, int fd);
void					put_type_object(char *type, int fd);
char					*check_color_value(double color);
void					put_color(t_color *color, int fd);
void					put_xyz(t_vector *point, int fd);
void					check_value_point(double *a);
void					put_obj_loop(int fd, t_object *tmp);
void					put_glass_file(t_object *glass, int fd);
void					put_triangle_file(t_object *triangle, int fd);
void					put_pyramide_file(t_object *pyramide, int fd);
void					put_double(char *name, double color, int fd);
char					*ft_strjoin_fre(char **s1, char **s2, int b1, int b2);
void					put_cam_win_file(t_env *e, int fd);
void					check_copy_lst(t_object *obj);
void					apply_texture(t_env *e, t_object *object);
void					put_loading_bar(t_env *e, int i);
void					put_material(int fd, t_object *object);
void					wrap_cone(t_env *e, t_object *object);
void					ft_pthread_no_load(t_env *e, void *(*f)(void *param));
void					wrap_damier(t_env *e, t_object *object);
void					open_close(char *src_file, t_env *e);
#endif
