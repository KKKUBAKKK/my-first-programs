#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, temp;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Calculating average value for pixel and assignig it to every colour
            temp = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtBlue = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    RGBTRIPLE temp;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width / 2; j++)
        {
            // Switching every pixel with the respective one from the other side
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    DWORD n, r, g, b;
    RGBTRIPLE temp[height][width];

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Adding the current pixel's values to temporary variables for each colour
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            // Setting n to 1 and adding to it every time to use later for counting average value
            n = 1;

            // Check if it's not the first line
            if (i != 0)
            {
                // Adding pixel above it
                r += image[i - 1][j].rgbtRed;
                g += image[i - 1][j].rgbtGreen;
                b += image[i - 1][j].rgbtBlue;
                n++;

                // If i is not the last line add pixel under it
                if (i != height - 1)
                {
                    r += image[i + 1][j].rgbtRed;
                    g += image[i + 1][j].rgbtGreen;
                    b += image[i + 1][j].rgbtBlue;
                    n++;
                }

                // If not on the right edge add next pixel from i and row above
                if (j != width - 1)
                {
                    r += image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    g += image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    b += image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    n += 2;

                    // If not the last row add pixel under and to the right
                    if (i != height - 1)
                    {
                        r += image[i + 1][j + 1].rgbtRed;
                        g += image[i + 1][j + 1].rgbtGreen;
                        b += image[i + 1][j + 1].rgbtBlue;
                        n++;
                    }
                }

                // If not on the left edge add previous pixel from i and row above
                if (j != 0)
                {
                    r += image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed;
                    g += image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                    b += image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
                    n += 2;

                    // If not in the last row add pixel from row below to the left
                    if (i != height - 1)
                    {
                        r += image[i + 1][j - 1].rgbtRed;
                        g += image[i + 1][j - 1].rgbtGreen;
                        b += image[i + 1][j - 1].rgbtBlue;
                        n++;
                    }
                }
            }
            // If it's the first row
            else
            {
                // Add pixel below if not last row
                if (i != height - 1)
                {
                    r += image[i + 1][j].rgbtRed;
                    g += image[i + 1][j].rgbtGreen;
                    b += image[i + 1][j].rgbtBlue;
                    n++;
                }

                // Check if not the right edge and if not add next pixel
                if (j != width - 1)
                {
                    r += image[i][j + 1].rgbtRed;
                    g += image[i][j + 1].rgbtGreen;
                    b += image[i][j + 1].rgbtBlue;
                    n++;

                    // If not the last row add next pixel from next row
                    if (i != height - 1)
                    {
                        r += image[i + 1][j + 1].rgbtRed;
                        g += image[i + 1][j + 1].rgbtGreen;
                        b += image[i + 1][j + 1].rgbtBlue;
                        n++;
                    }
                }

                // Check if not the left edge and if not add previous pixel
                if (j != 0)
                {
                    r += image[i][j - 1].rgbtRed;
                    g += image[i][j - 1].rgbtGreen;
                    b += image[i][j - 1].rgbtBlue;
                    n++;

                    // If not the last row add previous pixel from next row
                    if (i != height - 1)
                    {
                        r += image[i + 1][j - 1].rgbtRed;
                        g += image[i + 1][j - 1].rgbtGreen;
                        b += image[i + 1][j - 1].rgbtBlue;
                        n++;
                    }
                }
            }
            // Calculate the average value for each colour, round it and save in temp
            temp[i][j].rgbtRed = round((float) r / n);
            temp[i][j].rgbtGreen = round((float) g / n);
            temp[i][j].rgbtBlue = round((float) b / n);
        }
    }

    // Write new image from temp to image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    LONG rx = 0, gx = 0, bx = 0, ry = 0, gy = 0, by = 0, red, green, blue;
    RGBTRIPLE temp[height][width];

    // Run for every pixel
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Set values to 0
            rx = 0;
            ry = 0;
            gx = 0;
            gy = 0;
            bx = 0;
            by = 0;

            // Check if not the first row
            if (i != 0)
            {
                // Add values from pixel above
                ry += - 2 * image[i - 1][j].rgbtRed;
                gy += - 2 * image[i - 1][j].rgbtGreen;
                by += - 2 * image[i - 1][j].rgbtBlue;

                // If not the last row add values from pixel below
                if (i != height - 1)
                {
                    ry += 2 * image[i + 1][j].rgbtRed;
                    gy += 2 * image[i + 1][j].rgbtGreen;
                    by += 2 * image[i + 1][j].rgbtBlue;
                }

                // Check if not on the left edge
                if (j != 0)
                {
                    // Add values from i and above row from pixels to the left to both Gx and Gy
                    rx += - image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed;
                    gx += - image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen;
                    bx += - image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue;

                    ry += - image[i - 1][j - 1].rgbtRed;
                    gy += - image[i - 1][j - 1].rgbtGreen;
                    by += - image[i - 1][j - 1].rgbtBlue;


                    // If not the last row do the same with pixels below
                    if (i != height - 1)
                    {
                        rx += - image[i + 1][j - 1].rgbtRed;
                        gx += - image[i + 1][j - 1].rgbtGreen;
                        bx += - image[i + 1][j - 1].rgbtBlue;

                        ry += image[i + 1][j - 1].rgbtRed;
                        gy += image[i + 1][j - 1].rgbtGreen;
                        by += image[i + 1][j - 1].rgbtBlue;
                    }
                }

                // Check if not on the right edge
                if (j != width - 1)
                {
                    // Add values from i and above row from pixels to the right to both Gx and Gy
                    rx += image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed;
                    gx += image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen;
                    bx += image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue;

                    ry += - image[i - 1][j + 1].rgbtRed;
                    gy += - image[i - 1][j + 1].rgbtGreen;
                    by += - image[i - 1][j + 1].rgbtBlue;

                    // If not the last row do the same with pixels below
                    if (i != height - 1)
                    {
                        rx += image[i + 1][j + 1].rgbtRed;
                        gx += image[i + 1][j + 1].rgbtGreen;
                        bx += image[i + 1][j + 1].rgbtBlue;

                        ry += image[i + 1][j + 1].rgbtRed;
                        gy += image[i + 1][j + 1].rgbtGreen;
                        by += image[i + 1][j + 1].rgbtBlue;
                    }
                }
            }
            // If the first row
            else
            {
                // If not also the last row add values from pixel below
                if (i != height - 1)
                {
                    ry += 2 * image[i + 1][j].rgbtRed;
                    gy += 2 * image[i + 1][j].rgbtGreen;
                    by += 2 * image[i + 1][j].rgbtBlue;
                }

                // Check if not on the left edge
                if (j != 0)
                {
                    // Add values from pixel to the left
                    rx += - 2 * image[i][j - 1].rgbtRed;
                    gx += - 2 * image[i][j - 1].rgbtGreen;
                    bx += - 2 * image[i][j - 1].rgbtBlue;

                    // If not the last row do the same with pixels below
                    if (i != height - 1)
                    {
                        rx += - image[i + 1][j - 1].rgbtRed;
                        gx += - image[i + 1][j - 1].rgbtGreen;
                        bx += - image[i + 1][j - 1].rgbtBlue;

                        ry += image[i + 1][j - 1].rgbtRed;
                        gy += image[i + 1][j - 1].rgbtGreen;
                        by += image[i + 1][j - 1].rgbtBlue;
                    }
                }

                // Check if not on the rigth edge
                if (j != width - 1)
                {
                    // Add values from pixel to the right
                    rx += 2 * image[i][j + 1].rgbtRed;
                    gx += 2 * image[i][j + 1].rgbtGreen;
                    bx += 2 * image[i][j + 1].rgbtBlue;

                    // If not the last row do the same for pixels below
                    if (i != height - 1)
                    {
                        rx += image[i + 1][j + 1].rgbtRed;
                        gx += image[i + 1][j + 1].rgbtGreen;
                        bx += image[i + 1][j + 1].rgbtBlue;

                        ry += image[i + 1][j + 1].rgbtRed;
                        gy += image[i + 1][j + 1].rgbtGreen;
                        by += image[i + 1][j + 1].rgbtBlue;
                    }
                }
            }

            // Calculate value for each colour
            red = round((float)sqrt(pow(rx, 2) + pow(ry, 2)));
            green = round((float)sqrt(pow(gx, 2) + pow(gy, 2)));
            blue = round((float)sqrt(pow(bx, 2) + pow(by, 2)));

            // Check if it's not to big, if so change it to 255, then add to temp
            if (red > 255)
            {
                red = 255;
            }
            temp[i][j].rgbtRed = red;

            if (green > 255)
            {
                green = 255;
            }
            temp[i][j].rgbtGreen = green;

            if (blue > 255)
            {
                blue = 255;
            }
            temp[i][j].rgbtBlue = blue;
        }
    }

    // Write values from temp to image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
