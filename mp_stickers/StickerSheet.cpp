#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <iostream>

using namespace cs225;

//Initializes this StickerSheet with a deep copy of the base picture and the 
//ability to hold a max number of stickers with indices 0 thru max-1
StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    backgroundImage = Image(picture);
    stickersMax = max;
    stickers = new Image * [stickersMax];
    coordX = new unsigned int [stickersMax];
    coordY = new unsigned int [stickersMax];
    numStickers = 0;

    for (unsigned i = 0; i < stickersMax; i++) {
        stickers[i] = NULL;
    }
}

//Frees all space that was allocated
StickerSheet::~StickerSheet() {
    Clear();
    
}

void StickerSheet::Clear(){ 
    delete[] coordX;
    coordX = NULL;
    delete[] coordY;
    coordY = NULL;
    //delete stickers[];
    delete[] stickers;
    stickers = NULL;
    

}

//The copy constructor makes an independent copy
StickerSheet::StickerSheet(const StickerSheet & other) {
    stickersMax = other.stickersMax;
    numStickers = other.numStickers;
    backgroundImage = Image(other.backgroundImage);
    coordX = new unsigned int [stickersMax];
    coordY = new unsigned int [stickersMax];
    stickers = new Image * [stickersMax];
    for (unsigned i = 0; i < stickersMax; i++) {
        stickers[i] = other.stickers[i];
        coordX[i] = other.coordX[i];
        coordY[i] = other.coordY[i];
    }


}

//Adds a sticker to the StickerSheet so that the top left of the sticker is at (x,y)
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    if (numStickers < stickersMax) {
        coordX[numStickers] = x;
        coordY[numStickers] = y;
        stickers[numStickers] = & (sticker);
        numStickers++;
        return numStickers;
    }
    
    return -1;
}

//Modifies the max number of stickers that can be stored without changing existing indices
//if the new max is smaller than current number of stickers, stickers above max-1 will be lost
void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == stickersMax) {
        return;
    }

    //stickersMax = max;

    Image ** newStickers = new Image * [max];
    unsigned int * newCoordX = new unsigned int [max];
    unsigned int * newCoordY = new unsigned int [max];

    /*
    for (unsigned i = 0; i < max; i++) {
        newStickers[i] = stickers[i];
        newCoordX[i] = coordX[i];
        newCoordY[i] = coordY[i];
    } */
    
    if (max > stickersMax) {
        for (unsigned i = 0; i < stickersMax; i++) {
           /* stickers[i] = newStickers[i];
            coordX[i] = newCoordX[i];
            coordY[i] = newCoordY[i]; */
            newStickers[i] = stickers[i];
            newCoordX[i] = coordX[i];
            newCoordY[i] = coordY[i];
            //std::cout << "hello" << std::endl;
        }
        //std::cout << "hello" << std::endl;
        for (unsigned j = stickersMax; j < max; j++) {
            newStickers[j] = NULL; 
            //std::cout << "hello" << std::endl;

        }
    }
    //std::cout << "hello" << std::endl;
    if (max < stickersMax) {
        if (numStickers > max) {
            numStickers = max;
            //std::cout << "hello" << std::endl;
        }
        //std::cout << "hello" << std::endl;
        for (unsigned i = max; i < stickersMax; i++) {
            //delete stickers[i];
            stickers[i] = NULL;
            //std::cout << "hello" << std::endl;

        }
        stickersMax = max;
        for (unsigned i = 0; i < stickersMax; i++) {
            newStickers[i] = stickers[i];
            newCoordX[i] = coordX[i];
            newCoordY[i] = coordY[i];
        }
        for (unsigned i = 0; i < stickersMax; i++) {
            stickers[i] = newStickers[i];
            coordX[i] = newCoordX[i];
            coordY[i] = newCoordY[i];
        }
    }
    delete[] stickers;
    stickers = newStickers;
    delete[] coordX;
    coordX = newCoordX;
    delete[] coordY;
    coordY = newCoordY;

    
    stickersMax = max;
   /* stickers = newStickers;
    coordX = newCoordX;
    coordY = newCoordY; */
    
   /* delete[] stickers;
    delete[] coordX;
    delete[] coordY; 
    //delete stickers[stickersMax];
    
    stickers = newStickers;
    coordX = newCoordX;
    coordY = newCoordY;
    */
    //delete stickers[stickersMax];
    /*
    stickers = new Image * [max];
    coordX = new unsigned int [max];
    coordY = new unsigned int [max];

    stickers = newStickers;
    coordX = newCoordX;
    coordY = newCoordY;

    if (max > stickersMax) {
        for (unsigned i = 0; i < max; i++) {
            stickers[i] = newStickers[i];
            coordX[i] = newCoordX[i];
            coordY[i] = newCoordY[i];
        }
    }
    if (max < stickersMax) {
        for (unsigned i = max; i < stickersMax; i++) {
            delete stickers[i];
            stickers[i] = NULL;
        }
        stickersMax = max;
        for (unsigned i = 0; i < stickersMax; i++) {
            stickers[i] = newStickers[i];
            coordX[i] = newCoordX[i];
            coordY[i] = newCoordY[i];
        }
    }
    stickersMax = max;
    delete[] newStickers;
    delete[] newCoordX;
    delete[] newCoordY;
    */
}

//returns a pointer to the sticker at the index
//user can modify the image, return NULL if index invalid
Image * StickerSheet::getSticker(unsigned index) {
    if (index >= numStickers) {
        return NULL;
    }
    return stickers[index];
}

//Assignment operator for the StickerSheet class
const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this != &other) {
        Clear();
        stickersMax = other.stickersMax;
        numStickers = other.numStickers;
        backgroundImage = Image(other.backgroundImage);
        coordX = new unsigned int [stickersMax];
        coordY = new unsigned int [stickersMax];
        stickers = new Image * [stickersMax];
        for (unsigned i = 0; i < stickersMax; i++) {
            stickers[i] = other.stickers[i];
            coordX[i] = other.coordX[i];
            coordY[i] = other.coordY[i];
        }
    }
    return *this;
}

//Removes the sticker at the given zero based layer index
void StickerSheet::removeSticker(unsigned index) {
    if (index < numStickers) {
        coordX[index] = 0;
        coordY[index] = 0;
        stickers[index] = NULL;
        //delete stickers[index];
        numStickers--;
        //std::cout << "hello" << std::endl;
    }
}

// Renders the whole StickerSheet on one image and returns the image
Image StickerSheet::render() const {
    Image finished = Image(backgroundImage);
    
    for (unsigned i = 0; i < stickersMax; i++) {
        if (stickers[i] != NULL) {
            unsigned pixelWidth = stickers[i]->width();
            unsigned pixelHeight = stickers[i]->height();
            //std::cout << "hello" << std::endl;
            if ((pixelHeight + coordY[i]) > finished.height()) {
                finished.resize(finished.width() , (pixelHeight + coordY[i]));
            } else if ((pixelWidth + coordX[i]) > finished.width()) {
                finished.resize((pixelWidth + coordX[i]) , finished.height());
            }

            for (unsigned k = 0; k < pixelWidth; k++) {
                for (unsigned j = 0; j < pixelHeight; j++) {
                    HSLAPixel & finishedPixel = finished.getPixel((k + coordX[i]), (j + coordY[i]));
                    HSLAPixel & stickerPixel = stickers[i]->getPixel(k,j);
                    if (stickerPixel.a == 0) {
                        continue;
                    } else {
                        finishedPixel = stickerPixel;
                    }
                }
            }
        }
        

    }
    //finished.writeToFile("blah.PNG");
    return finished;
    
}

//Changes the x and y coordinates of the Image in the specified layer
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index >= numStickers) {
        return false;
    }
    coordX[index] = x;
    coordY[index] = y;
    return true;
}





