/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:33:47 by pablo             #+#    #+#             */
/*   Updated: 2024/06/22 21:42:14 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*src;
	size_t	i;

	i = 0;
	src = malloc(nmemb * size);
	if (!src)
		return (NULL);
	while (i < nmemb)
	{
		((char *)src)[i] = 0;
		i++;
	}
	return (src);
}

int	ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str && c != 0)
		return (-1);
	else if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

void	ft_strjoin(char **s1, char *s2)
{
	char	*str;
	int		totalsize;

	if (!(*s1) && !s2)
		return ;
	totalsize = 0;
	if (*s1)
		totalsize += ft_find_char(*s1, 0);
	if (s2)
		totalsize += ft_find_char(s2, 0);
	str = ft_calloc(totalsize + 1, sizeof(char));
	if (!str)
		return ;
	while (*s1 && *(*s1))
		*str++ = *(*s1)++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	// if (*s1)
	// 	free(*s1);
	*s1 = str - totalsize;
}

/**
 * @brief Devuelve dos subcadenas, divididas por un caracter de nueva linea
 * @param str La cadena a dividir
 * @param len La longitud de la cadena
 * @return El array de subcadenas (la primera es hasta elcaracter de
 * nueva linea (incluido), la segunda es despues del caracter de nueva linea)
 */
char	**ft_substr_comb(char *str, int len, int pos, int i)
{
	char	**ret;

	if (ft_find_char(str, '\n') == -1)
		ret = ft_calloc(3, sizeof(char *));
	else
		ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		return (NULL);
	while (pos < len && str[pos] != '\n')
		pos++;
	ret[0] = ft_calloc(pos + 1, sizeof(char));
	i = -1;
	while (++i < pos + 1)
		ret[0][i] = str[i];
	ret[0][i] = '\0';
	if (pos == len)
		return (ret);
	ret[1] = ft_calloc(len - pos, sizeof(char));
	pos++;
	i = -1;
	while (pos + ++i < len && str[pos + i] != '\0')
		ret[1][i] = str[pos + i];
	ret[1][i] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	char		str[BUFFER_SIZE + 1];
	ssize_t		byte_read;
	static char	*_static = NULL;
	char		**result;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	byte_read = 1;
	while (ft_find_char(_static, '\n') == -1 && ft_find_char(_static, 0) == 0)
	{
		byte_read = read(fd, str, BUFFER_SIZE);
		if (byte_read == -1)
			return (NULL);
		str[byte_read] = '\0';
		if (byte_read == 0)
			return (_static);
		ft_strjoin(&_static, str);
	}
	result = ft_substr_comb(_static, ft_find_char(_static, 0), 0, 1);
	ft_strjoin(&_static, result[1]);
	ft_strjoin(&ret, result[0]);
	if (result[1] != NULL)
		free(result[1]);
	return (free(result[0]), free(result), ret);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("~%s~\n", line);
	free(line);
	// printf("~%s~\n", get_next_line(fd));
	// printf("~%s~\n", get_next_line(fd));
	// printf("~%s~\n", get_next_line(fd));
	// printf("~%s~\n", get_next_line(fd));
	// printf("~%s~\n", get_next_line(fd));
	// printf("~%s~\n", get_next_line(fd));
	close(fd);
}
