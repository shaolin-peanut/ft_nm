#include "include/ft_nm.h"

void    add_to_output_tab(char  *name)
{
    // determine value to use
    // determine type
    // output->name = name;
}

// types
// global or local (that's an if later on, to make upper case or lowercase)
// section specific (bss, text, etc)

void    process_symbols(int symsize, int symcount, t_info  *info)
{
    Elf64_Ehdr  *elf_header = (Elf64_Ehdr *) info->m_elf;

    Elf64_Sym	*symbol = NULL;
    for (int i = 0; i < symcount; i++)
    {
        symbol = (Elf64_Sym *)((char *)info->sym_tab + (i * symsize));
        if (symbol->st_name != 0) {
            char	*sym_name = (char *)(info->sym_str_tab + symbol->st_name);

            printf(" %s %4x %s %c %c %s\n",
                    sym_name,   // Symbol name (left-aligned, 16 characters)
                    symbol->st_value, // Symbol value (hexadecimal)
                    symbol->st_info & 0x0F ? "FUNC" : "VAR",  // Symbol type (function or variable)
                    ELF64_ST_BIND(symbol->st_info) == STB_LOCAL ? 'l' : 'g',  // Symbol binding (local or global)
                    ELF64_ST_VISIBILITY(symbol->st_info) == STV_HIDDEN ? 'h' : ' ', // Symbol visibility (hidden or default)
                    symbol->st_shndx == SHN_UNDEF ? "UNDEF" : "");  // Symbol section (undefined or other)
        }
    }
    // types
    // The following types are used for N-bit architectures (N=32,64, ElfN stands for Elf32 or Elf64, uintN_t stands for uint32_t or
    //    uint64_t):

    //        ElfN_Addr       Unsigned program address, uintN_t
    //        ElfN_Off        Unsigned file offset, uintN_t
    //        ElfN_Section    Unsigned section index, uint16_t
    //        ElfN_Versym     Unsigned version symbol information, uint16_t
    //        Elf_Byte        unsigned char
    //        ElfN_Half       uint16_t
    //        ElfN_Sword      int32_t
    //        ElfN_Word       uint32_t
    //        ElfN_Sxword     int64_t
    //        ElfN_Xword      uint64_t
    
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