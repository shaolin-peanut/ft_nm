#include "include/ft_nm.h"

void    process_symbols(t_info  *info)
{
    t_row   *row = 0;
    int foundc = 0;
    int notfound = 0;

    info->output_tab = (t_row *) malloc(sizeof(t_row) * info->symcount);
    if (!info->output_tab)
        exit_err("malloc", 653);

    for (int i = 0; i < info->symcount; i++)
    {
        t_symbol    *sym = &info->my_symbols[i];
        
        row = &info->output_tab[i];
        row->value = 0;
        row->type = 0;
        row->print = false;
        row->name = sym->name;
        // section names
        char    *n = sym->section_name;
        if (sym->section == SHN_ABS)
            row->type = 'A';
        if (sym->binding ==  STB_GNU_UNIQUE)
            row->type = 'u'; // unique symbol
        if (sym->binding == STB_WEAK) // W is good, w was applied to one of 4 expected matches
            row->type = sym->section == SHN_UNDEF ? 'w' : 'W'; // On some systems, uppercase indicates that a default value has been specified. so if !undef = 'W'
        if (sym->type == STT_COMMON || (sym->type == STT_OBJECT && sym->section == SHN_COMMON))
            row->type = 'C';
        if (sym->type == STT_SECTION)
            row->type = 'S';
        if (sym->type == STT_FILE)
            row->type = 'F';
        if (sym->type == STT_TLS)
            row->type = 'T';
        if (sym->type == STT_NOTYPE) {
            if (sym->section == SHN_UNDEF)
                row->type = 'S';
            // else get section data
        }
        if (sym->type == STT_GNU_IFUNC)
            row->type = 'i';
        if (row->type) {
            printf("type for %s: %c\n", sym->name, row->type);
            foundc++;
        }
        else {
            printf("type for %s not found\n", sym->name);
            notfound++;
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

    }
    printf("found %i\nnotfound %i\n", foundc, notfound);
}
