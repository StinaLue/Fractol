#include <stdio.h>

#include "fractol.h"
#include <math.h>
#define RE_START -2.05
#define RE_END 1
#define IM_START -1.3
#define IM_END 1

#define ZOOM 300

double	real_part(double a, double b)
{
	return (a * a - b * b);
}

double	imaginary_part(double a, double b)
{
	return (2 * a * b);
}

int	mandelbrot(double rpart, double ipart)
{
	double zx;
	double zy;
	int n;
	double tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	while ((zx * zx) + (zy * zy) < 4 && n < 100)
	{
		tempx = zx;
		zx = zx * zx - zy * zy + rpart;
		zy = 2 * zx * zy + ipart;
		zy = 2 * zy * tempx + ipart;
		//printf("zx = %f and zy = %f\n", zx, zy);
		n++;
	}
	return (n);
}

void	fill_pix(int x, int y, t_fractol *fractol, int color)
{
	if ((x + y * WIN_WIDTH) < (WIN_WIDTH * WIN_HEIGHT) &&
			(x + y * WIN_WIDTH) > 0 && x < WIN_WIDTH && x > 0)
	{
		fractol->img.data[x + y * WIN_WIDTH] = color;
	}
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
	double rlpart;
	double impart;
	int m;
	int color;

	i = 0;
	while (i < WIN_WIDTH)
	{
		rlpart = i / ZOOM + RE_START;
		j = 0;
		while (j < WIN_HEIGHT)
		{
			impart = j / ZOOM + IM_START;
			//printf("rlpart = %f and impart = %f\n", rlpart, impart);
			m = mandelbrot(rlpart, impart);
			//printf("m = %d\n", m);
			color = 255 - (m * 255 / 100);
			fill_pix(i, j, fractol, color);
			//fill_pix(i, j, fractol, m == 100 ? 0x000000 : 0xFFFFFF);
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
	//keys_and_mouse(map);
	//menu(map);
	mlx_loop(fractol.mlx.mlx_ptr);
	return (0);
}
