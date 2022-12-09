#include <stdio.h>
#include <stdlib.h>

#define _height 400
#define _width 400

static unsigned int pixels[_height][_width] = {0};

void fillImage();
void saveImageToDisk();

int main(void)
{
    saveImageToDisk();

    return 0;
};

void fillImage()
{
    for(size_t i = 0; i < _height; ++i)
    {
        for(size_t j = 0; j < _width; ++j)
        {
        };
    };
};

void saveImageToDisk()
{
    FILE *file;

    file = fopen("image.ppm", "w");

    if(file == NULL)
    {
        printf("Failed to open file.");
        exit(1);  
    };

    fclose(file);
};