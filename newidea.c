/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcahill <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:11:52 by fcahill           #+#    #+#             */
/*   Updated: 2018/11/30 15:21:28 by fcahill          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_splitline(char *str)
{
	char *remain;
	char *line;
	size_t i;
	size_t j;
	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	line = ft_strnew(i);
	ft_strncpy(line, str, i);
	line[i] = '\0';
	remain = ft_strnew(ft_strlen(str) - ft_strlen(line));
	i++;
	while (j < i)
	{
		remain[j] = str[i + j];
		++j;
	}
	remain[j] = '\0';
	ft_strclr(str);
	ft_strcpy(str, line);
//	printf("str= %s\n", str);
//	printf("splitremain = %s\n", remain);
	return(remain);
}
int get_next_line(const int fd, char **line)
{
	static char buf[BUFF_SIZE + 1];
	char *bufp = buf;
	char *tmp = "";
	char *join = "";
	int n = 0;
	static char *remain;
	char *stock;

//	printf("start remain = %s\n",remain);

	while ((n = read(fd, buf, BUFF_SIZE)))
	{
		if (n < 0)
			break;
		buf[n] = '\0';
		bufp = buf;
		if (ft_strchr(buf, '\n'))
		{
			//printf("%s\n", join);
			remain = ft_splitline(bufp);
		//	printf("%s\n", bufp);
			join = ft_strjoin(join, bufp);
		//	printf("%s\n", join);
//			printf("mid remain = %s\n", remain);
			break;
		}
		if (remain != NULL)
		{	
//			printf("test");
			join = ft_strjoin(join, remain);
		}	
		tmp = ft_strnew(ft_strlen(join));
		tmp = join;
		join = ft_strnew(ft_strlen(tmp) + ft_strlen(bufp));
		join = ft_strjoin(tmp, bufp);
	}
	*line = join;
//	printf("end remain = %s\n", remain);
	if (n == 0)
		return (0);
	if (n > 0)
		return (1);
	return (-1);
}
int main()
{
	char *str = "Hello I am the first line\nand";
	char *remain = "";
	int fd = open("test.txt", O_RDONLY);
		get_next_line(fd, &str);
	printf("%s", str);
		get_next_line(fd, &str);

	printf("%s", str);
		get_next_line(fd, &str);

	printf("%s", str);
		get_next_line(fd, &str);

	printf("%s", str);
}	
