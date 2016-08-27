/**
  * @file matriz.h
  * @brief Fichero cabecera la gestión interna de una matriz
  *
  * Permite la gestión de una matriz en memoria dinámica
  *
  */


#ifndef _MATRIZ_H
#define _MATRIZ_H

    #include <cassert>   
    #include <iostream>
     
    /**
     * \class Matriz
     * @brief Gestiona los datos y la memoria de la matriz
     * 
     **/
     
    class Matriz{
        int* datos;
        int fils,cols;
     public:
        
        /// Constructor por defecto.

        Matriz(){
            fils=cols=0;
            datos=0;
        }
        
        /// Constructor de copias.
        
        Matriz(const Matriz& m2);
        
        /**
         * @brief Constructor por parametros
         * @param f filas de la matriz
         * @param c columnas de la matriz
         * 
         **/
         
        Matriz(int f,int c);
        
        /// Destructor
        
        ~Matriz();
        
        /// Operador de asignación
        
        Matriz& operator=(const Matriz& m2);
        
        /**
        * @brief Filas de la matriz
        * @return Devuelve el número de filas de la matriz
        *
        */
        int Filas() const {return fils;}
        
        /**
        * @brief Columnas de la matriz
        * @return Devuelve el número de columnas de la matriz
        *
        */
        
        int Columnas() const {return cols;}
        
        /**
        * @brief Elemento de una matriz
        * @param i indice de la fila 
        * @param j indice de la columna
        * @return Devuelve el elemento de la posición (i,j) de la matriz
        * @pre Los valores i y j deben ser los de una posición válida de la matriz
        *
        */
        
        int Elemento(int i,int j) const{
            assert(i>=0 && j>=0 && i<fils && j<cols);
                return datos[i*cols+j];
        }    
         /**
        * @brief Modifica el elemento de una matriz
        * @param i indice de la fila 
        * @param j indice de la columna
        * @param dato dato a introducir en la posición 
        * @pre Los valores i y j deben ser los de una posición valida de la matriz
        *
        */
        
        void Modifica(int i,int j,int dato){
            if(i>=0 && j>=0 && i<fils && j<cols)
                datos[i*cols+j]=dato;
        }
        
        /// Operador de Salida <<
        friend std::ostream& operator<<(std::ostream& os, const Matriz& m);
        
        /// Operador de Entrada >>
        friend std::istream& operator>>(std::istream& is, const Matriz& m);
            
    };
    
    std::ostream& operator<<(std::ostream& os, const Matriz& m);
    
    std::istream& operator>>(std::istream& is,Matriz& m);

#endif //_MATRIZ_H

/* Fin Fichero: matriz.h */