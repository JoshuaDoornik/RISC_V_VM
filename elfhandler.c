//
// Created by josh on 11/19/20.
//
#include <elf.h>
#include <link.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>

///Reads a single program header from raw elf file. If the file pointer is in the wrong position -1 is returned.
///Its not possible to detect wether it's in the correct position or not. So cant return anything if its not an Phdr file.
int read_elf64_header(FILE *file, Elf64_Ehdr  *header) {
    if(ftell(file) != 0){
        return -1;
    }
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

///Reads a single program header from raw elf file. Assumes the file pointer is in the correct position.
///Its not possible to detect wether it's in the correct position or not. So cant return anything if its not an Phdr file.
int read_program_header_table(FILE *file, ElfW(Phdr)   *program_header) {
    // Either Elf64_Ehdr or Elf32_Ehdr depending on architecture.

    fread(program_header, 56, 1, file);
    return 0;
}

///Prints the program header type in plain text. Useful for debugging if you don't feel like decoding hex numbers again.
void check_pheader_type(ElfW(Phdr) *phdr) {
    switch (phdr->p_type) {

        case PT_NULL:
            printf("PT_NULL\n");
            break;
        case PT_LOAD:
            printf("PT_LOAD\n");
            break;
        case PT_DYNAMIC:
            printf("PT_DYNAMIC\n");
            break;
        case PT_INTERP:
            printf("PT_INTERP\n");
            break;
        case PT_NOTE:
            printf("PT_NOTE\n");
            break;
        case PT_SHLIB:
            printf("PT_SHLIB\n");
            break;
        case PT_PHDR:
            printf("PT_PHDR\n");
            break;
        case PT_TLS:
            printf("PT_TLS\n");
            break;
        case PT_LOOS:
            printf("PT_LOOS\n");
            break;
        case PT_HIOS:
            printf("PT_HIOS\n");
            break;
        case PT_LOPROC:
            printf("PT_LOPROC\n");
            break;
        case PT_HIPROC:
            printf("PT_HIPROC\n");
            break;
        case PT_GNU_STACK:
            printf("PT_GNU_STACK\n");
        default:
            printf("NON STANDARD TYPE. PROBABLY GNU RELATED.\n");
    }
}

void get_section(ElfW(Shdr) *shdr,FILE *fp){
    unsigned long int position = ftell(fp);


}