.PHONY: clean mrproper all

AR= ar
CXX= g++

#Carpetas

INC= include
SRC= src
OBJ= obj
BIN= bin
LIB= lib

CXXFLAGS= -Wall -g -I./include
LDFLAGS= -L./lib
LDLIBS= -lpartida
 	
all : $(BIN)/conectaN 

clean :
	echo "Limpiando..."
	-rm $(OBJ)/*.o $(LIB)/*.a

mrproper : clean
	-rm $(BIN)/conectaN ./*.conf ./doc/html/*

documentacion:
	doxygen doc/doxys/Doxyfile
	
#Archivos Objeto

$(OBJ)/tablero.o : $(INC)/matriz.h $(INC)/tablero.h $(SRC)/tablero.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/tablero.cpp

$(OBJ)/matriz.o : $(INC)/matriz.h $(SRC)/matriz.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/matriz.cpp
	
$(OBJ)/jugador.o : $(INC)/player.h $(INC)/tablero.h $(SRC)/player.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/player.cpp
	
$(OBJ)/conectaN.o : $(INC)/matriz.h $(INC)/tablero.h $(INC)/player.h $(SRC)/conectaN.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/conectaN.cpp

# Mains

$(BIN)/conectaN : $(OBJ)/conectaN.o $(LIB)/libpartida.a
	$(CXX) $(CXXFLAGS) -o  $@ $(OBJ)/conectaN.o $(LDFLAGS) $(LDLIBS) 

	
# Librerias

$(LIB)/libpartida.a : $(OBJ)/tablero.o $(OBJ)/jugador.o $(OBJ)/matriz.o
	$(AR) rvs $@ $(OBJ)/tablero.o $(OBJ)/jugador.o $(OBJ)/matriz.o

