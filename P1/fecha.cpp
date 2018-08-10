#include "fecha.hpp"

Fecha::Fecha( int d, int m , int a): dia_{d}, mes_{m}, anno_{a}
{

        if(dia_==0 || mes_==0 || anno_==0)
        	{
        		std::time_t tiempo_calendario = std::time(nullptr);
        		std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
        		if(dia_==0)
                                dia_ = tiempo_descompuesto->tm_mday;
        		if(mes_==0)
                                mes_ = tiempo_descompuesto->tm_mon +1;
        		if(anno_==0)
                                anno_ = tiempo_descompuesto->tm_year + 1900;
        	}

        	if(anno_<AnnoMinimo || anno_>AnnoMaximo)
        		throw Invalida("El anno esta fuera de rango.");

        	else if(mes_<1 || mes_>12)
        		throw Invalida("El mes esta fuera de rango.");

        	else if(dia_<1 || dia_>auxfecha(mes_,anno_))
        		throw Invalida("El dia esta fuera de rango.");












        // using namespace std ;
        //
        // if(d == 0)
        // {
        //         time_t tiempoilegible = time ( nullptr);
        //         tm* structiempo = localtime(&tiempoilegible);
        //         dia_ = structiempo->tm_mday;
        // }
        //
        // else
        // {
        //         bool bisiesto = (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0)) ;
        //
        //         if((m==2 && !bisiesto && d > 28) ||
        //         (m==2 && bisiesto && d >29)||
        //         (m%2== 0 && m!=2 && d > 30) ||
        //         (m%2 == 1 && d > 31 ))
        //
        //         throw Invalida("Día inválido");
        //
        // }
        //
        // if(m == 0)
        // {
        //         time_t tiempoilegible = time ( nullptr);
        //         tm* structiempo = localtime(&tiempoilegible);
        //         mes_ = structiempo->tm_mon+1;
        // }
        //
        // else
        // {
        //         if( m < 0 || m > 12)
        //                 throw Invalida("Número del mes inválido");
        // }
        //
        // if(a==0)
        // {
        //         time_t tiempoilegible = time ( nullptr);
        //         tm* structiempo = localtime(&tiempoilegible);
        //         anno_ = structiempo->tm_year + 1900;
        // }
        //
        // else
        // {
        //         if( a < AnnoMinimo || a > AnnoMaximo)
        //                 throw Invalida(" Año Inválido");
        //
        //
        // }
}

Fecha::Fecha(const char* cad)
{
        int d,m,a;
        if(sscanf(cad,"%d/%d/%d",&d,&m,&a)!=3)
                throw Invalida(" Formato incorrecto");
        else
                *this = Fecha(d,m,a);


}

Fecha& Fecha::operator +=(int dias)
{
        tm sf = { 0,0,0,dia_+dias,mes_-1,anno_-1900,0,0,0 };

        std::mktime(&sf) ;

        dia_ = sf.tm_mday;
        mes_ = sf.tm_mon+1;
        anno_ = sf.tm_year+1900;

        if(anno_>AnnoMaximo || anno_<AnnoMinimo)
                throw Invalida("Año Invalido");

        return *this;
}

Fecha& Fecha::operator -=( int dias)
{
        return *this += -dias;
}

Fecha& Fecha::operator++()
{
        return (*this) +=1;
}

Fecha Fecha::operator ++(int)
{
        Fecha t(*this);
        *this +=1;
        return t ;

}

Fecha& Fecha::operator--()
{
        return ((*this) += (-1));
}

Fecha Fecha::operator--(int)
{
        Fecha t(*this);
        *this+=(-1);
        return t;
}


Fecha operator + (const Fecha& f, int dias)
{
       return Fecha(f) +=dias;
}

Fecha operator -( const Fecha& f, int dias)
{


       return Fecha( f ) += -dias;
}

bool operator ==(const Fecha& f1, const Fecha& f2)
{
        return (f1.dia()==f2.dia() && f1.mes() && f2.mes() && f1.anno() ==f2.anno());
}

bool operator != ( const Fecha& f1, const Fecha& f2)
{
        return !(f1==f2);
}

bool operator < ( const Fecha& f1, const Fecha& f2)
{
        bool aux = false;

        if ( f1.anno() < f2.anno())
                aux =true;
        else if(f1.anno() == f2.anno() && f1.mes() < f2.mes())
                aux=true;
        else if( f1.mes() == f2.mes() && f1.dia()<f2.dia() )
                aux=true;

        return aux;

}

bool operator >(const Fecha& f1, const Fecha& f2)
{
        return (f2<f1);
}

bool operator <=(const Fecha& f1, const Fecha& f2)
{
        return ! (f1 > f2);
}

bool operator >=( const Fecha& f1, const Fecha& f2)
{
        return !(f1 < f1);
}


const char* Fecha::cadena () const
{

        tm f = {0,0,0,dia_,mes_-1,anno_-1900,0,0,0 };

        static const char* m [] = {"enero", "febrero", "marzo", "abril", "mayo","junio", "julio", "agosto", "septiembre","octubre", "noviembre", "diciembre" };
        static const char* d [] ={"domingo","lunes", "martes", "miércoles", "viernes", "sábado" };
        static char* cad = new char[sizeof("Miércoles 00 de Septiembre de AAAA")];

        std::mktime(&f);

        sprintf(cad,"%s %d de %s de %d",*(d+f.tm_wday),dia_,*(m+f.tm_mon),anno_);
        // std::cout<<cad<< std::endl;

return cad;

}

long int operator - (const Fecha& f1, const Fecha& f2)
{
        // tm* f{};
        // f->tm_mday = f1.dia();
        // f->tm_mon = f1.mes();
        // f->tm_year = f1.anno();
        //
        // time_t tiempoilegible = mktime(f);
        // f = localtime(&tiempoilegible);
        //
        // long int f1d = f->tm_yday;
        //
        //
        // f->tm_mday = f2.dia();
        // f->tm_mon = f2.mes();
        // f->tm_year = f2.anno();
        //
        // tiempoilegible = mktime(f);
        // f = localtime(&tiempoilegible);
        //
        // long int f2d = f->tm_yday;
        //
        // return std::abs(f1d-f2d);
        tm sf1 = {0,0,0,f1.dia(),f1.mes()-1,f1.anno()-1900,0,0,0 };
	tm sf2 = {0,0,0,f2.dia(),f2.mes()-1,f2.anno()-1900,0,0,0 };
	long int tiempof1 = std::mktime(&sf1);
	long int tiempof2 = std::mktime(&sf2);

	return std::difftime(tiempof1,tiempof2)/86400;


}

std::ostream& operator <<(std::ostream& os, const Fecha& f)
{
        os<<f.cadena();
        return os;

}


std::istream& operator >>(std::istream& is, Fecha& f)
{
        char v[11];
        is.width(11);
        is >> v;
        f = Fecha(v);


        return is;
}



int Fecha::auxfecha(int m, int a)
{
	int ndiasmes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

        bool bisiesto = ((a % 4 == 0) && (a % 400 == 0 || a % 100 != 0));

	if(m==2 && bisiesto)
		return 29;
	else
		return ndiasmes[m];
}
