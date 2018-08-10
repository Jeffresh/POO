CXX = clang++
CXXFLAGS = -std=c++11  -g  -Wall -pedantic
OBJETOS1 = fecha.o fecha_check.o
OBJETOS2 = cadena.o cadena_check.o





fecha : fecha.o
	$(CXX) -o $@ $(LDFLAGS) fecha.o


fecha_check : $(OBJETOS1)
	$(CXX) -o $@ $(LDFLAGS) $(OBJETOS1)

cadena : cadena.o
	$(CXX) -o $@ $(LDFLAGS) cadena.o

cadenacheck : $(OBJETOS2)
	$(CXX) -o $@ $(LDFLAGS) $(OBJETOS2)


fecha.o: fecha.h

cadena.o: cadena.h

fecha_check.o:fct.h
cadena_check.o:fct.h

clean:
	$(RM) fecha.o cadena.o fecha_check.o cadena_check.o core *~







# checks: check_fecha check_cadena cadena.cpp fecha.cpp

# check_fecha: fecha_check fecha.cpp fecha.hpp
					# ./fecha_check  fecha.cpp  -- -std=c++11

# check_cadena: cadena_check cadena.cpp cadena.hpp
	        # ./cadena_check cadena.cpp -- -std=c++11

# fecha_check:
	        # ${MAKE} -f Make_check.mk $@

# cadena_check:
	        # ${MAKE} -f Make_check.mk $@
