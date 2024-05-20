#include "include/ft_nm.h"

char    *get_sym_name_ptr(t_info *info, int i)
{
    if (info->is32) {
        Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
        return ((char *)(info->sym_str_tab + sym->st_name));
    } else {
        Elf64_Sym   *sym = (Elf64_Sym *) (info->sym_tab + (i * info->symsize));
        return ((char *)(info->sym_str_tab + sym->st_name));
    }
}

void    *get_value(t_info *info, int i)
{
    if (info->is32) {
        Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
        return ((void *)((Elf32_Addr)(sym->st_value)));
    } else {
        Elf64_Sym   *sym = (Elf64_Sym *) (info->sym_tab + (i * info->symsize));
        return ((void *)((Elf64_Addr)(sym->st_value)));
    }
}

char    get_type32(t_info   *info, int i)
{
    Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
    bool        undef = sym->st_shndx == SHN_UNDEF;
    bool        local;
    // set up a var for type, section flags, and binding, with proper elf.h format
    // Elf32_Shdr  *section = (Elf32_Shdr *) sym->st_shndx;
    // Elf32_Shdr  *section_name = (char *)(info->sh_str_tab + section->sh_name);
    // double check with man elf to make sure these types are the right ones
    // Elf32_Word  section_flags = section->sh_flags;
    Elf32_Word  binding = ELF32_ST_BIND (sym->st_info);
    Elf32_Word  type = ELF32_ST_TYPE (sym->st_info);

    // char    *n = sym->section_name;
    if (sym->st_shndx == SHN_ABS)
        return ('A');
    // W is good, w was applied to one of 4 expected matches
    if (binding == STB_WEAK) // W is good, w was applied to one of 4 expected matches
        return (undef ? 'w' : 'W');
    if (type == STT_COMMON || (type && sym->st_shndx == SHN_COMMON))
        return ('C');
    if (binding == STT_SECTION)
        return ('S');
    if (type == STT_FILE)
        return ('F');
    if (type == STT_TLS)
        return ('T');
    if (type == STT_NOTYPE) {
        if (sym->st_shndx == SHN_UNDEF)
            return ('S');
    }
    if (type == STT_GNU_IFUNC)
        return ('i');

}

char    get_type64(t_info  *info, int  i)
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

    char            *n = 0;

    if (!index_too_big || undef) {
        section_headers = (Elf64_Shdr *)(info->m_elf + elf_header->e_shoff);
        section = section_headers[sym->st_shndx];
        sh_type = section.sh_type;
        sh_flags = section.sh_flags;
        intel_small = sh_flags & SHF_IA_64_SHORT;
        n = (char *)(info->sh_str_tab + section.sh_name);
    }
    Elf64_Word  binding = ELF64_ST_BIND (sym->st_info);
    Elf64_Word  type = ELF64_ST_TYPE (sym->st_info);

    local = binding == STB_LOCAL;

    // char    *n = sym->section_name;
    if (sym->st_shndx == SHN_ABS)
        return type == STT_FILE ? 'F' : 'A';
    // W is good, w was applied to one of 4 expected matches
    if (binding == STB_WEAK)
        return (undef ? 'w' : 'W');
    if (type == STT_COMMON || (type == STT_OBJECT && sym->st_shndx == SHN_COMMON))
        return ('C');
    //  
    if ((type == STT_OBJECT || type == STT_NOTYPE) && (section.sh_flags & SHF_ALLOC)) {
        if (sh_type == SHT_NOBITS) // it's in the bss section, or sbss if small
        {
            // if (strncmp(n, ".sbss", 5) == 0)
            if (intel_small) // small bss a.k.a sbss
                return (local ? 's' : 'S');
            else // bss
                return (local ? 'b' : 'B');
        }
        else if (section.sh_flags & SHF_WRITE) // not in bss, so it's initialized data section (g for small, d for regular)
            return intel_small ? (local? 'g' : 'G') : (local? 'd' : 'D');
        return local? 'r' : 'R'; // RO (const) data section if it fits all these but not writeable
    }
    if (type == STT_FUNC && section.sh_flags & SHF_EXECINSTR)
        return (local ? 't' : 'T');
    if (type == STT_SECTION)
        return ('S');
    if (type == STT_TLS)
        return ('T');
    if ((type == STT_NOTYPE || type == STT_FUNC) && undef)
        return ('U'); 
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
    return (strlen(name) == 0);
    // return (type == 'F' || strlen(name) == 0);
}

void    process_symbols(t_info  *info)
{
    t_row   output_tab[info->symcount];
    int foundc = 0;
    int notfound = 0;

    init_output_tab(output_tab, info->symcount);

    for (int i = 0; i < info->symcount; i++)
    {
        // output_tab[i].value = info->is32 ? get_value32(info, i) : get_value64(info, i);
        output_tab[i].value = get_value(info, i);
        output_tab[i].type = info->is32 ? get_type32(info, i) : get_type64(info, i);
        output_tab[i].name = get_sym_name_ptr(info, i);
        if (!filter_out(output_tab[i].type, output_tab[i].name)) {
            output_tab[i].print = true;
            if (output_tab[i].value)
                printf("%016lx ", (long unsigned int) output_tab[i].value);
            else
                printf("%016s ", " ");
            if (output_tab[i].type)
                printf("%c ", output_tab[i].type);
            if (output_tab[i].name)
                printf("%-35s \n", output_tab[i].name);

        }
        // printf("%-35s | %-16s\n", output_tab[i].name, output_tab[i].value);
            // foundc++;
            // notfound++;
    }
        // // all section dependent types have STT_OBJECT as type
        // if (row->type)
    // printf("found %i\nnotfound %i\n", foundc, notfound);
}
