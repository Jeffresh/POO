#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <cstdlib>
#include<stdexcept>
#include <stdio.h>
#include <cstring>
#include<iostream>
#include<cctype>
#include<functional>
#include<string>
#include<iterator>

class Cadena
{


public:


        static const size_t npos = -1 ;// declaración adelantada.
        //definicion tipo iteradores;
        typedef char* iterator; // typedef std::iterator<char*> iterator;
        typedef const char* const_iterator; //typedef std::const_iterator<char*> const iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // funciones iteradores
        iterator begin();
        iterator end();
        const_iterator begin()const;
        const_iterator end() const;

        const_iterator cbegin()const;
        const_iterator cend()const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;


        const_reverse_iterator crbegin()const;
        const_reverse_iterator crend()const;

        // constructores
        explicit Cadena(size_t tam = 0, char c = ' ' );
        Cadena(const char* cad , size_t n=npos);
        Cadena(const Cadena& cad ,size_t posini =0, size_t length = npos);
        Cadena(Cadena&& cad);

        // operadores []
        const char operator[](size_t indice) const;
        char& operator [](size_t indice);
        char at(size_t indice) const;
        char& at(size_t indice);

        //modificadores/obvservadores
        const char* cad()const{return s_ ;}
        char* cad(){return s_ ;};
        // const size_t length()const{return tam_; }
        size_t length()const {return tam_ ;}

        Cadena substr(size_t indice, size_t tam) const;
        const char* c_str () const ;


        Cadena& operator += (const Cadena& c1);
        Cadena& operator = (Cadena&& c1);

        Cadena& operator =(const Cadena& c1);
        Cadena& operator =(const char* c1);

        ~Cadena(){delete[] s_;}




private:

        char* s_;
        size_t tam_ ;


};

//definicion de tipo


// operadores insercción/extracción.
std::ostream& operator <<(std::ostream& os, const Cadena& cad);
std::istream& operator >>(std::istream& is, Cadena& cad);


Cadena operator + ( const Cadena& cad1, const Cadena& cad2);
bool operator < ( const Cadena& cad1, const Cadena& cad2 );
bool operator >(const Cadena& cad1 , const Cadena& cad2);
bool operator ==(const Cadena& cad1, const Cadena& cad2);
bool operator !=( const Cadena& cad1, const Cadena& cad2);
bool operator <=( const Cadena& cad1, const Cadena& cad2);
bool operator >=(const Cadena& cad1, const Cadena& cad2);


inline Cadena::iterator Cadena::begin()
{

        return s_;

}

inline Cadena::iterator Cadena::end()
{

        return s_+tam_;
}

inline Cadena::const_iterator Cadena::begin()const
{

        return s_;

}

inline Cadena::const_iterator Cadena::end()const
{

        return s_+tam_;
}

inline Cadena::const_iterator Cadena::cbegin()const
{

        return s_;
}

inline Cadena::const_iterator Cadena::cend()const
{

        return s_+tam_;
}

inline Cadena::reverse_iterator Cadena::rbegin()
{
        return reverse_iterator(end());
}

inline Cadena::reverse_iterator Cadena::rend()
{
        return reverse_iterator(begin());
}

inline Cadena::const_reverse_iterator Cadena::rbegin()const
{
        return const_reverse_iterator(end());
}

inline Cadena::const_reverse_iterator Cadena::rend()const
{
        return const_reverse_iterator(begin());
}


inline Cadena::const_reverse_iterator Cadena::crbegin()const
{
        return const_reverse_iterator(cend());
}

inline Cadena::const_reverse_iterator Cadena::crend()const
{
        return const_reverse_iterator(cbegin());
}



// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std
{
        template <> struct hash<Cadena>
        {
                size_t operator()(const Cadena& cad) const
                { // conversión const char* ->string
                        return hash<string>{}(cad.c_str());
                }
        };
}


#endif
