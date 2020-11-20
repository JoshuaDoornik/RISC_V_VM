//
// Created by josh on 11/19/20.
//

#include <elf.h>
#include <bits/types/FILE.h>

#ifndef RISCVVM_ELFHANDLER_H
#define RISCVVM_ELFHANDLER_H

#endif //RISCVVM_ELFHANDLER_H

int read_elf64_header(FILE *file, Elf64_Ehdr  *header);
int read_program_header_table(FILE *file, ElfW(Phdr) *program_header, ElfW(Ehdr) *ehdr);
int check_pheader_type(ElfW(Phdr) *phdr);
int check_fp_header_position(FILE *fp);
int get_header_position(FILE *fp);
int check_fp_program_header_position(FILE *fp, ElfW(Ehdr) *ehdr);
void set_fp_program_header_position(FILE *fp, ElfW(Ehdr) *ehdr);
void set_fp_to_section_header_part(FILE *fp, ElfW(Ehdr) *ehdr);
void read_section_header_part(FILE *fp, ElfW(Shdr) *shdr, ElfW(Ehdr) *ehdr);
