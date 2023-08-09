/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:11:48 by cahn              #+#    #+#             */
/*   Updated: 2023/08/09 21:12:13 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void	map_setting(t_fdf *fdf)
{
	fdf->map.x_value = 1.0;
	fdf->map.angle_y = cos(M_PI / 3);
	fdf->map.angle_z = fdf->map.angle_y * sin(M_PI / 6);
	if (fdf->map.width > fdf->map.height)
		fdf->map.zoom = ceil((WIN_WIDTH / fdf->map.width) + 2);
	else
		fdf->map.zoom = ceil((WIN_HEIGHT / fdf->map.height) + 2);
	fdf->color.r = 0xFF;
	fdf->color.g = 0xFF;
	fdf->color.b = 0xFF;
}

int	return_one_byte(char *hex)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while (hex[i] && i < 2)
	{
		value *= 16;
		if (hex[i] >= '0' && hex[i] <= '9')
			value += hex[i] - '0';
		else if (hex[i] >= 'A' && hex[i] <= 'Z')
			value += hex[i] - 'A' + 10;
		++i;
	}
	return (value);
}

t_color	return_color(char *hex)
{
	t_color	rgb;
	int		len;

	len = ft_strlen(hex);
	if (len > 0)
		rgb.r = return_one_byte(hex);
	if (len > 2)
		rgb.g = return_one_byte(hex + 2);
	if (len > 4)
		rgb.b = return_one_byte(hex + 4);
	return (rgb);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		print_error_exit("number of arguments is error\n");
	map_parsing(&fdf, argv);
	map_setting(&fdf);
	fdf.mlx.init = mlx_init();
	fdf.mlx.win = mlx_new_window(fdf.mlx.init, WIN_WIDTH, WIN_HEIGHT, "FDF");
	draw(&fdf);
	mlx_key_hook(fdf.mlx.win, &key_event, &fdf);
	mlx_hook(fdf.mlx.win, 17, 0, &close_button, &fdf);
	mlx_loop(fdf.mlx.init);
}
