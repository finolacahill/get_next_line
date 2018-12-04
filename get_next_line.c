/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcahill <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:11:52 by fcahill           #+#    #+#             */
/*   Updated: 2018/12/04 22:18:31 by fcahill          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char		*ft_splitline(char *str)
{
	char	*remain;
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	line = ft_strnew(i);
	ft_strncpy(line, str, i);
	line[i] = '\0';
	remain = ft_strnew(ft_strlen(str) - ft_strlen(line));
	i++;
	while (str[i + j] != '\0')
	{
		remain[j] = str[i + j];
		++j;
	}
	remain[j] = '\0';
	ft_strclr(str);
	ft_strcpy(str, line);
	return (remain);
}

static char		*ft_makeline(char *join, char *remain[], int fd, char *bufp)
{
	char *tmp;

	tmp = "";
	if (remain[fd] != NULL)
	{	
		join = ft_strjoin(join, remain[fd]);
		ft_strclr(remain[fd]);
	}
	tmp = ft_strnew(ft_strlen(join));
	tmp = join;
	join = ft_strnew(ft_strlen(tmp) + ft_strlen(bufp));
	join = ft_strjoin(tmp, bufp);
	join[ft_strlen(tmp) + ft_strlen(bufp)] = '\0';
	return (join);
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	char		*bufp;
	char		*join;
	int			n;
	static char	*remain[MAX_FD];

	join = "";
	if (BUFF_SIZE < 1 || line == NULL || fd < 0 || (!(join = ft_strnew(BUFF_SIZE))))
		return (-1);
	if (fd >= MAX_FD || (!(bufp = ft_strnew(BUFF_SIZE))))
		return (-1);

	if (remain[fd] != NULL && ft_strchr(remain[fd], '\n'))
	{
		join = ft_strjoin(join, remain[fd]);
		remain[fd] = ft_splitline(join);
		*line = join;
		free(join);
		return (1);
	}

	while ((n = read(fd, buf, BUFF_SIZE)) >= 0)
	{
		if(n == 0)
			break;
		buf[n] = '\0';
		bufp = buf;
		if (ft_strchr(buf, '\n'))
		{
			if (remain[fd] != NULL)
				join = ft_strjoin(remain[fd], join);
			remain[fd] = ft_splitline(bufp);
			join = ft_strjoin(join, bufp);
			break ;
		}
		join = ft_makeline(join, remain, fd, bufp);
	}
	*line = join;
	if (n == 0 && !*line[0])
		return (0);

	if (n > 0 || (n == 0 && *line[0]))
		return (1);
	return (-1);
}

/*   int		main()
	 {
	 int fd = open("test.txt", O_RDONLY);
	 char *str;

	 get_next_line(fd, &str);
	 printf("%s\n", str);
	 get_next_line(fd, &str);
	 printf("%s\n", str);
	 }i*/ 
