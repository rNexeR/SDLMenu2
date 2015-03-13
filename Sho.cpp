#include "Sho.h"

Sho::Sho(SDL_Renderer* renderer,list<Personaje*> *personajes)
{
    mapa_texturas[ANIMACION_IDLE_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_IDLE_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_WALKING_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_WALKING_LEFT] = new vector<SDL_Texture*>();

    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/standing/1.png"));
    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/standing/2.png"));
    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/standing/3.png"));
    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/standing/4.png"));

    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/1.png"));
    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/2.png"));
    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/3.png"));
    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/4.png"));

    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/walk/1.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/walk/2.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/walk/3.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/walk/4.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/walk/5.png"));

    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/1.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/2.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/3.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/4.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/5.png"));

    estado_actual = DERECHA;

    rect.x = 0;
    rect.y = 0;

    init(renderer,personajes);
}

void Sho::act()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if(currentKeyStates[SDL_SCANCODE_SPACE])
    {
        atacando = true;
        if(estado_actual==DERECHA || estado_actual==DERECHA)
        {
//            setAnimacion("punch_right");
        }

        if(estado_actual==IZQUIERDA || estado_actual==IZQUIERDA)
        {
//            setAnimacion("punch_left");
        }
    }else
    {
        atacando = false;
    }

    if(currentKeyStates[SDL_SCANCODE_W])
    {
        rect.y--;
    }
    else if(currentKeyStates[SDL_SCANCODE_S])
    {
        rect.y++;
    }

    if(currentKeyStates[SDL_SCANCODE_D])
    {
        rect.x++;
        setAnimacion(ANIMACION_WALKING_RIGHT);
    }
    else if(currentKeyStates[SDL_SCANCODE_Z])
    {
        rect.x--;
        setAnimacion(ANIMACION_WALKING_LEFT);
    }
    else
    {
        if(estado_actual == DERECHA)
            estado_actual = DERECHA;

        if(estado_actual == IZQUIERDA)
            estado_actual = IZQUIERDA;
    }

    attackCheck();
}

Sho::~Sho()
{
    //dtor
}

bool Sho::soySho()
{
    return true;
}
