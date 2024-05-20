#include "include/ft_nm.h"

char    *get_sym_name_ptr(t_einfo *info, int i)
{
    if (info->is32) {
        Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
        return ((char *)(info->sym_str_tab + sym->st_name));
    } else {
        Elf64_Sym   *sym = (Elf64_Sym *) (info->sym_tab + (i * info->symsize));
        return ((char *)(info->sym_str_tab + sym->st_name));
    }
}

uint64_t    get_value(t_einfo *info, int i)
{
    if (info->is32) {
        Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
        return ((uint64_t)(sym->st_value));
    } else {
        Elf64_Sym   *sym = (Elf64_Sym *) (info->sym_tab + (i * info->symsize));
        return ((uint64_t)(sym->st_value));
    }
}

char    get_type32(t_einfo   *info, int i)
{
    Elf32_Ehdr      *elf_header = (Elf32_Ehdr *) info->m_elf;
    Elf32_Sym       *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
    Elf32_Shdr      *section_headers = NULL;
    Elf32_Shdr      section;
    Elf32_Word      sh_type = 0;
    Elf32_Xword     sh_flags = 0;

    bool            index_too_big = (sym->st_shndx >= (elf_header->e_shnum));
    bool            undef = (sym->st_shndx == SHN_UNDEF);
    bool            intel_small = false;
    bool            local = false;

    if (!index_too_big || undef) {
        section_headers = (Elf32_Shdr *)(info->m_elf + elf_header->e_shoff);
        section = section_headers[sym->st_shndx];
        sh_type = section.sh_type;
        sh_flags = section.sh_flags;
        intel_small = sh_flags & SHF_IA_64_SHORT;
    }
    Elf32_Word  binding = ELF32_ST_BIND (sym->st_info);
    Elf32_Word  type = ELF32_ST_TYPE (sym->st_info);

    local = binding == STB_LOCAL;

    // char    *n = sym->section_name;
    if (sym->st_shndx == SHN_ABS) {
        return type == STT_FILE ? 'F' : 'A';
    }
	if (binding == STB_WEAK)
        return (undef ? 'w' : 'W');
	if (undef && (type == STT_NOTYPE || type == STT_FUNC))
        return ('U');
    if (type == STT_COMMON || (type == STT_OBJECT && sym->st_shndx == SHN_COMMON))
        return ('C');
    if ((type == STT_OBJECT || type == STT_NOTYPE) && (section.sh_flags & SHF_ALLOC)) {
        if (sh_type == SHT_NOBITS) // it's in the bss section, or sbss if small
			return intel_small ? (local? 's':'S'):(local? 'b':'B');
        else if (section.sh_flags & SHF_WRITE) // not in bss, so it's initialized data section (g for small, d for regular)
            return intel_small ? (local? 'g' : 'G') : (local? 'd' : 'D');
        return local? 'r' : 'R'; // RO (const) data section if it fits all these but not writeable
    }
    if (type == STT_FUNC && section.sh_flags & SHF_EXECINSTR)
        return (local ? 't' : 'T');
    if (type == STT_SECTION)
        return ('X');
    if (type == STT_TLS)
        return ('T');
     
    if (type == STT_GNU_IFUNC)
        return ('i');
    return ('?');
}

char    get_type64(t_einfo  *info, int  i)
{
    Elf64_Ehdr      *elf_header = (Elf64_Ehdr *) info->m_elf;
    Elf64_Sym       *sym = (Elf64_Sym *) (info->sym_tab + (i * info->symsize));
    Elf64_Shdr      *section_headers = NULL;
    Elf64_Shdr      section;
    Elf64_Word      sh_type = 0;
    Elf64_Xword     sh_flags = 0;

    bool            index_too_big = (sym->st_shndx >= (elf_header->e_shnum));
    bool            undef = (sym->st_shndx == SHN_UNDEF);
    bool            intel_small = false;
    bool            local = false;

    if (!index_too_big || undef) {
        section_headers = (Elf64_Shdr *)(info->m_elf + elf_header->e_shoff);
        section = section_headers[sym->st_shndx];
        sh_type = section.sh_type;
        sh_flags = section.sh_flags;
        intel_small = sh_flags & SHF_IA_64_SHORT;
    }
    Elf64_Word  binding = ELF64_ST_BIND (sym->st_info);
    Elf64_Word  type = ELF64_ST_TYPE (sym->st_info);

    local = binding == STB_LOCAL;

    if (sym->st_shndx == SHN_ABS) {
        return type == STT_FILE ? 'F' : 'A'; }
	if (binding == STB_WEAK)
        return (undef ? 'w' : 'W');
	if (undef && (type == STT_NOTYPE || type == STT_FUNC))
        return ('U');
    if (type == STT_COMMON || (type == STT_OBJECT && sym->st_shndx == SHN_COMMON))
        return ('C');
    if ((type == STT_OBJECT || type == STT_NOTYPE) && (section.sh_flags & SHF_ALLOC)) {
        if (sh_type == SHT_NOBITS) // it's in the bss section, or sbss if small
			return intel_small ? (local? 's':'S'):(local? 'b':'B');
        else if (section.sh_flags & SHF_WRITE) // not in bss, so it's initialized data section (g for small, d for regular)
            return intel_small ? (local? 'g' : 'G') : (local? 'd' : 'D');
        return local? 'r' : 'R'; // RO (const) data section if it fits all these but not writeable
    }
    if (type == STT_FUNC && section.sh_flags & SHF_EXECINSTR)
        return (local ? 't' : 'T');
    if (type == STT_SECTION)
        return ('X');
    if (type == STT_TLS)
        return ('T');
     
    if (type == STT_GNU_IFUNC)
        return ('i');
    return ('?');
}

void    init_output_tab(t_row *tab, int count)
{
    for (int i = 0; i < count; i++)
    {
        tab[i].value = 0;
        tab[i].type = 0;
        tab[i].print = false;
        tab[i].name = 0;
    }
}

bool    filter_out(char type, char *name) {
    return (strlen(name) == 0 || type == 'F' || type == 'X');
}

void    fill_tab(t_row *output_tab, t_einfo *info, int count)
{
    init_output_tab(output_tab, count);
    int symtab_index = 0;
    int out_i = 0;

    while (symtab_index < info->symcount)
    {
        char    type = info->is32 ? get_type32(info, symtab_index) : get_type64(info, symtab_index);
        if (!filter_out(type, get_sym_name_ptr(info, symtab_index))) {
            output_tab[out_i].value = get_value(info, symtab_index);
            output_tab[out_i].type = type;
            output_tab[out_i].name = get_sym_name_ptr(info, symtab_index);
            out_i++;
        }
        symtab_index++;
    }
}

int tablen(t_row *tab)
{
    int i = 0;
    while (tab[i].name)
        i++;
    return i;
}

int    count_symbols(t_einfo *info)
{
    int symtab_index = 0;
    int out_i = 0;

    while (symtab_index < info->symcount)
    {
        char    type = info->is32 ? get_type32(info, symtab_index) : get_type64(info, symtab_index);
        if (!filter_out(type, get_sym_name_ptr(info, symtab_index))) {
            out_i++;
        }
        symtab_index++;
    }
    return out_i;
}

void    print_symbols(t_row *tab, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (tab[i].value || tab[i].type == 'T') {
            int len = ft_nbrlen_base(tab[i].value, 16); // get the length of the hex value
            for (int j = 16 - len; j > 0; j--)
                ft_printf("0");
            ft_printf("%x ", tab[i].value);
        }
        else {
            ft_printf("                 "); 
        }
	    ft_printf("%c ", tab[i].type);
        if (tab[i].name)
            ft_printf("%s\n", tab[i].name);
    }
}

void    process_symbols(t_einfo  *info)
{
    int symc = count_symbols(info);
    t_row   output_tab[symc];

    fill_tab(output_tab, info, symc);
    
    sort(output_tab, 0, symc - 1);

    print_symbols(output_tab, symc);
}
