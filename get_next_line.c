/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcahill <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:11:52 by fcahill           #+#    #+#             */
/*   Updated: 2018/12/09 00:04:35 by fcahill          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_splitline(char *str)
{
	char		*remain;
	size_t		i;
	size_t		len;


	i = 0;
	while (str[i] != '\n')
		i++;

	len = ft_strlen(str);
	remain = ft_strnew(len);
	remain = ft_strchr(str, '\n') + 1;
	str[i] = '\0';
	//printf("str = %s\n", str);
//printf("remain2 = %s\n", remain);
//	line = ft_strnew(ft_strlen(str));	
//	ft_strcpy(line, str);
//	free(str);
//	printf("remain3 = %s\n", remain);
//	str = ft_strdup(line);

	return (remain);
}

static int		ft_makeline(char *buf, char **line, char *remain[], int fd)
{

	char *tmp;
	tmp = ft_strnew(BUFF_SIZE + 1);
	tmp = ft_strdup(buf);
	if (ft_strchr(buf, '\n') == NULL)
	{
		if ((remain[fd]) && remain[fd] != buf)
		{
			remain[fd] = ft_strjoin(remain[fd], buf);
			ft_strclr(buf);
			*line = remain[fd];	
			return (0);
		}
		remain[fd] = ft_strdup(buf);
		ft_strclr(buf);
		//	free(tmp);
		return (0);
	}
	if ((remain[fd] != NULL) && (buf != remain[fd]))
		tmp = ft_strjoin(remain[fd], buf);
	ft_strclr(remain[fd]);
	ft_strclr(buf);
	//	printf("tmp = %s\n", tmp);
	remain[fd] = ft_splitline(tmp);
	//	printf("remain %s\n", remain[fd]);
	*line = tmp;
	return (1);
}

static int		ft_end(int n, char **line, char *remain[], int fd)
{
	char *tmp;
	if (n == 0 && *remain[fd])
	{
		tmp = ft_strnew(ft_strlen(remain[fd]));
		tmp = ft_strdup(*line);
		ft_strclr(*line);
		free(*line);
		ft_strclr(remain[fd]);
		*line = tmp;
	//	printf("%s\n", *line);
		return (1);
	}
	if ((n == 0) && (!(*remain[fd])))
		return (0);

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
	//	printf("buf = %s\n", buf);
	//	printf("n = %d\n", n);
	//	printf("rem = %s\n", remain[fd]);

		if ((n = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		buf[n] = '\0';
		if ((ft_makeline(buf, line, remain, fd) == 1))
			return (1);
		if (n == 0)
			break ;
	}
	free(buf);
	n = ft_end(n, line, remain, fd);
	return (n);
}

