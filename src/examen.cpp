         
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "../lib/rrColor.h"
using namespace std;

const string RRCEDULA = "1003781018";
const string RRNOMBRE = "Ruth Fernanda Rueda Rueda";
const string RRCORREO = "ruth.rueda@epn.edu.ec";

struct rrCoordenada{
     int capacidadBelica;       
     string geolocalizacion;       
     string detalleArsenal;     
     struct rrCoordenada *izq, *der;
};


void Loading(string str)
{ 
    string c= " \\|/-"; 
    for(int i=0; i<= 100; i++)
    {   
        cout<< "\r " << c[i % 4] << " " << i << "%   ";
        usleep(5000);
    }
    cout << str  << endl;
}
/**
 * rrGetCoordenadas : procedimiento para leer las coordenadas desde un archivo .txt
*/
void rrGetCoordenadas() 
{
    string str;
    fstream f;
    cout << "[+]Leyendo coordenadas ... " << endl;
    f.open("../data/examen2Coord.txt", ios_base::in); 
    if ( f.is_open() ) 
          while( !f.eof() )
          {
               getline( f, str );
               ABB coord  = crearNodo(str);
               if(coord != NULL)
               {
                    insertar(arbol , coord);
                    Loading(str);
               }
          }
    else
          cout << "Error de abrir el archivo de coordenadas" << endl;
    f.close();
}

int main(void)
{
     rrSetTextColor(textColorGreen);
     rrGetCoordenadas();
     
     rrSetTextColor(textColorCyan);
     cout << endl << "\n\n[+]Informacion Arbol Binario de capacidad belica Ucrania";
     cout << endl << "   Developer-Nombre : "  << RRNOMBRE
          << endl << "   Developer-Cedula : "  << RRCEDULA


}