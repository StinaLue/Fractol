/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:53:39 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/09 10:29:40 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	menu_trigger(int key, t_fractol *fractol)
{
	(void)key;
	fractol->menu = !fractol->menu;
	multithread(*fractol);
}

void	output_bonus_frac(t_fractol fractol)
{
	if (fractol.frac == BUFFALO)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "BUFFALO");
	else if (fractol.frac == CELTIC_MANDEL)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "CELTIC MANDELBROT");
	else if (fractol.frac == TRICORN)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "TRICORN");
	else if (fractol.frac == MANDEL_FOURTH)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "MANDEL_FOURTH");
	else if (fractol.frac == MANDEL_FIFTH)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "MANDEL_FIFTH");
}

void	outputfrac(t_fractol fractol)
{
	if (fractol.frac == JULIA)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "JULIA");
	else if (fractol.frac == MANDELBROT)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "MANDELBROT");
	else if (fractol.frac == BURNING_SHIP)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "BURNING SHIP");
	else
		output_bonus_frac(fractol);
}

void	outputcommands(t_fractol fractol)
{
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 30,
			0xFFFFFF, "Change      palette: N");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 75, 30,
			fractol.color, "color");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 50,
			0xFFFFFF, "Iterations: O(+)/P(-) | Current iteration:");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 70,
			0xFFFFFF, "Zoom: scroll up/down");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 90,
			0xFFFFFF, "Move: arrows");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 110,
			0xFFFFFF, "Reset: R | Hide menu: H");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 130,
			0xFFFFFF, "Change fractal: 1/2/3/4/5/6/7/8");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 150,
			0xFFFFFF, "Change img size: '[' / ']'");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 170,
			0xFFFFFF, "Psychedelic mode: M");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 190,
			0xFFFFFF, "Close the window: 'esc'");
	if (fractol.frac == JULIA)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 210,
				0xFFFFFF, "Stop mouse movement: W");
}

void	menu(t_fractol fractol)
{
	outputfrac(fractol);
	outputcommands(fractol);
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 435, 50,
			0xFFFFFF, ft_itoa(fractol.itmax));
}
