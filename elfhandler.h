//
// Created by josh on 11/19/20.
//

#include <elf.h>
#include <bits/types/FILE.h>

#ifndef RISCVVM_ELFHANDLER_H
#define RISCVVM_ELFHANDLER_H

#endif //RISCVVM_ELFHANDLER_H

int read_elf64_header(FILE *file, Elf64_Ehdr  *header);
int read_program_header_table(FILE *file, Elf64_Phdr  *program_header);