/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:56:54 by afonck            #+#    #+#             */
/*   Updated: 2019/10/07 18:07:09 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = real_part(zx, zy) + fractol.realpart;
		zy = imaginary_part(zy, tempx) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	julia(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = i / fractol.zoom + fractol.realstart;
	zy = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = real_part(zx, zy) - 0.8 + (fractol.realpart / fractol.img.width);
		zy = imaginary_part(zy, tempx) + fractol.impart / fractol.img.width;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	buffalo(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = ft_absfloat(real_part(zx, zy)) + fractol.realpart;
		zy = ft_absfloat(imaginary_part(zy, tempx)) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	celticmandel(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = ft_absfloat(real_part(zx, zy)) + fractol.realpart;
		zy = imaginary_part(zy, tempx) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	burningship(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = real_part(ft_absfloat(zx), ft_absfloat(zy)) + fractol.realpart;
		zy = imaginary_part(ft_absfloat(zy), ft_absfloat(tempx))
			+ fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	tricorn(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = -real_part(zx, zy) + fractol.realpart;
		zy = imaginary_part(zy, tempx) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	mandelbrot_fourth(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = ft_pow(zx, 2) * ft_pow(zx, 2) + ft_pow(zy, 2) * ft_pow(zy, 2) - 6 * ft_pow(zx, 2) * ft_pow(zy, 2) + fractol.realpart;
		zy = 4 * tempx * zy * (ft_pow(tempx, 2) - ft_pow(zy, 2)) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	mandelbrot_fifth(int i, int j, t_fractol fractol)
{
	double	zx;
	double	zy;
	int		n;
	double	tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = zx * (ft_pow(zx, 2) * ft_pow(zx, 2) - 10 * ft_pow(zx, 2) * ft_pow(zy, 2) + 5 * ft_pow(zy, 2) * ft_pow(zy, 2)) + fractol.realpart;
		zy = zy * (5 * ft_pow(tempx, 2) * ft_pow(tempx, 2) - 10 * ft_pow(tempx, 2) * ft_pow(zy, 2) + ft_pow(zy, 2) * ft_pow(zy, 2)) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}
