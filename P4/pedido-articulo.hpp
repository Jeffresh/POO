#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <set>
#include<map>
#include "pedido.hpp"
#include"articulo.hpp"


//------------------------LineaPedido-------------------------------

class LineaPedido
{
public:

        explicit LineaPedido(double precio, unsigned cant = 1): precio_venta_{precio}, cantidad_{cant}{}
        double precio_venta()const{return precio_venta_;}
        unsigned cantidad()const{ return cantidad_;}


private:

        double precio_venta_ ;
        unsigned cantidad_ ;
};

std::ostream& operator <<(std::ostream& os,  const LineaPedido&);

// -------------------------------Pedido_Articulo------------------------------------------




class Pedido_Articulo
{

public:

        class OrdenaArticulos
        {
        public:
                bool operator()(const Articulo* a, const Articulo* b)const{return a->referencia()< b->referencia();}
        };

        class OrdenaPedidos
        {
        public:
                bool operator()(const Pedido* a, const Pedido* b)const{return a->numero()< b->numero();}
        };

        typedef std::map<Articulo*,LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*,LineaPedido, OrdenaPedidos> Pedidos;



        void pedir(Pedido&,Articulo&, double , unsigned cantidad =1 ) ;
        void pedir(Articulo&, Pedido&, double, unsigned cantidad = 1) ;

        ItemsPedido detalle(Pedido&);
        Pedidos ventas(Articulo&) ;

        void mostrarDetallePedidos(std::ostream& );
        void mostrarVentasArticulos(std::ostream& );


private:

        std::map<Pedido*,ItemsPedido,OrdenaPedidos> AD;
        std::map<Articulo*,Pedidos,OrdenaArticulos> AI;

};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& );
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos&);


#endif
