/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:51:51 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/09 10:27:00 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys_and_mouse.h"

void	close_window(t_fractol *fractol)
{
	destroy_and_clear(fractol);
	exit(0);
}

int		key_press(int key, void *param)
{
	if (key == W)
		julia_stop_mouse(key, (t_fractol *)param);
	else if ((key >= 18 && key <= 23) || key == 26 || key == 28)
		choose_frac(key, (t_fractol *)param);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP
		|| key == ARROW_DOWN)
		complexchange(key, (t_fractol *)param);
	else if (key == O || key == P)
		itmaxchange(key, (t_fractol *)param);
	else if (key == N || key == M)
		changecolor(key, (t_fractol *)param);
	else if (key == R)
		resetfrac(key, (t_fractol *)param);
	else if (key == 33 || key == 30 || key == F)
		imgsize(key, (t_fractol *)param);
	else if (key == HKEY)
		menu_trigger(key, (t_fractol *)param);
	else if (key == ESC)
		close_window((t_fractol *)param);
	return (1);
}

void	keys_and_mouse(t_fractol *fractol)
{
	mlx_hook(fractol->mlx.win_ptr, 6, 1L < 6, mouse_julia, fractol);
	mlx_hook(fractol->mlx.win_ptr, 2, 0, key_press, fractol);
	mlx_mouse_hook(fractol->mlx.win_ptr, mouse_hook, fractol);
}

int		print_usage(void)
{
	ft_dprintf(2, "usage: ./fractol %{r}s %{g}s / %{g}s",
	"[choice of fractal:", "julia", "mandelbrot / ");
	ft_dprintf(2, "%{g}s / %{g}s / %{g}s / %{g}s / %{g}s / %{g}s%{r}s\n", \
	"burningship", "buffalo", "celtic_mandel", "tricorn", "mandel_fourth", \
	"mandel_fifth", "]");
	return (1);
}

int		main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc != 2)
		return (print_usage());
	start_values(&fractol, argv[1]);
	if (fractol.frac == 0)
		return (print_usage());
	init_mlx(&(fractol.mlx), argv[1]);
	init_img(&(fractol.img), &(fractol.mlx));
	multithread(fractol);
	keys_and_mouse(&fractol);
	menu(fractol);
	mlx_loop(fractol.mlx.mlx_ptr);
	return (0);
}
