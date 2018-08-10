#include "cadena.hpp"



Cadena::Cadena(size_t tam, char c):s_{new char[tam+1]},tam_{tam}
{
        for(int i=0; i<tam_; ++i)
                s_[i] = c;

        s_[tam_] = '\0';


}


Cadena::Cadena(const char * cad, size_t n)
{

        if(n >= strlen(cad))
                tam_ = strlen(cad);
         else
                tam_ = n;

         s_ = new char[tam_+1];
         for(int i=0; i<tam_; ++i)
                s_[i] = cad[i];

         s_[tam_] = '\0';

}

Cadena::Cadena(const Cadena& cad, size_t posini, size_t length)
{

        if(posini>cad.tam_)
                throw std::out_of_range("const Cadena& fuera de rango en Cadena(const Cadena&, size_t, size_t)");

        if(length > cad.tam_ - posini)
                tam_= cad.tam_;
        else
                tam_ = length;

        s_ = new char[tam_+1];
        strncpy(s_, cad.s_ + posini, tam_);
        s_[tam_]='\0';

}

Cadena::Cadena(Cadena&& cad):s_{cad.s_},tam_{cad.tam_}
{
        cad.s_= nullptr;
        cad.tam_= 0;
}

const char Cadena::operator[](size_t indice)const
{

        return *(s_+indice);
}

char& Cadena::operator[](size_t indice)
{
        return *(s_+indice);

}

char Cadena::at(size_t indice)const
{
        if( indice >= tam_)
                throw std::out_of_range ("Fuera de rango");

        return *(s_+indice);

}


char& Cadena::at(size_t indice)
{
        if(indice >= tam_)
                throw std::out_of_range ("Fuera de rango");

        return *(s_+indice);
}




Cadena Cadena::substr(size_t indice, size_t tam)const
{
        if( indice >= tam_ || (tam_ -indice) < tam)
                throw std::out_of_range(" fuera de rango");

        char* aux = new char [tam+1];

        strncpy(aux, s_+indice, tam);
        aux[tam] = '\0';

        Cadena t (aux);

        return t;
}

const char* Cadena::c_str () const
{
        if(s_!=NULL)
                return s_;
        else
                return "";
}



Cadena& Cadena::operator +=(const Cadena& c1)
{
        char* aux = new char[tam_+1];

        for(int i=0; i<tam_; i++)
                aux[i] = s_[i];

        aux[tam_] = '\0';

        delete [] s_;
        tam_ = tam_+ c1.tam_;
        s_ = new char[tam_+1];

        strcpy(s_, aux);
        strcat(s_, c1.s_);

        return *this;
}

Cadena& Cadena::operator = (Cadena&& c1)
{
        delete [ ] s_;

        s_ = c1.s_;
        c1.s_ = nullptr;
        tam_= c1.tam_ ;
        c1.tam_= 0;

        return *this;

}

Cadena& Cadena::operator =(const Cadena& c1)
{
        if(this != &c1)
        {
                delete[] s_;

                tam_ = c1.tam_;
                s_ = new char[tam_+1];

                for(int i=0; i<tam_+1; i++)
                        s_[i] = c1.s_[i];
        }

        return *this;
}

Cadena& Cadena::operator =(const char* c1)
{
        delete[] s_;

        tam_ = strlen(c1);
        s_ = new char[tam_+1];

        for(int i=0; i<tam_; i++)
                s_[i] = c1[i];

        s_[tam_] = '\0';

        return *this;

}


Cadena operator + ( const Cadena& cad1, const Cadena& cad2)
{
        Cadena t(cad1);
        t+=cad2;
        return  t;
}

bool operator < (const Cadena& cad1, const Cadena& cad2)
{
        return strcmp(cad1.cad(), cad2.cad())<0;
}

bool operator ==( const Cadena& cad1, const Cadena& cad2)
{
        return strcmp(cad1.cad(), cad2.cad()) ==0;
}

bool operator !=( const Cadena& cad1, const Cadena& cad2)
{
        return ! (cad1 == cad2);
}

bool operator >= (const Cadena& cad1, const Cadena& cad2)
{
        return !(cad1< cad2);
}

bool operator >(const Cadena& cad1 , const Cadena& cad2)
{
        return !(cad1<=cad2);
}

bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
        return (cad1 == cad2) || (cad1< cad2);
}

std::ostream& operator <<(std::ostream& os , const Cadena& cad)
{
        os<<cad.c_str();
        return os;

}

std::istream& operator >>(std::istream& is, Cadena& cad)
{

        char v[32]= "";

        is.width(32);
        is>>v;
        cad = v;
        return is;

}
