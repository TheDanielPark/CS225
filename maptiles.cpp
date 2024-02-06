/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    if (theSource.getRows() == 0 || theSource.getColumns() == 0 || theTiles.empty()) {
        return NULL;
    } 
    map<Point<3>, int> temp;
    vector<Point<3>> tile;
    for (unsigned i = 0; i < theTiles.size(); i++) {
        Point<3> point = convertToXYZ(theTiles[i].getAverageColor());
        tile.push_back(point);
        temp[point] = i;
    }

    KDTree<3> avgColor(tile);

    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for (int x = 0; x < canvas->getRows(); x++) {
        for (int y = 0; y < canvas->getColumns(); y++) {
            Point<3> mark =  convertToXYZ(theSource.getRegionColor(x,y));
            Point<3> set = avgColor.findNearestNeighbor(mark);
            //TileImage * rightTile = temp[set];
            canvas->setTile(x,y, &theTiles[temp.at(set)]);
        }
    }
    return canvas;
}

