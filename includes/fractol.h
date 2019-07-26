#ifndef FRACTOL
# define FRACTOL
# include "mlx.h"
# include "libft.h"
# include <math.h>
# define WIN_WIDTH 1680
# define WIN_HEIGHT 1050

typedef struct		s_img
{
	void		*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}			t_img;

typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}			t_mlx;

typedef struct		s_fractol
{
	t_mlx		mlx;
	t_img		img;
	int		itmax;
	int		color;
	double		zoom;
	double		realstart;
	double		imstart;
}			t_fractol;

#endif