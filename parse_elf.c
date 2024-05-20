#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include "include/ft_nm.h"

void	print_symbols(t_info	*info)
{
	printf(" name                                    | value            | size     | type     | bind | visi | section name|\n");
	printf("------------------------------------------------------------------------------------------------------------------|\n");
	for (int i = 0; i < info->symcount; i++)
	{
		t_symbol	*sym = &info->my_symbols[i];
		printf("%-40s | %16lx | %8lx | %8lx | %4x | %4x | %s\n",
					sym->name,
					sym->value,
					sym->size,
					sym->type,
					sym->binding,
					sym->visibility,
					sym->section_name);
	}
}

void	parse_symbols(t_info	*info)
{
	if (info->is32) {
		//do stuff;
		printf("we're 32!!\n");
	} else {
		Elf64_Ehdr  *elf_header = (Elf64_Ehdr *) info->m_elf;
		Elf64_Shdr	*elf_section_hdrs = (Elf64_Shdr *)((char *)info->m_elf + elf_header->e_shoff);
		Elf64_Shdr	*section = NULL;
		Elf64_Sym	*symbol = 0;
		t_symbol	*mysym = 0;

		info->my_symbols = (t_symbol *) malloc(sizeof(t_symbol) * info->symcount);

		for (int i = 0; i < info->symcount; i++)
		{
			symbol = (Elf64_Sym *)((char *)info->sym_tab + (i * info->symsize));
			mysym = &info->my_symbols[i];

			mysym->name = symbol->st_name ? (char *)(info->sym_str_tab + symbol->st_name) : NULL;
			mysym->value = (long unsigned int) symbol->st_value;
			mysym->size = (long unsigned int) symbol->st_size;
			mysym->type = ELF64_ST_TYPE (symbol->st_info);
			mysym->binding = ELF64_ST_BIND (symbol->st_info);
			mysym->visibility = ELF64_ST_VISIBILITY (symbol->st_other);

			mysym->section = 0;
			mysym->section_name = 0;
			mysym->section_flags = 0;
			mysym->small = false;

			if (symbol->st_shndx != SHN_UNDEF && symbol->st_shndx < elf_header->e_shnum)
			{
				mysym->section = symbol->st_shndx == SHN_ABS ? SHN_ABS : (void *) &elf_section_hdrs[symbol->st_shndx];

				Elf64_Shdr *section = (Elf64_Shdr *) mysym->section;
				char *section_name = (char *)(info->sh_str_tab + section->sh_name);
				mysym->section_name = strlen(section_name) > 0 ? section_name : NULL;
				mysym->section_flags = section->sh_flags;
				if (section->sh_flags & SHF_IA_64_SHORT)
					mysym->small = true;
			} else {
				mysym->section = SHN_UNDEF;
			}
		
			section = 0;
		}
	}
}

void	parse_elf(t_info	*info)
{
	if (info->is32) {
		// todo
	} else {
		// headers
		Elf64_Ehdr	*elf_header = NULL;
		Elf64_Shdr	*elf_section_hdrs = NULL;
		Elf64_Shdr	*elf_section_hdr = NULL;
		// string tables
		Elf64_Shdr	shstrtab_sh;
		Elf64_Shdr	symstrtab_sh;

		elf_header = (Elf64_Ehdr *) info->m_elf;
		elf_section_hdrs = (Elf64_Shdr *)((char *)info->m_elf + elf_header->e_shoff);
		info->type = elf_header->e_type;

		if (!(info->type == ET_REL || info->type == ET_EXEC || info->type == ET_DYN))
			exit_err("Invalid file type", 42);

		// get string table headers for section header names and symbols
		shstrtab_sh = (Elf64_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
		info->sh_str_tab = (void *) info->m_elf + shstrtab_sh.sh_offset;

		// find symtab and string table
		for (int i = 0; i < elf_header->e_shnum; i++){
			if (info->sh_str_tab && info->sym_str_tab)
				break;

			elf_section_hdr = &elf_section_hdrs[i];
			char* sh_name_str = (char*)(info->sh_str_tab + elf_section_hdr->sh_name);

			if (elf_section_hdr->sh_type == SHT_SYMTAB) {
				info->sym_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
				info->symsize = elf_section_hdr->sh_entsize;
				info->symcount = (int) elf_section_hdr->sh_size / info->symsize;
			}
			if (strncmp(".strtab", sh_name_str, 7) == 0)
				info->sym_str_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
		}
	}
	parse_symbols(info);
}

#endif