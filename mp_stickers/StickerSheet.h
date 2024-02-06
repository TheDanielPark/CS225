/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"



class StickerSheet {
    public:

    //Initializes this StickerSheet with a deep copy of the base picture and the 
    //ability to hold a max number of stickers with indices 0 thru max-1
    StickerSheet(const Image & picture, unsigned max);

    //Frees all space that was allocated
    ~StickerSheet();

    //The copy constructor makes an independent copy
    StickerSheet(const StickerSheet & other);
    
    //Adds a sticker to the StickerSheet so that the top left of the sticker is at (x,y)
    int addSticker(Image & sticker, unsigned x, unsigned y);

    //Modifies the max number of stickers that can be stored without changing existing indices
    //if the new max is smaller than current number of stickers, stickers above max-1 will be lost
    void changeMaxStickers(unsigned max);

    //returns a pointer to the sticker at the index
    //user can modify the image, return NULL if index invalid
    Image * getSticker(unsigned index);

    //Assignment operator for the StickerSheet class
    const StickerSheet & operator=(const StickerSheet & other);

    //Removes the sticker at the given zero based layer index
    void removeSticker(unsigned index);

    // Renders the whole StickerSheet on one image and returns the image
    Image render() const ;

    //Changes the x and y coordinates of the Image in the specified layer
    bool translate (unsigned index, unsigned x, unsigned y);
    
    void Clear();
    
    private: 

    Image backgroundImage;
    Image ** stickers;
    unsigned int * coordX;
    unsigned int * coordY;
    unsigned numStickers;
    unsigned stickersMax;


};
