 #include "pedido-articulo.hpp"
 #include"tarjeta.hpp"
 #include <iomanip>

//----------------------LineaPedido---------------------------------------------

 std::ostream& operator <<(std::ostream& os, const LineaPedido& lp)
 {
         os<<std::fixed;
         os<<std::setprecision(2);
         os<<lp.precio_venta()<<" €\t"<<lp.cantidad();

         return os;

 }

//------------------------------Pedido Articulo----------------------------------------
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cant)
{
        AD[&p].insert(std::make_pair(&a,LineaPedido(precio,cant)) );
        AI[&a].insert(std::make_pair(&p,LineaPedido(precio,cant)) );
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, unsigned cant)
{
        AD[&p].insert(std::make_pair(&a,LineaPedido(precio,cant)) );
        AI[&a].insert(std::make_pair(&p,LineaPedido(precio,cant)) );


}

Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& p)
{
        return  AD.find(&p)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas (Articulo& a)
{
        return AI.find(&a)->second;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip)
{
        double auxtotal{};
        int num{};

        for(auto a :ip)
        {
                num = num + (a.second).cantidad();
                auxtotal = auxtotal + (a.second).precio_venta()*(a.second).cantidad();
        }

        os<<"\nNumero de ejemplares: "<<num<<"\nTotal: "<<std::fixed<<std::setprecision(2)<<auxtotal<<" €\n";


        return os;


}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p)
{
        double total {};
        for(auto a : p )
        {
                os<<(a.second).cantidad()<<"\t"<<std::fixed<<std::setprecision(2)<<(a.second).precio_venta()<<" €\t"
                <<(a.first)->fecha()<<"\n";
                total+=((a.second).cantidad()*(a.second).precio_venta());
        }

        os<<"\nTotal: "<<std::fixed<<std::setprecision(2)<<total<<" €\n";

        return os;

}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
        double total {};
	double ventas{};
	for(auto a : AD)
        {
                os << std::endl << "Pedido num. " << (a.first)->numero() << std::endl;

                os << "Cliente: " << (((a.first)->tarjeta())->titular())->id() << "\t\tFecha: " << (a.first)->fecha() << std::endl

                << "=================================================" << std::endl
                << "  PVP\t\t Cantidad\t Artículo" << std::endl
                << "=================================================" << std::endl;

                for( auto b = (a.second).begin(); b!=(a.second).end(); b++)
                {
                        os <<std::fixed<<std::setprecision(2)<< (b->second).precio_venta() <<" €\t"
                        << (b->second).cantidad() << "\t\t[" << (b->first)->referencia()
                        <<"] \"" << (b->first)->titulo() << "\"" << std::endl;
                        total += ((b->second).precio_venta())*((b->second).cantidad());
                        ventas += ((b->second).precio_venta())*((b->second).cantidad());
		}
		os << "===============================================" << std::endl
		  << "Total: " << ventas << " €" << std::endl << std::endl;
		ventas = 0.0;
	}
	os << "\nTOTAL VENTAS \t" << std::fixed
	  << total << " €"<< std::endl;

}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
        double ventas = 0;
	unsigned int cantidad = 0;
	for(auto a: AI)
        {
		os << std::endl << " Ventas de " << "[" << (a.first)->referencia() << "]" << " \"" << (a.first)->titulo() << "\""
		<< " [Pedidos: " << (a.second).size() << "]" << std::endl
		<<  "===============================================" << std::endl
		<<  "PVP\t\tCantidad\tFecha de venta" << std::endl
		<<  "===============================================" << std::endl
		;
		for(Pedido_Articulo::Pedidos::const_iterator b = (a.second).begin(); b!= (a.second).end(); b++)
                {
			os <<std::fixed<<std::setprecision(2)<< (b->second).precio_venta() << " €\t"
			<< (b->second).cantidad() << "\t\t" << (b->first)->fecha() << std::endl;
			ventas += ( (b->second).precio_venta())*((b->second).cantidad());
			cantidad += (b->second).cantidad();
		}
		os << "==============================================="<< std::endl
		<<std::fixed<<std::setprecision(2)<<ventas << " €\t" << cantidad << std::endl << std::endl;
		ventas = cantidad = 0;
	}

}
