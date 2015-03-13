#include "EnemigoAzul.h"

EnemigoAzul::EnemigoAzul(SDL_Renderer* renderer, list<Personaje*> *personajes)
{
    mapa_texturas[ANIMACION_IDLE_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_IDLE_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_WALKING_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_WALKING_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_STARTUP] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_ACTIVE] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_RECOVERY] = new vector<SDL_Texture*>();

    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/1.png"));
    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/2.png"));
    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/3.png"));
    mapa_texturas[ANIMACION_IDLE_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/4.png"));

    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/1.png"));
    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/2.png"));
    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/3.png"));
    mapa_texturas[ANIMACION_IDLE_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/4.png"));

    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk/1.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk/2.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk/3.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk/4.png"));
    mapa_texturas[ANIMACION_WALKING_RIGHT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk/5.png"));

    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk_left/1.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk_left/2.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk_left/3.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk_left/4.png"));
    mapa_texturas[ANIMACION_WALKING_LEFT]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/walk_left/5.png"));

    mapa_texturas[ANIMACION_ATACANDO_STARTUP]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/punch/1.png"));

    mapa_texturas[ANIMACION_ATACANDO_ACTIVE]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/punch/2.png"));

    mapa_texturas[ANIMACION_ATACANDO_RECOVERY]->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/punch/3.png"));


    estado_actual = DERECHA;

    rect.x = 100;
    rect.y = 350;

    estado = INICIO;
    frame_estado = 0;

    init(renderer,personajes);
}

EnemigoAzul::~EnemigoAzul()
{
    //dtor
}

int EnemigoAzul::estadoRandom()
{
    Personaje* sho = NULL;
    for(list<Personaje*>::iterator i = personajes->begin();
        i!=personajes->end();
        i++)
    {
        if((*i)->soySho())
        {
            sho = (*i);
            if(colision(sho->hitbox))
            {
                return true;
            }
        }
    }
    if(sho!=NULL)
    {
        int mi_random = rand()%2;

        if(mi_random==0)
        {
            if(sho->rect.y>rect.y)
                return ABAJO;

            if(sho->rect.y<rect.y)
                return ARRIBA;
        }
        else
        {
            if(sho->rect.x<rect.x)
            {
                return IZQUIERDA;
            }

            if(sho->rect.x>rect.x)
                return DERECHA;
        }
    }

//    int mi_random = rand()%5;
//
//    switch(mi_random)
//    {
//        case 0:
//            return ARRIBA;
//        break;
//        case 1:
//            return ABAJO;
//        break;
//        case 2:
//            return IZQUIERDA;
//        break;
//        case 3:
//            return DERECHA;
//        break;
//        case 4:
//            return PARADO;
//        break;
//    }
}

bool EnemigoAzul::estoyCerca()
{
    Personaje* sho = NULL;
    for(list<Personaje*>::iterator i = personajes->begin();
        i!=personajes->end();
        i++)
    {
        if((*i)->soySho())
        {
            sho = (*i);
            if(colision(sho->hitbox))
            {
                return true;
            }
        }
    }


    return false;
}

void EnemigoAzul::cambiarEstado(int estado)
{
    this->estado = estado;
    frame_estado = 0;
}

void EnemigoAzul::act()
{
//    if(frame%100==1)
//        atacando = true;
//    else
//        atacando = false;

    frame_estado++;
    switch(estado)
    {
        case INICIO:
            atacando = false;
            if(estoyCerca())
                cambiarEstado(CERCA);
            else
                cambiarEstado(LEJOS);
        break;

        case CERCA:
            estado = ATACANDO_STARTUP;
            setAnimacion(ANIMACION_ATACANDO_STARTUP);
        break;

        case ATACANDO_STARTUP:
            if(frame_estado%200==0)
            {
                atacando = true;
                cambiarEstado(ATACANDO_ACTIVE);
                setAnimacion(ANIMACION_ATACANDO_ACTIVE);
            }
        break;

        case ATACANDO_ACTIVE:
            if(frame_estado%200==0)
            {
                atacando = false;
                cambiarEstado(ATACANDO_RECOVERY);
                setAnimacion(ANIMACION_ATACANDO_RECOVERY);
            }
        break;

        case ATACANDO_RECOVERY:
            if(frame_estado%200==0)
            {
                cambiarEstado(INICIO);
            }
        break;

        case LEJOS:
            estado = estadoRandom();
            switch(estado)
            {
                case ARRIBA:
                    setAnimacion(ANIMACION_WALKING_RIGHT);
                break;
                case ABAJO:
                    setAnimacion(ANIMACION_WALKING_LEFT);
                break;
                case DERECHA:
                    setAnimacion(ANIMACION_WALKING_RIGHT);
                break;
                case IZQUIERDA:
                    setAnimacion(ANIMACION_WALKING_LEFT);
                break;
            }

        break;

        case IZQUIERDA:
            rect.x--;
            if(frame_estado%100==0)
                cambiarEstado(INICIO);
        break;

        case DERECHA:
            rect.x++;
            if(frame_estado%100==0)
                cambiarEstado(INICIO);
        break;

        case ARRIBA:
            rect.y--;
            if(frame_estado%100==0)
                cambiarEstado(INICIO);
        break;

        case ABAJO:
            rect.y++;
            if(frame_estado%100==0)
                cambiarEstado(INICIO);
        break;

        case PARADO:
            if(frame_estado%50==0)
                cambiarEstado(INICIO);
        break;
    }

//    this->estado_actual = estado;

    attackCheck();
}



