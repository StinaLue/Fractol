#include <stdio.h>

#include "fractol.h"
#include "keys_and_mouse.h"
#include <math.h>
#define RE_START -2.05
#define IM_START -1.3

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

void	zoom(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == W)
	{
		fractol->zoom += 100;
		fractol->realstart += fractol->realstart / fractol->zoom;
		fractol->imstart += fractol->imstart / fractol->zoom;
	}
	else if (key == S)
	{
		fractol->zoom -= 100;
		fractol->realstart -= fractol->realstart / fractol->zoom;
		fractol->imstart -= fractol->imstart / fractol->zoom;
	}
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

int	key_press(int key, void *param)
{
	if (key == W || key == S)
		zoom(key, (t_fractol *)param);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
		complexchange(key, (t_fractol *)param);
	else if (key == O || key == P)
		itmaxchange(key, (t_fractol *)param);
	else if	(key == N || key == M)
		changecolor(key, (t_fractol *)param);
	return (1);
}

void	keys_and_mouse(t_fractol *fractol)
{
	mlx_hook(fractol->mlx.win_ptr, 2, 0, key_press, fractol);
}

void	prepare_mandel(t_fractol *fractol)
{
	fractol->itmax = 100;
	fractol->zoom = 300;
	fractol->realstart = -2.05;
	fractol->imstart = -1.3;
	fractol->color = 100;
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

int	mandelbrot(int i, int j, t_fractol *fractol)
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
		zx = zx * zx - zy * zy + rlpart;
		zy = 2 * zy * tempx + impart;
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
			//printf("rlpart = %f and impart = %f\n", rlpart, impart);
			m = mandelbrot(i, j, fractol);
			//printf("m = %d\n", m);
			color = 255 - (m * 255 / 100);
			//fill_pix(i, j, fractol, color);
			j++;
		}
		i++;
	}
	/*
	int i;
	int j;
	int color;
	int count;

	color = 0xFF;
	i = 0;
	j = 0;
	count = 0;
	while (j < WIN_HEIGHT)
	{
		while (i < WIN_WIDTH)
		{
			while (count <= WIN_WIDTH / 255)
			{
			fill_pix(i, j, fractol, color);
			count++;
			i++;
			}
			color += 0xff;
			count = 0;
		}
		color = 0xFF;
		i = 0;
		j++;
	}
	*/
}

int		main(int argc, char **argv)
{
	t_fractol	fractol;

	prepare_mandel(&fractol);
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
