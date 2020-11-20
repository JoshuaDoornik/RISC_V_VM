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


///used to check whats in the file buffer. No other use or utility.
int debugbuffer(FILE *fp,size_t sz){
    unsigned char buffer [sz];
    fread(buffer,sz,1,fp);
    printf("debug hook");
    return 0;
}

///finds the size of the file and rewinds. As fseek and rewind are called it's slow.
///returns the file size by seeking SEEK_END and calling ftell on that position.
size_t find_file_size(FILE *fp){
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    rewind(fp);
    return sz;
}

int main() {
FILE* fp = fopen("/home/josh/adderRiscv","rb");
if (fp == NULL){
    printf("couldn't open file. \n");
}
size_t sz = find_file_size(fp);
printf("file is %zu bytes long\n", sz);


ElfW(Ehdr) header;
read_elf64_header(fp, &header);
uint16_t pheadercount = header.e_phnum;
ElfW(Phdr) pheaders[pheadercount];
ElfW(Shdr) sheaders[header.e_shnum];
    for (int i = 0; i < pheadercount; ++i) {
        read_program_header_table(fp, &pheaders[i], &header);
        check_pheader_type(&pheaders[i]);

    }
    set_fp_to_section_header_part(fp,&header);
    printf("ftell postion %ld, section headers located at %ld", ftell(fp),header.e_shoff);

    for (int i = 0; i < header.e_shnum; ++i) {
        read_section_header_part(fp,&sheaders[i],&header);
    }


fclose(fp);
exit(0);
}
