/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:50:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/09 09:58:42 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		zx = ft_pow(zx, 2) * ft_pow(zx, 2) + ft_pow(zy, 2) * ft_pow(zy, 2)
				- 6 * ft_pow(zx, 2) * ft_pow(zy, 2) + fractol.realpart;
		zy = 4 * tempx * zy * (ft_pow(tempx, 2)
				- ft_pow(zy, 2)) + fractol.impart;
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
		zx = zx * (ft_pow(zx, 2) * ft_pow(zx, 2)
				- 10 * ft_pow(zx, 2) * ft_pow(zy, 2)
				+ 5 * ft_pow(zy, 2) * ft_pow(zy, 2)) + fractol.realpart;
		zy = zy * (5 * ft_pow(tempx, 2) * ft_pow(tempx, 2)
				- 10 * ft_pow(tempx, 2) * ft_pow(zy, 2)
				+ ft_pow(zy, 2) * ft_pow(zy, 2)) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}
