elfinfo
=======

prints some info from ELF files

sample output:
==============

	File     /data/local/tmp/elfinfo (11529 bytes)
	Type     ARM executable
	OEP      0x000085e0 

	program-header table at offset 0x00000034 (8 entries) 

	TYPE     OFFSET   FSIZE    MEMSIZE  VADDRESS PADDRESS ALIGN    FLAGS
	PHDR     00000034 00000100 00000100 00008034 00008034 00000004 r-x
	INTERP   00000134 00000013 00000013 00008134 00008134 00000001 r--
	LOAD     00000000 00001738 00001738 00008000 00008000 00001000 r-x
	LOAD     00001e98 00000168 00000178 0000ae98 0000ae98 00001000 rw-
	DYNAMIC  00001eb8 000000e8 000000e8 0000aeb8 0000aeb8 00000004 rw-
	NOTE     00001720 00000018 00000018 00009720 00009720 00000004 r--
	STACK    00000000 00000000 00000000 00000000 00000000 00000004 rw-
	RELRO    00001e98 00000168 00000168 0000ae98 0000ae98 00000001 r--

	section-header table at offset 0x00002130 (23 entries) 

	TYPE     OFFSET   SIZE     ADDRESS  ALIGN    FLAGS   INFO
	NULL     00000000 00000034 00008000 00000000 ------- [ELF HEADER]
	NULL     00000034 00000100 00008034 00000000 ------- [PROGRAM HEADER TABLE]
	PROGBITS 00000134 00000013 00008134 00000001 a------ .interp
		 00000147 00000001 00008147 00000000 ------- 
	HASH     00000148 000000b0 00008148 00000004 a------ .hash
	DYNSYM   000001f8 00000190 000081f8 00000004 a------ .dynsym
	STRTAB   00000388 000000da 00008388 00000001 a------ .dynstr
		 00000462 00000002 00008462 00000000 ------- 
	REL      00000464 00000028 00008464 00000004 a------ .rel.dyn
	REL      0000048c 00000080 0000848c 00000004 a------ .rel.plt
	PROGBITS 0000050c 000000d4 0000850c 00000004 a-x---- .plt
	PROGBITS 000005e0 00000d50 000085e0 00000004 a-x---- .text
	PROGBITS 00001330 000003ed 00009330 00000001 a---ms- .rodata
		 0000171d 00000003 0000971d 00000000 ------- 
	NOTE     00001720 00000018 00009720 00000004 a------ .note.android.ident
		 00001738 00000760 0000a738 00000000 ------- 
	PINITARR 00001e98 00000008 0000ae98 00000004 aw----- .preinit_array
	INITARR  00001ea0 00000008 0000aea0 00000004 aw----- .init_array
	FINIARR  00001ea8 00000008 0000aea8 00000004 aw----- .fini_array
	PROGBITS 00001eb0 00000008 0000aeb0 00000004 aw----- .ctors
	DYNAMIC  00001eb8 000000e8 0000aeb8 00000004 aw----- .dynamic
	PROGBITS 00001fa0 00000060 0000afa0 00000004 aw----- .got
	NOBITS   00002000 00000010 0000b000 00000004 aw----- .bss
	PROGBITS 00002000 00000037 00000000 00000001 ------- .comment
	70000003 00002037 0000002f 00000000 00000001 ------- .ARM.attributes
	STRTAB   00002066 000000c7 00000000 00000001 ------- .shstrtab
		 0000212d 00000003 00000000 00000000 ------- 
	NULL     00002130 00000398 00000000 00000000 ------- [SECTION HEADER TABLE]
	SYMTAB   000024c8 00000620 00000000 00000004 ------- .symtab
	STRTAB   00002ae8 00000221 00000000 00000001 ------- .strtab

	symbol table at offset 0x000024c8 (98 entries) 

	TYPE     INFO     SIZE     VALUE    SYMBOL               SECTION
	NOTYPE   L U      00000000 00000000                      
	SECTION  L        00000000 00008134                      .interp
	SECTION  L        00000000 00008148                      .hash
	SECTION  L        00000000 000081f8                      .dynsym
	SECTION  L        00000000 00008388                      .dynstr
	SECTION  L        00000000 00008464                      .rel.dyn
	SECTION  L        00000000 0000848c                      .rel.plt
	SECTION  L        00000000 0000850c                      .plt
	SECTION  L        00000000 000085e0                      .text
	SECTION  L        00000000 00009330                      .rodata
	SECTION  L        00000000 00009720                      .note.android.ident
	SECTION  L        00000000 0000ae98                      .preinit_array
	SECTION  L        00000000 0000aea0                      .init_array
	SECTION  L        00000000 0000aea8                      .fini_array
	SECTION  L        00000000 0000aeb0                      .ctors
	SECTION  L        00000000 0000aeb8                      .dynamic
	SECTION  L        00000000 0000afa0                      .got
	SECTION  L        00000000 0000b000                      .bss
	SECTION  L        00000000 00000000                      .comment
	SECTION  L        00000000 00000000                      .ARM.attributes
	FILE     L A      00000000 00000000 crtbegin_dynamic.c   
	NOTYPE   L        00000000 000085e0 $a                   .text
	NOTYPE   L        00000000 00008644 $d                   .text
	NOTYPE   L        00000000 0000865c $a                   .text
	NOTYPE   L        00000000 0000866c $d                   .text
	NOTYPE   L        00000000 0000aea8 $d                   .fini_array
	NOTYPE   L        00000000 0000aea0 $d                   .init_array
	NOTYPE   L        00000000 0000b000 $d                   .bss
	NOTYPE   L        00000000 0000ae98 $d                   .preinit_array
	NOTYPE   L        00000000 0000aeb0 $d                   .ctors
	FILE     L A      00000000 00000000 crtbrand.c           
	NOTYPE   L        00000000 00009720 $d                   .note.android.ident
	OBJECT   L        00000018 00009720 abitag               .note.android.ident
	FILE     L A      00000000 00000000 elfinfo.c            
	NOTYPE   L        00000000 00008670 $a                   .text
	NOTYPE   L        00000000 00008764 $d                   .text
	NOTYPE   L        00000000 00008784 $a                   .text
	NOTYPE   L        00000000 00008928 $d                   .text
	NOTYPE   L        00000000 0000895c $a                   .text
	NOTYPE   L        00000000 00008bac $d                   .text
	NOTYPE   L        00000000 00008c08 $a                   .text
	NOTYPE   L        00000000 00008dc0 $d                   .text
	NOTYPE   L        00000000 00008dd8 $a                   .text
	NOTYPE   L        00000000 00008fe8 $d                   .text
	NOTYPE   L        00000000 00009018 $a                   .text
	NOTYPE   L        00000000 000090ec $d                   .text
	NOTYPE   L        00000000 000090f8 $a                   .text
	NOTYPE   L        00000000 00009308 $d                   .text
	NOTYPE   L        00000000 0000b004 $d                   .bss
	OBJECT   L        00000004 0000b004 last_offset.3076     .bss
	OBJECT   L        00000008 0000b008 flags.3077           .bss
	OBJECT   L        00000000 0000aeb8 _DYNAMIC             .dynamic
	OBJECT   L        00000000 0000afa0 _GLOBAL_OFFSET_TABLE_ .got
	NOTYPE   L        00000000 0000850c $a                   .plt
	NOTYPE   L        00000000 0000851c $d                   .plt
	NOTYPE   L        00000000 00008520 $a                   .plt
	FUNC     G U      00000000 00008520 putchar              
	FUNC     G U      00000000 0000852c printf               
	FUNC     G        00000240 00008dd8 dump_symbols         .text
	NOTYPE   G A      00000000 00009738 __exidx_end          
	NOTYPE   G A      00000000 0000b010 _bss_end__           
	FUNC     G        000000e0 00009018 hexdump              .text
	FUNC     G U      00000000 00008538 perror               
	FUNC     G U      00000000 00008544 puts                 
	FUNC     G U      00000000 00008550 malloc               
	OBJECT   G        00000004 0000aea8 __FINI_ARRAY__       .fini_array
	NOTYPE   G A      00000000 0000b000 __bss_start__        
	OBJECT   G        00000004 0000b000 __dso_handle         .bss
	FUNC     G        000002ac 0000895c dump_section         .text
	NOTYPE   G A      00000000 00009738 __exidx_start        
	FUNC     G U      00000000 0000855c lseek                
	FUNC     G U      00000000 00008568 __libc_init          
	FUNC     G        000001d0 00008c08 dump_sections        .text
	OBJECT   G        00000004 0000aeb0 __CTOR_LIST__        .ctors
	NOTYPE   G A      00000000 0000b010 __bss_end__          
	FUNC     G        0000007c 000085e0 _start               .text
	FUNC     G        00000050 00008670 get_pheader_by_offset .text
	OBJECT   G        00000004 0000aea0 __INIT_ARRAY__       .init_array
	FUNC     G U      00000000 00008574 read                 
	FUNC     G U      00000000 00008580 strncmp              
	FUNC     G U      00000000 0000858c __cxa_atexit         
	NOTYPE   G A      00000000 0000b000 __bss_start          
	FUNC     G        000001c0 00009170 main                 .text
	NOTYPE   G A      00000000 0000b010 __end__              
	FUNC     G U      00000000 00008598 isprint              
	FUNC     G        00000014 0000865c atexit               .text
	FUNC     G        000001d8 00008784 dump_segments        .text
	OBJECT   G        00000004 0000ae98 __PREINIT_ARRAY__    .preinit_array
	NOTYPE   G A      00000000 0000b000 _edata               
	NOTYPE   G A      00000000 0000b010 _end                 
	FUNC     G U      00000000 000085a4 exit                 
	FUNC     G        000000c4 000086c0 dump_header          .text
	FUNC     G U      00000000 000085b0 strlen               
	FUNC     G U      00000000 000085bc open                 
	NOTYPE   G        00000000 0000b000 __data_start         .bss
	FUNC     G U      00000000 000085c8 close                
	FUNC     G        00000078 000090f8 get_section_by_name  .text
	FUNC     G U      00000000 000085d4 free                 

	symbol table at offset 0x000001f8 (25 entries) 

	TYPE     INFO     SIZE     VALUE    SYMBOL               SECTION
	NOTYPE   L U      00000000 00000000                      
	FUNC     G U      00000000 00008520 putchar              
	FUNC     G U      00000000 0000852c printf               
	FUNC     G U      00000000 00008538 perror               
	FUNC     G U      00000000 00008544 puts                 
	FUNC     G U      00000000 00008550 malloc               
	OBJECT   G        00000004 0000aea8 __FINI_ARRAY__       .fini_array
	FUNC     G U      00000000 0000855c lseek                
	FUNC     G U      00000000 00008568 __libc_init          
	OBJECT   G        00000004 0000aeb0 __CTOR_LIST__        .ctors
	OBJECT   G        00000004 0000aea0 __INIT_ARRAY__       .init_array
	FUNC     G U      00000000 00008574 read                 
	FUNC     G U      00000000 00008580 strncmp              
	FUNC     G U      00000000 0000858c __cxa_atexit         
	NOTYPE   G A      00000000 0000b000 __bss_start          
	FUNC     G        000001c0 00009170 main                 .text
	FUNC     G U      00000000 00008598 isprint              
	OBJECT   G        00000004 0000ae98 __PREINIT_ARRAY__    .preinit_array
	NOTYPE   G A      00000000 0000b000 _edata               
	NOTYPE   G A      00000000 0000b010 _end                 
	FUNC     G U      00000000 000085a4 exit                 
	FUNC     G U      00000000 000085b0 strlen               
	FUNC     G U      00000000 000085bc open                 
	FUNC     G U      00000000 000085c8 close                
	FUNC     G U      00000000 000085d4 free                 

