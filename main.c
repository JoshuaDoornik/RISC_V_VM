#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <string.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <link.h>
#include "elfhandler.h"
#include <inttypes.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <bits/fcntl-linux.h>
#include <errno.h>
#define FILEMODE (S_IRWXU | S_IRGRP | S_IROTH)


///used to check whats in the file buffer. No other use or utility.
int debugbuffer(FILE *fp,size_t sz){
    unsigned char buffer [sz];
    fread(buffer,sz,1,fp);
    printf("debug hook");
    return 0;
}


int openELF(char* filename, char** addr, int* file_len,int* elf_descriptor){
    int ret;
    struct stat st;

    int fd = open(filename, O_RDWR | O_CREAT, FILEMODE);
    if (fd == 0){
        printf("couldn't open file. \n");
        return errno;
    }
    if((ret=fstat(fd,&st)) < 0){
        perror("Error in fstat");
        return ret;
    }
    *file_len = st.st_size;
    *elf_descriptor = fd;
    if ((*addr = mmap(NULL,*file_len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == MAP_FAILED)
    {
        perror("Error in mmap\n");
        return errno;
    }
    printf("addr of file is %p\n",addr);
    printf("file is %d bytes long\n", *file_len);
    return 0;
}

int main(int argc, char **argv) {

    int elf_descriptor,file_len;
    char *addr,*filename,*strab;
    if( argc < 2){
        filename = "/home/josh/riscHello";
    }else{
        filename = argv[1];
    }
    if (openELF(filename, &addr,&file_len,&elf_descriptor) != 0){
        exit(1);
    }
    ElfW(Ehdr)* header;

    //open the elf file and print some info about it
    header = (ElfW(Ehdr)*) malloc(sizeof(ElfW(Ehdr)));

    //setup the string table

    read_elf_header(addr, &header);
    setup_string_table(addr,header->e_shstrndx,header->e_shentsize);

    uint16_t pheadercount = header->e_phnum;
    ElfW(Phdr)* pheaders[pheadercount];
    ElfW(Shdr)* sheaders[header->e_shnum];
    printf("\n\n\n----PROGRAM HEADERS----\n\n\n");
    for (int j = 0; j < pheadercount; ++j) {
        printf("[%d] reading program header type: ",j);
        pheaders[j] = (ElfW(Phdr)* ) malloc(sizeof(ElfW(Phdr)));
        read_program_header_table(addr, &pheaders[j], header->e_phoff + (j * sizeof(ElfW(Phdr))));
        check_pheader_type(pheaders[j]);
    }
    printf("\n\n\n----SECTIONS----\n\n\n");

    for (int i = 0; i < header->e_shnum; ++i) {
        sheaders[i] = (ElfW(Shdr)* ) malloc(header->e_shentsize);
        read_section_header_part(addr,&sheaders[i], header->e_shoff + (header->e_shentsize * i),header);
        printf("[%d] reading section header type: ",i);
        check_sheader_type(sheaders[i]);
    }

    get_str_tab(sheaders[header->e_shstrndx],addr,&strab);
    print_array_part(strab,0,sheaders[header->e_shstrndx]->sh_size);


    for (int i = 0; i < header->e_shnum; ++i) {
        int name_off = sheaders[i]->sh_name;
        printf("%s\n",strab+name_off);
        if(memcmp(strab+name_off,".text",5) ==0){
            char* textdata = addr+ sheaders[i]->sh_offset;
            print_array_part(textdata,0,sheaders[i]->sh_size);
        }
        free(sheaders[i]);
    }
    free(header);
    for (int i = 0; i <pheadercount; ++i) {
        free(pheaders[i]);
    }
    free(strab);
    munmap(addr,file_len);
    close(elf_descriptor);
    exit(0);
}
