#ifndef HEATMAP_H
#define HEATMAP_H

#include <iostream>

class Heatmap
{
public:
    Heatmap();
    int getValue(int x, int y);
    int setValue(int value, int x, int y);
    int setMap(int newMap[8][7]);

    void printHeatMap();

    Heatmap operator+(const Heatmap& map);
private:
    int heatMap[8][7];

};

#endif // HEATMAP_H
