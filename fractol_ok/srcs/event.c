/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:39:14 by ecullier          #+#    #+#             */
/*   Updated: 2023/07/06 17:52:35 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_actions(int key, int x, int y, t_data *data)
{
	if (key == SCROLL_DOWN && data->zoom >= 4)
		return (0);
	if (key == SCROLL_UP)
	{
		data->zoom -= 0.03 * data->zoom;
		data->x_offset += ((double)(x - (WIDTH / 2)) *0.0001 * data->zoom)
			+ 0.01 * data->zoom;
		data->y_offset += ((double)(y - (HEIGHT / 2)) *0.0001 * data->zoom)
			+ 0.01 * data->zoom;
	}
	if (key == SCROLL_DOWN)
	{
		data->zoom += 0.03 * data->zoom;
		data->x_offset += ((double)(x - (WIDTH / 2)) *0.0001 * data->zoom)
			-0.01 * data->zoom;
		data->y_offset += ((double)(y - (HEIGHT / 2)) *0.0001 * data->zoom)
			-0.01 * data->zoom;
	}
	draw_fractal(data);
	mlx_do_sync(data->mlx->mlx);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx->title);
	exit(0);
}

int	keyboard_actions(int key, t_data *data)
{
	if (key == ESC)
		close_window(data);
	else if (key == SPACE)
		data->hue += 0.1;
	else if (key == UP)
		data->y_offset += -0.03 * data->zoom;
	else if (key == DOWN)
		data->y_offset += 0.03 * data->zoom;
	else if (key == RIGHT)
		data->x_offset += 0.03 * data->zoom;
	else if (key == LEFT)
		data->x_offset += -0.03 * data->zoom;
	draw_fractal(data);
	mlx_do_sync(data->mlx->mlx);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	return (0);
}

static int	create_color(double hue, int count)
{
	int	red;
	int	green;
	int	blue;

	red = sin(0.2 * count + hue + 0) * 127 + 128;
	green = sin(0.2 * count + hue + 2) * 127 + 128;
	blue = sin(0.2 * count + hue + 4) * 127 + 128;
	return (red << 16 | green << 8 | blue);
}

void	draw_fractal(t_data *data)
{	
	int		x;
	int		y;
	double	scale;
	t_point	c;
	char	*put_pixel;

	x = -1;
	while (x++ < WIDTH)
	{
		y = -1;
		while (y++ < HEIGHT)
		{
			scale = data->zoom / WIDTH;
			c.r = x * scale + data->x_offset;
			c.i = y * scale + data->y_offset;
			put_pixel = data->mlx->addr + (x * (data->mlx->bits_per_pixel / 8))
				+ (y * data->mlx->line_length);
			if (data->fractal(c, data->c) < MAX_ITER)
				*(unsigned int *)put_pixel = create_color(data->hue,
						data->fractal(c, data->c));
			else
				*(unsigned int *)put_pixel = 0x0000000;
		}
	}
}
