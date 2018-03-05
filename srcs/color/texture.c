/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:07:11 by notraore          #+#    #+#             */
/*   Updated: 2017/12/08 13:07:13 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		load_texture5(t_env *e)
{
	if (!((e->text_img[13] = (unsigned char*)mlx_xpm_file_to_image(
	e->mlx.mlx_ptr, "./textures/2k_sun.xpm", &(e->sl[13]), &e->bpp[13]))))
		ft_kill("Texture error");
	e->tx_dta[13] = (unsigned char*)mlx_get_data_addr(e->text_img[13], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[19] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_neptune.xpm", &(e->sl[19]), &e->bpp[19]))))
		ft_kill("Texture error");
	e->tx_dta[19] = (unsigned char*)mlx_get_data_addr(e->text_img[19], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[20] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_uranus.xpm", &(e->sl[20]), &e->bpp[20]))))
		ft_kill("Texture error");
	e->tx_dta[20] = (unsigned char*)mlx_get_data_addr(e->text_img[20], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[21] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_earth_clouds.xpm", &(e->sl[21]), &e->bpp[21]))))
		ft_kill("Texture error");
	e->tx_dta[21] = (unsigned char*)mlx_get_data_addr(e->text_img[21], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[22] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/paris.xpm", &(e->sl[22]), &e->bpp[22]))))
		ft_kill("Texture error");
	e->tx_dta[22] = (unsigned char*)mlx_get_data_addr(e->text_img[22], &e->naz,
	&e->naz, &e->end + 1);
}

void		load_texture4(t_env *e)
{
	if (!((e->text_img[14] = (unsigned char*)mlx_xpm_file_to_image(
	e->mlx.mlx_ptr, "./textures/2k_mars.xpm", &(e->sl[14]), &e->bpp[14]))))
		ft_kill("Texture error");
	e->tx_dta[14] = (unsigned char*)mlx_get_data_addr(e->text_img[14], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[15] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_mercury.xpm", &(e->sl[15]), &e->bpp[15]))))
		ft_kill("Texture error");
	e->tx_dta[15] = (unsigned char*)mlx_get_data_addr(e->text_img[15], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[16] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_jupiter.xpm", &(e->sl[16]), &e->bpp[16]))))
		ft_kill("Texture error");
	e->tx_dta[16] = (unsigned char*)mlx_get_data_addr(e->text_img[16], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[17] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_venus_surface.xpm", &(e->sl[17]), &e->bpp[17]))))
		ft_kill("Texture error");
	e->tx_dta[17] = (unsigned char*)mlx_get_data_addr(e->text_img[17], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[18] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_saturn.xpm", &(e->sl[18]), &e->bpp[18]))))
		ft_kill("Texture error");
	e->tx_dta[18] = (unsigned char*)mlx_get_data_addr(e->text_img[18], &e->naz,
	&e->naz, &e->end + 1);
}

void		load_texture3(t_env *e)
{
	if (!((e->text_img[4] = (unsigned char*)mlx_xpm_file_to_image(
	e->mlx.mlx_ptr, "./textures/wall.xpm", &(e->sl[4]), &e->bpp[4]))))
		ft_kill("Texture error");
	e->tx_dta[4] = (unsigned char*)mlx_get_data_addr(e->text_img[4], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[5] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/thewood.xpm", &(e->sl[5]), &e->bpp[5]))))
		ft_kill("Texture error");
	e->tx_dta[5] = (unsigned char*)mlx_get_data_addr(e->text_img[5], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[6] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/2k_moon.xpm", &(e->sl[6]), &e->bpp[6]))))
		ft_kill("Texture error");
	e->tx_dta[6] = (unsigned char*)mlx_get_data_addr(e->text_img[6], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[12] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/cave.xpm", &(e->sl[12]), &e->bpp[12]))))
		ft_kill("Texture error");
	e->tx_dta[12] = (unsigned char*)mlx_get_data_addr(e->text_img[12], &e->naz,
	&e->naz, &e->end + 1);
}

void		load_texture2(t_env *e)
{
	if (!((e->text_img[7] = (unsigned char*)mlx_xpm_file_to_image(
	e->mlx.mlx_ptr, "./textures/metal.xpm", &(e->sl[7]), &e->bpp[7]))))
		ft_kill("Texture error");
	e->tx_dta[7] = (unsigned char*)mlx_get_data_addr(e->text_img[7], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[8] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/space_skybox.xpm", &(e->sl[8]), &e->bpp[8]))))
		ft_kill("Texture error");
	e->tx_dta[8] = (unsigned char*)mlx_get_data_addr(e->text_img[8], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[9] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/jean.xpm", &(e->sl[9]), &e->bpp[9]))))
		ft_kill("Texture error");
	e->tx_dta[9] = (unsigned char*)mlx_get_data_addr(e->text_img[9], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[10] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/snow.xpm", &(e->sl[10]), &e->bpp[10]))))
		ft_kill("Texture error");
	e->tx_dta[10] = (unsigned char*)mlx_get_data_addr(e->text_img[10], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[11] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/paradise.xpm", &(e->sl[11]), &e->bpp[11]))))
		ft_kill("Texture error");
	e->tx_dta[11] = (unsigned char*)mlx_get_data_addr(e->text_img[11], &e->naz,
	&e->naz, &e->end + 1);
}

void		load_texture(t_env *e)
{
	check_load(e);
	if (!((e->text_img[0] = (unsigned char*)mlx_xpm_file_to_image(
	e->mlx.mlx_ptr, "./textures/2k_earth.xpm", &e->sl[0], &e->bpp[0]))))
		ft_kill("Texture error");
	e->tx_dta[0] = (unsigned char*)mlx_get_data_addr(e->text_img[0], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[1] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/sand.xpm", &(e->sl[1]), &e->bpp[1]))))
		ft_kill("Texture error");
	e->tx_dta[1] = (unsigned char*)mlx_get_data_addr(e->text_img[1], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[2] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/stars.xpm", &(e->sl[2]), &e->bpp[2]))))
		ft_kill("Texture error");
	e->tx_dta[2] = (unsigned char*)mlx_get_data_addr(e->text_img[2], &e->naz,
	&e->naz, &e->end + 1);
	if (!((e->text_img[3] = mlx_xpm_file_to_image(e->mlx.mlx_ptr,
	"./textures/wood.xpm", &(e->sl[3]), &e->bpp[3]))))
		ft_kill("Texture error");
	e->tx_dta[3] = (unsigned char*)mlx_get_data_addr(e->text_img[3], &e->naz,
	&e->naz, &e->end + 1);
	load_texture2(e);
	load_texture3(e);
	load_texture4(e);
	load_texture5(e);
}
