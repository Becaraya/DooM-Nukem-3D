/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:55:34 by becaraya          #+#    #+#             */
/*   Updated: 2019/03/11 14:25:10 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_readfd(const int fd, char **str)
{
	int			ret;
	char		c[BUFF_SIZE + 1];
	char		*tmp;
	size_t		i;

	i = 0;
	while ((ret = read(fd, c, BUFF_SIZE)) > 0)
	{
		c[ret] = '\0';
		if (!str[fd])
			str[fd] = ft_strnew(1);
		tmp = ft_strjoin(str[fd], c);
		free(str[fd]);
		str[fd] = tmp;
		while (str[fd][i] != '\n' && str[fd][i] != '\0')
			i++;
		if (str[fd][i] == '\n')
			break ;
	}
	return (ret);
}

static void		ft_assign_line(char **str, const int fd, char **line, int i)
{
	char *tmp;

	tmp = NULL;
	if (str[fd][i] != '\0')
	{
		tmp = str[fd];
		*line = ft_strsub(tmp, 0, i);
		tmp = ft_strdup(str[fd] + i + 1);
		free(str[fd]);
		str[fd] = tmp;
	}
	else
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		ft_strdel(&tmp);
	}
}

static int		ft_line_alloc(const int fd, char **line, char **str)
{
	int			ret;
	size_t		i;

	if ((ret = ft_readfd(fd, str)) < 0)
		return (-1);
	i = 0;
	while (str[fd])
	{
		if (str[fd][0] == '\0')
			return (0);
		while (str[fd][i] != '\0' && str[fd][i] != '\n')
			i++;
		if (i == ft_strlen(str[fd]) && (ret = ft_readfd(fd, str)) > 0)
			continue ;
		ft_assign_line(str, fd, line, i);
		return ((ret < 0) ? -1 : 1);
	}
	return ((ret < 0) ? -1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str[OPEN_MAX];
	int				ret;

	if (fd < 0 || !line || BUFF_SIZE < 1 || fd > OPEN_MAX)
		return (-1);
	if ((ret = ft_line_alloc(fd, line, &str[fd])) > 0)
		return (1);
	return (ret < 0 ? -1 : 0);
}
