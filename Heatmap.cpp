#include "Heatmap.h"

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

int Heatmap::getValue(int x, int y)
{
    return heatMap[y][x];
}

int Heatmap::setValue(int value, int x, int y)
{
    heatMap[y][x] = value;
}

int Heatmap::setMap(int newMap[8][7])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            heatMap[i][j] = newMap[i][j];
        }
    }
}

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
