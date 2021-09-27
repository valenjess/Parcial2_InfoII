#include <iostream>
#include <QImage>

using namespace std;

int main()
{   ///MEDIDAS IMAGEN  DIVISIBLES ENTRE 16 (MEDIDAS MATRIZ RGB'S)
    // IDEA -- CREAR UN CONTENEDOR BIDIMENSIONAL- VECTOR- Y GUARDAR LA INFO RGB DE CADA PIXEL
    //MATRIZ RGB'S 8*8
    //SUBMUESTREO
    /* imagen = 100*50
     * 100/8= 12 --> 12*8 = 96
     * modulo = 4         +  4
     * 4 grupos de 12 pixe
     * 4 de  13 pixe
     */


   string filename = "../Cod_Parcial2/Imagenes/Japon.jpg";
   QImage imag( filename.c_str() );

   unsigned int ancho = imag.width();
   unsigned int largo = imag.height();

   unsigned int MAT = 8; //filas matriz
   unsigned int Cmat = 8; //columnas matriz

   unsigned int fil = ancho/MAT;
   int auxfil = fil;
   unsigned int colum = largo/Cmat;

   vector <unsigned int> Reds;
   vector <unsigned int> Green; //IMAGEN GRANDE
   vector <unsigned int> Blue;

   vector <unsigned int> Rmat;
   vector <unsigned int> Gmat;  //INFO(REDUCIDA) MATRIZ LEDS
   vector <unsigned int> Bmat;

   int Info[3][8][8]{};
   int contRGB = 0;
   int FilRGB = 0; //8 elementos para cada fila de cada color
   int ColRGB = 0;

   /*

   int Datos[3][8][8]=
   {
     //inserte el txt
   {{226,226,213,213,255,255,187,206},{228,226,213,213,255,255,187,206},{196,196,187,187,184,184,183,185},{196,196,187,187,184,184,183,185},{255,255,155,155,163,163,152,255},{255,255,155,155,163,163,152,255},{255,255,255,255,160,160,255,255},{255,255,255,255,160,160,255,255}},
   {{35,35,42,42,180,180,54,40},{35,35,42,42,180,180,54,40},{41,41,43,43,59,59,60,50},{41,41,43,43,59,59,60,50},{210,210,67,67,57,57,50,214},{210,210,67,67,57,57,50,214},{229,229,211,211,62,62,202,236},{229,229,211,211,62,62,202,236}},
   {{53,53,50,50,166,166,37,42},{53,53,50,50,166,166,37,42},{59,59,53,53,53,53,53,54},{59,59,53,53,53,53,53,54},{229,229,83,83,69,69,61,221},{229,229,83,83,69,69,61,221},{248,248,229,229,85,85,220,244},{248,248,229,229,85,85,220,244}}

   };

   cout<<Datos[0][0][7]<<endl;
   cout<<Datos[1][0][0]<<endl;
   cout<<Datos[2][0][0]<<endl;
   cout<<Datos[0][0][0]<<endl;
   cout<<Datos[0][0][0]<<endl;*/


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

            for(int index=0; index<MAT*MAT; index++){
                for(int elem=0; elem<fil; elem++){
                    for(int i=0; i<colum; i++){
                       pixelR+= Reds[elem*colum*(MAT)+(i+cont)];
                       pixelG+= Green[elem*colum*(MAT)+(i+cont)];  //Acumuladores info pixeles
                       pixelB+= Blue[elem*colum*(MAT)+(i+cont)];

                    }

                }

                pixelR = (pixelR/divisorProm);
                pixelG = (pixelG/divisorProm);
                pixelB = (pixelB/divisorProm);

                //LLenando el arreglo tridimensional

                Info[0][FilRGB][ColRGB] = pixelR;
                Info[1][FilRGB][ColRGB] = pixelG;
                Info[2][FilRGB][ColRGB] = pixelB;

                ColRGB++;

                if((index+1)%8 == 0){
                    FilRGB++;
                    ColRGB = 0;
                }


                pixelR=0;
                pixelG=0;
                pixelB=0;

                if((index+1)%MAT==0){
                    cont=largo*auxfil;
                    auxfil += fil;
                }
                else{
                cont=cont+colum;

                }

            }


    ///MEDIDAS IMAGEN NO SON DIVISIBLES ENTRE 16(MEDIDAS MATRIZ RGB'S 16*16)
     //Crear una variable modulo que represente los pixeles que sobran

    return 0;
}
