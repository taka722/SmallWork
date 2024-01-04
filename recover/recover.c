#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover forensic_image\n");
        return 1;
    }
    // open file　for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    FILE *img = NULL;
    int cnt = 0;
    char filename[8];

    // read the image 512 byte at time
    while (fread(buffer, 512, 1, file))
    {
        // check for jpeg signeture
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close to the current file if its open
            if (img != NULL)
            {
                fclose(img);
            }
            // create new jpeg file
            sprintf(filename, "%03i.jpg", cnt);
            img = fopen(filename, "w");
            // cnt++;
            if (img == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(file);
                return 1;
                // fwrite(buffer, 512, 1, img);
            }
            cnt++;
        }
        // write to the jpeg file if it opens.
        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    // close open files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(file);
    return 0;
}