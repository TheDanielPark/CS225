#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image butler, murray, kyrie, kobe, i;
  kobe.readFromFile("kobe.png");
  murray.readFromFile("murray1.png");
  butler.readFromFile("butler1.png");
  butler.scale(1.3);
  kyrie.readFromFile("kyrie1.png");
  kyrie.scale(.8);
  i.readFromFile("i.png");

  StickerSheet finalImage(kobe, 5);
  finalImage.addSticker(butler, 40, 50);
  finalImage.addSticker(kyrie, 1800, 400);
  finalImage.addSticker(i, 2100, 100);
  finalImage.addSticker(murray, 40, 400);

  Image myImage = finalImage.render();
  myImage.writeToFile("myImage.png");

  return 0;
}
