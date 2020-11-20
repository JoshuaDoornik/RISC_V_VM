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
ElfW(Phdr) pheader[pheadercount];
ElfW(Phdr) text_pheader;
    for (int i = 0; i < pheadercount; ++i) {
        read_program_header_table(fp,&pheader[i]);
        check_pheader_type(&pheader[i]);

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
