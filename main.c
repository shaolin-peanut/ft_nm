# include "include/ft_nm.h"

t_data	info;

// void	init_info() {
// 	info = 
// 	{
// 		.m_elf = 0,
// 		.elf_size = 0,
// 		.sym_tab = 0,
// 		.symsize = 0,
// 		.symcount = 0,
// 		.sh_str_tab = 0,
// 		.sym_str_tab = 0,
// 		.is32 = false,
// 		.type = 0,
// 		.symbols = 0,
// 		.output_tab = 0
// 	}
// }

// returns file size
int	elf_setup(char	*path)
{
	struct stat		elf_info;
	int				ret;
	int				fd;

	if((fd = open(path, O_RDWR)) < 0) {
		exit_err(": No such file", path, 0);
		// ft_putstr_fd("\n", 1);
		ft_putchar_fd('\n', 1);
		return (-1);
	}
	// should be like printf("%s: No such file\n", path) but need to change function
	
	if((ret = fstat(fd, &elf_info)) < 0)
		exit_err("fstat error", 0, 1);

	info.elf_size = elf_info.st_size;

	if((info.m_elf = mmap(NULL, elf_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_err("Failed to map file to memory", 0, 42);

	if (check_elf_validity(info.m_elf) == false) {
		exit_err("Invalid binary file", 0, 8080);
	}

	info.is32 = (info.m_elf[EI_CLASS] == ELFCLASS32);

	return (fd);
}

void	init_32()
{
	Elf32_Ehdr	*elf_header = (Elf32_Ehdr *) info.m_elf;
	Elf32_Shdr	*elf_section_hdrs = (Elf32_Shdr *)((char *)info.m_elf + elf_header->e_shoff);
	Elf32_Shdr	*elf_section_hdr = 0;

	Elf32_Shdr	shstrab_sh;
	info.type = elf_header->e_type;

	if (!(info.type == ET_REL || info.type == ET_EXEC || info.type == ET_DYN))
		exit_err("Invalid file type", 0, 42);
	shstrab_sh = (Elf32_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
	info.sh_str_tab = (void *) info.m_elf + shstrab_sh.sh_offset;

	for (int i = 0; i < elf_header->e_shnum; i++) {
		if (info.sh_str_tab && info.sym_str_tab)
			break;
		elf_section_hdr = &elf_section_hdrs[i];
		char	*section_name = (char *)(info.sh_str_tab + elf_section_hdr->sh_name);

		if (elf_section_hdr->sh_type == SHT_SYMTAB) {
			info.sym_tab = (void *) info.m_elf + elf_section_hdr->sh_offset;
			info.symsize = elf_section_hdr->sh_entsize;
			info.symcount = (int) elf_section_hdr->sh_size / info.symsize;
		}
		if (ft_strncmp(".strtab", section_name, 7) == 0)
			info.sym_str_tab = (void *) info.m_elf + elf_section_hdr->sh_offset;
	}
}

// get the string tables and symbol metadata + pointers
void	init_64()
{
	Elf64_Ehdr	*elf_header = (Elf64_Ehdr *) info.m_elf;
	Elf64_Shdr	*elf_section_hdrs = (Elf64_Shdr *)ptr_add(info.m_elf, elf_header->e_shoff);
	// Elf64_Shdr	*elf_section_hdrs = (Elf64_Shdr *)((char *)info.m_elf + elf_header->e_shoff);
	Elf64_Shdr	*elf_section_hdr = 0;

	Elf64_Shdr	shstrab_sh;
	info.type = elf_header->e_type;

	if (!(info.type == ET_REL || info.type == ET_EXEC || info.type == ET_DYN))
		exit_err("Invalid file type", 0, 42);
	shstrab_sh = (Elf64_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
	info.sh_str_tab = (void *) info.m_elf + shstrab_sh.sh_offset;

	for (int i = 0; i < elf_header->e_shnum; i++) {
		if (info.sh_str_tab && info.sym_str_tab)
			break;
		elf_section_hdr = &elf_section_hdrs[i];
		char	*section_name = (char *)(info.sh_str_tab + elf_section_hdr->sh_name);

		if (elf_section_hdr->sh_type == SHT_SYMTAB) {
			info.sym_tab = (void *) info.m_elf + elf_section_hdr->sh_offset;
			info.symsize = elf_section_hdr->sh_entsize;
			info.symcount = (int) elf_section_hdr->sh_size / info.symsize;
		}
		if (ft_strncmp(".strtab", section_name, 7) == 0)
			info.sym_str_tab = (void *) info.m_elf + elf_section_hdr->sh_offset;
	}
}

void	nm(char *path, int i)
{
	int	fd;

	// init_info();

	if ((fd = elf_setup(path)) < 0)
		return ;
	if (i > 2)
		ft_printf("\n%s:\n", path);

	info.is32 ? init_32() : init_64();
	
	process_symbols();

	munmap(info.m_elf, info.elf_size);
	close(fd);
	ft_bzero(&info, sizeof(t_data));
}

int	main(int argc, char **argv)
{
	if (argc == 1) {
			nm("a.out", argc);
	} else if (argc > 1) {
		for (int i = 1; i < argc; i++)
			nm(argv[i], argc);
	}
	return (0);
}
