#include "fractol.h"

void            init_mlx(t_mlx *mlx, char *title)
{
	if ((mlx->mlx_ptr = mlx_init()) == NULL)
	{
		ft_dprintf(2, "there was a problem with %{r}s\n", "mlx_init");
		exit(-1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, title);
}

void            init_img(t_img *img, t_mlx *mlx)
{
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, img->width, img->height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_l, &img->endian);
}

void    prepare_frac(t_fractol *fractol)
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

void            start_values(t_fractol *fractol, char *title)
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
