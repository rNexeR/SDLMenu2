#include "Sho.h"

Sho::Sho(SDL_Renderer* renderer,list<Personaje*> *personajes)
{
    mapa_texturas[ANIMACION_IDLE_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_IDLE_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_WALKING_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_WALKING_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_STARTUP_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_ACTIVE_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_RECOVERY_RIGHT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_STARTUP_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_ACTIVE_LEFT] = new vector<SDL_Texture*>();
    mapa_texturas[ANIMACION_ATACANDO_RECOVERY_LEFT] = new vector<SDL_Texture*>();

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

    mapa_texturas[ANIMACION_ATACANDO_STARTUP_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/punch/1.png"));

    mapa_texturas[ANIMACION_ATACANDO_ACTIVE_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/punch/2.png"));

    mapa_texturas[ANIMACION_ATACANDO_RECOVERY_RIGHT]->push_back(IMG_LoadTexture(renderer,"Sho/punch/3.png"));

    mapa_texturas[ANIMACION_ATACANDO_STARTUP_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/punch_left/1.png"));

    mapa_texturas[ANIMACION_ATACANDO_ACTIVE_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/punch_left/2.png"));

    mapa_texturas[ANIMACION_ATACANDO_RECOVERY_LEFT]->push_back(IMG_LoadTexture(renderer,"Sho/punch_left/3.png"));

    estado_actual = DERECHA;

    rect.x = 0;
    rect.y = 0;

    init(renderer,personajes);
    frames_atacando=0;
    trigger_atacar=false;
    cout<<"!!"<<ANIMACION_IDLE_RIGHT<<endl;
    cout<<"!!"<<ANIMACION_IDLE_LEFT<<endl;
}

void Sho::setAttackingStartup()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_ATACANDO_STARTUP_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_ATACANDO_STARTUP_LEFT);
    }
}

void Sho::setAttackingActive()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_ATACANDO_ACTIVE_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_ATACANDO_ACTIVE_LEFT);
    }
    atacando=true;
}

void Sho::setAttackingRecovery()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_ATACANDO_RECOVERY_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_ATACANDO_RECOVERY_LEFT);
    }
    atacando=false;
}

void Sho::setIdle()
{
    if(orientacion=='r')
    {
        setAnimacion(ANIMACION_IDLE_RIGHT);
    }else
    {
        setAnimacion(ANIMACION_IDLE_LEFT);
    }
    trigger_atacar=false;
}

void Sho::actAttacking()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    frames_atacando++;
    if(frames_atacando==30)
    {
        setAttackingActive();
    }
    if(frames_atacando==60)
    {
        setAttackingRecovery();
    }
    if(frames_atacando==90)
    {
        setIdle();
    }
    attackCheck();
}

void Sho::actMoving()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates[SDL_SCANCODE_SPACE])
    {
        trigger_atacar = true;
        frames_atacando=0;
        setAttackingStartup();
    }
    else
    {
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
            orientacion='r';
            rect.x++;
            setAnimacion(ANIMACION_WALKING_RIGHT);
        }
        else if(currentKeyStates[SDL_SCANCODE_Z])
        {
            orientacion='l';
            rect.x--;
            setAnimacion(ANIMACION_WALKING_LEFT);
        }
        else
        {
            if(orientacion=='r')
            {
                setAnimacion(ANIMACION_IDLE_RIGHT);
            }
            else
            {
                setAnimacion(ANIMACION_IDLE_LEFT);
            }
        }
    }
}

void Sho::act()
{
    if(trigger_atacar)
    {
        actAttacking();
    }
    else
    {
        actMoving();
    }
}

Sho::~Sho()
{
    //dtor
}

bool Sho::soySho()
{
    return true;
}
