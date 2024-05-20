#include "include/ft_nm.h"

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
    if (ELF32_ST_BIND (sym->st_info) == STB_WEAK)
        return (undef ? 'w' : 'W');
    if (ELF32_ST_BIND (sym->st_info) == STB_WEAK) // W is good, w was applied to one of 4 expected matches
        return (undef ? 'w' : 'W');
    if (ELF32_ST_TYPE (sym->st_info) == STT_COMMON || (ELF32_ST_TYPE (sym->st_info) && sym->st_shndx == SHN_COMMON))
        return ('C');
    if (ELF32_ST_BIND (sym->st_shndx) == STT_SECTION)
        return ('S');
    if (ELF32_ST_TYPE (sym->st_info) == STT_FILE)
        return ('F');
    if (ELF32_ST_TYPE (sym->st_info) == STT_TLS)
        return ('T');
    if (ELF32_ST_TYPE (sym->st_info) == STT_NOTYPE) {
        if (sym->st_shndx == SHN_UNDEF)
            return ('S');
        // else get section data
    }
    if (ELF32_ST_TYPE (sym->st_info) == STT_GNU_IFUNC)
        return ('i');

}

char    get_type64(t_info  *info, int  i)
{
    // todo
}

void    init_output_tab(t_row *output_tab, int count)
{
    for (int i = 0; i < count; i++)
    {
        output_tab[i].value = 0;
        output_tab[i].type = 0;
        output_tab[i].print = false;
        output_tab[i].name = 0;
    }
}

void    process_symbols(t_info  *info)
{
    t_row   output_tab[info->symcount];
    int foundc = 0;
    int notfound = 0;

    init_output_tab(&output_tab, info->symcount);
    
    for (int i = 0; i < info->symcount; i++) {
        output_tab[i].type = get_type(info, i);
        output_tab[i].name = info->symbols[i].st_name ? (char *)(info->sym_str_tab + info->symbols[i].st_name) : NULL;
        if (output_tab[i].type) {
            printf("type for %s: %c\n", sym->name, output_tab[i].type);
            foundc++;
        }
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
