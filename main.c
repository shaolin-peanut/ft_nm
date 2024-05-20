# include "include/ft_nm.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		ret;
	struct stat	elf_info;
	char		*mapped_elf;
	unsigned char* elf_ident;
	t_info	*info;
	info = (t_info *) malloc(sizeof(t_info) * 1);
	info->m_elf = 0;
	info->sym_tab = 0;
	info->str_tab = 0;
	info->is32 = false;
	info->type = 0;
	info->output_tab = 0;

	if (argc < 2)
		exit_err("no binary file found", 1);
	printf("%s\n", argv[1]);

	if((fd = open(argv[1], O_RDWR)) < 0)
		exit_err("Failed to open file", 1);
	
	if((ret = fstat(fd, &elf_info)) < 0)
		exit_err("fstat error", 1);

	if((mapped_elf = mmap(NULL, elf_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_err("Failed to map file to memory", 42);

	if (check_elf_validity(mapped_elf) == false) {
		printf("mapped elf: %2x%c%c%c", mapped_elf[0], mapped_elf[1], mapped_elf[2], mapped_elf[3]);
		exit_err("Invalid binary file", 8080);
	}

	info->m_elf = mapped_elf;
	elf_ident = (unsigned char*)mapped_elf;
	if(elf_ident[EI_CLASS] == ELFCLASS32)
		info->is32 = true;
	else
		info->is32 = false;

	parse_elf(info);

	munmap(mapped_elf, elf_info.st_size);
	free(info);
	close(fd);
}
