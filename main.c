#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

void	exit_err(char *msg, int exit_code)
{
	printf("nm: %s\n", msg);
	//perror();
	exit(exit_code);
}

void	check_elf_validity(char	*mapped_elf)
{
	assert (mapped_elf[0] == ELFMAG0);
	assert (mapped_elf[1] == 'E');
	assert (mapped_elf[2] == 'L');
	assert (mapped_elf[3] == 'F');
	printf("valid\n");
}

int	main(int argc, char **argv)
{
	int		fd;
	int		ret;
	struct stat	elf_info;
	char		*mapped_elf;

	if (argc < 2)
		exit_err("no binary file found", 1);
	printf("%s\n", argv[1]);

	if((fd = open(argv[1], O_RDWR)) < 0)
		exit_err("Failed to open file", 1);
	
	if((ret = fstat(fd, &elf_info)) < 0)
			exit_err("fstat error", 1);

	if((mapped_elf = mmap(NULL, elf_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_err("Failed to map file to memory", 42);

	check_elf_validity(mapped_elf);

	//elf_header = (Elf64_Ehdr*)mapped_elf;

	//elf_section_hdrs = (Elf64_Shdr*)(mapped_elf + elf_header->e_shoff);

	munmap(mapped_elf, elf_info.st_size);
	close(fd);
}
