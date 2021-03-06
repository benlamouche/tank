#include "Map.h"
#include <iostream>
#include <fstream>

using namespace std;

Map::Map() : m_width(0),m_height(0),tileMap(0),objMap(0)
{
    //ctor
}

Map::Map(const Map & source): m_tileWidth(source.m_tileWidth),m_tileHeight(source.m_tileHeight),m_width(source.m_width),m_height(source.m_height)
{
    // constructeur par copie
    createMap();
    for (int i=0; i < m_width; i++)
        for (int j=0; j < m_height; j++){
                        tileMap[i][j] = source.tileMap[i][j];
            objMap[i][j] = source.objMap[i][j];
        }
}

Map::Map(int width,int height) : m_width(width),m_height(height)
{
    createMap();
}

Map::Map(const char* fileName): m_width(0),m_height(0),tileMap(0),objMap(0)
{
    this->loadFromFile(fileName);
}

Map::~Map()
{
    //dtor
    freeMap();
}

void Map::freeMap()
{
    for (int i=0; i < m_width; i++){
        delete[] tileMap[i];
        delete[] objMap[i];
    }
    delete[] tileMap;
    delete[] objMap;
}

void Map::createMap()
{
    tileMap = new int* [ m_width ];
    objMap = new int* [ m_width ];
    for (int i=0; i < m_width; i++){
            tileMap[i] = new int[ m_height ];
            objMap[i] = new int[ m_height ];
    }
}

void Map::loadFromFile(const char* fileName)
{
    uint16_t mapWidth;
    uint16_t mapHeight;
    uint16_t tileWidth;
    uint16_t tileHeight;
    uint16_t temp;
    uint16_t temp2;
    ifstream in(fileName,std::ios::binary);
    if (!in){
        cout << "Erreur lors de l ouverture du fichier "<< fileName << ".\n";
    }else{
        freeMap();
        in >> mapWidth >> mapHeight>>tileWidth>>tileHeight;
        m_width=mapWidth;
        m_height=mapHeight;
        m_tileWidth=tileWidth;
        m_tileHeight=tileHeight;
        createMap();
        for (int i = 0; i < mapWidth; ++i) {
            for (int j = 0; j < mapHeight; ++j) {
                in >> temp >> temp2;
                this->setTile(i,j,temp);
                this->setObj(i,j,temp2);
            }
        }
    }
    in.close();
}

void Map::resizeMap(int width,int height)
{
    freeMap();
    m_width=width;
    m_height=height;
    createMap();
}

void Map::showTxt()const
{
    cout<<"Tile\n";
    for (int j = 0; j < this->height(); ++j) {
        for (int i = 0; i < this->width(); ++i) {
            cout << this->tile(i,j)<<" ";
        }
        cout << endl;
    }
    cout<<"Obj\n";
    for (int j = 0; j < this->height(); ++j) {
        for (int i = 0; i < this->width(); ++i) {
            cout << this->obj(i,j)<<" ";
        }
        cout << endl;
    }
}

void Map::fillTile(int val)
{
    /* Initialisation */
  for (int i=0; i < m_width; i++)
    for (int j=0; j < m_height; j++)
      tileMap[i][j] = val;
}

void Map::incrementFill()
{
    /* Initialisation */
  for (int i=0; i < m_width; i++)
    for (int j=0; j < m_height; j++)
      tileMap[i][j] = i*j,objMap[i][j] = i*j;

}

Map & Map::operator= (const Map & source)
{
    if (this != &source)
    {
        freeMap();
        m_width=source.m_width;
        m_height=source.m_height;
        m_tileWidth=source.m_tileWidth;
        m_tileHeight=source.m_tileHeight;
        createMap();
        for (int i=0; i < m_width; i++)
            for (int j=0; j < m_height; j++)
                tileMap[i][j] = source.tileMap[i][j],objMap[i][j] = source.objMap[i][j];
    }
    return *this;
}
