/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:06:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/03/29 11:45:37 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_vertical(int yinc, int xinc, t_fractol *fractol)
{
	int i;
	int cumul;

	i = 1;
	cumul = fractol->dy / 2;
	while (i <= fractol->dy)
	{
		fractol->point_one.y += yinc;
		cumul += fractol->dx;
		if (cumul >= fractol->dy)
		{
			cumul -= fractol->dy;
			fractol->point_one.x += xinc;
		}
		fill_pix(fractol->point_one.x, fractol->point_one.y, fractol);
		i++;
	}
}

void	draw_horizontal(int yinc, int xinc, t_fractol *fractol)
{
	int i;
	int cumul;

	i = 1;
	cumul = fractol->dx / 2;
	while (i <= fractol->dx)
	{
		fractol->point_one.x += xinc;
		cumul += fractol->dy;
		if (cumul >= fractol->dx)
		{
			cumul -= fractol->dx;
			fractol->point_one.y += yinc;
		}
		fill_pix(fractol->point_one.x, fractol->point_one.y, fractol);
		i++;
	}
}

int		pos_or_neg(int i)
{
	if (i > 0)
		return (1);
	else
		return (-1);
}

void	draw_line(t_fractol *fractol)
{
	int xinc;
	int yinc;

	fractol->dx = fractol->point_two.x - fractol->point_one.x;
	fractol->dy = fractol->point_two.y - fractol->point_one.y;
	xinc = pos_or_neg(fractol->dx);
	yinc = pos_or_neg(fractol->dy);
	fractol->dx = ft_absolute(fractol->dx);
	fractol->dy = ft_absolute(fractol->dy);
	fill_pix(fractol->point_one.x, fractol->point_one.y, fractol);
	if (fractol->dx > fractol->dy)
		draw_horizontal(yinc, xinc, fractol);
	else
		draw_vertical(yinc, xinc, fractol);
}
