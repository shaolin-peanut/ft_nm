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

char    *get_value32(t_info *info, int i)
{
    Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
    char        *buf = ((char *)(sym->st_value));
    if (buf)
            printf("value: %s\n", buf);
    return (buf);
}

char    *get_value64(t_info *info, int i)
{
    Elf64_Sym   *sym = (Elf64_Sym *) (info->sym_tab + (i * info->symsize));
    return ((char *)(sym->st_value));
}

char    get_type32(t_info   *info, int i)
{
    Elf32_Sym   *sym = (Elf32_Sym *) (info->sym_tab + (i * info->symsize));
    bool        undef = sym->st_shndx == SHN_UNDEF;
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
    if (binding == STB_WEAK)
        return (undef ? 'w' : 'W');
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
    // todo
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

void    process_symbols(t_info  *info)
{
    t_row   output_tab[info->symcount];
    int foundc = 0;
    int notfound = 0;
    char    *valptr = 0;

    init_output_tab(output_tab, info->symcount);
    // bzero(output_tab, sizeof(output_tab));
    
    for (int i = 0; i < info->symcount; i++) {
        output_tab[i].value = info->is32 ? get_value32(info, i) : get_value64(info, i);
        output_tab[i].type = info->is32 ? get_type32(info, i) : get_type64(info, i);
        output_tab[i].name = get_sym_name_ptr(info, i);
        printf("type for %s: %c\n", output_tab[i].name, output_tab[i].type);
        // if (output_tab[i].type) {
        //     printf("type for %s: %c\n", output_tab[i].name, output_tab[i].type);
        //     foundc++;
        // }
    }
        // if (sym->type == STT_OBJECT) {
        //     if (sym->section_flags & SHF_ALLOC) {
        //         if (strncmp(sym->section_name, '.bss', 4) == 0)
        //             row->type = sym->binding == STB_LOCAL ? 'b' : 'B';
        //         // if (strncmp)
        //     } else {
        //         sym->type = 'U';
        //     }
        // }
        // // all section dependent types have STT_OBJECT as type
        // if (row->type)
    printf("found %i\nnotfound %i\n", foundc, notfound);
}
