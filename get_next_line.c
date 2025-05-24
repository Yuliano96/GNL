/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:10:20 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/24 19:24:10 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Extrae una línea completa del buffer (incluyendo el \n si existe)
 * @param buffer: buffer que contiene los datos leídos
 * @return: línea extraída o NULL si está vacío
 */
char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || !buffer[0])
		return (NULL);
	
	// Encontrar la longitud hasta \n o final de cadena
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	
	// Reservar memoria (+1 para \n si existe, +1 para \0)
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	
	// Copiar caracteres
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	
	// Incluir \n si existe
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

/**
 * Actualiza el buffer eliminando la línea ya procesada
 * @param buffer: buffer actual
 * @return: nuevo buffer con el contenido restante
 */
char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (NULL);
	
	// Encontrar posición después del \n
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	
     if (buffer[i] == '\0' || buffer[i + 1] == '\0')
     {
         free(buffer);
         return (NULL);
     }
	
	// Crear nuevo buffer con el contenido restante
	new_buffer = malloc(ft_strlen(buffer) - i);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	
	i++; // Saltar el \n
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	
	free(buffer);
	return (new_buffer);
}

/**
 * Lee el archivo línea por línea
 * @param fd: descriptor de archivo
 * @return: siguiente línea del archivo o NULL si no hay más líneas
 */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		temp[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	// Validar parámetros
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	// Leer hasta encontrar \n o EOF
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (buffer)
			{
				free(buffer);
				buffer = NULL;
			}
			return (NULL);
		}
		if (bytes_read > 0)
		{
			temp[bytes_read] = '\0';
			buffer = ft_strjoin(buffer, temp);
			if (!buffer)
				return (NULL);
		}
	}
	
	// Extraer línea y actualizar buffer
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	
	return (line);
}
