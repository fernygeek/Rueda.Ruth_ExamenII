#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "../lib/rrUtility.h"
#include "../lib/rrColor.h"
using namespace std;

const string RRCEDULA = "1003781018";
const string RRNOMBRE = "Ruth Fernanda Rueda Rueda";
const string RRCORREO = "ruth.rueda@epn.edu.ec";

struct rrCoordenada{
     int rrCapacidadBelica;       
     string rrGeolocalizacion;       
     string rrTipoArsenal;     
     struct rrCoordenada *izq, *der;
};
typedef struct rrCoordenada *ABB;
ABB arbol           = NULL;        // creacion del Arbol Binario de Coordenadas
int arbolNroNodos   = 0;           // numero de nodos 
int arbolCapBelica  = 0;           // suma de capacidad belica
int const TKError   =-1;           // Token de Error
int const TKBomba   =-2;           // Token de Bomba 
string const ALFA = "abc.";        // Tipo Arsenal


int mtBOMBIA_I[3][4]=    {// matriz de transicion
                         {1,         2,         TKError,     TKError},
                         {1,         2,         TKError,     TKError},
                         {TKError,   TKError,   2,           TKBomba}
                         }; 

int getIndexAlfabeto(char c)
{
    int index = ALFA.find(c);
    if(index < ALFA.length())
        return index;
    return TKError;    
}

string aplicaBOMBIA_I(string rrTipoArsenal) 
{        
    int q=0, l=0;
    for (auto &&c : rrTipoArsenal+"." ) // caracter de fin de cadena
    {
          l = getIndexAlfabeto(c);
          q = mtBOMBIA_I[q][l];
          //cout<< c << " " << q <<","<< l <<endl;
          if(q == TKError || q > 3)
               return "";
          if(q == TKBomba)
               return "BOMBIA_IP";
    }
    return "";
}

int rrCapB (string str)
{
     char c = str.back(); 
     int n = stoi(&c);
     //cout<< "dato"<< n<<endl;
     return n;
}

ABB rrCrearNodo(const string data)  
{
     try
     {
          vector<string> rrDividirDato;
          rrSepararStr(data,',',rrDividirDato);
          ABB rrNuevaCoord = new(struct rrCoordenada);
          rrNuevaCoord->rrCapacidadBelica    = rrCapB(rrDividirDato[0]); 
          rrNuevaCoord->rrGeolocalizacion   = rrDel(rrDividirDato[0]);
          rrNuevaCoord->rrTipoArsenal     = rrDel(rrDividirDato[1]);
          rrNuevaCoord->izq = NULL;
          rrNuevaCoord->der = NULL;
          return rrNuevaCoord;
     }
     catch(const exception& e)
     {
          rrSetTextColor(textColorRed);
          cout << ">> Error: "<< data << " -> " << e.what() << endl;
          rrSetTextColor(textColorGreen);
     }
     return NULL;
}
void insertar(ABB &arbol, ABB coord) 
{
     if(arbol==NULL)
     {
          arbol = coord; 
          arbolNroNodos++;
          arbolCapBelica += coord->rrCapacidadBelica;
     }
     else if(coord->rrCapacidadBelica < arbol->rrCapacidadBelica)
          insertar(arbol->izq, coord);
     else if(coord->rrCapacidadBelica > arbol->rrCapacidadBelica)
          insertar(arbol->der, coord);
}
void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->rrCapacidadBelica <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}
void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          cout << arbol->rrCapacidadBelica << " ";
          enOrden(arbol->der);
     }
}
void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          postOrden(arbol->izq);
          postOrden(arbol->der);
          cout << arbol->rrCapacidadBelica << " ";
     }
}
void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"\t";

     rrSetTextColor(textColorBlue);
     cout << " "  << arbol->rrGeolocalizacion          << "."  << arbol->rrCapacidadBelica;
     rrSetTextColor(textColorWhite);
     cout << " { " << arbol->rrTipoArsenal;
     rrSetTextColor(textColorRed);
     cout << "  " << aplicaBOMBIA_I(arbol->rrTipoArsenal);
     rrSetTextColor(textColorWhite);
     cout << " }"<< endl;

     verArbol(arbol->izq, n+1);
}

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
 * rrGetCoordenadas: es procedimiento para leer datos desde un archivo
*/
void rrGetCoordenadas() 
{
    string str;
    fstream f;
    cout << "[+]Leyendo coordenadas ... " << endl;
    f.open("../data/exaCoordenadas.txt", ios_base::in); 
    if ( f.is_open() ) 
          while( !f.eof() )
          {
               getline( f, str );
               ABB coord  = rrCrearNodo(str);
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
          << endl << "   Capacidad Belica : "  << arbolCapBelica
          << endl << "   Coordenada-Total : "  << arbolNroNodos;

     rrSetTextColor(textColorWhite);
     cout << "\n\n[+]ARBOL BINARIO DE COORDENADAS & BOMBA  \n\n";
     verArbol( arbol, 0);
}