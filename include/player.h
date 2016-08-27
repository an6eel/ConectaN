/**
  * @file player.h
  * @brief Fichero cabecera para la gestión de un jugador de Conecta-N
  *
  * Permite la gestión de un jugador durante la partida de Conecta-N
  *
  */

#include "tablero.h"

#ifndef _PLAYER_H
#define _PLAYER_H
     
    #include <iostream>
    
     /**
     * \class Jugador
     * @brief Gestiona los datos del jugador durante la partida
     * 
     **/
    class Jugador{
        char* nombre;///<Nombre
        int turno;///<Turno
        int dificultad;///< Dificultad jugador
        unsigned int puntos,p_won,p_lost,p_emp;///<Resultados
	
	    /**
        * @brief Operación de insertar una columna
        * para un jugador automático de dificultad
        * elevada
        * 
        **/

        void InsertaIA(Tablero& t,int dato);

        /**
        * @brief Operación de insertar una columna
        * para un jugador automático de dificultad
        * fácil
        * 
        **/

	
        void InsertaIAFacil(Tablero& t,int dato);

        /**
        * @brief Operación de insertar una columna
        * para un jugador automático de dificultad
        * normal
        * 
        **/

	
        void InsertaIAMedio(Tablero& t,int dato);

        /**
        * @brief Actualiza la dificultad según se 
        * desarrollen las partidas
        *
        **/

        void UpdateLevel();
        
     public:
        /// Constructor por defecto.
        
        Jugador():nombre(0),turno(0),puntos(0),p_won(0),p_lost(0),p_emp(0){}
        
        /**
         * @brief Contructor por parametros
         * @param name Nombre con el que se contruirá el jugador
         * @param turn Turno que tendrá el jugador en la partida
         * @param dif Dificultad del jugador
         * */
        
        Jugador(const char* name,int turn, int dif=0);
        
        /// Constructor de copias.
        
        Jugador(const Jugador& j2);
        
        /// Destructor
        ~Jugador(){
            delete[] nombre;
        }
        /**
         * @brief Partidas ganadas por el jugador
         * @return Devuelve el número de partidas ganadas por el jugador
         * */
         
        int Ganadas() const {return p_won;} 
        
        /**
         * @brief Nombre del jugador
         * @return Devuelve el nombre del jugador
         * */
        const char* Nombre() const{
            
            return nombre[0]=='@' ? nombre+1:nombre;
        }
        /**
         * @brief Partidas perdidas por el jugador
         * @return Devuelve el número de partidas perdidas por el jugador
         * */

        int Perdidas() const {return p_lost;}
        
        /**
         * @brief Partidas empatadas por el jugador
         * @return Devuelve el número de partidas empatadas por el jugador
         * */
        
        int Empate() const {return p_emp;}
        
        /**
         * @brief Muestra en pantalla los datos del jugador
         * */
        
        void Results() const {
            std::cout << Nombre() << ": " << p_won << " ganadas que acumulan " << puntos << " puntos"<<std::endl;
        }
        /**
         * @brief Acumula los puntos obtenidos en la partida
         **/
        
        void UpdatePoints(const Tablero& t);
        
        /**
         * @brief Escoge una columna del tablero para introducir la ficha
         * @param t Tablero de la partida
         * @retval true si se introduce en una posición correcta
         * @reval false si no se introduce en una posición correcta
         **/
        bool escogeColumna(Tablero& t);
        
        /// Operador de asignacióm
        Jugador& operator=(const Jugador& j2);
	
        /// Operador de Salida <<
        friend std::ostream& operator<<(std::ostream& os,const Jugador& j);
        
        /// Operador de Entrada >>
        friend std::istream& operator>>(std::istream& is,Jugador& j);

    };
    
    std::ostream& operator<<(std::ostream& os,const Jugador& j);
    
    std::istream& operator>>(std::istream& is,Jugador& j);
    
#endif //_PLAYER_H

/* Fin Fichero: player.h */
