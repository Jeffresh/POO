#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include"cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"




// ----------------------------------- Numero ---------------------------------------------------------------

class Numero
{

public:

        enum Razon{LONGITUD,DIGITOS, NO_VALIDO};

        class Incorrecto
        {
        public:
                Incorrecto(Numero::Razon r ): razon_{r}{}
                Numero::Razon razon()const{return razon_;}

        private:
                Numero::Razon razon_;
        };

        Numero(const Cadena& );
        operator const char* ()const ;

private:

        Cadena num_;
};

bool operator <(const Numero& n1, const Numero& n2);



// -----------------------------------Tarjeta--------------------------------------------------

class Tarjeta
{

public:

        enum Tipo{VISA, Mastercard ,Maestro, JCB, AmericanExpress};

        class Caducada
        {
        public:

                Caducada(const Fecha& f): fc_{f}{}
                Fecha cuando()const{return fc_;}

        private:

                Fecha fc_;
        };

        Tarjeta(Tipo, const Numero&, Usuario&,const Fecha&);
        Tarjeta(Tarjeta&) = delete ;
        Tarjeta& operator = (Tarjeta&) = delete;

        Tipo tipo()const {return tipo_;}
        Numero numero()const {return num_;}
        const Usuario* titular()const { return titular_;}
        Fecha caducidad()const { return f_cad_;}
        Cadena titular_facial()const {return titular_facial_;}

        void anula_titular();

        ~Tarjeta();

private:

        Tipo tipo_ ;
        Numero num_ ;
        const Usuario* titular_ ;
        Fecha f_cad_ ;
        Cadena titular_facial_ ;

};

std::ostream& operator <<(std::ostream& os, Tarjeta::Tipo t);
std::ostream& operator <<(std::ostream& os, const Tarjeta& t);

bool operator <( const Tarjeta& t1, const Tarjeta& t2);

#endif
