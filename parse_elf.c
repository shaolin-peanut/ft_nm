#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include "include/ft_nm.h"

void	parse_elf(t_info	*info)
{
	if (info->is32) {
		// Elf32_Ehdr	*elf_header;
		// Elf32_Shdr	**elf_section_hdrs;
		// Elf32_Shdr	*elf_section_hdr;
		int			off;
		int			size;
		off = 0;
		size = 0;

		// // set up pointers elf header, section headers and get the section headers total size
		// elf_header = (Elf32_Ehdr *)info->m_elf;
		// elf_section_hdrs = (Elf32_Shdr **)(info->m_elf + elf_header->e_shoff);
		// size = elf_header->e_shentsize * elf_header->e_shnum;

		// // Loop through sections to find the symbol table
		// for (off = elf_header->e_shoff; off < size; off += elf_header->e_shentsize)
		// {
		// 	elf_section_hdr = (Elf32_Shdr *) info->m_elf + off;
		// 	if (elf_section_hdr->sh_type == SHT_SYMTAB || elf_section_hdr->sh_type == SHT_DYNSYM)
		// 		printf("found sym tab");
		// }
	} else {
		// headers
		Elf64_Ehdr	*elf_header = NULL;
		Elf64_Shdr	*elf_section_hdrs = NULL;
		Elf64_Shdr	*elf_section_hdr = NULL;

		// string tables
		Elf64_Shdr	shstrtab_sh;
		Elf64_Shdr	symstrtab_sh;

		// symbol infos
		int			symsize;
		int			symcount;

		elf_header = (Elf64_Ehdr *) info->m_elf;
		elf_section_hdrs = (Elf64_Shdr *)((char *)info->m_elf + elf_header->e_shoff);

		info->type = elf_header->e_type;
		// is it relocatable (obj), executable or shared object file (dyn)?
		if (!(info->type == ET_REL || info->type == ET_EXEC || info->type == ET_DYN))
			exit_err("Invalid file type", 42);
		printf("This is a %s file\n",
				(info->type == ET_REL ? "relocatable" : "executable"));

		printf("Section Headers:\n");
		printf(" [Nr] Name (Type)       Addr         Off       Size   ESz   Flg Link  Info\n");


		// get string table headers for section header names and symbols
		shstrtab_sh = (Elf64_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
		info->sh_str_tab = (void *) info->m_elf + shstrtab_sh.sh_offset;

		// find symbols string table section header

		// find symtab and string table
		for (int i = 0; i < elf_header->e_shnum; i++){
			if (info->sh_str_tab && info->sym_str_tab)
				break; // to stop looping when we've got them

			elf_section_hdr = &elf_section_hdrs[i];
			char* sh_name_str = (char*)(info->sh_str_tab + elf_section_hdr->sh_name);

			// TODO: refactor the code below to have thinner conditions, simpler logic

			// get symbol table
			if ((info->type == ET_REL && elf_section_hdr->sh_type == SHT_SYMTAB)
				|| (info->type == ET_DYN && elf_section_hdr->sh_type == SHT_DYNSYM))
			{
				info->sym_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
				symsize = elf_section_hdr->sh_entsize;
				symcount = elf_section_hdr->sh_size / symsize;
			} // and get string table (dynstr for dynsym, or strtab for )
			else if ((strncmp(".strtab", sh_name_str, 7) == 0  && info->type == ET_REL)
						|| (strncmp(".dynstr", sh_name_str, 7) == 0 && info->type != ET_REL))
			{
				info->sym_str_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
				printf("found %s\n", sh_name_str);
			}
		}
		process_symbols(symsize, symcount, info);
	}
}

// char* sh_name_str = (char*)(info->str_tab + elf_section_hdr->sh_name);

// printf(" %-16s (%2x) %016lx %08lx %08lx %4lx %4lx %4x %4x\n",<
// 	sh_name_str, elf_section_hdr->sh_type,
// 	elf_section_hdr->sh_addr, elf_section_hdr->sh_offset,
// 	elf_section_hdr->sh_size, elf_section_hdr->sh_entsize,
// 	elf_section_hdr->sh_flags, elf_section_hdr->sh_link,
// 	elf_section_hdr->sh_info);
#endif