/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algofractal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecullier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:41:19 by ecullier          #+#    #+#             */
/*   Updated: 2023/07/07 09:07:03 by ecullier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_point z, t_point c)
{
	t_point		z_square;
	int			count;

	z_square.r = pow(z.r, 2);
	z_square.i = pow(z.i, 2);
	count = 0;
	while (z_square.r + z_square.i < 4 && count < MAX_ITER)
	{
		z.i = (2 * z.r * z.i) + c.i;
		z.r = z_square.r - z_square.i + c.r;
		z_square.r = pow(z.r, 2);
		z_square.i = pow(z.i, 2);
		count++;
	}
	return (count);
}

int	mandelbrot(t_point c, t_point v)
{
	t_point		z;
	t_point		z_square;
	int			count;

	(void)v;
	z.r = 0;
	z.i = 0;
	z_square.r = pow(z.r, 2);
	z_square.i = pow(z.i, 2);
	count = 0;
	while (z_square.r + z_square.i < 4 && count < MAX_ITER)
	{
		z.i = (2 * z.r * z.i) + c.i;
		z.r = z_square.r - z_square.i + c.r;
		z_square.r = pow(z.r, 2);
		z_square.i = pow(z.i, 2);
		count++;
	}
	return (count);
}

void	sierpinski_helper(t_point *z)
{
	if (z->r <= 0.5 && z->i <= 0.5)
	{
		z->r *= 2;
		z->i *= 2;
	}
	else if (z->r > 0.5 && z->i <= 0.5)
	{
		z->r = 2 * z->r - 1;
		z->i = 2 * z->i;
	}
	else if (z->i > 0.5)
	{
		z->r = 2 * z->r - 0.5;
		z->i = 2 * z->i - 1;
	}
}

int	sierpinski(t_point z, t_point c)
{
	int		iter;

	(void)c;
	iter = 0;
	while (iter < MAX_ITER)
	{
		sierpinski_helper(&z);
		if (z.r > 1 || z.i > 1)
			return (iter);
		iter++;
	}
	return (iter);
}
