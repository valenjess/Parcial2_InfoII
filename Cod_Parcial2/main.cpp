#include <iostream>
#include <QImage>

using namespace std;

int main()
{
    string filename = "../Cod_Parcial2/Imagenes/cosa.jpg";
    QImage imag( filename.c_str() );


    unsigned int X = 10;
    unsigned int Y = 19;

    unsigned int ancho = imag.width();
   unsigned int largo = imag.height();

    cout<<ancho<<endl;
    cout<<largo <<endl;
    cout<<"Rojo "<<imag.pixelColor(X,Y).red()<<endl;
    cout<<"Verde "<<imag.pixelColor(X,Y).green()<<endl;
    cout<<"Azul "<<imag.pixelColor(X,Y).blue()<<endl;



    return 0;
}
