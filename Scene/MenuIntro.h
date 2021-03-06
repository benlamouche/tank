#ifndef MENUINTRO_H
#define MENUINTRO_H

#include "../core/Scene.h"
#include "../menu/Menu.h"


class MenuIntro : public Scene
{
    public:
        MenuIntro(Scene* parent = NULL);
        virtual ~MenuIntro();
        virtual void draw();

    protected:
        virtual void load();
        virtual void unload();
        virtual void update(int dt);
        void input();


    private:
        Menu *mPrincipal;
        Mix_Music *musique;
        SDL_Surface *backGround;
};

#endif // MENUINTRO_H
