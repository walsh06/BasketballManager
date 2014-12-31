#ifndef HEATMAP_H
#define HEATMAP_H

#include <iostream>

class Heatmap
{
public:
    Heatmap();
    int getValue(int x, int y);
    void setValue(int value, int x, int y);
    void setMap(int newMap[8][7]);
    void incrementValue(int x, int y);

    void printHeatMap();

    Heatmap operator+(const Heatmap& map);
private:
    int heatMap[8][7];

};

#endif // HEATMAP_H
