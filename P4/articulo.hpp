#ifndef ARTICULOS_HPP_
#define ARTICULOS_HPP_

#include"cadena.hpp"
#include"fecha.hpp"
#include <set>

class Autor
{
public:



        Autor( const Cadena nom , const  Cadena ap , const Cadena dir):
        nom_{nom}, ap_{ap}, dir_{dir}{}

        Cadena nombre()const {return nom_;}
        Cadena apellidos()const { return ap_;}
        Cadena direccion()const { return dir_ ;}

private:
        const Cadena nom_ ;
        const Cadena ap_ ;
        const Cadena dir_ ;


};

class Articulo
{

public:

        typedef std::set<Autor*> Autores;
        class Autores_vacios{};

        Articulo(const Articulo::Autores& au ,const  Cadena& ref, const Cadena& tit, const Fecha& f , double p );

        // realmente da igual que sean virtual, ya que no se van a heredar metodos duplicados
        virtual Cadena referencia()const{return ref_;}
        virtual Cadena titulo()const { return titulo_;}
        virtual Fecha f_publi()const { return f_publi_;}
        virtual double precio()const { return precio_; }
        virtual double& precio() {return precio_; }
        virtual const Autores& autores()const{return autores_;}

        virtual void impresion_especifica(std::ostream&)const = 0;


        virtual ~Articulo(){}

protected:
         const Cadena ref_;
         const Cadena titulo_;
         const Fecha f_publi_;
         double precio_;
         const  Autores autores_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& a );

class ArticuloAlmacenable : public Articulo
{
public:

        ArticuloAlmacenable(Articulo::Autores& ats, const  Cadena& rf, const Cadena& tl ,const Fecha& fch , double p, size_t st )
        : Articulo{ats,rf,tl,fch,p}, stock_{st} {}

        size_t stock()const{return stock_;}
        size_t& stock(){ return stock_;}
        virtual ~ArticuloAlmacenable(){}

protected:

        size_t stock_ ;
};

class Libro: public ArticuloAlmacenable
{
public:
        Libro(Articulo::Autores& ats, const  Cadena& rf, const Cadena& tl ,const Fecha& fch , double p, size_t np, size_t st)
        :ArticuloAlmacenable(ats,rf,tl,fch,p,st), n_pag_{np}{}

        size_t n_pag()const{return n_pag_;}

        void impresion_especifica(std::ostream& os) const;


private:
        const size_t n_pag_;
};




class Cederron: public ArticuloAlmacenable
{

public:

        Cederron(Articulo::Autores& ats, const  Cadena& rf, const Cadena& tl ,const Fecha& fch , double p, size_t t, size_t st )
        :ArticuloAlmacenable{ats,rf,tl,fch,p,st},tam_{t} {}

        size_t tam()const {return tam_;}

        void impresion_especifica(std::ostream& os) const;

private:

         const size_t tam_;

};

class LibroDigital: public Articulo
{
public:

        LibroDigital(Articulo::Autores& ats, const  Cadena& rf, const Cadena& tl ,const Fecha& fch , double p, const Fecha ex)
        :Articulo{ats,rf,tl,fch,p},f_expir_{ex}{}

        Fecha f_expir()const {return f_expir_;}

        void impresion_especifica(std::ostream& os) const;

private:


        const Fecha f_expir_;


};






#endif
