//
// Created by josh on 11/19/20.
//
#include <elf.h>
#include <link.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>


int check_fp_header_position(FILE *fp){
    return ftell(fp) != 0;
}

void set_fp_header_position(FILE *fp){
    rewind(fp);
}

void ERROR(const char* errorstring){
    fprintf(stderr,"%s", errorstring);
    _exit(-1);
}
bool elf_check_file(ElfW(Ehdr)  *hdr) {
    if(!hdr) return false;
    if(hdr->e_ident[EI_MAG0] != ELFMAG0) {
        ERROR("ELF Header EI_MAG0 incorrect.\n");
        return false;
    }
    if(hdr->e_ident[EI_MAG1] != ELFMAG1) {
        ERROR("ELF Header EI_MAG1 incorrect.\n");
        return false;
    }
    if(hdr->e_ident[EI_MAG2] != ELFMAG2) {
        ERROR("ELF Header EI_MAG2 incorrect.\n");
        return false;
    }
    if(hdr->e_ident[EI_MAG3] != ELFMAG3) {
        ERROR( "ELF Header EI_MAG3 incorrect.\n");
        return false;
    }
    return true;
}

///Reads the header from the elf. Assumes file pointer in correct position
int read_elf_header(char* elf, ElfW(Ehdr)** header) {
    *header = memcpy( *header, elf, 0x40);
    if (elf_check_file(*header)){
        return 0;
    }else{
        return 1;
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
int read_program_header_table(char *elf, ElfW(Phdr) **program_header, unsigned long offset) {
    *program_header = memcpy( *program_header, elf + offset, sizeof(ElfW(Phdr)));
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

void check_sheader_type(ElfW(Shdr) *shdr) {
    switch (shdr->sh_type) {

        case SHT_NULL:
            printf("ST_NULL\n");
            break;
        case SHT_PROGBITS:
            printf("SHT_PROGBITS\n");
            break;
        case SHT_SYMTAB:
            printf("SHT_SYMTAB\n");
            break;
        case SHT_STRTAB:
            printf("SHT_STRTAB\n");
            break;
        case SHT_RELA:
            printf("SHT_RELA\n");
            break;
        case SHT_HASH:
            printf("SHT_HASH\n");
            break;
        case SHT_DYNAMIC:
            printf("SHT_DYNAMIC\n");
            break;
        case SHT_NOTE:
            printf("SHT_NOTE\n");
            break;
        case SHT_NOBITS:
            printf("SHT_NOBITS\n");
            break;
        case SHT_REL:
            printf("SHT_REL\n");
            break;
        case SHT_SHLIB:
            printf("SHT_SHLIB\n");
            break;
        case SHT_DYNSYM:
            printf("SHT_DYNSYM\n");
            break;
        case SHT_LOPROC:
            printf("SHT_LOPROC\n");
            break;
        case SHT_HIPROC:
            printf("SHT_HIPROC\n");
            break;
        case SHT_LOUSER:
            printf("SHT_LOUSER\n");
            break;
        case SHT_HIUSER:
            printf("SHT_HIUSER\n");
            break;
        case SHT_PREINIT_ARRAY:
            printf("SHT_PREINIT_ARRAY\n");
            break;
        default:
            printf("NON STANDARD TYPE. PROBABLY GNU RELATED.\n");
    }
}

///Takes a SHT_STRTAB header, empty pointer and a file pointer.
///get this data and load it into the correct datastructures to ensure the VM correctly performs the executable.
int get_str_tab(ElfW(Shdr) *shdr, ElfW(Sym)* data, FILE* fp){
    //data = malloc(shdr->sh_size);
    int org_position = ftell(fp);
    fseek(fp,shdr->sh_offset,SEEK_SET);
    printf("position is %ld should be %lu \n",ftell(fp),shdr->sh_offset);
    char* tempdata [shdr->sh_size];
    fread(tempdata,1,shdr->sh_size,fp);
    data = (ElfW(Sym)*)  tempdata;
    //return the pointer to its original position.
    fseek(fp,org_position,SEEK_SET);

    if(data == NULL){
        return -1;
    }
    printf("\n");
    return 0;
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

void read_section_header_part(char* elf, ElfW(Shdr) **shdr, unsigned long offset, ElfW(Ehdr) *ehdr){
    *shdr = memcpy( *shdr, elf + offset, ehdr->e_shentsize);
}
