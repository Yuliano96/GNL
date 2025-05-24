// Función de prueba (opcional - quitar en versión final)
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: No se pudo abrir el archivo\n");
		return (1);
	}
	
	line_count = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Línea %d: %s", line_count++, line);
		if (line[ft_strlen(line) - 1] != '\n')
			printf("\n"); // Agregar \n si la línea no lo tiene
		free(line);
	}
	
	close(fd);
	printf("\nTotal de líneas leídas: %d\n", line_count - 1);
	return (0);
}