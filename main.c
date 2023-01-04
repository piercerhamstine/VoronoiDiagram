#include <stdio.h>
#include <stdlib.h>

#define _height 500
#define _width 500
#define _seedcount 15

typedef unsigned int Color;
enum BasicColors
{
    BLACK = 0x000000,
    RED = 0x0000FF,
    GREEN = 0x00FF00,
    BLUE = 0xFF0000
};

struct Seed
{
    int x;
    int y;
}typedef Seed;

static unsigned int pixelColors[_height][_width] = {0};
static Seed seeds[_seedcount];

void setPixel(int x, int y, Color color);
void fillImage(unsigned int hexVal);
void saveImageToDisk();
void bresenhamMidPointCircle();

int main(void)
{
    fillImage(BLACK);
    bresenhamMidPointCircle(100, 100, 10, 0, GREEN);
    saveImageToDisk();
    return 0;
};

void drawOctants(int xi, int yi, int x, int y, Color color)
{
    setPixel(xi+x, yi+y, color);
    setPixel(xi+x, yi-y, color);
    setPixel(xi+y, yi+x, color);
    setPixel(xi+y, yi-x, color);

    setPixel(xi-x, yi+y, color);
    setPixel(xi-x, yi-y, color);
    setPixel(xi-y, yi+x, color);
    setPixel(xi-y, yi-x, color);
};

void fillOctants(int xi, int yi, int x, int y, Color color)
{
    for(int i = xi-x; i < xi+x; i++)
    {
        setPixel(i, yi+y, color);
        setPixel(i, yi-y, color);
    };

    for(int i = yi-y; i < yi+y; i++)
    {
        setPixel(i, yi+x, color);
        setPixel(i, yi-x, color);
    };
};

void bresenhamMidPointCircle(int xi, int yi, int radius, int fill, Color color)
{
    if(radius <= 0)
    {
        pixelColors[xi][yi] = color;
        return;
    };

    int x = 0;
    int y = radius;
    int distance = 3-(2*radius);

    while(x <= y)
    {
        if(fill>0)
            fillOctants(xi, yi, x, y, color);
        else
            drawOctants(xi, yi, x, y, color);

        // Outside circle, choose pixel that is over and down to stay within the circle.
        if(distance > 0)
        {
            y--;
            distance = distance+(4*x)-(4*y)+10;
        }
        else
        {
            distance = distance+4*x+6;
        };
        x++;
    };
};

void setPixel(int x, int y, Color color)
{
    pixelColors[y][x] = color;
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