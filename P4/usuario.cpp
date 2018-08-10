#include"usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "iomanip"
#include <unistd.h>
#include<crypt.h>
#include <chrono>
#include <random>


// ---------------Clave-----------------------------------------------


Clave::Clave(const char* key)
{

        if(strlen(key)<5)
                throw Clave::Incorrecta(Clave::CORTA);
        else
                {

                        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                        std::default_random_engine generator (seed);
                        std::uniform_int_distribution<int> distribution(0,64);

                         int a = distribution(generator);
                         int b = distribution(generator);
                         int c = distribution(generator);
                         const char caracteres[] = "abcdefghijklmnopqrstuvwxyz"
                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

                         char salt[] = {caracteres[a],caracteres[b], caracteres[c]};
                        //  sprintf(salt,"%d",a);
                        // const char* claveaux = new char[strlen(crypt(key,salt))+1];
                        const char * claveaux = crypt(key,salt);


                        if(claveaux == nullptr)
                                throw Clave::Incorrecta(Clave::ERROR_CRYPT);

                        clave_=Cadena(claveaux);


                }
}


bool Clave::verifica(const char* cad)const
{
        bool c {false};
        // desencriptar clave.
        if(strcmp( clave_.c_str() ,crypt(cad,clave_.c_str())) == 0)
                c = true;

        return c;
}

// ----------------Usuario------------------------------------------------

Usuario::Ids Usuario::ids_;

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& ap,const Cadena& dir, const Clave& clave):
clave_{clave}
{


        if(  Usuario:: ids_.insert(id).second  )
        {
                id_=id;
                nom_ = Cadena(nom);
                ap_ = Cadena(ap);
                dir_ = Cadena(dir);
        }
                else
                     throw Usuario::Id_duplicado(id);
}



void Usuario::es_titular_de(Tarjeta& t)
{
        if(t.titular()==this)
        tarjetas_[t.numero()] = &t;
}

void Usuario::no_es_titular_de(Tarjeta& t)
{
        tarjetas_.erase(t.numero());
}

void Usuario::compra(Articulo& a, unsigned cant )
{
        if(cant )
                articulos_[&a]=cant;

        else
                articulos_.erase(&a);
}

Usuario::~Usuario()
{

        for(auto i =tarjetas().begin() ; i != tarjetas().end(); i++)
                (i->second)->anula_titular();
        Usuario::ids_.erase(id_);
}

std::ostream& operator <<(std::ostream& os, const Usuario& us)
{


        os<< us.id()<<" ["<<us.clave_.clave()<<"] "<<us.nom_<<" "<<us.ap_<<"\n"<<us.dir_
        <<"\nTarjetas:\n";

        for(auto a : us.tarjetas())
                os<<"<"<<*(a.second)<<">\n" ;

        return os;
}


std::ostream& mostrar_carro(std::ostream& os, const Usuario& us)
{
        auto carro = us.compra();

        os<<"Carrito de compra de "<<us.id()<<" [Artículos: "<<carro.size()<<"]\n"<<"\tCant. Artículo\n";
        os<<"==================================================\n";

        for(auto i: carro)
        {
          os<<"\t "<<(i.second)<<" ";

        os<<"["<<i.first->referencia()<<"] \""<<i.first->titulo()<<"\", "<<i.first->f_publi().anno()<<". "
        <<std::fixed<<std::setprecision(2)<<i.first->precio()<<" €\n";
          }




        return os;
}
