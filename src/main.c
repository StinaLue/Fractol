#include <stdio.h>

#include "fractol.h"
#include "keys_and_mouse.h"
#include <math.h>
#include "libft.h"

void		multithread(t_fractol fractol);

void	prepare_frac(t_fractol *fractol);

void	*trace_fractal(void *fractol);

void	destroy_and_clear(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx.mlx_ptr, fractol->img.img_ptr);
	mlx_clear_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr);
	fractol->img.img_ptr = mlx_new_image(fractol->mlx.mlx_ptr, fractol->img.width,
			fractol->img.height);
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
	multithread(*fractol);
}

void	close_window(t_fractol *fractol)
{
	destroy_and_clear(fractol);
	exit(0);
}

void	zoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	fractol->realstart = (x / fractol->zoom + fractol->realstart) - (x / (fractol->zoom * 1.3));
	fractol->imstart = (y / fractol->zoom + fractol->imstart) - (y / (fractol->zoom * 1.3));
	fractol->zoom *= 1.3;
	multithread(*fractol);
}

void	unzoom(int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	fractol->realstart = (x / fractol->zoom + fractol->realstart) - (x / (fractol->zoom / 1.3));
	fractol->imstart = (y / fractol->zoom + fractol->imstart) - (y / (fractol->zoom / 1.3));
	fractol->zoom /= 1.3;
	multithread(*fractol);
}

void	itmaxchange(int key, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (key == O)
	{
		fractol->itmax += 10;
	}
	else if (key == P && fractol->itmax > 0)
	{
		fractol->itmax -= 10;
	}
	multithread(*fractol);
}

void	resetfrac(int key, t_fractol *fractol)
{
	(void)key;
	destroy_and_clear(fractol);
	prepare_frac(fractol);
	multithread(*fractol);
}

int	isfullscreen(int width, int height)
{
	if (width == WIN_WIDTH && height == WIN_HEIGHT)
		return (1);
	return (0);
}

void	togglefullscreen(t_fractol *fractol)
{
	if (isfullscreen(fractol->img.width, fractol->img.height))
	{
		fractol->img.width = 500;
		fractol->img.height = 500;
	}
	else
	{
		fractol->img.width = WIN_WIDTH;
		fractol->img.height = WIN_HEIGHT;
	}
}

void	imgsize(int key, t_fractol *fractol)
{
	if (key == 33 && fractol->img.width < WIN_WIDTH && fractol->img.height < WIN_HEIGHT \
			&& !isfullscreen(fractol->img.width, fractol->img.height))
	{
		fractol->img.width += 10;
		fractol->img.height += 10;
	}
	else if (key == 30 && fractol->img.width > 100 && fractol->img.height > 100 && \
			!isfullscreen(fractol->img.width, fractol->img.height))
	{
		fractol->img.width -= 10;
		fractol->img.height -= 10;
	}
	else if (key == F && fractol->img.width > 0 && fractol->img.height > 0)
		togglefullscreen(fractol);
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

void	julia_trigger(int key, t_fractol *fractol)
{
	(void)key;
	if (fractol->frac == JULIA)
		fractol->julia_mouse = !fractol->julia_mouse;
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

void	menu_trigger(int key, t_fractol *fractol)
{
	(void)key;
	fractol->menu = !fractol->menu;
	multithread(*fractol);
}

int	key_press(int key, void *param)
{
	printf("KEY = %d\n", key);
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

int             mouse_hook(int mousecode, int x, int y, t_fractol *fractol)
{
	destroy_and_clear(fractol);
	if (mousecode == 4 || mousecode == 1)
		zoom(x, y, fractol);
	else if (mousecode == 5 || mousecode == 2)
		unzoom(x, y, fractol);
	multithread(*fractol);
	return (0);
}

int             mouse_julia(int x, int y, t_fractol *fractol);

void	keys_and_mouse(t_fractol *fractol)
{
	mlx_hook(fractol->mlx.win_ptr, 6, 1L < 6, mouse_julia, fractol);
	mlx_hook(fractol->mlx.win_ptr, 2, 0, key_press, fractol);
	mlx_mouse_hook(fractol->mlx.win_ptr, mouse_hook, fractol);
}

void	prepare_frac(t_fractol *fractol)
{
	fractol->itmax = 100;
	fractol->zoom = fractol->img.height / 3;
	fractol->realstart = -2.0;
	fractol->imstart = -1.9;
	fractol->menu = 1;
	fractol->index = 0;
	fractol->palettes[0] = 0x525252;
	fractol->palettes[1] = 0xfac0e1;
	fractol->palettes[2] = 0x090088;
	fractol->palettes[3] = 0xecfcff;
	fractol->palettes[4] = 0x1e0411;
	//fractol->palettes[4] = 0xff5200;
	fractol->color = fractol->palettes[fractol->index];
	fractol->realpart = 0.285;
	fractol->impart = 0.01;
	fractol->julia_mouse = 1;
}

int             mouse_julia(int x, int y, t_fractol *fractol)
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

void		menu(t_fractol fractol);

void		init_mlx(t_mlx *mlx, char *title)
{
	if ((mlx->mlx_ptr = mlx_init()) == NULL)
	{
		ft_dprintf(2, "there was a problem with %{r}s\n", "mlx_init");
		exit(-1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, title);
}

void		init_img(t_img *img, t_mlx *mlx)
{
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, img->width, img->height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_l, &img->endian);
}

void		start_values(t_fractol *fractol, char *title)
{
	fractol->img.width = 500;
	fractol->img.height = 500;
	prepare_frac(fractol);
	if (ft_strncmp(title, "julia", ft_strlen("julia")) == 0)
		fractol->frac = JULIA;
	else if (ft_strncmp(title, "mandelbrot", ft_strlen("mandelbrot")) == 0)
		fractol->frac = MANDELBROT;
	else if (ft_strncmp(title, "burningship", ft_strlen("burningship")) == 0)
		fractol->frac = BURNING_SHIP;
	else
		fractol->frac = 0;
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
