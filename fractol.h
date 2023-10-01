/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <ecullier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:56:28 by ecullier          #+#    #+#             */
/*   Updated: 2023/07/05 20:14:39 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL.H
# define FRACTOL.H

#include <unistd.h>
#include <math.h>
#include  "./minilibx/mlx.h"
#include "./libft/libft.h"
//#include "color.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

#define MANDELBROT_COLOR 0xffefd5
#define JULIA_COLOR 0x48d1cc
#define FERN_COLOR 0x228b22

#define MAX_ITERATIONS 200
#define key_esc 53
#define key_num_1 18
#define key_num_2 19
#define key_num_3 20

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			fractol;
	int			color;
	int			width;
	int			height;
	double		min_real;
	double		max_real;
	double		min_i;
	double		max_i;
	double		c_re;
	double		c_im;
	double		new_re;
	double		new_im;
	double		old_re;
	double		old_im;
	double		zoom;
	double		max_n;
	int			random;
}				t_data;

/*
** main
*/

int				fract_select(char **argv, t_data *data);
void			put_text(t_data *data);

/*
** mandelbrot
*/

void			mandelbrot_init(t_data *data);
int				mandelbrot_n(double cr, double ci, double max_n);
void			mandelbrot(t_data *data);
double			find_real(int x, t_data *data);
double			find_imaginary(int y, t_data *data);

/*
** julia
*/

void			julia(t_data *data);
void			julia_init(t_data *data);
void			zoom_julia(t_data *data, int mousecode);
int				julia_n(t_data *data);

/*
** mouse and keys = buttons
*/

void			ft_zoom(int x, int y, t_data *data);
void			ft_dezoom(int x, int y, t_data *data);
int				keys(int key, t_data *data);
int				mouse_hook(int mousecode, int x, int y, t_data *data);

/*
** fern blya
*/

void			fern(t_data *data);
void			fern_init(t_data *data);
void			second_part(t_data *data);

#endif