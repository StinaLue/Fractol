#include <stdio.h>
#include <pthread.h>

#include "fractol.h"
#include "keys_and_mouse.h"
#include <math.h>
#include "libft.h"
#define JULIA 1
#define MANDELBROT 2
#define BURNING_SHIP 3
#define BUFFALO 4
#define NB_THREADS 100

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
	if ((x + y * fractol->img.width) < (fractol->img.width * fractol->img.height)
			&& (x + y * fractol->img.width) > 0 && x < fractol->img.width && x > 0)
	{
		fractol->img.data[x + y * fractol->img.width] = color;
	}
}

int	mandelbrot(int i, int j, t_fractol fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = real_part(zx, zy) + fractol.realpart;
		zy = imaginary_part(zy, tempx) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
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

int	julia(int i, int j, t_fractol fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;

	n = 0;
	zx = i / fractol.zoom + fractol.realstart;
	zy = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = real_part(zx, zy) - 0.8 + (fractol.realpart / fractol.img.width);
		zy = imaginary_part(zy, tempx) + fractol.impart / fractol.img.width;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	buffalo(int i, int j, t_fractol fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = ft_absfloat(real_part(zx, zy)) + fractol.realpart;
		zy = ft_absfloat(imaginary_part(zy, tempx)) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

int	burningship(int i, int j, t_fractol fractol)
{
	double zx;
	double zy;
	int n;
	double tempx;

	n = 0;
	zx = 0.0;
	zy = 0.0;
	fractol.realpart = i / fractol.zoom + fractol.realstart;
	fractol.impart = j / fractol.zoom + fractol.imstart;
	while ((zx * zx) + (zy * zy) < 4 && n < fractol.itmax)
	{
		tempx = zx;
		zx = real_part(ft_absfloat(zx), ft_absfloat(zy)) + fractol.realpart;
		zy = imaginary_part(ft_absfloat(zy), ft_absfloat(tempx)) + fractol.impart;
		n++;
	}
	fill_pix(i, j, &fractol, n == fractol.itmax ? 0x000000 : fractol.color * n);
	return (n);
}

void		calc_frac(int i, int j, t_fractol fractol)
{
	if (fractol.frac == JULIA)
		julia(i, j, fractol);
	else if (fractol.frac == MANDELBROT)
		mandelbrot(i, j, fractol);
	else if (fractol.frac == BURNING_SHIP)
		burningship(i, j, fractol);
	else if (fractol.frac == BUFFALO)
		buffalo(i, j, fractol);
}

void		*trace_fractal(void *fractol)
{
	int i;
	int temp;
	t_fractol	*fract;

	i = 0;
	fract = (t_fractol *)fractol;
	temp = fract->j;
	while (i < fract->img.width)
	{
		fract->j = temp;
		while (fract->j < fract->j_max)
		{
			calc_frac(i, fract->j, *fract);
			fract->j++;
		}
		i++;
	}
	return (NULL);
}

void		menu(t_fractol fractol);

void		multithread(t_fractol fractol)
{
	t_fractol	params[NB_THREADS];
	pthread_t	threads[NB_THREADS];
	int		i;
	int		height;

	i = 0;
	height = fractol.img.height;
	while (i < NB_THREADS)
	{
		ft_memcpy((void *)&params[i], (void *)&fractol, sizeof(t_fractol));
		params[i].j = (height / NB_THREADS) * i;
		params[i].j_max = (height / NB_THREADS) * (i + 1);
		pthread_create(&threads[i], NULL, trace_fractal, &params[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, fractol.img.img_ptr, 0, 0);
	if (fractol.menu)
		menu(fractol);
	else
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
					0xFFFFFF, "Show menu: H");
}

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
	else if (fractol.frac == BUFFALO)
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
					0xFFFFFF, "BUFALLO");
}

void	outputcommands(t_fractol fractol)
{
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 30,
					0xFFFFFF, "Change      palette: N");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 75, 30,
					fractol.color, "color");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 50,
					0xFFFFFF, "Iterations: O(+)/P(-) | current:");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 70,
					0xFFFFFF, "Zoom: scroll up/scroll down");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 90,
					0xFFFFFF, "Move: arrows");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 110,
					0xFFFFFF, "Reset: R | Hide menu: H");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 130,
					0xFFFFFF, "Change fractal: 1/2/3/4");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 150,
					0xFFFFFF, "Change img size: '[' / ']'");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 170,
					0xFFFFFF, "Psychedelic mode: M");
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 10, 190,
					0xFFFFFF, "Close the window: 'esc'");
}

void	menu(t_fractol fractol)
{
	outputfrac(fractol);
	outputcommands(fractol);
	mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 350, 50,
					0xFFFFFF, ft_itoa(fractol.itmax));
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
