#ifndef HEATMAP_H
#define HEATMAP_H

#include <iostream>

/* Heatmap is used for storing influence values on the court
 * The half court is represented in the 7x8 array. Each element
 * stores the influence value at that position. This class is
 * used by players, strategies and positions.
 */
class Heatmap
{
public:
    Heatmap();
    ~Heatmap();

    int getValue(int x, int y);
    void setValue(int value, int x, int y);
    void setMap(int newMap[8][7]);
    void incrementValue(int x, int y);
    void decrementValue(int x, int y);

    void printHeatMap();

    Heatmap operator+(const Heatmap& map);
private:
    int heatMap[8][7];

};

#endif // HEATMAP_H
