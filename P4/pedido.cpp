#include <iomanip>
#include "pedido.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"


int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa,  Usuario& u, const Tarjeta& t, const Fecha& f)
:num_{N_pedidos +1},tarjeta_{&t},fecha_{f},total_{}

{
        auto auxcarro = u.compra();

        if(auxcarro.empty())
                throw Vacio(u);

        if(t.titular()!= &u)
                throw Impostor(u);


        if( t.caducidad()< fecha_)
                throw Tarjeta::Caducada(t.caducidad());

        ArticuloAlmacenable* paa;
        LibroDigital* pld;


        for(auto a : auxcarro)
        {
                if((paa = dynamic_cast<ArticuloAlmacenable*>(a.first)) != nullptr)
                {
                        if(a.second > paa->stock())
                        {
                                const_cast<Usuario::Articulos&>(u.compra()).clear();
                                throw SinStock(*(a.first));
                        }
                }

                else if ((pld = dynamic_cast<LibroDigital*>(a.first))!= nullptr)
                {

                        if((fecha_ >pld->f_expir()))
                                u.compra(*(a.first),0);
                }
        }

        if(u.compra().empty())
                throw Vacio(u);


        for(auto a : auxcarro)
        {
                if((paa = dynamic_cast<ArticuloAlmacenable*>(a.first)) != nullptr)
                        paa->stock() -=a.second;

               total_ +=  ((a.first)->precio())* ( a.second) ;
                pa.pedir(*this,(*a.first),a.first->precio(),a.second);
                u.compra(*(a.first),0);
        }



        ++N_pedidos;
        up.asocia(u,*this);


}





std::ostream& operator <<(std::ostream& os, const Pedido& p)
{

        os<<"Núm. pedido:\t"<<p.numero()<<"\n"
        <<"Fecha:\t"<<p.fecha()<<"\n"
        <<"Pagado con:\t"<<p.tarjeta()->tipo()<<" "<<p.tarjeta()->numero()<<"\n"
        <<"Importe:\t"<<std::fixed<<std::setprecision(2)<<p.total()<<" €\n";

        return os;
}
