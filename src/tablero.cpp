/** 
  *  @file tablero.cpp
  *  @author Ángel García Malagón
  *  
  *  @brief Archivo con los métodos de la clase Tablero
  *
  **/

#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <vector>

bool Tablero::Terminada() const {
        if(EsGanador(1,fichas) || EsGanador(2,fichas) || Lleno())
            return true;
            
        else return false;
}

void Tablero::prettyPrint(ostream& os) const {
        char letra='a';
        for(int i=0;i<m.Columnas();++i){
            os << " "<< letra;
            letra++;
        }
        os << endl;
        
        for(int i=0;i<m.Filas();++i){
            for(int j=0;j<m.Columnas()+1;++j){
                os << "|";
                
                if(j<m.Columnas()){
                    if(m.Elemento(i,j)==1)
                        os << "x";
                    
                    else if(m.Elemento(i,j)==2)
                        os << "o";
                        
                    else
                        os << " ";
                }
            }
            os << std::endl;
        }
        
        for(int j=0;j<2*m.Columnas()+1;++j){
            os << "=";
        }
        
        os << endl;
        
        
        if(Terminada()){
            if(Ganador()==0){
                os << "Partida finalizada.Empate." << endl; 
            }
            else
                os << "Partida finalizada. Ganador: jugador " << Ganador() << endl;
        }
        
        else{
            if(TurnoActual()==1){
                os << "Turno: jugador 1: (x)" << endl;
            }
            
            else
                os << "Turno: jugador 2: (o)" << endl;
        }
}

bool Tablero::Lleno() const {
    
    for(int i=0;i<Columnas();++i){
        if(m.Elemento(0,i)==0)
            return false;
    }
        
    return true;
}

bool Tablero::EnRaya(int i,int j,int tipo,int n) const {
    
    int auxi,auxj;
    int cdi,cdd,ch,cv;
    
    auxi=i;
    auxj=j;
    
    if(Elemento(i,j)==tipo){
        cdi=cdd=ch=cv=1;
        
        while(j>0 && i>0 && Elemento(--i,--j)==tipo)
            cdi++;
            
        i=auxi;
        j=auxj;
            
        while(j<Columnas()-1 && i>0 && Elemento(--i,++j)==tipo)
            cdd++;
            
        i=auxi;
        j=auxj;
        
        while(j<Columnas()-1 && Elemento(i,++j)==tipo)
            ch++;
            
        i=auxi;
        j=auxj;
            
        while(i>0 && Elemento(--i,j)==tipo)
            cv++;

        return (ch>=n || cv>=n || cdi >=n || cdd>=n);
    }

    else return false;

}

int Tablero::Puntuacion() const {
    int punt=30;
    
    if(Filas()==6 && Columnas()==7)
        punt+=20;
        
    else if(Filas()>6 && Columnas()>7)
        punt+=30;
        
        else 
            punt+=25;
        
    if(fichas==4)
        punt+=27;
        
    else if(fichas>4)
        punt+=37;
        
    if(EsGanador(1,fichas+2) || EsGanador(2,fichas+2))
        punt+=40;
        
    else if(EsGanador(1,fichas+1) || EsGanador(2,fichas+1))
        punt+=20;

    return punt;        
}
    
bool Tablero::EsGanador(int tipo,int nfichas) const{
    
    int i=Filas()-1,j;
    
    while(i>=0){
            j=0;
            while(j<Columnas()){
                if(Elemento(i,j)==tipo){
                    if(EnRaya(i,j,tipo,nfichas)){
                      return true;
                    }
                }
                ++j;
            }
            --i;
        }
        
    return false;
}

int Tablero::Ganador() const{
            
    if(Lleno())
        return 0;
        
    else if(EsGanador(1,fichas))
        return 1;
        
        else if(EsGanador(2,fichas))
            return 2;
            
            else return 0;
}

int Tablero::TurnoActual() const{
        bool fila_vacia=false;
        int turno=inicio;
        
        for(int i=Filas()-1;i>=0&& !fila_vacia;--i){
            fila_vacia=true;
            
            for(int j=0;j<Columnas();++j){
                if(Elemento(i,j)!=0){
                    turno++;
                    fila_vacia=false;
                }
            }
        }
        
        if(f_turno==1)
            return ((turno%2) ==1) ? 1:2;
            
        else {
            int n=(turno%(2*f_turno));
            
            if(inicio==1)
                return( n<= f_turno && n!=0 ) ? 1:2;
            else
                return (n<=f_turno+1 && n!=0 && n!=1 ) ? 2:1;
        }
}

int Tablero::Tiradas_Quedan() const{
    bool fila_vacia=false;
    int turno=0;
    
    for(int i=Filas()-1;i>=0&& !fila_vacia;--i){
        fila_vacia=true;
        
        for(int j=0;j<Columnas();++j){
            if(Elemento(i,j)!=0){
                turno++;
                fila_vacia=false;
            }
        }
    }
    return f_turno-turno%f_turno;
}
    
void Tablero::Inserta(int dato,int c){
        int i=Filas()-1;
        
        if(Elemento(i,c)==0)
            m.Modifica(i,c,dato);
        

        else{
            --i;
            while(i>=0){
                if(Elemento(i,c)==0){
                    m.Modifica(i,c,dato);
                    break;
                }
                
                --i;
            }
        }
}

void Tablero::Resetea(){
     inicio=inicio==1 ? 2:1;

     for(int i=0;i<Filas();++i){
            for(int j=0;j<Columnas();++j){
                m.Modifica(i,j,0);
            }
     }
}

Tablero& Tablero::operator=(const Tablero& t2){
    if(this!=&t2){
        m=t2.m;
        f_turno=t2.f_turno;
        fichas=t2.fichas;
        inicio=t2.inicio;
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& os,const Tablero& t){
    os << t.fichas << " " << t.f_turno << std::endl;
    os << t.m;
    
    return os;
}

std::istream& operator>>(std::istream& is,Tablero& t){
    
    is >> t.fichas;
    is >> t.f_turno;
    is >> t.m;
    
    return is;
}

std::vector<int> Tablero::Posibilidades(int f,int c,int dato) const {
    std::vector<int> v;
    int contrario=dato==1 ? 2:1;
    int value_iz=0;
    int value_der=0;
    bool iz=true,der=true;

    //Horizontal
    for(int i=c-fichas+1;i<c+fichas;++i){
        if(i<c){
            if(i>=0 && iz && (Elemento(f,i)==dato || Elemento(f,i)==0))
                ++value_iz;
            
            else if( i>=0 && Elemento(f,i)==contrario)
                iz=false;
        }

        else if(i>c){
            if(i<Columnas() && der && (Elemento(f,i)==dato || Elemento(f,i)==0))
                ++value_der;

            else if(i<Columnas() && Elemento(f,i)==contrario)
                der=false;
        }
    }

    if(value_iz==fichas-1)
        v.push_back(1);
    else 
        v.push_back(0);

    if(value_der==fichas-1)
        v.push_back(1);
    else
        v.push_back(0);

    if(value_iz!=0 && value_der!=0 &&(value_iz+value_der) >=fichas-1)
        v.push_back(1);
    else
        v.push_back(0);
    
    value_iz=value_der=0;
    iz=der=true;


    //Diagonal principal

    for(int i=f+fichas-1,j=c-fichas+1;i>f-fichas && j<c+fichas;--i,++j){
        if(j<c){
            if(i<Filas() && j>=0 && iz && (Elemento(i,j)==dato || Elemento(i,j)==0))
                ++value_iz;
            
            else if(i<Filas() && j>=0 && Elemento(i,j)==contrario)
                iz=false;
        }

        else if(j>c){
            if(i>=0 && j<Columnas() && der && (Elemento(i,j)==dato || Elemento(i,j)==0))
                ++value_der;

            else if(i>=0 && j<Columnas() && Elemento(i,j)==contrario)
                der=false;
        }
    }

    if(value_iz==fichas-1)
        v.push_back(1);
    else 
        v.push_back(0);

    if(value_der==fichas-1)
        v.push_back(1);
    else
        v.push_back(0);

    if(value_iz!=0 && value_der!=0 &&(value_iz+value_der) >=fichas-1)
        v.push_back(1);
    else
        v.push_back(0);
    
    value_iz=value_der=0;
    iz=der=true;

    //Vertical

    for(int i=f-fichas+1;i<f+fichas;++i){
        if(i<f){
            if(i>=0 && iz && (Elemento(i,c)==dato || Elemento(i,c)==0))
                ++value_iz;
            
            else if(i>=0 && Elemento(i,c)==contrario)
                iz=false;
        }

        else if(i>f){
            if(i<Filas() && der && (Elemento(i,c)==dato || Elemento(i,c)==0))
                ++value_der;

            else if(i<Filas() && Elemento(i,c)==contrario)
                der=false;
        }
    }

    if(value_iz==fichas-1)
        v.push_back(1);
    else 
        v.push_back(0);

    if(value_der==fichas-1)
        v.push_back(1);
    else
        v.push_back(0);

    if(value_iz!=0 && value_der!=0 &&(value_iz+value_der) >=fichas-1)
        v.push_back(1);
    else
        v.push_back(0);
    
    value_iz=value_der=0;
    iz=der=true;

    //Diagonal opuesta
    
    for(int i=f-fichas+1,j=c-fichas+1;i<f+fichas && j>c-fichas;++i,++j){
        if(j<c){
            if(i>=0 && j>=0 && iz && (Elemento(i,j)==dato || Elemento(i,j)==0))
                ++value_iz;
            
            else if(i>=0 && j>=0 && Elemento(i,j)==contrario)
                iz=false;
        }

        else if(j>c){
            if(i<Filas() && j<Columnas() && der && (Elemento(i,j)==dato || Elemento(i,j)==0))
                ++value_der;

            else if(i<Filas() && j<Columnas() && Elemento(i,j)==contrario)
                der=false;
        }
    }


    if(value_iz==fichas-1)
        v.push_back(1);
    else 
        v.push_back(0);

    if(value_der==fichas-1)
        v.push_back(1);
    else
        v.push_back(0);

    if(value_iz!=0 && value_der!=0 &&(value_iz+value_der) >=fichas-1)
        v.push_back(1);
    else
        v.push_back(0);
    
    value_iz=value_der=1;
    iz=der=true;




    return v;
}

int Tablero::Heuristica(int dato,int c){
    int contrario= dato==1 ? 2:1,pos=0;
    int value_d=0,value_c=0;
    std::vector<int> v1,v2;
    Tablero aux1(*this);

    if(Elemento(0,c)==0){
        Inserta(contrario,c);

        if(Ganador()==contrario)
            return 100;

        else if(aux1.Elemento(0,c)==0){
            while(pos <Filas() && aux1.Elemento(pos,c)==0)
                ++pos;
            --pos;

            v1=aux1.Posibilidades(pos,c,dato);
            v2=aux1.Posibilidades(pos,c,contrario);

            for(unsigned int i=0;i<v1.size();++i)
                if(v1[i]==1)
                    ++value_d;

            for(unsigned int j=0;j<v2.size();++j)
                if(v2[j]==1)
                    ++value_c;
            
            
            bool v=true;
            int first=0;
            for(int i=Filas()-1;i>=0 && v;--i){
                v=false;
                for(int j=0;j<Columnas();++j){
                    
                    if(Elemento(i,j)!=0){
                        ++first;
                        v=true;
                    }
                }
            }

            if(first==1)
                return value_d;
            else{
                aux1.Inserta(dato,c);
            
                if(aux1.Ganador()==dato)
                    return 101;

                else if(Elemento(0,c)==0){
                    aux1.Inserta(contrario,c);

                    if(aux1.Ganador()==contrario)
                        return -100;

                    else return value_d>value_c ? value_d:abs(value_d-value_c);
                }

                else return value_d>value_c ? value_d:abs(value_d-value_c);

            }
        }

        else return -101;
    }

    else return -101;
}

/* Fin Fichero: tablero.cpp */
