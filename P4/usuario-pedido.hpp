#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_
#include <set>
#include <map>


 class Usuario_Pedido
 {
 public:

         typedef std::set<Pedido*> Pedidos;
         void asocia(Usuario&, Pedido&);
         void asocia(Pedido&, Usuario&);
         const Pedidos& pedidos(Usuario&);
          Usuario* cliente(Pedido&);


 private:

         std::map<Usuario*, Pedidos> AD;
         std::map<Pedido*, Usuario*> AI;
 };

 inline void Usuario_Pedido::asocia(Usuario& u, Pedido& p)
 {
         AD[&u].insert(&p);
         AI[&p] = &u;
 }

 inline void Usuario_Pedido::asocia(Pedido& p, Usuario& u)
 {
         asocia(u,p);
 }

inline  const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& u)
 {
         return AD[&u];
 }

 inline Usuario* Usuario_Pedido::cliente(Pedido& p)

 {
         return AI[&p];
 }

#endif
