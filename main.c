# include "include/ft_nm.h"

void	init_info(t_info	*info, int size)
{
	info->m_elf = 0;
	info->elf_size = size;
	info->sym_tab = 0;
	info->symsize = 0;
	info->symcount = 0;
	info->sh_str_tab = 0;
	info->sym_str_tab = 0;
	info->is32 = false;
	info->type = 0;
}

// returns file size
int	elf_setup(int argc, char **argv, int *fd, t_info *info)
{
	struct stat		elf_info;
	int				ret;

	if (argc < 2)
		exit_err("no binary file found", 1);

	if((*fd = open(argv[1], O_RDWR)) < 0)
		exit_err("Failed to open file", 1);
	
	if((ret = fstat(*fd, &elf_info)) < 0)
		exit_err("fstat error", 1);

	if((info->m_elf = mmap(NULL, elf_info.st_size, PROT_READ, MAP_PRIVATE, *fd, 0)) == MAP_FAILED)
		exit_err("Failed to map file to memory", 42);

	if (check_elf_validity(info->m_elf) == false) {
		exit_err("Invalid binary file", 8080);
	}
	return (elf_info.st_size);
}

// get the string tables and symbol metadata + pointers
int	init_64(t_info	*info)
{
	Elf64_Ehdr	*elf_header = (Elf64_Ehdr *) info->m_elf;
		Elf64_Shdr	*elf_section_hdrs = (Elf64_Shdr *)((char *)info->m_elf + elf_header->e_shoff);
		Elf64_Shdr	*elf_section_hdr = 0;

		Elf64_Shdr	shstrab_sh;
		Elf64_Shdr	symstrab_sh;
		info->type = elf_header->e_type;

		if (!(info->type == ET_REL || info->type == ET_EXEC || info->type == ET_DYN))
			exit_err("Invalid file type", 42);
		shstrab_sh = (Elf64_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
		info->sh_str_tab = (void *) info->m_elf + shstrab_sh.sh_offset;

		for (int i = 0; i < elf_header->e_shnum; i++) {
			if (info->sh_str_tab && info->sym_str_tab)
				break;
			elf_section_hdr = &elf_section_hdrs[i];
			char	*section_name = (char *)(info->sh_str_tab + elf_section_hdr->sh_name);

			if (elf_section_hdr->sh_type == SHT_SYMTAB) {
				info->sym_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
				info->symsize = elf_section_hdr->sh_entsize;
				info->symcount = (int) elf_section_hdr->sh_size / info->symsize;
			}
			if (strncmp(".strtab", section_name, 7) == 0)
				info->sym_str_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
		}
}

int	main(int argc, char **argv)
{
	int				fd = 0;
	int				elf_size = 0;
	char			*mapped_elf;
	t_info			info_struct;
	t_info			*info = &info_struct;

	init_info(info, elf_size);

	elf_size = elf_setup(argc, argv, &fd, info);
	info->is32 = (info->m_elf[EI_CLASS] == ELFCLASS32);

	if (info->is32) {
		// todo
	}
	else {
		init_64(info);

		process_symbols(info);
	}

	free_all(info);
	close(fd);
	return (0);
}
