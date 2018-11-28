/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcahill <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:11:52 by fcahill           #+#    #+#             */
/*   Updated: 2018/11/28 18:12:03 by fcahill          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 10000
char 	*ft_strnew(size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char *ft_getcharfd(int fd)
{
	static char buf[BUF_SIZE + 1];
	char *bufp = buf;
	char *tmp = "";
	char *join = "";
	int n = 0;
	size_t i = 0;

	// This could go two ways. I could take out the condition re newline, and it will collect the whole string or leave this as a line collector and then find a way to return the starting position for the next line //
	while ((n = read(fd, buf, 1)))
	{
	if (n <= 0 || buf[0] == '\n')
			break;
		bufp = buf;
		tmp = ft_strnew(i);
		tmp = join;
		join = ft_strnew(++i);
		join = ft_strjoin(tmp, bufp);
	}
	if (n > 0)
		return (&*join);
	return (NULL);
}
int main()
{
	char c;
	char *str = ft_strnew(500);
	char *str2 = ft_strnew(500);
	int i = 0;
	static char buf[1];
		int fd = open("test.txt", O_RDONLY);
	str = ft_getcharfd(fd);
	printf("%s\n", str);
	str2 = ft_getcharfd(fd);
	printf("%s\n", str2);
	str2 = ft_getcharfd(fd);
	printf("%s\n", str2);
	str2 = ft_getcharfd(fd);
	printf("%s\n", str2);
	str2 = ft_getcharfd(fd);
printf("%s\n", str2);
	str2 = ft_getcharfd(fd);
	printf("%s\n", str2);


}
