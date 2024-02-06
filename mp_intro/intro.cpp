#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG image;

  image.readFromFile(inputFile);
  int width = image.width();
  int height = image.height();

  PNG image2(width,height);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      HSLAPixel & input = image.getPixel(i,j);
      HSLAPixel & output = image2.getPixel(width - i - 1, height - j - 1);
      output = input;
    }
  }
  image2.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  /*Meaning of this art
  I know this may sound like a joke and look bad but I actually appreciate this "noisy" type art.
  When I was younger I had a condition where I would occasionally get super fuzzy vision with random colors.
  I was able to get medical attention and get the problem fixed but I still sometimes miss being able to see
  the random colors. It is weirdly comforting which is why I chose to make this. I was messing around with hue values
  until it became something that resembled what I saw in my past.
  */
  for (unsigned int i = 0; i < width; i++) {
    for (unsigned int j = 0; j < height; j++) {
      if (i < 400) {
        HSLAPixel & pixel = png.getPixel(i,j);
        pixel.h = rand() % 184;
        pixel.s = 1;
        pixel.l = rand() & 2;
        pixel.a = 1;
      } else {
          HSLAPixel & pixel = png.getPixel(i,j);
          pixel.h = (rand() % 184) + 125;
          pixel.s = 1;
          pixel.l = rand() & 2;
          pixel.a = 1;
      }
      
    }
  }
  return png;
}
