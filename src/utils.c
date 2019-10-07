/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:55:57 by afonck            #+#    #+#             */
/*   Updated: 2019/10/07 19:56:13 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double  real_part(double a, double b)
{
        return (a * a - b * b);
}

double  imaginary_part(double a, double b)
{
        return (2 * a * b);
}

void    fill_pix(int x, int y, t_fractol *fractol, int color)
{
        if ((x + y * fractol->img.width) < (fractol->img.width * fractol->img.height)
                        && (x + y * fractol->img.width) > 0 && x < fractol->img.width && x > 0)
        {
                fractol->img.data[x + y * fractol->img.width] = color;
        }
}
