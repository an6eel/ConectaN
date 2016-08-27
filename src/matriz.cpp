/** 
 *  @file    matriz.cpp
 *  @author  Ángel García Malagón
 *  
 *  @brief Archivo con los métodos de la clase Matriz
 *
 **/

#include "matriz.h"

Matriz::Matriz(int f,int c){
        if(f>=0 && c>=0 ){
            fils=f;
            cols=c;
            datos=new int[fils*cols];
        }
        
        else{
            fils=0;
            cols=0;
            datos=0;
        }
    }

Matriz::Matriz(const Matriz& m1):fils(m1.fils),cols(m1.cols){
    datos=new int[fils*cols];
    
    for(int i=0;i<fils;++i){
        for(int j=0;j<cols;++j){
            Modifica(i,j,m1.Elemento(i,j));
        }
    }
}

Matriz::~Matriz(){
    if(datos!=0)
        delete[] datos;

}

Matriz& Matriz::operator=(const Matriz& m2){
    if(this!=&m2){
        fils=m2.fils;
        cols=m2.cols;
        delete[] datos;
        datos=new int[fils*cols];
        
        for(int i=0;i<fils;++i)
            for(int j=0;j<cols;++j)
                Modifica(i,j,m2.Elemento(i,j));
            
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matriz& m){
    os << m.Filas() << " " << m.Columnas() << std::endl;
    
    for(int i=0;i<m.Filas();++i){
        for(int j=0;j<m.Columnas();++j){
            os << m.Elemento(i,j) << " ";
        }
        os << std::endl;
    }
    
    return os;
}

std::istream& operator>>(std::istream& is,Matriz& m){
    int f,c,d;
    bool b;
    
    while(isspace(is.peek()) || is.peek()== '#'){
        if(is.peek()== '#')
            is.ignore(1024,'\n');
        else is.ignore();
    }
    
    is >> f >> c;
    
    if(is){
        Matriz aux(f,c);
        b=true;
        
        for(int i=0;i<aux.Filas() && is;++i){
            for(int j=0;j<aux.Columnas() && is && b;++j){
                is >> d;
                aux.Modifica(i,j,d);
                b=(d==1 || d==0 || d==2);
            }
        }
        
        if(b&&is){
            m=aux;
        }
        
    
    }
    
    return is;
} 

/* Fin Fichero: matriz.cpp */