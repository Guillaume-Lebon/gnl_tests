/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebon <glebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:08:03 by glebon            #+#    #+#             */
/*   Updated: 2020/12/08 02:00:25 by glebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void		ft_shifted_copy(char **str, long int j)
{
	long int i;

	if ((*str)[j] == '\0')
	{
		free(*str);
		*str = NULL;
		return ;
	}
	i = 0;
	while ((*str)[j])
	{
		(*str)[i] = (*str)[j];
		++i;
		++j;
	}
	(*str)[i] = '\0';
}

static long int	ft_calc_size(char *s)
{
	long int i;

	i = 0;
	while (s != NULL && s[i] && s[i] != '\n')
		++i;
	return (i);
}

static char		ft_copy(char *line2, char **line, char **str)
{
	long int i;
	long int j;

	i = -1;
	while (*line != NULL && (*line)[++i])
		line2[i] = (*line)[i];
	if (*line != NULL)
		--i;
	j = -1;
	while (*str != NULL && (*str)[++j] && (*str)[j] != '\n')
		line2[++i] = (*str)[j];
	line2[++i] = '\0';
	free(*line);
	*line = line2;
	if (*str != NULL && (*str)[j] == '\n')
	{
		ft_shifted_copy(str, j + 1);
		return (1);
	}
	free(*str);
	*str = NULL;
	return (0);
}

static char		ft_create_line(char **line, char **str)
{
	char		*line2;
	long int	size;

	size = ft_calc_size(*line) + ft_calc_size(*str);
	line2 = malloc(sizeof(char) * (size + 1));
	if (line2 == NULL)
	{
		free(*str);
		return (-1);
	}
	return (ft_copy(line2, line, str));
}

int				get_next_line(int fd, char **line)
{
	static char	*str[INT_MAX];
	ssize_t		ret1;
	char		ret2;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	ret1 = -2;
	*line = NULL;
	while (ret1 != 0)
	{
		if ((ret2 = ft_create_line(line, &(str[fd]))) == 1)
			return (1);
		if (ret2 == -1)
			return (-1);
		str[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (str[fd] == NULL)
			return (-1);
		ret1 = read(fd, str[fd], BUFFER_SIZE);
		if (ret1 == -1)
			free(str[fd]);
		if (ret1 == -1)
			return (-1);
		str[fd][ret1] = '\0';
	}
	return (0);
}
