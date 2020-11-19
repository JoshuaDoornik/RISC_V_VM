//
// Created by josh on 11/19/20.
//
#include <elf.h>
#include <link.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>


int read_elf64_header(FILE *file, Elf64_Ehdr  *header) {
    // Either Elf64_Ehdr or Elf32_Ehdr depending on architecture.

        fread(header, 64, 1, file);
        // check so its really an elf file
        if (memcmp(header->e_ident, ELFMAG, SELFMAG) == 0) {
            return 0;
        }
        else{
            return -1;
        }
    }

void printElfHeader(unsigned char *header){

}

int read_program_header_table(FILE *file, Elf64_Phdr  *program_header) {
    // Either Elf64_Ehdr or Elf32_Ehdr depending on architecture.

    fread(program_header, 56, 1, file);
    return 0;
}