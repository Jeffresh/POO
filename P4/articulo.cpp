#include"articulo.hpp"
#include<iostream>
#include<iomanip>


Articulo::Articulo(const Articulo::Autores& a ,const Cadena& ref, const Cadena& titulo, const  Fecha& f, double precio)
 :  ref_{ref},titulo_{titulo},f_publi_{f},precio_{precio},autores_{a}
 {
         if(autores_.empty())
                throw Autores_vacios();
 }

std::ostream& operator <<(std::ostream& os, const Articulo& a )
{

        bool flag = true;
        os<<"["<<a.referencia()<<"] \"" <<a.titulo()<< "\", de ";


        for( auto i = a.autores().begin(); i!= a.autores().end(); i++)
        {
                if(flag == true)
                {
                        os<<(*i)->apellidos();
                        flag= false;
                }

                else
                {
                        os<<", "<<(*i)->apellidos();
                }
        }

        os<<". "<<a.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<a.precio()<<" €\n";


        a.impresion_especifica(os);

        return os;



}

void Libro::impresion_especifica(std::ostream& os) const
{
        os<<"\t"<<n_pag_<<" págs., "<<stock_<<" unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const
{
        os<<"\t"<<tam_<<" MB, "<<stock_<<" unidades.";
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
         os<<"\tA la venta hasta el "<<f_expir_<<".";
}



// void Articulo::impresion_especifica(std::ostream& os)const
// {
//         if( Libro* lb = dynamic_cast<Libro*>(this) )
//         {
//                 // char buffer[100];
//
//                 // if(std::snprintf(buffer,100, "[%s] ,%s, de  %s \" ,%d, %f € ",this->referencia(), this->titulo().c_str(),this->Autores this->f_publi().anno(), this->precio() ) <0)
//                 os<<"\t"<<n_pag()<<"págs ."<<stock()<<"unidades." ;
//                         // std::cout<<"Demasiado largo para el buffer auxiliar, salida erronea"<< std::endl;
//         }
//
//         if(LibroDigital* ld = dynamic_cast<LibroDigital*>(this))
//         {
//                 // char buffer[100];
//
//                 // if(std::snprintf(buffer,100, "[%s] \" %s \" ,%d, %f € ",a.referencia().c_str(), a.titulo().c_str(), a.f_publi().anno(), a.precio() ) <0)
//
//                         // std::cout<<"Demasiado largo para el buffer auxiliar, salida erronea"<< std::endl;
//
//                 os<<"\t"<<tam()<<" MB,"<<stock()<<" unidades.";
//
//         }
//
//         if(Cederron* cd = dynamic_cast<Cederron*>(this))
//         {
//
//                 // char buffer[100];
//
//                 // if(std::snprintf(buffer,100, "[%s] \" %s \" ,%d, %f € ",a.referencia().c_str(), a.titulo().c_str(), a.f_publi().anno(), a.precio() ) <0)
//
//                         // std::cout<<"Demasiado largo para el buffer auxiliar, salida erronea"<< std::endl;
//
//                 os<<"\t A la venta hasta el "<<f_expir()<<". ";
//                 // os<< buffer;
//
//         }

//}
