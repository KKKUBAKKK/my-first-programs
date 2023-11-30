#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    FILE *input, *img;
    unsigned char buffer[512] = "0";
    char name[8];
    int i = -1;

    // Check if there is 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the input file
    input = fopen(argv[1], "r");

    // Loop as long as you didn't reach the end of the file
    while (fread(buffer, sizeof(char), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // Check if it's the start of an image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it's the first image set i to 0
            if (i < 0)
            {
                i = 0;
            }

            // If not the first image first close previous image
            if (i != 0)
            {
                fclose(img);
            }

            // Update name
            sprintf(name, "%03i.jpg", i);

            // Create new image
            img = fopen(name, "w");

            // Write to new image
            fwrite(buffer, 512 * sizeof(char), 1, img);

            i++;
        }
        // If not start of new image and there is an image open write to it
        else if (i >= 0)
        {
            fwrite(buffer, 512 * sizeof(char), 1, img);
        }
    }

    // Close all open files
    fclose(img);
    fclose(input);

    return 0;
}
