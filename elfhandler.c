//
// Created by josh on 11/19/20.
//
#include <elf.h>
#include <link.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>


int check_fp_header_position(FILE *fp){
    return ftell(fp) != 0;
}

void set_fp_header_position(FILE *fp){
    rewind(fp);
}

///Reads the header from the elf. Assumes file pointer in correct position
int read_elf64_header(FILE *file, Elf64_Ehdr  *header) {

        fread(header, 0x40, 1, file);
        // check so its really an elf file
        if (memcmp(header->e_ident, ELFMAG, SELFMAG) == 0) {
            return 0;
        }
        else{
            return -1;
        }
    }
///Reads a single program header from raw elf file. If the file pointer is in the wrong position -1 is returned.
int read_elf32_header(FILE *file, Elf32_Ehdr *header){
    fread(header, 0x34, 1, file);
    // check so its really an elf file
    if (memcmp(header->e_ident, ELFMAG, SELFMAG) == 0) {
        return 0;
    }
    else{
        return -1;
    }
}
///checks wether the pointer is at the start of the program headers or past it
int check_fp_program_header_position(FILE *fp, ElfW(Ehdr) *ehdr){
    long int pos = ftell(fp);
    int endOfPhdrPos = ehdr->e_phentsize * ehdr->e_phnum;
    return (pos >= ehdr->e_phoff && pos <= endOfPhdrPos);
}

void set_fp_program_header_position(FILE *fp, ElfW(Ehdr) *ehdr){
    fseek(fp,ehdr->e_phoff,0l);
}

///Reads a single program header from raw elf file. Assumes the file pointer is in the correct position.
int read_program_header_table(FILE *file, ElfW(Phdr) *program_header, ElfW(Ehdr) *ehdr) {
    // Either Elf64_Ehdr or Elf32_Ehdr depending on architecture.
    fread(program_header, ehdr->e_phentsize, 1, file);
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
            break;
        default:
            printf("NON STANDARD TYPE. PROBABLY GNU RELATED.\n");
    }
}

///TODO segments contain useful data for the VM to start the executable.
///get this data and load it into the correct datastructures to ensure the VM correctly performs the executable.
void get_segment(ElfW(Phdr) *phdr,ElfW(Shdr) *shdr, FILE *fp){
}

///sets file pointer to the section header table start
void set_fp_to_section_header_part(FILE *fp, ElfW(Ehdr) *ehdr) {
    int currPos = ftell(fp);
    if (currPos == ehdr->e_shoff) {
        return;
    } else {
        fseek(fp, ehdr->e_shoff, SEEK_SET);
        return;
    }
}

void read_section_header_part(FILE *fp, ElfW(Shdr) *shdr, ElfW(Ehdr) *ehdr){

    fread(shdr,1,ehdr->e_shentsize,fp);
}
