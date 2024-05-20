#ifndef _GNU_SOURCE
#define _GNU_SOURCE

#include "include/ftnm.h"

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

		elf_header = (Elf64_Ehdr *) info->m_elf;
		elf_section_hdrs = (Elf64_Shdr *)((char *)info->m_elf + elf_header->e_shoff);

		printf("Section Headers:\n");
		printf(" [Nr] Name (Type)       Addr         Off       Size   ESz   Flg Link  Info\n");

		// find string table section
		strtab_sh = (Elf64_Shdr)(elf_section_hdrs[elf_header->e_shstrndx]);
		// get string table offset, put in t_info
		info->str_tab = (void *) info->m_elf + strtab_sh.sh_offset;

		// find symtab
		for (int i = 0; i < elf_header->e_shnum; i++){
			elf_section_hdr = &elf_section_hdrs[i];

			if (
				(elf_section_hdr->sh_type == SHT_SYMTAB
				|| elf_section_hdr->sh_type == SHT_DYNSYM)
				&& elf_section_hdr->sh_link != 0)
			{
				info->sym_tab = (void *) info->m_elf + elf_section_hdr->sh_offset;
				char* sh_name_str = (char*)(info->str_tab + elf_section_hdr->sh_name);

				printf(" %-16s (%2x) %016lx %08lx %08lx %4x %4x %4x %4x\n",
					sh_name_str, elf_section_hdr->sh_type,
					elf_section_hdr->sh_addr, elf_section_hdr->sh_offset,
					elf_section_hdr->sh_size, elf_section_hdr->sh_entsize,
					elf_section_hdr->sh_flags, elf_section_hdr->sh_link,
					elf_section_hdr->sh_info);
				break;
			}
		}
		int symcount = elf_section_hdr->sh_size / elf_section_hdr->sh_entsize;
		Elf64_Sym	*symbol = NULL;
		for (int i = 0; i < symcount; i++)
		{
			// if ((i * elf_section_hdr->sh_entsize) >= elf_section_hdr->sh_size)
			// 	break;
			symbol = (Elf64_Sym *)((char *)info->sym_tab + (i * elf_section_hdr->sh_entsize));
			if (symbol->st_name != 0) {
				char	*sym_name = (char *)(info->str_tab + symbol->st_name);
				printf("Found symbol: %s\n", sym_name);
			}
		}
		// looop through symbol table. TODO: get number of symbols or other iterator from symtab section header
		// - cast into Elf64_Sym. Use that to print symbol name using strtab, and then categorize/build output table
			// 		typedef struct {
			// Elf32_Word st_name;
			// Elf32_Addr st_value;
			// Elf32_Word st_size;
			// unsigned char st_info;
			// unsigned char st_other;
			// Elf32_Half st_shndx;
			// } Elf32_Sym;
	}
}

#endif