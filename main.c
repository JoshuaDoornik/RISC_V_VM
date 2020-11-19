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



int debugbuffer(FILE *fp,size_t sz){
    unsigned char buffer [sz];
    fread(buffer,sz,1,fp);
    printf("debug hook");
    return 0;
}
int main() {
FILE* fp = fopen("/home/josh/adderRiscv","rb");
if (fp == NULL){
    printf("couldn't open file. \n");
}
fseek(fp, 0L, SEEK_END);
size_t sz = ftell(fp);
rewind(fp);
printf("file is %zu bytes long\n", sz);


ElfW(Ehdr) header;
read_elf64_header(fp, &header);
uint16_t pheadercount = header.e_phnum;
ElfW(Phdr) pheader[pheadercount];

    for (int i = 0; i < pheadercount; ++i) {
        read_program_header_table(fp,&pheader[i]);
    }

unsigned long leftover = sz-64-(56*pheadercount);
unsigned char buffer [leftover];
unsigned int accumulator = 0;
fread(buffer,1,leftover,fp);

    for (int i = 0; i < leftover; i++) {
        accumulator+=buffer[i];
        if (i %32 ==0){
            accumulator =0;
        }
    }

fclose(fp);
exit(0);
}
