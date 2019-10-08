/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:54:16 by afonck            #+#    #+#             */
/*   Updated: 2019/10/08 09:42:39 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	fractol->realstart = (x / fractol->zoom + fractol->realstart)
		- (x / (fractol->zoom * 1.3));
	fractol->imstart = (y / fractol->zoom + fractol->imstart)
		- (y / (fractol->zoom * 1.3));
	fractol->zoom *= 1.3;
	multithread(*fractol);
}

void	unzoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	fractol->realstart = (x / fractol->zoom + fractol->realstart)
		- (x / (fractol->zoom / 1.3));
	fractol->imstart = (y / fractol->zoom + fractol->imstart)
		- (y / (fractol->zoom / 1.3));
	fractol->zoom /= 1.3;
	multithread(*fractol);
}

int		mouse_hook(int mousecode, int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (mousecode == 4 || mousecode == 1)
		zoom(x, y, fractol);
	else if (mousecode == 5 || mousecode == 2)
		unzoom(x, y, fractol);
	multithread(*fractol);
	return (0);
}

int		mouse_julia(int x, int y, t_fractol *fractol)
{
	if (fractol->frac == JULIA && fractol->julia_mouse == 1)
	{
		fractol->realpart = x * 2;
		fractol->impart = y * 2 - 800;
		destroy_and_clear(fractol);
		multithread(*fractol);
	}
	return (0);
}

void	julia_trigger(int key, t_fractol *fractol)
{
	(void)key;
	if (fractol->frac == JULIA)
		fractol->julia_mouse = !fractol->julia_mouse;
}
