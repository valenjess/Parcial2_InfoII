#include <iostream>
#include <QImage>

using namespace std;

int main()
{
    // IDEA -- CREAR UN CONTENEDOR BIDIMENSIONAL- VECTOR- Y GUARDAR LA INFO RGB DE CADA PIXEL
    //MATRIZ RGB'S 8*8
    //SUBMUESTREO
    /* imagen = 100*50
     * 100/8= 12 --> 12*8 = 96
     * modulo = 4         +  4
     * 4 grupos de 12 pixe
     * 4 de  13 pixe
     */


    string filename = "../Leer_Imagen/Imagenes/rick2.jpg";
    QImage imag( filename.c_str() );

    unsigned int X = 20;
    unsigned int Y = 20;

    unsigned int ancho = imag.width();
   unsigned int largo = imag.height();

   unsigned int modulo = ancho%8;


    cout<<modulo<<endl;
    cout<<ancho<<endl;
    cout<<largo <<endl;
    cout<<"Rojo "<<imag.pixelColor(X,Y).red()<<endl;
    cout<<"Verde "<<imag.pixelColor(X,Y).green()<<endl;
    cout<<"Azul "<<imag.pixelColor(X,Y).blue()<<endl;

    for(int index=0; index<ancho; index++){
        for(int elem=0; elem<largo; elem++){
            cout<<index<<"-"<<elem;
            cout<<"Rojo "<<imag.pixelColor(index,elem).red()<<"-";
            cout<<"Verde "<<imag.pixelColor(index,elem).green()<<"-";
            cout<<"Azul "<<imag.pixelColor(index,elem).blue()<<endl;

        }
    }
    return 0;
}
