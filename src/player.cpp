/** 
 *  @file    player.cpp
 *  @author  Ángel García Malagón
 *  
 *  @brief Archivo con los métodos de la clase Jugador
 *
 **/

#include "player.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>


Jugador::Jugador(const char* name,int turn,int dif):dificultad(dif){
    nombre=new char[strlen(name)+1];
    strcpy(nombre,name);
    turno=turn;
    p_won=p_lost=p_emp=puntos=0;
}

Jugador::Jugador(const Jugador& j2):turno(j2.turno){
    nombre=new char[strlen(nombre)+1];
    strcpy(nombre,j2.nombre);
    p_won=j2.p_won;
    p_lost=j2.p_lost;
    p_emp=j2.p_emp;
    puntos=j2.puntos;
    dificultad=j2.dificultad;
}

void Jugador::UpdatePoints(const Tablero& t){
    if(t.Ganador()==turno){
        puntos+=t.Puntuacion();
        p_won++;
    }
    
    else if(t.Ganador()==0){
        puntos+=(t.Puntuacion())/2;
        p_emp++;
        }
        
        else
            p_lost++;

	UpdateLevel();
}

inline int Uniforme(int min,int max){
    double u01=rand()/ (RAND_MAX+1.0);
    return min + (max-min+1)*u01;
}

bool Jugador::escogeColumna(Tablero& t){
    t.prettyPrint();
    
    char c;
    int al,difmod=dificultad<50 ? dificultad:dificultad-50;
    int k=0;
    char col=t.Columnas()-1;
    
    if(nombre[0]=='@'){
        al=Uniforme(1,50);

        if(dificultad>50){
            
            if(al<difmod)
            	InsertaIA(t,turno);
            
            else
            	InsertaIAMedio(t,turno);
        }
	
        else{
        	
            if(al<difmod)
        		InsertaIAMedio(t,turno);
        	else
        		InsertaIAFacil(t,turno);
        }
                
        std::cout << Nombre() << " ha insertado su ficha.(" << dificultad << ") " << std::endl;
        return true;
    }
    
    
    else{
        std::cout << Nombre()<< ", escoja una columna (letra a-" << (char)('a'+col) <<") para la ficha " << t.Fichas_Turn()-t.Tiradas_Quedan()+1 << " de " << t.Fichas_Turn() << ": ";
        std::cin >> c;
        std::cout << std::endl;
        c=tolower(c);
            
        if( c<'a' || c>'a'+col)
            return false;
        
        k=c-'a';
        
        if(t.Elemento(0,k)!=0){
            return false;
        }
        
        else{
            t.Inserta(turno,k);
            return true;
        }
        
    } 
}

std::ostream& operator<<(std::ostream& os,const Jugador& j){
    
    os << "#" << j.nombre << std::endl;
    os << j.puntos << " " << j.p_won << " " << j.p_emp << " " << j.p_lost << " " << j.turno << " " << j.dificultad << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is,Jugador& j){
    while(is&&is.peek()!= '#'){
            is.ignore(1024,'\n');
    }
    
    is.ignore();
    
    char nombre[1024];
    is.getline(nombre,1024);
    
    j.nombre=new char[strlen(nombre)+1];
    strcpy(j.nombre,nombre);
    is >> j.puntos >> j.p_won >> j.p_emp >> j.p_lost >> j.turno >> j.dificultad;

    return is;
    
}

Jugador& Jugador::operator=(const Jugador& j2){
    if(this!=&j2){
        delete[] nombre;
        nombre=new char[strlen(j2.nombre)+1];
        strcpy(nombre,j2.nombre);
        turno=j2.turno;
        puntos=j2.puntos;
        p_won=j2.p_won;
        p_emp=j2.p_emp;
        p_lost=j2.p_lost;
        dificultad=j2.dificultad;
    }
    
    return *this;
}

void Jugador::InsertaIA(Tablero& t,int dato){
    int valor=-1000,heux,pos;

    for(int i=0;i<t.Columnas();++i){
        Tablero aux(t);
        heux=aux.Heuristica(dato,i);

        if(heux>= valor){
            pos=i;
            valor=heux;
        }
    }

    t.Inserta(dato,pos);

}

void Jugador::InsertaIAFacil(Tablero& t,int dato){
    int c=Uniforme(0,t.Columnas()-1);

    while(t.Elemento(0,c)!=0){
        c=Uniforme(0,t.Columnas()-1);
    }

    t.Inserta(dato,c);
}

void Jugador::InsertaIAMedio(Tablero& t,int dato){
    int contrario=dato==1 ? 2:1;
    int c=-1;

    for(int i=0;i<t.Columnas();++i){
        Tablero aux(t);

        aux.Inserta(contrario,i);

        if(aux.Ganador()==contrario)
            c=i;
    }

    if(c==-1){
        c=Uniforme(0,t.Columnas()-1);

        while(t.Elemento(0,c)!=0){
            c=Uniforme(0,t.Columnas()-1);
        }

        t.Inserta(dato,c);
    }

    else
        t.Inserta(dato,c);
}

void Jugador::UpdateLevel(){
	if(nombre[0]=='@'){		
		if((int)(p_lost-p_won)>=4){		
			dificultad+=3;
			dificultad=dificultad>100 ? 100:dificultad;
		}
		
		else if((int)(p_won-p_lost)>=4){			
			dificultad-=3;;
			dificultad=dificultad<1 ? 1:dificultad;
		}
	}
}

/* Fin Fichero: player.cpp */