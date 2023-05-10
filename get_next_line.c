/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:51:43 by melee             #+#    #+#             */
/*   Updated: 2023/05/10 18:27:42 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	check_endline_index(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}


char	*parse_return_line(char *line)
{
	int	i;
	char *res;

	i = check_endline_index(line);
	if (i != -1)
	{
		res = ft_substr(line, 0, i+1);
		printf("line string %s\n",line);
		line = line + i + 1;

		printf("line string2 %s\n",line);
		return (res);
	}
	else
		return (line);
}


/* read only the minimum times each time read_file is called, stop whenever buffer has
 * a \n.
 */
char	*read_file(int fd, char *line)
{	
	char	*buffer;
	int		read_status;

	read_status = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (read_status && check_endline_index(buffer) == -1)
	{
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		read_status = read(fd, buffer, BUFFER_SIZE);
		//printf("buffer %s\n",buffer);
		//printf("read status %d\n",read_status);
		if (read_status == -1)
			return (NULL);
		line = ft_strjoin(line, buffer);
		//printf("line %s\n",line);
			
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*res;
	int			index;
	
	if	(!line)
	{
		line = malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		ft_memset(line, '\0', 1);
	}
	i = check_endline_index(line)
	if (i == -1)
	{
		line = read_file(fd, line);
		i = check_endline_index(line);
	}
	if (line=="" || line == NULL)
		return (NULL);
	res = parse_return_line(line);
	line += i+1;

	return (res);
}



#include <stdio.h>

int	main(void)
{
	int	fd = open("ms.txt", O_RDONLY);
	char *str;
	
	str = get_next_line(fd);
	while (str && *str)
	{
		if (*str == '\n')
			printf("\\n");
		printf("%c",*str);
		str++;
	}
}



