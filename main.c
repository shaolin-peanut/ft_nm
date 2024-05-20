#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <elf.h>

#include "include/ftnm.h"

#include <stdio.h>
void	parse_elf(t_info	*info)
{
	if (info->is32) {
		Elf32_Ehdr	*elf_header;
		Elf32_Shdr	**elf_section_hdrs;
		Elf32_Shdr	*elf_section_hdr;
		int			off;
		int			size;

		// set up pointers elf header, section headers and get the section headers total size
		elf_header = (Elf32_Ehdr *)info->m_elf;
		elf_section_hdrs = (Elf32_Shdr **)(info->m_elf + elf_header->e_shoff);
		size = elf_header->e_shentsize * elf_header->e_shnum;

		// Loop through sections to find the symbol table
		for (off = elf_header->e_shoff; off < size; off += elf_header->e_shentsize)
		{
			elf_section_hdr = (Elf32_Shdr *) info->m_elf + off;
			if (elf_section_hdr->sh_type == SHT_SYMTAB || elf_section_hdr->sh_type == SHT_DYNSYM)
				printf("found sym tab");
		}
	} else {
		Elf64_Ehdr	*elf_header = NULL;
		Elf64_Shdr	*elf_section_hdrs = NULL;
		Elf64_Shdr	*elf_section_hdr = NULL;
		Elf64_Shdr	strtab_sh;
		void		*strtab_ptr = NULL;

		elf_header = (Elf64_Ehdr *)info->m_elf;
		elf_section_hdrs = (Elf64_Shdr *)((char *)info->m_elf + elf_header->e_shoff);

		printf("Section Headers:\n");
		printf(" [Nr] Name (Type)       Addr         Off       Size   ESz   Flg Link  Info\n");

        // 
		strtab_sh = (Elf64_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
		info->str_tab = (void *) info->m_elf + strtab_sh.sh_offset;
		strtab_ptr = info->str_tab;

		// find symtab
		for (int i = 0; i < elf_header->e_shnum; i++){
			// printf(" [%2d]", i);
			elf_section_hdr = &elf_section_hdrs[i];

			if (elf_section_hdr->sh_type == SHT_SYMTAB || elf_section_hdr->sh_type == SHT_DYNSYM)
			{
				char* sh_name_str = ((char*)strtab_ptr + elf_section_hdr->sh_name);

				printf(" %-16s (%2x) %016lx %08lx %08lx %4x %4x %4x %4x\n",
					sh_name_str, elf_section_hdr->sh_type,
					elf_section_hdr->sh_addr, elf_section_hdr->sh_offset,
					elf_section_hdr->sh_size, elf_section_hdr->sh_entsize,
					elf_section_hdr->sh_flags, elf_section_hdr->sh_link,
					elf_section_hdr->sh_info);
			}
		}
	}
}

void	exit_err(char *msg, int exit_code)
{
	printf("nm: %s\n", msg);
	exit(exit_code);
}

void	check_elf_validity(char	*mapped_elf)
{
	if (!(mapped_elf[0] == ELFMAG0
		&& mapped_elf[1] == 'E'
		&& mapped_elf[2] == 'L'
		&& mapped_elf[3] == 'F'))
		exit_err("Invalid binary file", 1);
}

// init info struct 

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
	info->str_tab = 0;
	info->is32 = false;

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
