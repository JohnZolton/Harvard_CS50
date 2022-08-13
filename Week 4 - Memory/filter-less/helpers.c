#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //take the average of the RGB values 0 = black, 255 = white
    //BMP stores triples backwards (BGR)
    RGBTRIPLE new[height][width];
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int x = round(((float)red + (float)green + (float)blue)/3.0);
            image[i][j].rgbtRed = x;
            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new[height][width];
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            int red = image[i][j].rgbtRed;
            int blue =image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            int sepia_red = round(.393*red + .769*green + .189*blue);
            if (sepia_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed= sepia_red;
            }
            // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            int sepia_green = round(.349*red + .686*green + .168*blue);
            if (sepia_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepia_green;
            }
            // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            int sepia_blue = round(.272*red + .534*green + .131*blue);
            if (sepia_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepia_blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE placeholder[height][width];
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<(width/2); j++)
        {
            //reflecting the left half of the image
            //store left half to copy to right half
            placeholder[i][j].rgbtRed = image[i][j].rgbtRed;
            placeholder[i][j].rgbtBlue = image[i][j].rgbtBlue;
            placeholder[i][j].rgbtGreen = image[i][j].rgbtGreen;
            //store right half into left half
            image[i][j].rgbtRed = image[i][width-j-1].rgbtRed;
            image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width-j-1].rgbtGreen;
            // store left half into right half
            image[i][width -j -1].rgbtRed = placeholder[i][j].rgbtRed;
            image[i][width - j -1].rgbtBlue = placeholder[i][j].rgbtBlue;
            image[i][width - j -1].rgbtGreen = placeholder[i][j].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new[height][width];

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            // box blur, each pixel becomes the average of the 3x3 pixels around and including itself
            float counter = 0.0;
            float total_red = 0;
            float total_blue=0;
            float total_green =0;
            //cycle through neighboring pixels
            for (int k =-1; k<2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    //check for valid pixels
                    if (i + k < 0 || i+ k > (height-1) || j + h < 0 || j + h > (width-1))
                    {
                        continue; //skip if out of bounds
                    }
                    total_red = total_red + image[i + k][j + h].rgbtRed;
                    total_blue = total_blue + image[i + k][j + h].rgbtBlue;
                    total_green = total_green + image[i+ k][j+ h].rgbtGreen;
                    counter = counter+1.0;
                }

            }
            new[i][j].rgbtRed = round(total_red/counter);
            new[i][j].rgbtBlue = round(total_blue/counter);
            new[i][j].rgbtGreen = round(total_green/counter);
        }
    }
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            image[i][j].rgbtRed=new[i][j].rgbtRed;
            image[i][j].rgbtBlue=new[i][j].rgbtBlue;
            image[i][j].rgbtGreen=new[i][j].rgbtGreen;
        }
    }
    return;
}
