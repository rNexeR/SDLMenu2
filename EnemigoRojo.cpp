#include "EnemigoRojo.h"

EnemigoRojo::EnemigoRojo(SDL_Renderer* renderer, list<Personaje*> *personajes)
{
//    vector<SDL_Texture*>*texturas = new vector<SDL_Texture*>();
//    vector<SDL_Texture*>*texturas_left = new vector<SDL_Texture*>();
//
//    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/1.png"));
//    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/2.png"));
//    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/3.png"));
//    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing/4.png"));
//
//    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/1.png"));
//    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/2.png"));
//    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/3.png"));
//    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoRojo/standing_left/4.png"));
//
//    mapa_texturas[ANIMACION_IDLE_RIGHT]=texturas_left;
//    mapa_texturas[ANIMACION_IDLE_RIGHT]=texturas;

    ifstream in("personaje_rojo.txt");

    if(!in)
    {
        cout<<"Error no se encontro el archivo!"<<endl;
        return;
    }

    string animacion;
    while(in>>animacion)
    {
        string llave;
        in>>llave;
        string path;
        in>>path;
        mapa_texturas[enumStringToInt(animacion)] = new vector<SDL_Texture*>();
        while(path!="}")
        {
            mapa_texturas[enumStringToInt(animacion)]->push_back(IMG_LoadTexture(renderer,path.c_str()));
            in>>path;
        }
    }



    estado_actual = DERECHA;

    rect.x = 750;
    rect.y = 250;

    init(renderer, personajes);
}

EnemigoRojo::~EnemigoRojo()
{
    //dtor
}

void EnemigoRojo::act()
{
    rect.x--;
}
