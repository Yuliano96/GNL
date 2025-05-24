/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:35:18 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/24 18:30:48 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Calcula la longitud de una cadena de caracteres
 * @param str: cadena a medir
 * @return: longitud de la cadena
 */
size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * Busca la primera aparición de un carácter en una cadena
 * @param s: cadena donde buscar
 * @param c: carácter a buscar
 * @return: puntero al carácter encontrado o NULL si no se encuentra
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * Concatena dos cadenas en una nueva cadena
 * @param s1: primera cadena (se libera automáticamente)
 * @param s2: segunda cadena a concatenar
 * @return: nueva cadena concatenada o NULL en caso de error
 */
char	*ft_strjoin(char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}