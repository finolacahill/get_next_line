/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcahill <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:11:52 by fcahill           #+#    #+#             */
/*   Updated: 2018/12/09 21:08:40 by fcahill          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_splitline(char *buf, char **line, char *remain[], int fd)
{
	char *tmp;

	tmp = NULL;
	if ((remain[fd] != NULL) && (buf != remain[fd]))
		tmp = ft_strjoin(remain[fd], buf);
	else
		tmp = ft_strdup(buf);
	ft_strclr(remain[fd]);
	ft_strclr(buf);
	remain[fd] = ft_strdup(ft_strchr(tmp, '\n') + 1);
	*(ft_strchr(tmp, '\n')) = '\0';
	free(*line);
	*line = ft_strdup(tmp);
	free(tmp);
	return (1);
}

static int		ft_makeline(char *buf, char **line, char *remain[], int fd)
{
	char *tmp;

	tmp = NULL;
	if (ft_strchr(buf, '\n') == NULL)
	{
		if ((remain[fd]))
		{
			tmp = ft_strdup(remain[fd]);
			free(remain[fd]);
			remain[fd] = ft_strjoin(tmp, buf);
			ft_strclr(buf);
			free(*line);
			*line = ft_strdup(remain[fd]);
			ft_strdel(&tmp);	
			return (0);
		}
		remain[fd] = ft_strdup(buf);
		ft_strclr(buf);
		free(tmp);
		return (0);
	}
	free(tmp);
	if ((ft_splitline(buf, line, remain, fd)) == 1)
		return (1);
	return (-1);
}

static int		ft_end(int n, char **line, char *remain[], int fd)
{
	char *tmp;

	if (n == 0 && *remain[fd])
	{
		tmp = ft_strnew(ft_strlen(remain[fd]));
		tmp = ft_strdup(*line);
		ft_strclr(*line);
		ft_strclr(remain[fd]);
		*line = tmp;
		return (1);
	}
	if ((n == 0) && (!(*remain[fd])))
	{
		free(*line);
		return (0);
	}
	return (-1);
}

int				get_next_line(const int fd, char **line)
{
	char		*buf;
	int			n;
	static char	*remain[MAX_FD];

	if (BUFF_SIZE < 1 || line == NULL || (!(buf = ft_strnew(BUFF_SIZE + 1))))
		return (-1);
	if (fd >= MAX_FD || (!(*line = ft_strnew(BUFF_SIZE))) || fd < 0)
		return (-1);
	if ((n = 1 || 1) && (remain[fd]))
		if ((ft_makeline(remain[fd], line, remain, fd)) == 1)
			return (1);
	while (n > 0)
	{
		if ((n = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[n] = '\0';
		if ((ft_makeline(buf, line, remain, fd) == 1))
			return (1);
	}
	free(buf);
	n = ft_end(n, line, remain, fd);
	return (n);
}
