/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:49:10 by afonck            #+#    #+#             */
/*   Updated: 2019/10/07 19:51:21 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys_and_mouse.h"

void	complexchange(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == ARROW_LEFT)
		fractol->realstart += 100 / fractol->zoom;
	else if (key == ARROW_UP)
		fractol->imstart += 100 / fractol->zoom;
	else if (key == ARROW_RIGHT)
		fractol->realstart -= 100 / fractol->zoom;
	else if (key == ARROW_DOWN)
		fractol->imstart -= 100 / fractol->zoom;
	multithread(*fractol);
}

void	itmaxchange(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == O)
		fractol->itmax += 10;
	else if (key == P && fractol->itmax > 0)
		fractol->itmax -= 10;
	multithread(*fractol);
}

void	resetfrac(int key, t_fractol *fractol)
{
	(void)key;
	destroy_and_clear(fractol);
	prepare_frac(fractol);
	multithread(*fractol);
}

void	changecolor(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == N)
	{
		fractol->index++;
		if (fractol->index > 4)
			fractol->index = 0;
		fractol->color = fractol->palettes[fractol->index];
	}
	else if (key == M)
	{
		fractol->color += 10;
	}
	multithread(*fractol);
}

void	choose_frac(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	prepare_frac(fractol);
	if (key == 18)
		fractol->frac = JULIA;
	else if (key == 19)
		fractol->frac = MANDELBROT;
	else if (key == 20)
		fractol->frac = BURNING_SHIP;
	else if (key == 21)
		fractol->frac = BUFFALO;
	else if (key == 23)
		fractol->frac = CELTIC_MANDEL;
	multithread(*fractol);
}
