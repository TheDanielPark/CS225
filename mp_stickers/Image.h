/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;


    class Image : public PNG {
        public:

        //Lighten an Image by increasing the luminance of every pixel by 0.1
        //This function ensures that the luminance remains in the range [0,1]
        void lighten();

        //Lighten an Image by increasing the luminance of every pixel by amount
        //This function ensures that the luminance remains in the range [0,1]
        void lighten(double amount);

        //Darken an Image by decreasing the luminance of every pixel by 0.1
        //This function ensures that the luminance remains in the range [0,1]   
        void darken();

        //Darken an Image by cecreasing the luminance of every pixel by amount
        //This function ensures that the luminance remains in the range [0,1]
        void darken(double amount);

        //Saturates an Image by increasing the saturation of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void saturate();

        //Saturates an Image by increasing the saturation of every pixel by amount
        //This function ensures that the saturation remains in the range [0,1]
        void saturate(double amount);

        //Desaturates an image by decreasing the saturation of every pixel by 0.1
        //This function ensures that the saturation remains in the range [0,1]
        void desaturate();

        //Desaturates an image by decreasing the saturation of every pixel by amount
        //This function ensures that the saturation remains in the range [0,1]
        void desaturate(double amount);

        //Turns the image grayscale
        void grayscale();

        //Rotates the color wheel by degrees
        //Rotating in a positive direction increases the degree of the hue. 
        //This function ensures that the hue remains in the range [0,360]
        void rotateColor(double degrees);

        //Illinify the image
        void illinify();

        //Scale the image by a given factor
        //This function both resizes the Image and scales the contents
        void scale(double factor);

        //Scales the image to fit within the size (w x h) 
        //This function both resizes the Image and scales the contents
        void scale(unsigned w, unsigned h);
    };


