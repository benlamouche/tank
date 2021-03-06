#include "MenuIntro.h"
#include "../core/Game.h"
#include "../menuItem/Quit.h"
#include "../menuItem/GoLevel.h"
#include "../menuItem/FullScreen.h"
//#include "../menuItem/LoachMenu.h"

#include <iostream>

extern Game* game;

extern SDL_Window *ecran;//  main.cpp
extern TTF_Font * menuFont;


MenuIntro::MenuIntro(Scene* parent): Scene(parent)
{
    //ctor
}

MenuIntro::~MenuIntro()
{
    //dtor
}

void MenuIntro::load()
{
    mPrincipal= new Menu(350,50,menuFont,50);

    mPrincipal->addElement(new GoLevel(1,"level 1"));
    mPrincipal->addElement(new GoLevel(2,"level 2"));
    mPrincipal->addElement(new GoLevel(3,"level 3"));
    mPrincipal->addElement(new FullScreen("Full Screen"));
    //mPrincipal->addElement(new LoachMenu(mPrincipal,"Menu"));
    mPrincipal->addElement(new Quit("Quit"));
    Menu::setMenuActif(mPrincipal);
    setRGB(0,0,0);
    if(parent()){
        switchClean();
    }


    // musique

    musique = Mix_LoadMUS("data/music/327500_sam.mp3");
    if(!musique) {
    cerr<<"Mix_LoadMUS: "<< Mix_GetError()<<endl;
    // this might be a critical error...
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    Mix_PlayMusic(musique,-1);

    //backGround
    backGround = IMG_Load("./data/sprite/tank2.png");
}

void MenuIntro::unload()
{
    delete mPrincipal;
    // ************ music *************

    Mix_HaltMusic();//stop la musique
    Mix_FreeMusic(musique);

    // ************ music end *************

    SDL_FreeSurface(backGround);
}

void MenuIntro::input()
{
    switch(event.type)
    {
        case SDL_QUIT:
            game->quit();
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    loop=0;
                    break;
                case SDLK_UP:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::menuActif()->up();
                    break;
                case SDLK_DOWN:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::menuActif()->down();
                    break;
                case SDLK_RETURN:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::activation();
                    break;
                case SDLK_BACKSPACE:
                    event.key.keysym.sym=0;//evite les pb de repetition de touche
                    Menu::setMenuActif(Menu::menuActif()->menuParent());
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN  :
                switch(event.button.button)//  Gestion des bouton souris
                {
                    case SDL_BUTTON_LEFT:
                        event.button.button=0;
                        Menu::activation();// a optimiser fonctionne en dehor du menu
                        break;
                }
                break;
        case SDL_MOUSEMOTION:
                Menu::menuActif()->onMouse(event.motion.x,event.motion.y);
            break;
    }
}

void MenuIntro::update(int dt)
{


    int returnVal =0;
    returnVal = Menu::updateMenu(returnVal);
    if(returnVal==PLAY){
        loop = 0;
    }

    if(game->status()==QUIT)loop = 0;
}

void MenuIntro::draw()
{
//    if(parent()){
//        parent()->clean();
//        parent()->draw();
//    }

    SDL_BlitSurface(backGround,NULL,SDL_GetWindowSurface(ecran),NULL);

    Menu::menuActif()->affiche(ecran);
}
