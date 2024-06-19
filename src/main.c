# include "../include/ft_nm.h"

t_data	info;

// returns file size
int	elf_setup(char	*path)
{
	struct stat		elf_info;
	int				ret;
	int				fd;

	ft_bzero(&info, sizeof(t_data));
	if((fd = open(path, O_RDONLY)) < 0)
		return (err(": No such file", path));
	
	if((ret = fstat(fd, &elf_info)) < 0)
		return (err("fstat error", 0));

	info.elf_size = elf_info.st_size;

	if((info.m_elf = mmap(NULL, elf_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (err("Failed to map file to memory", 0));

	if (check_elf_validity(info.m_elf) == false)
		return (err("Invalid binary file", 0));

	info.is32 = (info.m_elf[EI_CLASS] == ELFCLASS32);
	info.path = path;

	return (fd);
}

bool	init_32()
{
	if (!info.is32)
		return false;

	Elf32_Ehdr	*elf_header = (Elf32_Ehdr *) info.m_elf;
	Elf32_Shdr	*section_headers = (Elf32_Shdr *)ptr_add(info.m_elf, elf_header->e_shoff);
	Elf32_Shdr	*section_header = 0;
	Elf32_Shdr	*shstrab_sh;

	if (!elf_header || !section_headers)
		return false;

	if (elf_header->e_type != ET_REL && elf_header->e_type != ET_EXEC && elf_header->e_type != ET_DYN)
		return (err("Invalid file type", 0));
	 if (!(shstrab_sh = (Elf32_Shdr *) &section_headers[elf_header->e_shstrndx]))
		return false;
	if (!(info.sh_str_tab = (void *)ptr_add(info.m_elf, shstrab_sh->sh_offset)))
		return false;

	for (int i = 0; i < elf_header->e_shnum; i++) {
		if (info.sh_str_tab && info.sym_str_tab)
			break;
		section_header = &section_headers[i];
		char	*section_name = (char *)ptr_add(info.sh_str_tab, section_header->sh_name);

		if (section_header->sh_type == SHT_SYMTAB) {
			info.sym_tab = (void *)ptr_add(info.m_elf, section_header->sh_offset);
			info.symsize = section_header->sh_entsize;
			info.symcount = (int) section_header->sh_size / info.symsize;
		}
		if (ft_strncmp(".strtab", section_name, 7) == 0)
			info.sym_str_tab = (void *)ptr_add(info.m_elf, section_header->sh_offset);
	}
	return true;
}

// get the string tables and symbol metadata + pointers
bool	init_64()
{
	if (info.is32)
		return false;

	Elf64_Ehdr	*elf_header = (Elf64_Ehdr *) info.m_elf;
	Elf64_Shdr	*section_headers = (Elf64_Shdr *)ptr_add(info.m_elf, elf_header->e_shoff);
	Elf64_Shdr	*section_header = 0;
	Elf64_Shdr	*shstrab_sh;

	if (!elf_header || !section_headers)
		return false;

	if (elf_header->e_type != ET_REL && elf_header->e_type != ET_EXEC && elf_header->e_type != ET_DYN)
		return (err("Invalid file type", 0));
	 if (!(shstrab_sh = (Elf64_Shdr *) &section_headers[elf_header->e_shstrndx]))
		return false;
	if (!(info.sh_str_tab = (void *)ptr_add(info.m_elf, shstrab_sh->sh_offset)))
		return false;

	for (int i = 0; i < elf_header->e_shnum; i++) {
		if (info.sh_str_tab && info.sym_str_tab)
			break;
		section_header = &section_headers[i];
		char	*section_name = (char *)ptr_add(info.sh_str_tab, section_header->sh_name);

		if (section_header->sh_type == SHT_SYMTAB) {
			info.sym_tab = (void *)ptr_add(info.m_elf, section_header->sh_offset);
			info.symsize = section_header->sh_entsize;
			info.symcount = (int) section_header->sh_size / info.symsize;
		}
		if (ft_strncmp(".strtab", section_name, 7) == 0)
			info.sym_str_tab = (void *)ptr_add(info.m_elf, section_header->sh_offset);
	}
	return true;
}

void	nm(char *path, int i)
{
	int	fd;

	if ((fd = elf_setup(path)) < 1)
		return ;

	if (init_32() == false && init_64() == false)
		return ;

	if (i > 2)
		ft_printf("\n%s:\n", path);
	
	process_symbols();

	munmap(info.m_elf, info.elf_size);
	ft_bzero(&info, sizeof(t_data));
	close(fd);
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
