#pragma once

#include <map>
#include <string>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Graph.h"

using namespace DEA;

class MapProjection {
    public:
        MapProjection();
        ~MapProjection();
        void floodFill(std::string state, double hue, double saturation, double lightness);
        void drawLine (std::string origin, std::string destination, double hue, double saturation, double lightness);
        void drawOrigin(std::string origin);
        void drawDestination(std::string destination);
        std::pair<int, int> getStateCoord(std::string state);
        void exportImage(std::string filename);

    private:
        std::map<std::string, std::pair<int, int>> stateCoordinates;
        cs225::PNG image;
        cs225::PNG originLabel;
        cs225::PNG destinationLabel;

        void floodFillHelper(std::pair<int, int> coord, double hue, double saturation, double lightness);
    protected:
};