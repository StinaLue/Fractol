#include "fractol.h"
#include "keys_and_mouse.h"

void	close_window(t_fractol *fractol)
{
	destroy_and_clear(fractol);
	exit(0);
}

int	key_press(int key, void *param)
{
	if (key == W)
		julia_trigger(key, (t_fractol *)param);
	else if (key >= 18 && key <= 25)
		choose_frac(key, (t_fractol *)param);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
		complexchange(key, (t_fractol *)param);
	else if (key == O || key == P)
		itmaxchange(key, (t_fractol *)param);
	else if	(key == N || key == M)
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

int		main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: ./fractol %{b}s %{r}s / %{g}s / %{m}s%{b}s\n",
				"[choice of fractal:", "julia", "mandelbrot", "burningship", "]");
		return (1);
	}
	start_values(&fractol, argv[1]);
	if (fractol.frac == 0)
	{
		ft_dprintf(2, "usage: ./fractol %{b}s %{r}s / %{g}s / %{m}s%{b}s\n",
				"[choice of fractal:", "julia", "mandelbrot", "burningship", "]");
		return (1);
	}
	init_mlx(&(fractol.mlx), argv[1]);
	init_img(&(fractol.img), &(fractol.mlx));
	multithread(fractol);
	keys_and_mouse(&fractol);
	menu(fractol);
	mlx_loop(fractol.mlx.mlx_ptr);
	return (0);
}
