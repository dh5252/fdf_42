/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:11:54 by cahn              #+#    #+#             */
/*   Updated: 2022/11/27 20:11:26 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	allocate_vector(t_vector *info)
{
	char	*tmp;

	tmp = 0;
	if (info->capacity == 0)
		info->capacity = BUFFER_SIZE;
	else if (info->len + BUFFER_SIZE >= info->capacity)
	{
		info->capacity = info->capacity << 1;
		tmp = info->string;
	}
	else
		return (1);
	info->string = (char *)malloc(sizeof(char) * info->capacity);
	if (!info->string)
	{
		if (tmp != 0)
			free(tmp);
		return (0);
	}
	ft_memmove(info->string, tmp, info->len);
	if (tmp != 0)
		free(tmp);
	return (1);
}

t_fd_list	*get_node(int fd)
{
	t_fd_list	*newnode;

	newnode = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (newnode == 0)
		return (0);
	newnode->fd = fd;
	newnode->next = 0;
	newnode->prev = 0;
	newnode->str_info.capacity = 0;
	newnode->str_info.index = 0;
	newnode->str_info.string = 0;
	newnode->str_info.len = 0;
	return (newnode);
}

char	*copy_newline(t_vector *info, char *return_str, int eof)
{
	return_str = ft_memndup(info->string, info->index + !eof);
	if (return_str == 0)
	{
		free(info->string);
		return (0);
	}
	if (!eof)
	{
		ft_memmove(info->string, info->string + info->index + 1, \
		info->len - info->index - 1);
		info->len = info->len - info->index - 1;
		info->index = 0;
	}
	else
		free(info->string);
	return (return_str);
}

char	*return_next_line(t_vector *info, int fd)
{
	int		read_len;
	char	*return_str;

	return_str = 0;
	read_len = 3;
	while (!(read_len == 0 || read_len == -1))
	{
		if (!allocate_vector(info))
			return (0);
		if (info->index == info->len)
		{
			read_len = read(fd, info->string + info->index, BUFFER_SIZE);
			info->len += (read_len > 0) * read_len;
		}
		while (info->index < info->len)
		{
			if (info->string[info->index] == '\n')
				return (copy_newline(info, return_str, 0));
			info->index++;
		}
	}
	if (info->len != 0 && read_len != -1)
		return (copy_newline(info, return_str, 1));
	free(info->string);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_fd_list		*list;
	t_fd_list				*find;
	char					*tmp;

	find = list;
	while (find != 0)
	{
		if (find->fd == fd)
		{
			tmp = return_next_line(&(find->str_info), fd);
			if (!tmp || is_last_line(tmp))
				list = ft_del_one(list, find);
			return (tmp);
		}
		find = find->next;
	}
	find = get_node(fd);
	if (find == 0)
		return (0);
	ft_lstadd_back(&list, find);
	tmp = return_next_line(&(find->str_info), fd);
	if (!tmp || is_last_line(tmp))
		list = ft_del_one(list, find);
	return (tmp);
}
