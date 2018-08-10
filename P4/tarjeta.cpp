#include "tarjeta.hpp"
#include "usuario.hpp"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <functional>

bool luhn(const Cadena& numero, size_t n);

// ------------------------------------------- Numero -------------------------------------------------------


class NoValido
{
public:
  bool operator() (char c) const{return std::isdigit(c);}
  typedef char argument_type;
};

Numero::Numero(const Cadena& cad)
{
        Cadena caux{cad};
        char* aux= (std::remove_if(caux.begin(),caux.end(), [ ](char c ){ return std::isspace(c);}));
        *aux = '\0';

        if(aux !=std::find_if(caux.begin(),aux,std::not1(NoValido())))/*[ ](char c){ return int(c) >=48&& int(c)<=57;}))*/
                throw Incorrecto(Razon::DIGITOS);
        num_ = caux.c_str();

        if(num_.length()<13 || num_.length()>19)
                        throw Incorrecto(Razon::LONGITUD);

        if(!luhn(num_ , num_.length() ) )
                        throw Incorrecto(Razon::NO_VALIDO);
}

Numero::operator const char* () const
{
        return  num_.c_str();

}

bool operator <(const Numero& n1, const Numero& n2)
{
        return strcmp (n1 , n2) < 0;
}

// -------------------------------------------------Tarjeta------------------------------------------------------



Tarjeta::Tarjeta(Tarjeta::Tipo t, const Numero& num, Usuario& u,const Fecha& f)
:tipo_{t}, num_{num}, titular_{&u}, f_cad_{f}
{

        if(caducidad() < Fecha())
                throw Tarjeta::Caducada(caducidad());
        else
        {
                titular_facial_= u.nombre() +" "+u.apellidos();

                for(int i = 0; i<titular_facial_.length(); i++)
                        titular_facial_[i]= std::toupper(titular_facial_[i]);

                u.es_titular_de(*this);
        }
}



void Tarjeta::anula_titular(){ titular_ = nullptr;}

Tarjeta::~Tarjeta()
{
        if(titular_ !=  nullptr)
        {
                Usuario* usaux = const_cast<Usuario*>(titular_);
                usaux->no_es_titular_de(*this);
        }
}

std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo t)
{
        switch (t)
        {
                case 0: os<<"VISA";
                        break;
                case 1: os<<"Mastercard";
                        break;
                case 2: os<< "Maestro";
                        break;
                case 3: os<<"JCB";
                        break;
                case 4: os<< "AmericanExpress";
                        break;

        }

        return os;

}


std::ostream& operator <<(std::ostream& os, const Tarjeta& t)
{

        os<<t.tipo()<<"\n"<<t.numero()<<"\n"<<t.titular_facial()
        <<"\nCaduca: ";

        if(t.caducidad().mes()<10)
                os<<"0"<<t.caducidad().mes()<<"/"<<t.caducidad().anno()%100<<"\n";
        else
                os<<t.caducidad().mes()<<"/"<<t.caducidad().anno()%100<<"\n";


        return os;
}

bool operator <(const Tarjeta& t1, const Tarjeta& t2)
{
        return t1.numero() < t2.numero();
}
