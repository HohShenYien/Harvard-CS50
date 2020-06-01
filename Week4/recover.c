#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //checking if there's two arguments
    if (argc != 2)
    {
        printf("Please give 2 arguments\n");
        return 1;
    }
    // Opening file
    FILE *file = fopen(argv[1], "r");
    // Checking if the file can be opened
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    // 7 char + 1 \0
    char title[8];
    uint8_t buffer[512];
    int count = 0;
    FILE *img = NULL;
    while (true)
    {
        // read a block of the memory card image
        size_t bytesRead = fread(buffer, sizeof(uint8_t), 512, file);

        // break out of the loop when we reach the end of the card image
        if (bytesRead == 0 && feof(file))
        {
            break;
        }
        // Checking if the header of the buffer has jpg style
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        
        if (containsJpegHeader && img != NULL)
        {
            // Close the img file since a new jpg file is incoming
            fclose(img);
            count++;
        }
        if (containsJpegHeader)
        {
            // Open a new img file
            sprintf(title, "%03i.jpg", count);
            img = fopen(title, "w");
        }
        if (img != NULL)
        {
            // Writes on the img file
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }

    }
    // Closing the files
    fclose(img);
    fclose(file);
}
