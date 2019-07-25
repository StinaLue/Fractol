#include "fractol.h"

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
