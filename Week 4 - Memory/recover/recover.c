#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check for proper arguments
    if (argc != 2)
    {
        printf("error, only one file please\n");
        return 1;
    }
    //check that file opens
    if (!argv)
    {
        printf("error, couldn't open file\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    FILE *new_file = NULL;
    BYTE buffer[512];

    int pic_counter = 0;
    char filename[8];
    //reads every 512-byte block in a file
    while (fread(buffer, sizeof(char), 512, file))
    {
        //search for jpg signature
        if (buffer[0] == 0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                //close new jpg file if there's one open
                if (!(pic_counter ==0))
                {
                    fclose(new_file);
                }
            // read into new file named "00X.jpg"
                sprintf(filename, "%03i.jpg", pic_counter);
                new_file = fopen(filename, "w");
                pic_counter++;
            }
            if (!(pic_counter==0))
                {
                    fwrite(buffer, sizeof(char), 512, new_file);
                }
    }
    fclose(new_file);
    fclose(file);
    return 0;
}