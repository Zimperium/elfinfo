/*
 * elfinfo by Elia Yehuda, (C) zImperium 2013
 *
 * prints some info from ELF files. for 32 bit only. maybe can be extended 
 * to 64 using a macro.
 * 
 * code cleanup is required.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

#define ELFMAGIC "\177ELF"

/* get the section header string table */
Elf32_Shdr *get_string_table(char *elfptr) 
{
        Elf32_Ehdr *header = (Elf32_Ehdr *) elfptr;
        Elf32_Shdr *section = (Elf32_Shdr *)(elfptr + header->e_shoff + (header->e_shstrndx * sizeof(Elf32_Shdr)) );
        return section;
}

/* get a section by name */
Elf32_Shdr *get_section_by_name(char *elfptr, char *name)
{
        Elf32_Ehdr *header = (Elf32_Ehdr *) elfptr;
        Elf32_Shdr *section = (Elf32_Shdr *) (elfptr + header->e_shoff);
        char *strtbl = (char *)(get_string_table(elfptr)->sh_offset + elfptr);
        int k, namelen = strlen(name);
        for (k = 0; k < header->e_shnum; k++, section++) {
                if ( strncmp(strtbl + section->sh_name, name, namelen) == 0) 
                        return section;
        }
        return NULL;
}


void hexdump(void *ptr, int buflen) 
{
        unsigned char *buf = (unsigned char*)ptr;
        int i, j;
        printf("\n");
        for (i=0; i<buflen; i+=16) {
                printf("%04x: ", i);
                for (j=0; j<16; j++) 
                        if (i+j < buflen) printf("%02x ", buf[i+j]); else printf("   ");
                printf(" ");
                for (j=0; j<16; j++) 
                        if (i+j < buflen)
                                printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
                printf("\n");
        }
}

void dump_symbols(char *input, Elf32_Shdr *symbols,Elf32_Shdr *strings)
{
	if (!input || !symbols || !strings)
		return;
	int i;
        Elf32_Ehdr *ehdr = (Elf32_Ehdr*)input;
        Elf32_Shdr *shdr = (Elf32_Shdr*)( (int)input + ehdr->e_shoff );
	int symtab_size = symbols->sh_size / sizeof(Elf32_Sym);
	Elf32_Sym *symtab = (Elf32_Sym *) (input + symbols->sh_offset);
	char *strtab = (char *) input + strings->sh_offset;
        char *strtbl      = (char*)((int)ehdr+shdr[ehdr->e_shstrndx].sh_offset );

        printf("\nsymbol table at offset 0x%08x (%d entries) \n", symbols->sh_offset , symtab_size);
        printf("\nID       SIZE     VALUE    SYMBOL                             SECTION\n");
  
	for (i = 0; i < symtab_size; ++i) {
		printf("%-8d %08x %08x %-34s ", i, symtab[i].st_size, symtab[i].st_value ,symtab[i].st_name ? strtab + symtab[i].st_name : "");
		if ((symtab[i].st_shndx > 0) && (symtab[i].st_shndx < ehdr->e_shnum))
			printf("%-10s", strtbl + shdr[symtab[i].st_shndx].sh_name);
		printf("\n");
	}
}

void dump_header(char *input)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr*)input;
        switch (ehdr->e_machine) {
		case EM_386:  printf("Type     : IA32 "); break;
		case EM_ARM:  printf("Type     : ARM ");  break;
		case EM_MIPS: printf("Type     : MIPS "); break;
		default:      printf("Type     : Unrecognized "); break;
        }

        switch( ehdr->e_type ) {
		case ET_REL:  printf( "relocatable\n" ); break;
		case ET_EXEC: printf( "executable\n" ); break;
		default:      printf( "unknown\n\nFile is neither linkable nor executable\n" ); exit(1);
        }

        printf( "OEP      : 0x%08x \n", ehdr->e_entry );
}

void dump_segments(char *input)
{
	int i;
        Elf32_Ehdr *ehdr = (Elf32_Ehdr*)input;
        char flags[8]    = {0,0,0,0,0,0,0,0};
        int phnum        = ehdr->e_phnum;
        Elf32_Phdr *phdr = (Elf32_Phdr*)( (int)input + ehdr->e_phoff );

        printf( "\nprogram-header table at offset 0x%08x (%d entries) \n", ehdr->e_phoff , ehdr->e_phnum);
        printf("\nTYPE     OFFSET   FSIZE    MEMSIZE  VADDRESS PADDRESS FLAGS        ALIGN\n");

        for (i = 0; i < phnum; i++) {
                switch (phdr[i].p_type) {
		        case PT_LOAD:    printf("LOAD     "); break;
		        case PT_DYNAMIC: printf("DYNAMIC  "); break;
		        case PT_NOTE:    printf("NOTE     "); break;
		        case PT_NULL:    printf("NULL     "); break;
		        case PT_PHDR:    printf("PHDR     "); break;
		        case PT_INTERP:  printf("INTERP   "); break;
		        case 0x6474E551: printf("STACK    "); break;
		        case 0x6474E552: printf("RELRO    "); break;
		        default: printf("%08x ", phdr[i].p_type); break;
                }
                flags[0] = (phdr[i].p_flags & PF_R) ? 'r' : '-';
                flags[1] = (phdr[i].p_flags & PF_W) ? 'w' : '-';
                flags[2] = (phdr[i].p_flags & PF_X) ? 'x' : '-';
                printf( "%08x %08x %08x %08x %08x %08x %s %08x \n",
                        phdr[i].p_offset , phdr[i].p_filesz , phdr[i].p_memsz, phdr[i].p_vaddr, phdr[i].p_paddr, phdr[i].p_flags, flags, phdr[i].p_align );
        }
}

void dump_sections(char *input)
{
	int i;
        char flags[8]    = {0,0,0,0,0,0,0,0};
        Elf32_Ehdr *ehdr = (Elf32_Ehdr*)input;
        int  shnum        = ehdr->e_shnum;
        Elf32_Shdr *shdr  = (Elf32_Shdr*)( (int)ehdr + ehdr->e_shoff );
        char *strtbl      = (char*)((int)ehdr+shdr[ehdr->e_shstrndx].sh_offset );
	char *title;

        printf("\nsection-header table at offset 0x%08x (%d entries) \n", ehdr->e_shoff , ehdr->e_shnum);
        printf("\nTYPE     OFFSET   SIZE     ADDRESS  ALIGN    FLAGS            INFO\n");

	unsigned int last_offset = 0, last_addr = 0, e_shoff = ehdr->e_shoff, e_phoff = ehdr->e_phoff;
        for (i = 0; i < shnum; i++, shdr++) {
		title = strtbl + shdr->sh_name;
		if (i == 0) {
			shdr->sh_size = ehdr->e_ehsize;
			title = (char*)"[ELF HEADER]";
		}
		if (shdr->sh_offset > last_offset) {
			if (shdr->sh_offset > e_shoff) {
				if (e_shoff - last_offset) 
	                		printf( "         %08x %08x %08x %08x %08x %s %-30s\n", last_offset , e_shoff - last_offset , last_addr, 0 , 0, "-------", "" );
                		printf( "         %08x %08x %08x %08x %08x %s %-30s\n", e_shoff , ehdr->e_shnum * sizeof( Elf32_Shdr ) , last_addr, 0 , 0, "-------", "[SECTION HEADER TABLE]" );
				e_shoff = -1;
			}
			else if (shdr->sh_offset > e_phoff) {
				if (e_phoff - last_offset) 
					printf( "         %08x %08x %08x %08x %08x %s %-30s\n", last_offset , e_phoff - last_offset , last_addr, 0 , 0, "-------", "" );
                		printf( "         %08x %08x %08x %08x %08x %s %-30s\n", e_phoff , ehdr->e_phnum * sizeof( Elf32_Phdr ) , last_addr, 0 , 0, "-------", "[PROGRAM HEADER TABLE]" );
				e_phoff = -1;
                	} else printf( "         %08x %08x %08x %08x %08x %s %-30s\n", last_offset , shdr->sh_offset - last_offset , last_addr, 0 , 0, "-------", "" );
		}
		last_offset = shdr->sh_offset + shdr->sh_size;
		last_addr = (shdr->sh_addr) ? shdr->sh_addr + shdr->sh_size : 0;
                switch (shdr->sh_type) {
		        case SHT_NULL:     printf("NULL     "); break;
		        case SHT_PROGBITS: printf("PROGBITS "); break;
		        case SHT_SYMTAB:   printf("SYMTAB   "); break;
		        case SHT_STRTAB:   printf("STRTAB   "); break;
		        case SHT_RELA:     printf("RELA     "); break;
		        case SHT_HASH:     printf("HASH     "); break;
		        case SHT_DYNAMIC:  printf("DYNAMIC  "); break;
		        case SHT_NOTE:     printf("NOTE     "); break;
		        case SHT_NOBITS:   printf("NOBITS   "); break;
		        case SHT_REL:      printf("REL      "); break;
		        case SHT_SHLIB:    printf("SHLIB    "); break;
		        case SHT_DYNSYM:   printf("DYNSYM   "); break;
#define	SHT_INIT_ARRAY		14
#define	SHT_FINI_ARRAY		15
#define	SHT_PREINIT_ARRAY	16
			case SHT_PREINIT_ARRAY : printf("PINITARR "); break;
			case SHT_INIT_ARRAY    : printf("INITARR  "); break;
			case SHT_FINI_ARRAY    : printf("FINIARR  "); break;
		        default:           printf("%08x ", shdr->sh_type)     ; break;
                }

                flags[0] = (shdr->sh_flags & SHF_ALLOC)     ? 'a' : '-';
                flags[1] = (shdr->sh_flags & SHF_WRITE)     ? 'w' : '-';
                flags[2] = (shdr->sh_flags & SHF_EXECINSTR) ? 'x' : '-';
                flags[3] = (shdr->sh_flags & SHF_MASKPROC)  ? 'p' : '-';
#define SHF_MERGE 		0x10
#define SHF_STRINGS 		0x20
#define SHF_LINK_ORDER 		0x80
                flags[4] = (shdr->sh_flags & SHF_MERGE)     ? 'm' : '-';
                flags[5] = (shdr->sh_flags & SHF_STRINGS)   ? 's' : '-';
                flags[6] = (shdr->sh_flags & SHF_LINK_ORDER)? 'l' : '-';

                printf( "%08x %08x %08x %08x %08x %s %-30s\n", shdr->sh_offset , shdr->sh_size , shdr->sh_addr, shdr->sh_addralign , shdr->sh_flags, flags, title );
	
	}
	if (e_shoff != -1) {
		if (e_shoff - last_offset) 
        		printf( "         %08x %08x %08x %08x %08x %s %-30s\n", last_offset , e_shoff - last_offset , last_addr, 0 , 0, "-------", "" );
		printf( "         %08x %08x %08x %08x %08x %s %-30s\n", e_shoff , ehdr->e_shnum * sizeof( Elf32_Shdr ) , last_addr, 0 , 0, "-------", "[SECTION HEADER TABLE]" );
	}
}

int main( int argc, char **argv )
{
        if ( argc == 1 ) {
                printf( "No input-file\n" );
                exit(1);
        }

        int fd = open( argv[1], O_RDONLY );
        if ( fd < 0 ) {
                perror( "open" );
                exit(1);
        }

        int size    = lseek( fd, 0, SEEK_END );
        char *input = malloc( size );

        lseek( fd, 0, SEEK_SET );
        if ( read( fd, input, size ) < size ) {
                perror( "read" );
		free(input);
		close(fd);
                exit(1);
        }
	close(fd);

        Elf32_Ehdr *ehdr = (Elf32_Ehdr*)input;
        if ( strncmp( (char*)ehdr->e_ident, ELFMAGIC, 4 ) ) {
                printf( "Not an ELF-format file\n" );
		free(input);
                exit(1);
        }

        printf( "\nFilename : %s (%d bytes)\n", argv[1] , size);

	dump_header(input);
	dump_segments(input);
	dump_sections(input);
	dump_symbols( input, get_section_by_name(input, ".symtab"),  get_section_by_name(input, ".strtab"));
	dump_symbols( input, get_section_by_name(input, ".dynsym"),  get_section_by_name(input, ".dynstr"));

        printf( "\n" );
	free(input);
}


