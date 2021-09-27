#include <iostream>
#include <QImage>
#include <fstream>

using namespace std;


void EscrituraArchivo(array<array<array<int,8>,8>,3> Info);
void Submuestreo( array<array<array<int,8>,8>,3> &Info);

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

    array<array<array<int,8>,8>,3> Info{};

    Submuestreo(Info);
    EscrituraArchivo(Info);

   ///MEDIDAS NO DIVISIBLES
   ///   int MAT = 8;
    int largimag=20;
    int anchimag=25;

    int moduloF = largimag%MAT;
    int cocienteF = largimag/MAT;

    int moduloC = anchimag%MAT;
    int cocienteC = anchimag/MAT;

    int vecesFil1 = moduloF;
    int vecesFil2 = MAT - moduloF;
    int pixFil1 = cocienteF +1 ;
    int pixFil2 = cocienteF ;

    int vecesCol1 =  moduloC;
    int vecesCol2 = MAT - moduloC;
    int pixCol1 = cocienteC + 1;
    int pixCol2 = MAT - moduloC;

    int objeto = 0;
    int cont = 0;


    for (int indi=0; indi<MAT*MAT; indi++){

        for(int elem=0; elem<MAT; elem++){
            for(int indexF=0; indexF<vecesFil1; indexF++){
                 for(int indexC=0; indexC<vecesCol1; indexC++){

                    objeto = Rojo[indexF*pixCol1*(MAT)+(indexC+cont)];

                }
            }
        }
    }



    return 0;
}


void EscrituraArchivo(array<array<array<int,8>,8>,3> Datos){
    string contenido;

    for (int i = 0; i < 3; i++){
        contenido+="{";
        for (int j = 0; j < 8; j++){
            contenido+="{";
            for (int k = 0; k < 8; k++){
                contenido+=to_string(Datos[i][j][k]);
                if(k<7){
                    contenido+=",";
                }
            }
            contenido+="}";
            if(j<7){
                contenido+=",";
            }
        }
        contenido+="}";
        if(i<2){
            contenido+=",";
            contenido+="\n";
        }
    }

    ofstream archi;

    archi.open("../Cod_Parcial2/BD/MatrizLeds.txt");

    if (!archi.is_open())
       {
         cout << "Error abriendo el archivo" << endl;
         exit(1);
       }


    archi << contenido;

    archi.close();

}

void Submuestreo( array<array<array<int,8>,8>,3> &Info){


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

    int FilRGB = 0; //8 elementos para cada fila de cada color
    int ColRGB = 0;

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


}
