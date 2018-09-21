#include "../inc/vm.h"

void	save_in_var(unsigned int *var, unsigned char *arr)
{
	*var = (*var | arr[0]) << 8;
	*var = (*var | arr[1]) << 8;
	*var = (*var | arr[2]) << 8;
	*var = *var | arr[3];
}

int		read_header(header_t *header, char *filename)
{
	unsigned char	buf[COMMENT_LENGTH + 1];
	int				fd;

	fd = open(filename, O_RDONLY);
	header->magic = 0;
	if (fd < 0)
		return (0);
	if (read(fd,buf, 4) < 4)
		return (0);
	save_in_var(&header->magic, buf);
	if (read(fd, buf, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (0);
	ft_strcpy(header->prog_name, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (0);
	if (read(fd, buf, 4) < 4)
		return (0);
	save_in_var(&header->prog_size, buf);
	ft_printf("%x", header->prog_size);
	if (read(fd, buf, COMMENT_LENGTH) < COMMENT_LENGTH)
		return (0);
	ft_strcpy(header->comment, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (0);
	return (fd);
}

int		main (int argc, char **argv)
{
	header_t	*header;
	int			fd;

	header = (header_t *)ft_memalloc(sizeof(header_t));
	if (!(fd = read_header(header, "../files/helltrain.cor")))
	{
		close(fd);
		exit(75);
	}
	return (0);
}