#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // check for no of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open the image to be recovered
    FILE *card = fopen(argv[1], "r");
    // check if file could be opened
    if (card == NULL)
    {
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    }

    uint8_t buffer[512];
    char image[8];
    int i = 0;
    sprintf(image, "%03i.jpg", i);
    FILE *currentImg = fopen(image, "w");
    while (fread(buffer, sizeof(uint8_t), 512, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (i == 0)
            {
                fwrite(buffer, sizeof(uint8_t), 512, currentImg);
                i++;
            }
            else if (i > 0)
            {
                fclose(currentImg);
                sprintf(image, "%03i.jpg", i);
                currentImg = fopen(image, "w");
                fwrite(buffer, sizeof(uint8_t), 512, currentImg);
                i++;
            }
        }
        else if (i > 0)
        {
            fwrite(buffer, sizeof(uint8_t), 512, currentImg);
        }

    }
    fclose(currentImg);
    currentImg = NULL;
    fclose(card);
    card = NULL;
    return 0;
}