#ifndef ENEMIGOAZUL_H
#define ENEMIGOAZUL_H

#include "Enemigo.h"

class EnemigoAzul : public Enemigo
{
    public:
        int estado;
        int frame_estado;

        int estadoRandom();
        bool estoyCerca();
        void cambiarEstado(int estado);

        EnemigoAzul(SDL_Renderer* renderer,list<Personaje*> *personajes);
        virtual ~EnemigoAzul();

        void act();
    protected:
    private:
};

#endif // ENEMIGOAZUL_H
