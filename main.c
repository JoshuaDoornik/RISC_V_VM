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
#define FILEMODE S_IRWXU | S_IRGRP | S_IROTH


///used to check whats in the file buffer. No other use or utility.
int debugbuffer(FILE *fp,size_t sz){
    unsigned char buffer [sz];
    fread(buffer,sz,1,fp);
    printf("debug hook");
    return 0;
}

int main() {
int elf_descriptor = open("/home/josh/adderRiscv",O_RDWR | O_CREAT, FILEMODE);
int ret,file_len;
char *addr;
struct stat st;
ElfW(Ehdr)* header;
    header = (ElfW(Ehdr)*) malloc(sizeof(ElfW(Ehdr)));
    if (elf_descriptor == 0){
    printf("couldn't open file. \n");
}
    if((ret=fstat(elf_descriptor,&st)) < 0){
        perror("Error in fstat");
    }
    file_len = st.st_size;
    if ((addr = mmap(NULL,file_len,PROT_READ|PROT_WRITE,MAP_SHARED,elf_descriptor,0)) == MAP_FAILED)
    {
        perror("Error in mmap");
        return EXIT_FAILURE;
    }
    printf("addr of file is %04x\n",addr);

printf("file is %zu bytes long\n", file_len);

    for (int i = 0; i < file_len; ++i) {
        printf("%c",addr[i]);
    }


read_elf64_header(addr, &header);
uint16_t pheadercount = header->e_phnum;
//ElfW(Phdr) pheaders[pheadercount];
//ElfW(Shdr) sheaders[header->e_shnum];
printf("\n\n\n----PROGRAM HEADERS----\n\n\n");
int j = 0;
for (; j < pheadercount; ++j) {
    printf("[%d] reading program header type: ",j);
    //read_program_header_table(elf_descriptor, &pheaders[j], &header);
    //check_pheader_type(&pheaders[j]);
}
//
//set_fp_to_section_header_part(fp,&header);
//printf("\n\n\n----SECTIONS----\n\n\n");
//int strtabcounter = 0;
//
//
//for (int i = 0; i < header.e_shnum; ++i) {
//    read_section_header_part(fp,&sheaders[i],&header);
//    printf("[%d] reading section header type: ",i+j);
//    check_sheader_type(&sheaders[i]);
//    if (sheaders[i].sh_type == SHT_STRTAB){
//        strtabcounter++;
//    }
//}
//
//ElfW(Sym) sym[strtabcounter];
//for (int i = 0; i < header.e_shnum; ++i) {
//    if(sheaders[i].sh_type == SHT_STRTAB){
//        if (get_str_tab(&sheaders[i], &sym[i], fp) == 0){
//            strtabcounter++;
//        }
//    }
//    }
printf("\n\n\n----string tabs----\n\n\n");
free(header);
munmap(addr,file_len);
close(elf_descriptor);
exit(0);
}
