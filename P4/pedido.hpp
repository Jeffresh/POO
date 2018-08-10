#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include<iostream>
#include "fecha.hpp"
class Articulo;
class Pedido_Articulo;
class Tarjeta;
class Usuario;
class Usuario_Pedido;

//def pedido

class Pedido
{
public:

        class Vacio
        {
        public:
                Vacio(const Usuario& u):u_{&u}{}
                const Usuario& usuario()const{return *u_; }
        private:
                const Usuario* u_;
        };

        class Impostor
        {
        public:
                Impostor(const Usuario& u):u_{&u}{}
                const Usuario& usuario()const{return *u_;}
        private:
                const Usuario* u_;

        };

        class SinStock
        {
        public:
                SinStock(const Articulo& a): a_{&a}{}
                const Articulo& articulo()const{return *a_;}
        private:
                const Articulo* a_;

        };

        Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha&  f = Fecha() );
        int numero()const{ return num_ ;}
        const Tarjeta* tarjeta()const {return tarjeta_ ;}
        const Fecha& fecha()const{ return fecha_ ;}
        double total()const { return total_ ;}
        static int n_total_pedidos(){return N_pedidos;}

private:


        int num_;
        static int N_pedidos;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
};

std::ostream& operator <<(std::ostream& , const Pedido&);


#endif
