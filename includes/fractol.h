#ifndef FRACTOL
# define FRACTOL
# include "mlx.h"
# include "libft.h"
//# include <math.h>
# define WIN_WIDTH 1680
# define WIN_HEIGHT 1050
# define JULIA 1
# define MANDELBROT 2
# define BURNING_SHIP 3
# define BUFFALO 4
# define CELTIC_MANDEL 5
# define NB_THREADS 100

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
	int		palettes[5];
	int		index;
	int		julia_mouse;
	int		menu;
	int		frac;
}			t_fractol;

void	menu(t_fractol fractol);

/*
** FRACTALS
*/

int     mandelbrot(int i, int j, t_fractol fractol);

int     julia(int i, int j, t_fractol fractol);

int     buffalo(int i, int j, t_fractol fractol);

int     burningship(int i, int j, t_fractol fractol);

int     celticmandel(int i, int j, t_fractol fractol);

/*
** MULTITHREAD TRACING
*/

void            multithread(t_fractol fractol);

/*
** UTILS
*/

double  real_part(double a, double b);

double  imaginary_part(double a, double b);

void    fill_pix(int x, int y, t_fractol *fractol, int color);

#endif
