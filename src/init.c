/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:15:28 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/09 10:13:44 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mlx(t_mlx *mlx, char *title)
{
	if ((mlx->mlx_ptr = mlx_init()) == NULL)
	{
		ft_dprintf(2, "there was a problem with %{r}s\n", "mlx_init");
		exit(-1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, title);
}

void	init_img(t_img *img, t_mlx *mlx)
{
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, img->width, img->height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr,
			&img->bpp, &img->size_l, &img->endian);
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
	fractol->color = fractol->palettes[fractol->index];
	fractol->realpart = 0.285;
	fractol->impart = 0.01;
	fractol->julia_mouse = 1;
}

void	bonus_values(t_fractol *fractol, char *title)
{
	if (ft_strncmp(title, "buffalo", ft_strlen("buffalo")) == 0)
		fractol->frac = BUFFALO;
	else if (ft_strncmp(title, "celtic_mandel",
				ft_strlen("celtic_mandel")) == 0)
		fractol->frac = CELTIC_MANDEL;
	else if (ft_strncmp(title, "tricorn",
				ft_strlen("tricorn")) == 0)
		fractol->frac = TRICORN;
	else if (ft_strncmp(title, "mandel_fourth",
				ft_strlen("mandel_fourth")) == 0)
		fractol->frac = MANDEL_FOURTH;
	else if (ft_strncmp(title, "mandel_fifth",
				ft_strlen("mandel_fifth")) == 0)
		fractol->frac = MANDEL_FIFTH;
	else
		fractol->frac = 0;
}

void	start_values(t_fractol *fractol, char *title)
{
	fractol->img.width = 700;
	fractol->img.height = 700;
	prepare_frac(fractol);
	if (ft_strncmp(title, "julia", ft_strlen("julia")) == 0)
		fractol->frac = JULIA;
	else if (ft_strncmp(title, "mandelbrot", ft_strlen("mandelbrot")) == 0)
		fractol->frac = MANDELBROT;
	else if (ft_strncmp(title, "burningship", ft_strlen("burningship")) == 0)
		fractol->frac = BURNING_SHIP;
	else
		bonus_values(fractol, title);
}
