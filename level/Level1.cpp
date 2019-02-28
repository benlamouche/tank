#include "Level1.h"
#include <iostream>
#include "../Player.h"
#include "../MyGame.h"
extern Player player;

Level1::Level1(): FinalMap("data/map/level1.mp","data/map/wmap.png")
{
    //ctor
}

Level1::~Level1()
{
    //dtor
}

void Level1::initPlayer()
{
    player.init(1400,1000);
}

void Level1::initEni()
{

    Eni::vec.push_back(Eni(1200,250));
    Eni::vec.push_back(Eni(1250,300));
    Eni::vec.push_back(Eni(1300,350));
    Eni::vec.push_back(Eni(1350,400));
    Eni::vec.push_back(Eni(1400,450));
    Eni::vec.push_back(Eni(1450,500));



    Eni::vec.push_back(Eni(750,100));
    Eni::vec.push_back(Eni(750,150));
    Eni::vec.push_back(Eni(750,200));
    Eni::vec.push_back(Eni(750,250));

    Eni::vec.push_back(Eni(750,300));
    Eni::vec.push_back(Eni(750,350));
    Eni::vec.push_back(Eni(750,400));
    Eni::vec.push_back(Eni(750,450));

    Eni::vec.push_back(Eni(250,300));
    Eni::vec.push_back(Eni(300,350));
    Eni::vec.push_back(Eni(350,400));
    Eni::vec.push_back(Eni(400,450));

    Eni::vec.push_back(Eni(50,800));
    Eni::vec.push_back(Eni(100,800));
    Eni::vec.push_back(Eni(150,800));
    Eni::vec.push_back(Eni(200,800));
    Eni::vec.push_back(Eni(800,1100));
    Eni::vec.push_back(Eni(800,1150));
    Eni::vec.push_back(Eni(800,1200));
    Eni::vec.push_back(Eni(800,1250));
    Eni::vec.push_back(Eni(250,1150));
    Eni::vec.push_back(Eni(250,1200));
    Eni::vec.push_back(Eni(250,1250));
    Eni::vec.push_back(Eni(250,1300));
    Eni::vec.push_back(Eni(250,1350));
    Eni::vec.push_back(Eni(250,1400));
}

void Level1::loadMusic()
{
    musique = Mix_LoadMUS("data/music/298274_Military_Theme.mp3");
    if(!musique) {
    std::cerr<<"Mix_LoadMUS: "<< Mix_GetError()<<std::endl;
    // this might be a critical error...
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    Mix_PlayMusic(musique,-1);
}

void Level1::unloadMusic()
{
    Mix_HaltMusic();//stop la musique
    Mix_FreeMusic(musique);
}

void Level1::goNextLevel()
{
    dynamic_cast<MyGame *>(game)->goScene(2);
}
