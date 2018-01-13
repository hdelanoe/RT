/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 02:00:21 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/26 11:00:27 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# define LEN(x) ft_strlen(x)
# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct	s_ep
{
	int		flag[10];
	char	tab_fld[320];
	char	tab_accu[320];
	int		fld;
	int		accu;
	int		conv;
	int		len;
	int		i;
}				t_ep;
typedef struct	s_buff
{
	char			fld[320];
	char			accu[320];
	char			*tmp;
	char			*er;
	unsigned int	*wer;
}				t_buff;
int				ft_printf(const char *format, ...);
int				ft_vfprintf(char *fmt, va_list arg);
void			ft_set_zero(t_ep *e);
void			ft_free(t_ep *e);
int				ft_count_flag(char *fmt, t_ep *e, va_list arg);
int				ft_convert(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putmod(t_ep *e, t_buff *buff);
int				ft_puts(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putp(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putd(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_puto(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putu(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putx(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putc(char c, va_list arg, t_ep *e, t_buff *buff);
int				ft_putf(char c, va_list arg, t_ep *e, t_buff *buff);
char			*ft_ftoa(double value, int accur);
int				ft_isflag(char c);
int				ft_isconv(char c);
int				ft_wlen(unsigned int w);
#endif
