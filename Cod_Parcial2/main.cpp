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

   unsigned int ancho = imag.width();
   unsigned int largo = imag.height();

   unsigned int MAT = 8; //filas matriz
   unsigned int Cmat = 8; //columnas matriz

   unsigned int fil = ancho/MAT;
   unsigned int colum = largo/Cmat;

   vector <unsigned int> Reds;
   vector <unsigned int> Green; //IMAGEN GRANDE
   vector <unsigned int> Blue;

   vector <unsigned int> Rmat;
   vector <unsigned int> Gmat;  //INFO(REDUCIDA) MATRIZ LEDS
   vector <unsigned int> Bmat;


    //VECTORES CON INFO RGB -->1 vector para cada color
            for(int index=0; index<ancho; index++){
                for(int elem=0; elem<largo; elem++){

                    Reds.push_back(imag.pixelColor(index,elem).red());
                    Green.push_back(imag.pixelColor(index,elem).green());
                    Blue.push_back(imag.pixelColor(index,elem).blue());

                }
            }

            //VECTORES CON INFO RGB PARA MATRIZ -->PROMEDIO DE PIXELES
            int pixelR=0, pixelG=0, pixelB=0;

            int divisorProm = fil * colum;
            int cont = 0;

            for(int index=0; index<MAT; index++){
                for(int elem=0; elem<fil; elem++){
                    for(int i=0; i<colum; i++){
                       pixelR+= Reds[elem*colum*(MAT)+(i+cont)];
                       pixelG+= Green[elem*colum*(MAT)+(i+cont)];  //Acumuladores info pixeles
                       pixelB+= Blue[elem*colum*(MAT)+(i+cont)];

                    }

                }
                Rmat.push_back(pixelR/divisorProm);
                Gmat.push_back(pixelG/divisorProm);
                Bmat.push_back(pixelB/divisorProm);

                pixelR=0;
                pixelG=0;
                pixelB=0;

                cont=cont+colum;

            }

            for(int i=0; i<Rmat.size(); i++){
                cout<<Rmat[i]<<endl;
            }

            cout<<"-----"<<endl;

            for(int i=0; i<Rmat.size(); i++){
                cout<<Gmat[i]<<endl;
            }
            cout<<"-----"<<endl;

            for(int i=0; i<Rmat.size(); i++){
                cout<<Bmat[i]<<endl;
            }
    return 0;
}
