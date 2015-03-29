#include "Heatmap.h"

/** Heatmap Constructor */
Heatmap::Heatmap()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            heatMap[i][j] = 0;
        }
    }
}

/** Return the value at position x, y */
int Heatmap::getValue(int x, int y)
{
    return heatMap[y][x];
}

/** Set the value at position x, y */
void Heatmap::setValue(int value, int x, int y)
{
    heatMap[y][x] = value;
}

/** Set the entire map to the map passed in */
void Heatmap::setMap(int newMap[8][7])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            heatMap[i][j] = newMap[i][j];
        }
    }
}

/** Increment the value at position x, y */
void Heatmap::incrementValue(int x, int y)
{
    heatMap[y][x]++;
}

/** Decrement the value at position x, y */
void Heatmap::decrementValue(int x, int y)
{
    heatMap[y][x]--;
}

/** Overloaded operator to add heatmaps */
Heatmap Heatmap::operator+(const Heatmap& map)
{
    Heatmap newMap;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            newMap.setValue(this->heatMap[i][j] + map.heatMap[i][j], j , i);
        }
    }
    return newMap;
}

/** Print the heatmap values to console */
void Heatmap::printHeatMap()
{
    for(int i = 0; i < 8; i++)
    {
        std::cout << i << " > ";
        for(int j = 0; j < 7; j++)
        {
            std::cout << heatMap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
