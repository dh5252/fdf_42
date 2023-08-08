/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cahn <cahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:25:10 by cahn              #+#    #+#             */
/*   Updated: 2023/01/10 18:04:33 by cahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 1000

typedef struct s_vector
{
	int		capacity;
	int		index;
	int		len;
	char	*string;
}	t_vector;

typedef struct s_fd_list
{
	int					fd;
	t_vector			str_info;
	struct s_fd_list	*next;
	struct s_fd_list	*prev;
}	t_fd_list;

char		*ft_memndup(char *target, int n);
void		*ft_memmove(void *dst, const void *src, size_t len);
char		*get_next_line(int fd);
char		*return_next_line(t_vector *info, int fd);
t_fd_list	*get_node(int fd);
int			allocate_vector(t_vector *info);
t_fd_list	*ft_del_one(t_fd_list *lst, t_fd_list *obj);
void		ft_lstadd_back(t_fd_list **lst, t_fd_list *new);
int			is_last_line(char *str);
char		*copy_newline(t_vector *info, char *return_str, int eof);
#endif