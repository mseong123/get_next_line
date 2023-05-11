/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:51:43 by melee             #+#    #+#             */
/*   Updated: 2023/05/11 17:53:52 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*free_join(char *line, char* buffer)
{
	char *joined;
	joined = ft_strjoin(line, buffer);
	free(line);
	return (joined);
}



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

char	*parse_next_line(char *line)
{
	char	*res;
	int		index;
	int		i;

	index = check_endline_index(line);
	i = 0;
	if (index == -1)
	{
		free(line);
		return (NULL);
	}
	else
	{
		res = ft_substr(line, index+1, ft_strlen(line));	
	}
	free(line);
	return (res);
}

char	*parse_result(char *line)
{
	int	i;
	char *res;

	i = check_endline_index(line);
	if (i != -1)
	{
		res = ft_substr(line, 0, i+1);
		return (res);
	}
	else if (*line == '\0')
		return (NULL);
	else
	{
		res = ft_substr(line, 0, ft_strlen(line));
		return (res);
	}

}


/* read only the minimum times each time read_file is called, stop whenever buffer has a \n.
 */
char	*read_file(int fd, char *line)
{	
	char	*buffer;
	int		read_status;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_status = 1;

	//printf("line ptr BUFFER [%p]\n", buffer);
	while (read_status > 0)	
	{
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		read_status = read(fd, buffer, BUFFER_SIZE);
		if (read_status == -1)
		{
			free(buffer);
			return (NULL);
		}
		//if (read_status>0)
			line = free_join(line, buffer);
//	printf("TOTAL LINE %s\n",line);	
//	printf("line ptr LINE [%p]\n", line);

		if (check_endline_index(line) != -1)
			break;
	}
	free(buffer);
	
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*res;

	if (fd == -1 || read(fd, NULL, 0) < 0)
		return (NULL);

	if	(!line)
	{
		line = malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		ft_memset(line, '\0', 1);
	}

	//printf("line ptr START LINE [%p]\n", line);
	//printf("string = %s\n",line);
	line = read_file(fd, line);

	if (line == NULL)
		return (NULL);
	res = parse_result(line);	
	line = parse_next_line(line);	
	//printf("line ptr END2 LINE [%p]\n", line);
	
	
	return (res);
}


/*
#include <stdio.h>

int	main(void)
{
	int	fd = open("ms.txt", O_RDONLY);
	char *str;
	
	str = get_next_line(fd);
	printf("%s",str);	
str = get_next_line(fd);

	printf("%s",str);	
	}
*/






/*
while (str && *str)
	{	 
		if (*str == '\n')
			printf("\\n");
		printf("%c",*str);
		str++;
	}
*/


