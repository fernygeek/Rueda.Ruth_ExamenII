#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <conio.h>
using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

/**
 * rrDelLeft: elimina los espacios de una cadena de caracteres por la izquierda
 * @param s   : cadena de caracteres
*/
string rrDelLeft(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
/**
 * rrDelRight: elimina los espacios de una cadena de caracteres por la derecha
 * @param s   : cadena de caracteres
*/
string rrDelRight(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE)
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
/**
 * rrDel: elimina los espacios en blanco de una cadena por la izquierda y derecha
 * @param s   : cadena de caracteres
*/
string rrDel(const string &s)
{
    return rrDelRight(rrDelLeft(s));	
}
/**
 * rrSepararStr: divide una cadena por un delimitador y almacena los datos en un vector
 * @param str   : cadena de caracteres
 * @param delim   : delimitador
 * @param outlst  : vector
*/
void rrSepararStr( const string  str, const char delim,  vector<string> &outlst )
{
    string strDiv;
    stringstream s(str);
    while ( getline(s, strDiv, delim) )
        outlst.push_back(strDiv);
}
