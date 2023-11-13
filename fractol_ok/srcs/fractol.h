/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:43:08 by ecullier          #+#    #+#             */
/*   Updated: 2023/07/07 09:05:22 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITER 150

# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define SPACE 32
# define ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364

typedef struct s_mlx {
	void	*mlx;
	char	*title;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_mlx;

typedef struct s_point {
	double	r;
	double	i;
}		t_point;

typedef struct s_data {
	t_mlx	*mlx;
	char	*set;
	int		(*fractal)(t_point, t_point);
	t_point	c;
	double	hue;
	double	x_offset;
	double	y_offset;
	double	zoom;
}		t_data;

// algofractal.c
int		julia(t_point z, t_point c);
int		mandelbrot(t_point c, t_point v);
int		sierpinski(t_point z, t_point c);

// event.c
int		mouse_actions(int key, int x, int y, t_data *data);
int		close_window(t_data *data);
int		keyboard_actions(int key, t_data *data);
void	draw_fractal(t_data *data);

#endif
