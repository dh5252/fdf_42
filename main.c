/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:11:48 by cahn              #+#    #+#             */
/*   Updated: 2023/08/08 20:31:57 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

void    map_setting(t_fdf *fdf)
{
    fdf->map.coordi_y = 0 ;
    fdf->map.coordi_z = 0;
    fdf->map.x_value = 1.0;
    fdf->map.angle_y = cos(M_PI / 3);
    fdf->map.angle_z = fdf->map.angle_y * sin(M_PI / 6);
    fdf->map.zoom = ceil((WIN_WIDTH / fdf->map.width) + 2);
    fdf->color.r = 0x2F;
	fdf->color.g = 0x2F;
	fdf->color.b = 0x2F;
}

void    color_set(t_fdf *fdf)
{
    fdf->color.r = (fdf->color.r + 1) % 0x7F;
    fdf->color.g = (fdf->color.g + 1) % 0x7F;
    fdf->color.b = (fdf->color.b + 1) % 0x7F;
}

int main(int argc, char **argv)
{
    t_fdf fdf;

    if (argc != 2)
        print_error_exit("number of arguments is error\n");
    map_parsing(&fdf, argv);
    map_setting(&fdf);
    fdf.mlx.init = mlx_init();
    fdf.mlx.win = mlx_new_window(fdf.mlx.init, WIN_WIDTH, WIN_HEIGHT, "FDF");
    draw(&fdf);
    mlx_loop(fdf.mlx.init);
}