#include <stdio.h>
#include <stdlib.h>

#define _height 400
#define _width 400

static unsigned int pixelColors[_height][_width] = {0};

void fillImage(unsigned int hexVal);
void saveImageToDisk();

int main(void)
{
    fillImage(0xFF0000);
    saveImageToDisk();
    return 0;
};

void fillImage(unsigned int hexVal)
{
    for(size_t i = 0; i < _height; ++i)
    {
        for(size_t j = 0; j < _width; ++j)
        {
            pixelColors[i][j] = hexVal;
        };
    };
};

void saveImageToDisk()
{
    FILE *file = fopen("image.ppm", "wb");
    fprintf(file, "P6\n");
    fprintf(file, "%d %d\n", _width, _height);
    fprintf(file, "255\n");

    for(size_t i = 0; i < _height; ++i)
    {
        for(size_t j = 0; j < _width; ++j)
        {
            unsigned int currPixel = pixelColors[i][j];
            
            unsigned char pixelInfo[3] = 
            {
                (currPixel>>8*0) & 0xFF,
                (currPixel>>8*1) & 0xFF,
                (currPixel>>8*2) & 0xFF,
            };

            fwrite(pixelInfo, sizeof(pixelInfo), 1, file);
        };
    };

    fclose(file);
};