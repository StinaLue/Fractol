/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread_trace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:55:05 by sluetzen          #+#    #+#             */
/*   Updated: 2019/10/09 10:09:06 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

void	bonus_frac(int i, int j, t_fractol fractol)
{
	if (fractol.frac == BUFFALO)
		buffalo(i, j, fractol);
	else if (fractol.frac == CELTIC_MANDEL)
		celticmandel(i, j, fractol);
	else if (fractol.frac == TRICORN)
		tricorn(i, j, fractol);
	else if (fractol.frac == MANDEL_FOURTH)
		mandelbrot_fourth(i, j, fractol);
	else if (fractol.frac == MANDEL_FIFTH)
		mandelbrot_fifth(i, j, fractol);
}

void	calc_frac(int i, int j, t_fractol fractol)
{
	if (fractol.frac == JULIA)
		julia(i, j, fractol);
	else if (fractol.frac == MANDELBROT)
		mandelbrot(i, j, fractol);
	else if (fractol.frac == BURNING_SHIP)
		burningship(i, j, fractol);
	else
		bonus_frac(i, j, fractol);
}

void	*trace_fractal(void *fractol)
{
	int			i;
	int			temp;
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

void	multithread(t_fractol fractol)
{
	t_fractol	params[NB_THREADS];
	pthread_t	threads[NB_THREADS];
	int			i;
	int			height;

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
	mlx_put_image_to_window(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr,
		fractol.img.img_ptr, 0, 0);
	if (fractol.menu)
		menu(fractol);
	else
		mlx_string_put(fractol.mlx.mlx_ptr, fractol.mlx.win_ptr, 100, 10, \
				0xFFFFFF, "Show menu: H");
}
