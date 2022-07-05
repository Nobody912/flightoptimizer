#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "MapProjection.h"

using cs225::HSLAPixel;

MapProjection::MapProjection()
{
    image.readFromFile("flightpath.png");
    originLabel.readFromFile("originicon.png");
    destinationLabel.readFromFile("destinationicon.png");
    stateCoordinates["AL"] = {1130, 745};
    stateCoordinates["AK"] = {445, 845};
    stateCoordinates["AZ"] = {550, 680};
    stateCoordinates["AR"] = {995, 695};
    stateCoordinates["CA"] = {380, 580};
    stateCoordinates["CO"] = {700, 570};
    stateCoordinates["CT"] = {1402, 443};
    stateCoordinates["DE"] = {1360, 535};
    stateCoordinates["FL"] = {1260, 835};
    stateCoordinates["GA"] = {1120, 740};
    stateCoordinates["HI"] = {685, 930};
    stateCoordinates["ID"] = {530, 395};
    stateCoordinates["IL"] = {1060, 545};
    stateCoordinates["IN"] = {1125, 535};
    stateCoordinates["IA"] = {965, 490};
    stateCoordinates["KS"] = {860, 595};
    stateCoordinates["KY"] = {1160, 605};
    stateCoordinates["LA"] = {995, 800};
    stateCoordinates["ME"] = {1445, 320};
    stateCoordinates["MD"] = {1325, 525};
    stateCoordinates["MA"] = {1410, 420};
    stateCoordinates["MI"] = {1140, 440};
    stateCoordinates["MN"] = {940, 380};
    stateCoordinates["MS"] = {1060, 745};
    stateCoordinates["MO"] = {990, 595};
    stateCoordinates["MT"] = {645, 330};
    stateCoordinates["NE"] = {830, 500};
    stateCoordinates["NV"] = {465, 515};
    stateCoordinates["NH"] = {1410, 380};
    stateCoordinates["NJ"] = {1370, 495};
    stateCoordinates["NM"] = {680, 690};
    stateCoordinates["NY"] = {1350, 420};
    stateCoordinates["NC"] = {1300, 645};
    stateCoordinates["ND"] = {840, 430};
    stateCoordinates["OH"] = {1200, 525};
    stateCoordinates["OK"] = {880, 680};
    stateCoordinates["OR"] = {500, 515};
    stateCoordinates["PA"] = {1250, 545};
    stateCoordinates["RI"] = {1410, 320};
    stateCoordinates["SC"] = {1300, 645};
    stateCoordinates["SD"] = {840, 430};
    stateCoordinates["TN"] = {1060, 745};
    stateCoordinates["TX"] = {835, 790};
    stateCoordinates["UT"] = {530, 395};
    stateCoordinates["VT"] = {1410, 380};
    stateCoordinates["VA"] = {1300, 645};
    stateCoordinates["WA"] = {500, 515};
    stateCoordinates["WV"] = {1300, 645};
    stateCoordinates["WI"] = {940, 380};
    stateCoordinates["WY"] = {645, 330};
}


void MapProjection::floodFill(std::string state, double hue, double saturation, double lightness) {
    std::pair<int, int> stateCoord = getStateCoord(state);
    HSLAPixel & pixel = image.getPixel(stateCoord.first, stateCoord.second);
    floodFillHelper(stateCoord, hue, saturation, lightness);
}

void MapProjection::floodFillHelper(std::pair<int, int> coord, double hue, double saturation, double lightness) {
    if (coord.first < 0 || coord.first >= (int)image.width() || coord.second < 0 || coord.second >= (int)image.height()) {
        std::cout << "illegal size: " << coord.first << " " << coord.second << std::endl;
        return;
    }

    HSLAPixel & pixel = image.getPixel(coord.first, coord.second);

    // quick rounding
    int left = int(pixel.l * 1000) % 10;
    if (left >= 5)
        pixel.l = std::ceil(pixel.l * 100.00) / 100.00;
    else
        pixel.l = std::floor(pixel.l * 100.0) / 100.00;

    if (pixel.h == hue && pixel.s == saturation && pixel.l == lightness) {;
        return;
    }

    if (!(pixel.h == 0.0 && pixel.s == 0.0 && pixel.l == 0.80)) {
        return;
    }
    else {
        pixel.h = hue;
        pixel.s = saturation;
        pixel.l = lightness;
    }
    
    floodFillHelper(std::make_pair(coord.first + 1, coord.second), hue, saturation, lightness);
    floodFillHelper(std::make_pair(coord.first - 1, coord.second), hue, saturation, lightness);
    floodFillHelper(std::make_pair(coord.first, coord.second + 1), hue, saturation, lightness);
    floodFillHelper(std::make_pair(coord.first, coord.second - 1), hue, saturation, lightness);
}

void MapProjection::drawLine(std::string origin, std::string destination, double hue, double saturation, double lightness) {
    std::pair<int, int> originCoord = getStateCoord(origin);
    std::pair<int, int> destinationCoord = getStateCoord(destination);

    for (int xAdj = -2; xAdj <= 2; xAdj++) {
        for (int yAdj = -2; yAdj <= 2; yAdj++) {
            int x0 = originCoord.first + xAdj;
            int x1 = destinationCoord.first + xAdj;

            int y0 = originCoord.second + yAdj;
            int y1 = destinationCoord.second + yAdj;

            int startX = std::min(x0, x1);
            int endX = std::max(x0, x1);

            for (int x = startX; x <= endX; x++) {
                if (x1 == x0) {
                    x1++;
                }
                double y = y0 + ((y1 - y0) * (x - x0)) / (x1 - x0);
                HSLAPixel & pixel = image.getPixel(x, int(y));
                pixel.h = hue;
                pixel.s = saturation;
                pixel.l = lightness;
            }
        }
    }

    for (int xAdj = -8; xAdj < 8; xAdj++) {
        for (int yAdj = -8; yAdj < 8; yAdj++) {
            HSLAPixel & pixel = image.getPixel(originCoord.first + xAdj, originCoord.second + yAdj);
            pixel.h = hue;
            pixel.s = saturation;
            pixel.l = lightness;
        }
    }

    for (int xAdj = -8; xAdj < 8; xAdj++) {
        for (int yAdj = -8; yAdj < 8; yAdj++) {
            HSLAPixel & pixel = image.getPixel(destinationCoord.first + xAdj, destinationCoord.second + yAdj);
            pixel.h = hue;
            pixel.s = saturation;
            pixel.l = lightness;
        }
    }
}

void MapProjection::drawOrigin(std::string origin) {
    std::pair<int, int> originCoord = getStateCoord(origin);
    for (int x = -15; x <= 16; x++) {
        for (int y = -15; y <= 16; y++) {
            HSLAPixel & pixel = image.getPixel(originCoord.first + x, originCoord.second + y);
            HSLAPixel & pixel2 = originLabel.getPixel(x + 15, y + 15);
            if (pixel2.a > 0.5) {
                pixel.h = pixel2.h;
                pixel.s = pixel2.s;
                pixel.l = pixel2.l;
                pixel.a = pixel2.a;
            }
        }
    }
}

void MapProjection::drawDestination(std::string destination) {
    std::pair<int, int> destinationCoord = getStateCoord(destination);
    for (int x = -15; x <= 16; x++) {
        for (int y = -15; y <= 16; y++) {
            HSLAPixel & pixel = image.getPixel(destinationCoord.first + x, destinationCoord.second + y);
            HSLAPixel & pixel2 = destinationLabel.getPixel(x + 15, y + 15);
            if (pixel2.a > 0.5) {
                pixel.h = pixel2.h;
                pixel.s = pixel2.s;
                pixel.l = pixel2.l;
                pixel.a = pixel2.a;
            }
        }
    }
}

void MapProjection::exportImage(std::string filename) {
    image.writeToFile(filename);
}

std::pair<int, int> MapProjection::getStateCoord(std::string state) {
    std::pair<int, int> stateCoord;
    stateCoord = stateCoordinates[state];
    return stateCoord;
}