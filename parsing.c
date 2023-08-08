/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:13:05 by cahn              #+#    #+#             */
/*   Updated: 2023/08/08 20:31:44 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

char    *return_file_name(char **argv)
{
    int i;

    i = 0;
    while (argv[1][i])
        ++i;
    if (i >= 5 && (argv[1][i - 4] == '.' && argv[1][i - 3] == 'f' && \
        argv[1][i - 2] == 'd' && argv[1][i - 1] == 'f'))
        return (argv[1]);
    print_error_exit("File Format Error\n");
    return (NULL);
}

int count_cols(char *line)
{
    int i;

    i = 0;
    while (*line)
    {
        if (*line >= '0' && *line <= '9')
        {
            ++i;
            while (*line >= '0' && *line <= '9')
                ++line;
        }
        else if (*line != ' ' && *line != '-' && *line != '\n')
            print_error_exit("map value error\n");
        ++line;
    }
    return (i);
}

void    count_rows(t_fdf *fdf, char *file_name)
{
    char    *line;
    int     length;
    int     fd;

    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        print_error_exit("File Open Error\n");
    fdf->map.width = -1;
    fdf->map.height = 0;
    line = get_next_line(fd);
    while (line)
    {
        ++fdf->map.height;
        length = count_cols(line);
        free(line);
        if (fdf->map.width == -1)
            fdf->map.width = length;
        else if (fdf->map.width != length)
            print_error_exit("map size Error\n");
        line = get_next_line(fd);
    }
    if (close(fd) == -1)
        print_error_exit("File close Error");
}

void    input_values(t_fdf *fdf, char *line, int h)
{
    char    **split;
    int     i;
    int     w;

    split = ft_split(line, ' ');
    if (!split)
        print_error_exit("Split Error\n");
    i = 0;
    w = 0;
    while (split[i] && w < fdf->map.width)
        fdf->map.values[h][w++] = ft_atoi(split[i++]);
    i = 0;
    while (split[i])
    {
        free(split[i]);
        ++i;
    }
    free(split);
}

void    map_parsing(t_fdf *fdf, char **argv)
{
    int     fd;
    char    *line;
    int     h;

    count_rows(fdf, return_file_name(argv));
    fdf->map.values = (int **)malloc(sizeof(int *) * fdf->map.height);
    if (!fdf->map.values)
        print_error_exit("Memory allocation Error\n");
    fd = open(return_file_name(argv), O_RDONLY);
    line = get_next_line(fd);
    h = 0;
    while (line && h < fdf->map.height)
    {
        fdf->map.values[h] = NULL;
        fdf->map.values[h] = (int *)malloc(sizeof(int) * fdf->map.width);
        if (!fdf->map.values[h])
            print_error_exit("Memory allocation Error\n");
        input_values(fdf, line, h);
        free(line);
        line = get_next_line(fd);
        ++h;
    }
    if (close(fd) == -1)
        print_error_exit("File close Error\n");
}