#ifndef FECHA_HPP_
#define FECHA_HPP_

#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
// #include"fct.h"

class Fecha
{

public:

        //clase para implementar excepción
        class Invalida
        {

        public:
                Invalida(const char* cad)
                {
                        motivo_ = new char[std::strlen(cad)+1];
                        strcpy(motivo_, cad);
                }
                const char* por_que()const{return motivo_;}
        private:
                char* motivo_;
        };


        explicit Fecha(int d = 0, int m = 0, int y = 0);
        // constructor de conversión
        Fecha(const char* cad);
        //constructor de copia
        //Fecha(const Fecha& f);
        //operador de asignación.
        // Fecha& operator = (const Fecha& f);




        // operadores asimétricos


        Fecha& operator ++();
        Fecha& operator --();
        Fecha operator ++(int);
        Fecha operator --(int);


        Fecha& operator +=(int dias);
        Fecha& operator -=(int dias);


        // conversión
         const char* cadena () const ;




        int dia()const {return dia_; }
        int mes()const {return mes_; }
        int anno()const {return anno_ ;}




        static const  int AnnoMinimo = 1902;
        static const  int AnnoMaximo = 2037;


private:

        int dia_ , mes_ , anno_ ;
        int auxfecha(int, int );

};

//Operadores inserccion extracción

 std::ostream& operator <<(std::ostream& os, const Fecha& f);
 std::istream& operator >>(std::istream& is, Fecha& f);




// constantes
// const unsigned int Fecha::AnnoMaximo = 2037;
// const unsigned int Fecha::AnnoMinimo = 1902;


Fecha operator + (const Fecha& f, int dias);
Fecha operator - (const Fecha& f, int dias);
// operadores binarios simétrico


long int operator - (const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);



#endif
