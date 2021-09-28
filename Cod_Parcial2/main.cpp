#include <iostream>
#include <QImage>
#include <fstream>
#include <vector>
#include "redimensionar.h"

#define dimension 8

using namespace std;

/* El siguiente programa recibe la ruta en la cual se encuentra la imagen que el usuario desea representar en la matriz
 * de neopixeles de tamaño 8*8
 * ESPECIFICACIONES : el usuario debe ingresar unicamente el nombre de la imagen, ya que por defecto se
 * pone al inicio de la ruta "../Cod_Parcial2/Imagenes/"
 * La imagen debe estar en formato jpg
 * -->El programa emplea una clase llamada "redimensionar", la cual tiene los metodos necesario
 *    para modificar el tamaño de la imagen dada, a un tamaño de 8*8, mediante los procesos de
 *    submuestreo y sobremuestreo segun sea necesario.
 * */


int main()
{
   string txt="Mex.jpg";
   cout<<"Ingrese el nombre de la imagen a procesar"<<endl;
   cin>>txt;

   Redimensionar obj1(txt);

   QImage imag ((obj1.getFilename()).c_str());

   unsigned int ancho = imag.width();
   unsigned int largo = imag.height();

   unsigned int moduloAn = ancho%dimension;
   unsigned int moduloLa = largo%dimension;

   if( ancho && largo > dimension){

        obj1.Submuestreo1();

    }

   else if ((largo && ancho) < dimension){

        obj1.SobreMuestreo();
   }

   else{

       obj1.SobreSub();
   }






    return 0;
}

                                             
