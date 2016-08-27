/**
  * @file tablero.h
  * @brief Fichero cabecera para la gestión de un tablero de conecta-N
  *
  * Permite la gestión del tablero
  *
  */

#ifndef _TABLERO_H
#define _TABLERO_H
   
    #include "matriz.h"
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    /**
     *  \class Tablero
     *  @brief Gestiona la partida de Conecta-N
     * 
     **/
     
    class Tablero{
        Matriz m;///< Matriz del tablero
        int fichas;///< Fichas a alinear
        int inicio;///< Jugador que empieza
        int f_turno;///< Fichas a introducir por turno
        
        /**
         * @brief Comprueba si a partir de una posicion
         * se ha conseguido alinear la fichas establecidas
         * @param i indice de fila
         * @param j indice de columna
         * @param tipo Ficha que se comprubea
         * @param n numero de fichas a alinear
         * @retval true si se han alineado el numero de fichas
         * establecido
         * @retval false si no se han alineado
         * 
         **/
         
        bool EnRaya(int i,int j,int tipo,int n) const;
        
        /**
         * @brief Analiza todas las posiciones del tablero
         * para comprobar si se han conseguido alinear
         * las nfichas establecidas
         * @param tipo Ficha a comprobar
         * @param nfichas Fichas a alinear
         * @retval true si se ha hecho n en raya en alguna posicion
         * @retval fañse si no se ha conseguido n en raya
         * @see EnRaya
         * 
         **/
         
        bool EsGanador(int tipo,int nfichas) const ;
        
     public:
        /// Contructor por defecto
        Tablero():m(){
            fichas=0;
            inicio=0;
            f_turno=0;
        }
        
        /**
         * @brief Contructor por parametros
         * @param f Filas del tablero
         * @param c Columnas del tablero
         * @param fic Fichas a alinear
         * @param fic_turn Fichas por turno
         * 
         **/
         
        Tablero(int f,int c,int fic,int fic_turn): m(f,c){
            assert(fic > 0);
            fichas=fic;
            inicio=1;
            
            if(fic_turn>(fichas-2))
                f_turno=1;
                
            else
                f_turno=fic_turn;
            
            for(int i=0;i<m.Filas();++i){
                for(int j=0;j<m.Columnas();++j){
                    m.Modifica(i,j,0);
                }
            }
        }
        
        /**
         * @brief Filas del tablero
         * @return Devuelve las filas del tablero
         * 
         **/
         
        int Filas() const{return m.Filas();}
        
        /**
         * @brief Columnas del tablero
         * @return Devuelve las columnas del tablero
         * 
         **/
         
        int Columnas() const {return m.Columnas();}
        
        /**
         * @brief Fichas a alinear
         * @return Devuelve las fichas que se deben alinear
         * 
         **/
         
        int Fichas() const {return fichas;}
        
        /**
        * @brief Elemento del tablero
        * @param i indice de la fila 
        * @param j indice de la columna
        * @return Devuelve el elemento de la posición (i,j) del tablero
        * @pre Los valores i y j deben ser los de una posición válida del tablero
        *
        */
        int Elemento(int i,int j) const {return m.Elemento(i,j);}
        
        /**
         * @brief Comprueba si el tablero está lleno
         * @retval true si el tablero está lleno
         * @retval false si el tablero no está lleno
         * 
         **/
         
        bool Lleno() const ;
        
        /**
         * @brief Fichas por turno
         * @return Devuelve el numero de fichas por turno
         * 
         **/
         
        int Fichas_Turn() const {return f_turno;}
        
        /**
         * @brief Número de tiradas que quedan en el turno
         * @return Devuelve las tiradas que quedan en el turno
         * 
         **/
         
        int Tiradas_Quedan() const;
        
        /**
         * @brief Comprueba si la partida ha terminado
         * @retval true si ha ganado algún jugador o se ha empatado
         * @retval false si no ha ganado nadie y el tablero aún no está lleno
         * 
         **/
         
        bool Terminada() const;
        
        /**
         * @brief Dibuja en la entrada éstandar el tablero
         * 
         **/
        void prettyPrint(ostream& os=std::cout) const ;
        
        /**
         * @brief Ganador de la partida
         * @retval 1 Si ha ganado el jugador 1
         * @retval 2 Si ha ganado el jugador 2
         * @retval 0 Si han empatado
         * 
         **/
         
        int Ganador() const ;
        
        /**
         * @brief Gestiona el turno de la partida
         * @retval 1 si le toca tirar al jugador 1
         * @retval 2 si le toca tirar al jugador 2
         * 
         **/
         
        int TurnoActual() const ;
        
        /**
         * @brief Puntuación de la partida
         * @return Devuelve la puntuación de la partida
         * 
         **/
         
        int Puntuacion() const ;
        
        /**
         * @brief Inserta una ficha en una columna
         * @param dato ficha a introducir
         * @param c columna donde se introduce la ficha
         * 
         **/
         
        void Inserta(int dato,int c);

        /**
         * @brief Vacia el tablero
         * 
         **/

        void Resetea();
        
        /**
         * @brief Posibilidades favorables del jugador en la posicióm
         * (i,j)
         * @param f Indice de la fila
         * @param c Indice de la columna
         * @param dato Dato sobre el que se busca las posibilidades
         * favorables
         * @return Vector de posibilidades favorables
         *
         **/

        std::vector<int> Posibilidades(int f,int c,int dato) const ;

        /**
         * @brief Función heuristica que analiza como es de
         * favorable introducir una ficha en una posición
         * @param f Indice de la fila
         * @param c Indice de la columna
         * @param dato Dato sobre el que se realiza la
         * heuristica
         * @return valoración según sea de favorable introducir
         * la ficha en la posición determinada
         *
         */
         
        int Heuristica(int dato,int c);

        /// Operador de asignación
        Tablero& operator= (const Tablero& t2);
        
        /// Operador de Salida <<
        friend std::ostream& operator<<(std::ostream& os,const Tablero& t);
        
        /// Operador de Entrada >>
        friend std::istream& operator>>(std::istream& is,Tablero& t);
    };
    
    std::ostream& operator<<(std::ostream& os,const Tablero& t);
    
    std::istream& operator>>(std::istream& is,Tablero& t);


#endif //_TABLERO_H

/* Fin Fichero: tablero.h */
