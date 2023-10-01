/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <ecullier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:37:04 by ecullier          #+#    #+#             */
/*   Updated: 2023/07/05 20:14:40 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Zoom and dezoom mandelbrot
*/

void	ft_zoom(int x, int y, t_data *data)
{
	data->min_real = (x / data->zoom + data->min_real) - (x / (data->zoom * 1.2));
	data->min_i = (y / data->zoom + data->min_i) - (y / (data->zoom * 1.2));
	data->zoom *= 1.2;
	data->max_n++;
}

void	ft_dezoom(int x, int y, t_data *data)
{
	data->min_real = (x / data->zoom + data->min_real) - (x /
		(data->zoom / 1.2));
	data->min_i = (y / data->zoom + data->min_i) - (y / (data->zoom / 1.2));
	data->zoom /= 1.2;
	data->max_n--;
}

/*
** Using mouse to zoom and dezoom + increase/dicrease iterations
*/

int		mouse_hook(int mousecode, int x, int y, t_data *data)
{
	if (data->fractol == 0)
	{
		if (mousecode == 5 || mousecode == 2)
			ft_zoom(x, y, data);
		else if (mousecode == 4 || mousecode == 1)
			ft_dezoom(x, y, data);
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mandelbrot(data);
	}
	else if (data->fractol == 1)
		zoom_julia(data, mousecode);
	put_text(data);
	if (data->fractol == 2)
	{
		if (mousecode == 2 || mousecode == 5)
			data->zoom *= 1.2;
		else if (mousecode == 4 || mousecode == 1)
			data->zoom /= 1.2;
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		fern(data);
	}
	return (0);
}

void	zoom_julia(t_data *data, int mousecode)
{
	if (mousecode == 2 || mousecode == 5)
	{
		data->zoom *= 1.2;
		data->max_n++;
	}
	else if (mousecode == 4 || mousecode == 1)
	{
		data->zoom /= 1.2;
		data->max_n--;
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	julia(data);
}

/*
** Change colors for all + exit. keys
*/

int		keys(int key, t_data *data)
{
	if (key == key_esc)
		exit(1);
	else if (key == key_num_1)
		data->color = 0xf0ffff;
	else if (key == key_num_2)
		data->color = 0xff1493;
	else if (key == key_num_3)
		data->color = 0xfff68f;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (data->fractol == 0)
		mandelbrot(data);
	else if (data->fractol == 1)
		julia(data);
	else if (data->fractol == 2)
		fern(data);
	return (0);
}
void	fern_init(t_data *data)
{
	data->width = WINDOW_WIDTH;
	data->height = WINDOW_HEIGHT;
	data->old_re = 0;
	data->new_re = 0;
	data->old_im = 0;
	data->new_im = 0;
	data->color = FERN_COLOR;
	data->zoom = 1;
	fern(data);
}

void	second_part(t_data *data)
{
	if (data->random >= 1 && data->random <= 7)
	{
		data->new_re = -0.15 * data->old_re + 0.28 * data->old_im * data->zoom;
		data->new_im = 0.26 * data->old_re + 0.24 * data->old_im + 0.44 *
			data->zoom;
	}
	else if (data->random >= 8 && data->random <= 15)
	{
		data->new_re = 0.2 * data->old_re - 0.26 * data->old_im * data->zoom;
		data->new_im = 0.23 * data->old_re + 0.22 * data->old_im + 1.6 *
			data->zoom;
	}
	else
	{
		data->new_re = 0.85 * data->old_re + 0.04 * data->old_im * data->zoom;
		data->new_im = -0.04 * data->old_re + 0.85 * data->old_im + 1.6 *
			data->zoom;
	}
}

void draw_pixel(t_data *data, int x, int y, int n)
{
    int color;
    if (n == data->max_n)
        color = 0x000000;
    else
        color = (data->color * n / 100);
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
}
/*
** Starts to draw here
*/

void	fern(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 500, 40, 0xffffff,
		"Barnsley fern");
	data->max_n = 10000;
	while (data->max_n > 0)
	{
		data->random = rand() % 100;
		if (data->random == 0)
		{
			data->new_re = 0 * data->zoom;
			data->new_im = 0.16 * data->old_im * data->zoom;
		}
		else
			second_part(data);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, 30 * data->new_re +
			data->width / 2, 50 * data->new_im + data->height / 3, data->color);
		data->old_re = data->new_re;
		data->old_im = data->new_im;
		data->max_n--;
	}
}
void	julia_init(t_data *data)
{
	data->width = WINDOW_WIDTH;
	data->height = WINDOW_HEIGHT;
	data->color = JULIA_COLOR;
	data->zoom = 1;
	data->c_re = -0.7;
	data->c_im = 0.27015;
	data->new_re = 0;
	data->new_im = 0;
	data->old_re = 0;
	data->old_im = 0;
	data->max_n = MAX_ITERATIONS;
	julia(data);
}

/*
** number of iterations
*/

int		julia_n(t_data *data)
{
	int i;

	i = 0;
	while (i < data->max_n && data->new_re * data->new_re +
		data->new_im * data->new_im < 4)
	{
		data->old_re = data->new_re;
		data->old_im = data->new_im;
		data->new_re = data->old_re * data->old_re - data->old_im *
			data->old_im + data->c_re;
		data->new_im = 2 * data->old_re * data->old_im + data->c_im;
		i++;
	}
	return (i);
}
void julia(t_data *data)
{
    int n;
    int x = 100;
    int y = 100;

    mlx_string_put(data->mlx_ptr, data->win_ptr, 500, 40, 0xffffff, "Julia");
    while (y < data->height) {
        while (x < data->width) {
            data->new_re = 1.5 * (x - data->width / 2) / (0.3 * data->zoom *
                data->width);
            data->new_im = (y - data->height / 2) / (0.3 * data->zoom *
                data->height);
            n = julia_n(data);
            draw_pixel(data, x, y, n);
            x++;
        }
        y++;
        x = 100;
    }
}


void	mandelbrot_init(t_data *data)
{
	data->width = WINDOW_WIDTH;
	data->height = WINDOW_HEIGHT;
	data->min_real = -2.05;
	data->max_real = 1.2;
	data->min_i = -1.3;
	data->max_i = 1.2;
	data->color = MANDELBROT_COLOR;
	data->zoom = 200;
	data->max_n = MAX_ITERATIONS;
	mandelbrot(data);
}

/*
** find a number of iterations for mandelbrot
*/

int		mandelbrot_n(double cr, double ci, double max_n)
{
	int			i;
	double		zr;
	double		zi;
	double		temp;

	i = 0;
	zr = 0;
	zi = 0;
	while (i < max_n && zr * zr + zi * zi < 4.0)
	{
		temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return (i);
}



void mandelbrot(t_data *data)
{
    int x = 100, y, n;
    mlx_string_put(data->mlx_ptr, data->win_ptr, 500, 40, 0xffffff, "Mandelbrot Set");
    while (x < data->width) {
        y = 100;
        while (y < data->height) {
            data->c_re = find_real(x, data);
            data->c_im = find_imaginary(y, data);
            n = find_n(data->c_re, data->c_im, data->max_n);
            draw_pixel(data, x, y, n);
            y++;
        }
        x++;
    }
}


/*
** Find out the real and imaginary part for mandelbrot seperately
*/

double	find_real(int x, t_data *data)
{
	double	range;

	range = data->max_real - data->min_real;
	return (x * (range / data->width) + data->min_real);
}

double	find_imaginary(int y, t_data *data)
{
	double range;

	range = data->max_i - data->min_i;
	return (y * (range / data->height) + data->min_i);
}
int		fract_select(char **argv, t_data *data)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		data->fractol = 0;
		mandelbrot_init(data);
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		data->fractol = 1;
		julia_init(data);
	}
	else if (ft_strcmp(argv[1], "fern") == 0)
	{
		data->fractol = 2;
		fern_init(data);
	}
	else
	{
		ft_putendl("Usage: ./fractol [julia] or [mandelbrot] or [fern]");
		return (0);
	}
	return (1);
}

/*
** For iterations when zooming only
*/

void	put_text(t_data *data)
{
	char	*text;
	char	*nb;

	nb = ft_itoa(data->max_n);
	text = ft_strjoin("Number of iterations : ", nb);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0xFFFFFF, text);
	ft_strdel(&text);
	ft_strdel(&nb);
}

int		main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2)
	{
		data = (t_data*)malloc(sizeof(t_data));
		data->mlx_ptr = mlx_init();
		data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My Fractol");
		if ((fract_select(argv, data)) == 0)
			return (-1);
		mlx_key_hook(data->win_ptr, keys, data);
		mlx_hook(data->win_ptr, 4, 0, mouse_hook, data);
		mlx_loop(data->mlx_ptr);
		free(data);
	}
	else if (argc > 2)
		ft_putendl("oops trop d arguments");
	else
		ft_putendl("il faut choisir entre, julier, mandelbroth ou fern, merci");
}