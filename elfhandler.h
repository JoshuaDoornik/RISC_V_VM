//
// Created by josh on 11/19/20.
//

#include <elf.h>
#include <bits/types/FILE.h>

#ifndef RISCVVM_ELFHANDLER_H
#define RISCVVM_ELFHANDLER_H

#endif //RISCVVM_ELFHANDLER_H

int read_elf_header(char* elf, ElfW(Ehdr)** header);
int read_program_header_table(char *elf, ElfW(Phdr) **program_header, unsigned long offset) ;
int check_pheader_type(ElfW(Phdr) *phdr);
int check_fp_header_position(FILE *fp);
int get_header_position(FILE *fp);
int check_fp_program_header_position(FILE *fp, ElfW(Ehdr) *ehdr);
void set_fp_program_header_position(FILE *fp, ElfW(Ehdr) *ehdr);
void set_fp_to_section_header_part(FILE *fp, ElfW(Ehdr) *ehdr);
void read_section_header_part(char* elf, ElfW(Shdr) **shdr, unsigned long offset, ElfW(Ehdr) *ehdr);
void check_sheader_type(ElfW(Shdr) *shdr);
int get_str_tab(ElfW(Shdr) *stringHeader, char* elf,char *strTab);
int setup_string_table(char *elf, int shstrndx, int e_shentsize);
void print_array_part(char* arr, int offset, int length);