/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:06:49 by jhakala           #+#    #+#             */
/*   Updated: 2020/02/17 23:17:50 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

/*
**length_type hh=1, h=2, l=3, ll=4, L=5
*/

typedef struct			s_flags
{
	int					p;
	int					p_total;
	char				buffer[1023];
	int					precision;
	int					minus;
	int					plus;
	int					space;
	int					zero;
	int					width;
	int					length_type;
	int					hastag;
	int					star_minus;
	char				type;
}						t_flags;

typedef struct			s_type
{
	char				name;
	int					(*f)();
}						t_type;

int						ft_printf(const char *str, ...);
int						ft_write(void *s, int size, t_flags *flags);
void					ft_writef(long double n, t_flags *flags);
int						f_putsign(long double n, t_flags *flags);
int						ft_write_char(char c, t_flags *flags);
int						ft_write_until(char **format, t_flags *flags);

/*
**f_parse.c
*/
int						parse(char **str, va_list ap, t_flags *flags);
int						ft_padding(t_flags *flags, int size);

/*
**f_flags_handle.c
*/
int						ft_length(char **str, t_flags *flags);
int						ft_flags(char **str, t_flags *flags);
int						ft_width(char **str, t_flags *flags, va_list ap);
int						ft_precision(char **str, t_flags *flags, va_list ap);

/*
**f_length_types.c
*/
void					h_length(char **str, t_flags *flags);
void					l_length(char **str, t_flags *flags);
void					bigl_length(char **str, t_flags *flags);

/*
**types
*/
int						type_c(va_list ap, t_flags *flags);
int						type_d(va_list ap, t_flags *flags);
int						type_s(va_list ap, t_flags *flags);
int						type_o(va_list ap, t_flags *flags);
int						type_x(va_list ap, t_flags *flags);
int						type_xx(va_list ap, t_flags *flags);
int						type_u(va_list ap, t_flags *flags);
int						type_p(va_list ap, t_flags *flags);
int						type_f(va_list ap, t_flags *flags);

/*
**f_type_bases
*/
long long int			ft_get_n(va_list ap, t_flags *flags);
unsigned long long int	ft_get_n_u(va_list ap, t_flags *flags);
void					ft_putnbr_base(unsigned long long int n, char *str,
						unsigned long long int length, t_flags *flags);
void					ft_get_n_size_u(unsigned long long int n, unsigned long
						long int length, int *size);
int						ft_pad_n(va_list ap, t_flags *flags, char *base, char
						*content);

/*
**f_flags_utlis.c
*/
int						ft_hastag(unsigned long long int n, t_flags *flags, int
						*size, char *content);
void					ft_display_padding(t_flags *flags, unsigned long long
						int n, int *size, char *base);

#endif
