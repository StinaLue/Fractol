#ifndef FRACTOL
# define FRACTOL
# include "mlx.h"
# include "libft.h"
# include <math.h>
# define WIN_WIDTH 1680
# define WIN_HEIGHT 1050
//# define WIN_WIDTH 500
//# define WIN_HEIGHT 500

typedef struct		s_img
{
	void		*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
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
	int		j;
	int		j_max;
	double		realstart;
	double		imstart;
	double		realpart;
	double		impart;
	int		julia_mouse;
	int		frac;
}			t_fractol;

#endif
