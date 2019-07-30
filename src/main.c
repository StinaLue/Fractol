#include <stdio.h>

#include "fractol.h"
#include "keys_and_mouse.h"
#include <math.h>
#include "libft.h"
#define RE_START -2.05
#define IM_START -1.3
#define JULIA 1
#define MANDELBROT 2
#define BURNING_SHIP 3
#define BUFFALO 4

void	trace_fractal(t_fractol *fractol);

void	destroy_and_clear(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx.mlx_ptr, fractol->img.img_ptr);
	mlx_clear_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr);
	fractol->img.img_ptr = mlx_new_image(fractol->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fractol->img.data = (int *)mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bpp,
			&fractol->img.size_l, &fractol->img.endian);
}

void	complexchange(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == ARROW_LEFT)
	{
		fractol->realstart += 100 / fractol->zoom;
	}
	else if (key == ARROW_UP)
	{
		fractol->imstart += 100 / fractol->zoom;
	}
	else if (key == ARROW_RIGHT)
	{
		fractol->realstart -= 100 / fractol->zoom;
	}
	else if (key == ARROW_DOWN)
	{
		fractol->imstart -= 100 / fractol->zoom;
	}
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
}

void	close_window(t_fractol *fractol)
{
	destroy_and_clear(fractol);
	exit(0);
}
/*
void	zoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == W)
	{
		fractol
		fractol->julia_mouse = !fractol->julia_mouse;->realstart = fractol->zoom += 100;
		//fractol->realstart += fractol->realstart / fractol->zoom;
		//fractol->imstart += fractol->imstart / fractol->zoom;
	}
	else if (key == S)
	{
		fractol->zoom -= 100;
		//	fractol->realstart -= fractol->realstart / fractol->zoom;
		//	fractol->imstart -= fractol->imstart / fractol->zoom;
	}
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
}
*/
void	zoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	fractol->realstart = (x / fractol->zoom + fractol->realstart) - (x / (fractol->zoom * 1.3));
	fractol->imstart = (y / fractol->zoom + fractol->imstart) - (y / (fractol->zoom * 1.3));
	fractol->zoom *= 1.3;
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
}

void	unzoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	fractol->realstart = (x / fractol->zoom + fractol->realstart) - (x / (fractol->zoom / 1.3));
	fractol->imstart = (y / fractol->zoom + fractol->imstart) - (y / (fractol->zoom / 1.3));
	fractol->zoom /= 1.3;
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
}

void	itmaxchange(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == O)
	{
		fractol->itmax += 10;
	}
	else if (key == P)
	{
		fractol->itmax -= 10;
	}
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
}

void	changecolor(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == N)
	{
		fractol->color += 10;
	}
	else if (key == M)
	{
		fractol->color -= 10;
	}
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
}

void	julia_trigger(int key, t_fractol *fractol)
{
	(void)key;
	if (fractol->frac == JULIA)
		fractol->julia_mouse = !fractol->julia_mouse;
}

void	choose_frac(int key, t_fractol *fractol)
{
	if (key == 13)
		fractol->frac = JULIA;
	else if (key == 14)
		fractol->frac = MANDELBROT;
	else if (key == 15)
		fractol->frac = BURNING_SHIP;
	else if (key == 16)
		fractol->frac = BUFFALO;
}

int	key_press(int key, void *param)
{
	if (key == W)
		julia_trigger(key, (t_fractol *)param);
	else if (key >= 13 && key <= 25)
		choose_frac(key, (t_fractol *)param);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
		complexchange(key, (t_fractol *)param);
	else if (key == O || key == P)
		itmaxchange(key, (t_fractol *)param);
	else if	(key == N || key == M)
		changecolor(key, (t_fractol *)param);
	else if (key == ESC)
		close_window((t_fractol *)param);
	return (1);
}

int             mouse_hook(int mousecode, int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (mousecode == 4 || mousecode == 1)
		zoom(x, y, fractol);
	else if (mousecode == 5 || mousecode == 2)
		unzoom(x, y, fractol);
	trace_fractal(fractol);
	mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
	return (0);
}

int             mouse_julia(int x, int y, t_fractol *fractol);

void	keys_and_mouse(t_fractol *fractol)
{
	mlx_hook(fractol->mlx.win_ptr, 6, 1L < 6, mouse_julia, fractol);
	mlx_hook(fractol->mlx.win_ptr, 2, 0, key_press, fractol);
	mlx_mouse_hook(fractol->mlx.win_ptr, mouse_hook, fractol);
}

void	prepare_mandel(t_fractol *fractol)
{
	fractol->itmax = 100;
	fractol->zoom = WIN_HEIGHT / 3;
	fractol->realstart = -2.8;
	fractol->imstart = -1.45;
	fractol->color = 100;
}

void	prepare_julia(t_fractol *fractol)
{
	fractol->itmax = 100;
	fractol->zoom = WIN_HEIGHT / 3;
	fractol->realstart = -2.0;
	fractol->imstart = -1.9;
	fractol->color = 2050;
	fractol->realpart = 0.285;
	fractol->impart = 0.01;
	fractol->julia_mouse = 1;
	fractol->frac = JULIA;
}

double	real_part(double a, double b)
{
	return (a * a - b * b);
}

double	imaginary_part(double a, double b)
{
	return (2 * a * b);
}

void	fill_pix(int x, int y, t_fractol *fractol, int color)
{
	if ((x + y * WIN_WIDTH) < (WIN_WIDTH * WIN_HEIGHT) &&
			(x + y * WIN_WIDTH) > 0 && x < WIN_WIDTH && x > 0)
	{
		fractol->img.data[x + y * WIN_WIDTH] = color;
	}
}

int	mandeltest(int i, int j, t_fractol *fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;
	double rlpart;
	double impart;

	n = 0;
	zx = 0.0;
	zy = 1.0;
	rlpart = i / fractol->zoom + fractol->realstart;
	impart = j / fractol->zoom + fractol->imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol->itmax)
	{
		tempx = zx;
		zx = zx * zx - zy * zy + rlpart;
		zy = 2 * zy * tempx + impart;
		n++;
	}
	fill_pix(i, j, fractol, n == fractol->itmax ? 0x000000 : fractol->color * n);
	return (n);
}

int	mandelbrot(int i, int j, t_fractol *fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;
	double realpart;
	double impart;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	realpart = i / fractol->zoom + fractol->realstart;
	impart = j / fractol->zoom + fractol->imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol->itmax)
	{
		tempx = zx;
		zx = zx * zx - zy * zy + realpart;
		zy = 2 * zy * tempx + impart;
		//printf("zx = %f and zy = %f\n", zx, zy);
		n++;
	}
	fill_pix(i, j, fractol, n == fractol->itmax ? 0x000000 : fractol->color * n);
	return (n);
}

int             mouse_julia(int x, int y, t_fractol *fractol)
{
	if (fractol->frac == JULIA && fractol->julia_mouse == 1)
	{
		fractol->realpart = x * 2;
		fractol->impart = y * 2 - 800;
		destroy_and_clear(fractol);
		trace_fractal(fractol);
		mlx_put_image_to_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr, fractol->img.img_ptr, 0, 0);
	}
	return (0);
}

int	julia(int i, int j, t_fractol *fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;

	n = 0;
	zx = i / fractol->zoom + fractol->realstart;
	zy = j / fractol->zoom + fractol->imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol->itmax)
	{
		tempx = zx;
		zx = zx * zx - zy * zy - 0.8 + (fractol->realpart / WIN_WIDTH);
		zy = 2 * zy * tempx + fractol->impart / WIN_WIDTH;
		n++;
	}
	fill_pix(i, j, fractol, n == fractol->itmax ? 0x000000 : fractol->color * n);
	return (n);
}

int	buffalo(int i, int j, t_fractol *fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;
	double rlpart;
	double impart;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	rlpart = i / fractol->zoom + fractol->realstart;
	impart = j / fractol->zoom + fractol->imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol->itmax)
	{
		tempx = zx;
		zx = ft_absfloat(real_part(zx, zy)) + rlpart;
		zy = ft_absfloat(imaginary_part(zy, tempx)) + impart;
		//printf("zx = %f and zy = %f\n", zx, zy);
		n++;
	}
	fill_pix(i, j, fractol, n == fractol->itmax ? 0x000000 : fractol->color * n);
	return (n);
}

int	burningship(int i, int j, t_fractol *fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;
	double rlpart;
	double impart;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	rlpart = i / fractol->zoom + fractol->realstart;
	impart = j / fractol->zoom + fractol->imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol->itmax)
	{
		tempx = zx;
		zx = real_part(ft_absfloat(zx), ft_absfloat(zy)) + rlpart;
		zy = imaginary_part(ft_absfloat(zy), ft_absfloat(tempx)) + impart;
		//printf("zx = %f and zy = %f\n", zx, zy);
		n++;
	}
	fill_pix(i, j, fractol, n == fractol->itmax ? 0x000000 : fractol->color * n);
	return (n);
}

/*
   void	keys_and_mouse(t_fractol *fractol)
   {
   mlx_hook(fractol->mlx.win_ptr, 2, 0, key_press, fractol);
   mlx_hook(fractol->mlx.win_ptr, 4, 0, mouse_press, fractol);
   }
 */
void		trace_fractal(t_fractol *fractol)
{
	double i;
	double j;
	int m;
	int color;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			//m = mandelbrot(i, j, fractol);
			m = julia(i, j, fractol);
			//m = buffalo(i, j, fractol);
			//m = mandeltest(i, j, fractol);
			//m = burningship(i, j, fractol);
			color = 255 - (m * 255 / 100);
			//fill_pix(i, j, fractol, color);
			j++;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_fractol	fractol;

	prepare_julia(&fractol);
	//prepare_mandel(&fractol);
	if (argc != 2)
	{
		ft_printf("usage: ./fractol %{b}s\n", "[choice of fractal]");
		return (1);
	}
	if ((fractol.mlx.mlx_ptr = mlx_init()) == NULL)
		return (ft_printf("there was a problem with %{r}s\n", "mlx_init"));
	fractol.mlx.win_ptr = mlx_new_window(fractol.mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, argv[1]);
	fractol.img.img_ptr = mlx_new_image(fractol.mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fractol.img.data = (int *)mlx_get_data_addr(fractol.img.img_ptr,
			&fractol.img.bpp, &fractol.img.size_l, &fractol.img.endian);
	trace_fractal(&fractol);
	mlx_put_image_to_window(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, fractol.img.img_ptr, 0, 0);
	keys_and_mouse(&fractol);
	//menu(map);
	mlx_loop(fractol.mlx.mlx_ptr);
	return (0);
}
