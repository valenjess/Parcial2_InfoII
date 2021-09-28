#ifndef REDIMENSIONAR_H
#define REDIMENSIONAR_H

#include <iostream>
#include <QImage>
#include <fstream>
#include <vector>

#define dimension 8

using namespace std;



class Redimensionar
{

private:

    array<array<array<int,8>,8>,3> Datos;
    string filename= "../Cod_Parcial2/Imagenes/";
    array<vector<vector<int>>,3> Dat{};


public:

    Redimensionar( string txt); //Constructor de la clase redimensionar
                                //parámetro => string con el nombre de la imagen con extension .jpg

    void SobreMuestreo();   //Metodo que permite transformar una imagen de medidas menores a las de
                            //la matriz de 8 * 8 a estas correspondientes medidas
                            //Ej: imagen 4*7 ----> imagen 8*8

    void EscrituraArchivo(); //Metodo que escribe el arreglo tridimensional con la info de la imagen
                             //redimensionada  en un txt


    void Submuestreo1( );  //Metodo que permite transformar una imagen de medidas mayores a las de
                           //la matriz de 8 * 8 a estas correspondientes medidas
                            //Ej: imagen 50*100 ----> imagen 8*8


    void SobreSub();    //Metodo en el cual se analizan las medidas de las imagenes, y en caso de
                        //ser una de estas mayor y otra menor a 8(medidas matriz), se accede a este



    void setFilename(const string &newFilename);

    const string &getFilename() const;
};

#endif // REDIMENSIONAR_H
