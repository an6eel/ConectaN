/** 
 *  @file  conectaN.cpp
 *  @author  Ángel García Malagón
 *  @date    18/05/2016
 *  @version 1.0 
 *  
 *  @brief Juego de Conecta-N
 *
 *  @section DESCRIPCIÓN
 * 
 * Juego llevado a cabo entre dos jugadores
 * en un tablero de n*m dimensiones cuyo objetivo
 * es ir introduciendo fichas en el tablero hasta 
 * conseguir alinear en el tablero las n fichas
 * establecidas inicialmente para ganar la partida.
 *  
 **/
 
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "player.h"

using namespace std;

bool Save(Tablero& t,Jugador& j1,Jugador& j2){
    char nombre[1024];
    cout << "Introduzca nombre de archivo: ";
    cin.ignore();
    cin.getline(nombre,1024);
    strcat(nombre,".conf");
    
    ofstream f(nombre);
    
    f << "#MP-CONECTAN-1.0" << endl;
    f << j1;
    f << j2;
    f << t;
    f << endl;
    
    return f;   
}

bool Load(istream& f,Tablero& t,Jugador& j1,Jugador& j2){
    
    char conf[100];
    
    f.getline(conf,100);
    
    if(!strcmp(conf,"#MP-CONECTAN-1.0")){
        f >> j1;
        f >> j2;
        f >> t;
        
        return f;
    }
    
    else return false;
}

int main(int argc,char* argv[]){
    int fils,cols,fichas,f_turn;
    char name1[1024], name2[1024];
    char option;
    bool otra=true;
    int dif;
    bool columna=true;
    Jugador j1,j2;
    Tablero t;
    
    srand(time(0));

    if(argc==2){
        ifstream f(argv[1]);
        
        if(!f){
            cerr << "Error:No existe el archivo" << endl;
            return 1;
        }
        
        if(!Load(f,t,j1,j2)){
            cerr << "Error: Lectura de archivo de configuración incorrecto." << endl;
            return 1;
        }
        
    }
    
    else if(argc==1){
        
        do{
            cout << "Introduzca filas: ";
            cin >> fils;

            if(!cin){
                cerr << "Error:Lectura de filas incorrecto" << endl;
                return 1;
            }
        }while(fils<=3);
        

        do{
            cout << "Introduzca columnas: ";
            cin>>cols;

            if(!cin){
                cerr << "Error:Lectura de columnas incorrecto" << endl;
                return 1;
            }
        }while(cols <=3);

	    int min=cols<fils ? cols:fils;

        do{
            cout << "Introduzca fichas a alinear (3-" << min-1 << "): ";
            cin >> fichas;

            if(!cin){
                cerr << "Error:Lectura de fichas a alinear incorrecto" << endl;
                return 1;
            }

        }while(fichas <3 || fichas>min-1);
        
        do{
            cout << "Introduzca fichas por turno (1-" <<fichas-2 <<"): ";
            cin >> f_turn;

            if(!cin){
                cerr << "Error:Lectura de fichas por turno incorrecto" << endl;
                return 1;
            }

        }while(f_turn <1 || f_turn > fichas-2 );
        
        cin.ignore();
        
        cout << "Introduzca nombre del primer jugador: ";
        cin.getline(name1,1024);
        
        cout << "Introduzca nombre del segundo jugador: ";
        cin.getline(name2,1024);

        if(name1[0]=='@' || name2[0]=='@'){
            do{
                cout << "Elige un grado de dificultad dificultad (1-100): ";
                cin >> dif;

                if(!cin){
                    cerr << "Error:Lectura de dificultad incorrecta." <<endl;
                    return 1;
                }
            }while(dif<=0 || dif >100);
	    
	        if(name1[0]=='@')
                j1=Jugador(name1,1,dif);
	        else
                j1=Jugador(name1,1);

	        if(name2[0]=='@')
                j2=Jugador(name2,2,dif);
            else
                j2=Jugador(name2,2);

        }
        
        else{
            j1=Jugador(name1,1);
            j2=Jugador(name2,2);
        }
        
        t=Tablero(fils,cols,fichas,f_turn);
    }
    
    else{
        cerr << "Número de argumentos incorrecto" << endl;
        return 1;
    }
    
    
    while(otra){
        while(!t.Terminada()){

            if(t.TurnoActual()==1)
                    columna=j1.escogeColumna(t);
        
            else
                    columna=j2.escogeColumna(t);
               
            if(!columna){
                cerr<< "Error en la selección de la columna.¿Quiere guardar la partida? ";
                cin >> option;
                
                switch(option){
                    case 's':
                    case 'S':
                        if(Save(t,j1,j2))
                            cout << "Guardado correctamente." << endl;
                        break;;

                    default:
                        break;;
                }
                
               
            }
        }
        
        t.prettyPrint();
        j1.UpdatePoints(t);
        j2.UpdatePoints(t);
        cout << "Resultados tras esta partida: " << endl;
        j1.Results();
        j2.Results();
        cout << "¿Jugar de nuevo(S/N)?: ";
        cin >> option;
        
        switch(option){
            case 's':
            case 'S':
                t.Resetea();
                break;;
                
            case 'n':
            case 'N':
                t.Resetea(); 
                otra=false;
                break;;
                
            default:
                cout << "Opcion no valida.Salimos del juego"<< endl;
                otra=false;
                break;;
        }
    }
    
    cout << "¿Desea guardar la partida? ";
    cin >> option;
    
    switch(option){
        case 's':
        case 'S':
          
            if(Save(t,j1,j2))
                cout << "Guardado correctamente." << endl;
            break;;

        default:
            break;;
    }
                
    
    
    cout << "Resultados finales:" << endl;
    j1.Results();
    j2.Results();
    cout << j1.Empate() << " empatadas" << endl;;
        
    

}

/* Fin de fichero: conectaN.cpp */
