#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;


//Darken an Image by decreasing the luminance of every pixel by 0.1
//This function ensures that the luminance remains in the range [0,1]
void Image::darken() {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.l = pixel.l - 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

//Darken an Image by cecreasing the luminance of every pixel by amount
//This function ensures that the luminance remains in the range [0,1]
void Image::darken (double amount) {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.l = pixel.l - amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

//Desaturates an image by decreasing the saturation of every pixel by 0.1
//This function ensures that the saturation remains in the range [0,1]
void Image::desaturate() {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.s = pixel.s - 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

//Desaturates an image by decreasing the saturation of every pixel by amount
//This function ensures that the saturation remains in the range [0,1]
void Image:: desaturate(double amount) {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.s = pixel.s - amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

//Turns the image grayscale
void Image::grayscale() {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.s = 0;
            
        }
    }
}

//Illinify the image
void Image::illinify() {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
      for (int j = 0; j < height1; j++) {
        HSLAPixel & pixel = getPixel(i,j);
        if (pixel.h < 113 || pixel.h > 294) {
            pixel.h = 11;
        } else {
            pixel.h = 216;
        }
      }
    }
}

//Lighten an Image by increasing the luminance of every pixel by 0.1
//This function ensures that the luminance remains in the range [0,1]
void Image::lighten() {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.l = pixel.l + 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

//Lighten an Image by increasing the luminance of every pixel by amount
//This function ensures that the luminance remains in the range [0,1]
void Image::lighten(double amount) {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.l = pixel.l + amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

//Rotates the color wheel by degrees
//Rotating in a positive direction increases the degree of the hue. 
//This function ensures that the hue remains in the range [0,360]
void Image::rotateColor(double degrees) {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.h = pixel.h + degrees;
            if (pixel.h > 360) {
                pixel.h = pixel.h - 360;
            } else if (pixel.h < 0) {
                pixel.h = pixel.h + 360;
            }
        }
    }
}

//Saturates an Image by increasing the saturation of every pixel by 0.1
//This function ensures that the saturation remains in the range [0,1]
void Image::saturate() {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.s = pixel.s + 0.1;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}

//Saturates an Image by increasing the saturation of every pixel by amount
//This function ensures that the saturation remains in the range [0,1]
void Image::saturate(double amount) {
    int width1 = width();
    int height1 = height();

    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            pixel.s = pixel.s + amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}

//Scale the image by a given factor
//This function both resizes the Image and scales the contents
void Image::scale(double factor) {
    int width1 = width() * factor;
    int height1 = height() * factor;

    
    Image * oldImage = new Image();
    * oldImage = * this;
    
    resize(width1, height1);
    for (int i = 0; i < width1; i++) {
        for (int j = 0; j < height1; j++) {
            HSLAPixel & pixel = getPixel(i,j);
            HSLAPixel & oldPixel = oldImage->getPixel((i / factor), (j / factor));
            pixel = oldPixel;
           // cout << "hi" << endl;
        }
    }
    delete oldImage;
}

//Scales the image to fit within the size (w x h) 
//This function both resizes the Image and scales the contents
void Image::scale(unsigned w, unsigned h) {
    double widthScaled =  w / width();
    double heightScaled =  h / height();
    

    if (widthScaled > heightScaled) {
        scale(heightScaled);
    } else {
        scale(widthScaled);
    }
}



