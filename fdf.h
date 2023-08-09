/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:11:59 by cahn              #+#    #+#             */
/*   Updated: 2023/08/09 21:13:37 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define KEY_ESC 53

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}	t_mlx;

typedef struct s_image
{
	char	*data;
	int		size;
	int		endian;
	int		bpp;
}	t_image;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map_value
{
	int		value;
	t_color	rgb;
}	t_map_value;

typedef struct s_map
{
	t_map_value	**values;
	int			width;
	int			height;
	int			y0;
	int			y1;
	int			z0;
	int			z1;
	int			zoom;
	double		x_value;
	double		angle_y;
	double		angle_z;
}	t_map;

typedef struct s_fdf
{
	t_mlx	mlx;
	t_map	map;
	t_image	img;
	t_color	color;
}	t_fdf;

void	print_error_exit(char *err);
char	**ft_split(char const *str, char c);
int		ft_atoi(const char *str);
void	map_parsing(t_fdf *fdf, char **argv);
int		draw(t_fdf *fdf);
void	draw_vertical(t_fdf *fdf, int y, int z);
void	draw_horizontal(t_fdf *fdf, int y, int z);
void	put_pixel(t_fdf *fdf, int y, int z);
void	draw_lines(t_fdf *fdf);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);
t_color	return_color(char *hex);
void	free_split(char **split);
int		ft_isalnum(int c);
void	set_color(t_fdf *fdf, t_color rgb);
int		close_button(void);
int		key_event(int keycode, t_fdf *fdf);

#endif