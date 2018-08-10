#ifndef USUARIO_HPP_
#define USUARIO_HPP_


#include <map>
#include <unordered_map>
#include <unordered_set>
#include"cadena.hpp"

class Articulo;
class Numero;
class Tarjeta;

// -------------------------------------------Clave-----------------------------------------------


class Clave
{
public:

                enum Razon{ CORTA, ERROR_CRYPT};

                Clave(const char*);
                const Cadena& clave() const {return clave_;}
                bool verifica(const char*)const;



                class Incorrecta
                {
                public:
                        Incorrecta(Clave::Razon);
                        Clave::Razon razon()const;
                private:
                        Clave::Razon motivo_;
        };

private:
                Cadena clave_ ;

};


inline Clave::Incorrecta::Incorrecta(Clave::Razon cad):motivo_{cad}{}
inline Clave::Razon Clave::Incorrecta::razon()const{return motivo_;}


// -------------------------------Usuario-----------------------------------------------------------

class Usuario
{
public:

                typedef std::map<Numero, Tarjeta*>  Tarjetas;
                typedef std::unordered_map<Articulo*, unsigned int> Articulos;
                typedef std::unordered_set<Cadena> Ids ;



                class Id_duplicado
                {
                public:
                        Id_duplicado(Cadena);
                        const Cadena& idd()const ;
                private:
                        Cadena idd_;
                };


                Usuario(const Cadena& ,const Cadena& , const Cadena&, const Cadena& ,const  Clave& );
                Usuario(const Usuario&) = delete ;
                Usuario& operator = (const Usuario&) = delete ;

                Cadena id()const;
                Cadena nombre() const ;
                Cadena apellidos() const ;
                Cadena direccion() const ;
                Cadena clavec()const;
                const Tarjetas& tarjetas() const ;
                const Articulos& compra()const ;

                size_t n_articulos()const ;

                void es_titular_de(Tarjeta&);
                void no_es_titular_de(Tarjeta&);
                void compra(Articulo&, unsigned cant =1 );

                ~Usuario();

friend std::ostream& operator <<(std::ostream& os, const Usuario& us);
private:

                Cadena id_ , nom_ , ap_ , dir_;
                Clave clave_ ;
                Tarjetas tarjetas_ ;
                Articulos articulos_ ;
                static Ids ids_;


};

inline Usuario::Id_duplicado::Id_duplicado(Cadena c):idd_{c}{}
inline const Cadena& Usuario::Id_duplicado::idd()const{return idd_;}
inline Cadena Usuario::id()const {return id_;}
inline Cadena Usuario::nombre() const { return nom_ ; }
inline Cadena Usuario::apellidos() const { return ap_; }
inline Cadena Usuario::direccion() const {return dir_ ; }
inline const Usuario::Tarjetas& Usuario::tarjetas() const {return tarjetas_;}
inline const Usuario::Articulos& Usuario::compra()const{return articulos_ ;}
inline size_t Usuario::n_articulos()const{ return articulos_.size(); }

// std::ostream& operator <<(std::ostream& os, const Usuario& us);
std::ostream& mostrar_carro(std::ostream& os, const Usuario& us);








#endif
