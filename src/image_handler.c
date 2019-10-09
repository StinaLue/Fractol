/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:07:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/08 13:15:40 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys_and_mouse.h"

void	destroy_and_clear(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx.mlx_ptr, fractol->img.img_ptr);
	mlx_clear_window(fractol->mlx.mlx_ptr, fractol->mlx.win_ptr);
	fractol->img.img_ptr = mlx_new_image(fractol->mlx.mlx_ptr,
		fractol->img.width, fractol->img.height);
	fractol->img.data = (int *)mlx_get_data_addr(fractol->img.img_ptr,
		&fractol->img.bpp, &fractol->img.size_l, &fractol->img.endian);
}

int		isfullscreen(int width, int height)
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
	if (key == 33 && fractol->img.width < WIN_WIDTH && fractol->img.height
		< WIN_HEIGHT && !isfullscreen(fractol->img.width, fractol->img.height))
	{
		fractol->img.width += 10;
		fractol->img.height += 10;
	}
	else if (key == 30 && fractol->img.width > 100 && fractol->img.height
		> 100 && !isfullscreen(fractol->img.width, fractol->img.height))
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
