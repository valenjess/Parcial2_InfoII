#include <iostream>
#include <QImage>
#include <fstream>
#include <vector>

#define dimension 8



using namespace std;


void SobreMuestreo( array<array<array<int,8>,8>,3> &Datos);
void EscrituraArchivo(array<array<array<int,8>,8>,3> Datos);
void Submuestreo( array<array<array<int,8>,8>,3> &Info);
void Submuestreo1( array<array<array<int,8>,8>,3> &Datos);


int main()
{


    array<array<array<int,8>,8>,3> Datos{};

    SobreMuestreo(Datos);

    EscrituraArchivo(Datos);
  
    Submuestreo(Info);
  
    EscrituraArchivo(Info);


    return 0;
}

                                             
 void SobreMuestreo(array<array<array<int,8>,8>,3> &Datos)
{
    string filename = "../Cod_Parcial2/Imagenes/cosa.jpg";
    QImage imag( filename.c_str() );


    unsigned int ancho = imag.width();
    unsigned int largo = imag.height();

    int cantPixRepx=dimension/ancho;
    int cantPixRepY=dimension/largo;

    int residuoX = dimension % ancho, residuoY = dimension % largo;


    if (residuoX == 0 && residuoY ==0){
        int cont=0;
        for (int i =0;i < imag.width();i++){
            vector<int> RedX,GreenX,BlueX;
            for (int j =0; j < imag.height();j++){


                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(j,i).red());
                    GreenX.push_back(imag.pixelColor(j,i).green());
                    BlueX.push_back(imag.pixelColor(j,i).blue());
                }

            }
            int longitud=RedX.size();
            for(int i=0;i < cantPixRepY;i++){
                for(int j=0;j<longitud;j++){
                    //Red.push_back(RedX[j]);
                    Datos[0][cont][j]=RedX[j];//rojo
                    //Green.push_back(GreenX[j]);
                    Datos[1][cont][j]=GreenX[j];//verde
                    //Blue.push_back(BlueX[j]);
                    Datos[2][cont][j]=BlueX[j];//azul
                }
                cont++;
            }
        }
    }

    else {
        int cont=0,contY=0;
        for (unsigned int i =0;i < largo;i++){
            vector<int> RedX,GreenX,BlueX;
            int contX = 0;
            for (unsigned int j =0; j < ancho;j++){

                for (int l=0;l<cantPixRepx;l++){
                    cout<<"[ "<<imag.pixelColor(j,i).red() <<" , "<<imag.pixelColor(j,i).green()<<" , "<<imag.pixelColor(j,i).blue()<<endl;
                    RedX.push_back(imag.pixelColor(j,i).red());
                    GreenX.push_back(imag.pixelColor(j,i).green());
                    BlueX.push_back(imag.pixelColor(j,i).blue());
                }
                if (contX < residuoX){
                    RedX.push_back(imag.pixelColor(j,i).red());
                    GreenX.push_back(imag.pixelColor(j,i).green());
                    BlueX.push_back(imag.pixelColor(j,i).blue());
                    contX++;
                }
            }
            int longitud=RedX.size();
            if(contY < residuoY){
                for( int i = 0; i < ( cantPixRepY + 1 ); i++){
                    for( int j = 0; j < longitud; j++){
                        Datos[0][cont][j]=RedX[j];//rojo
                        Datos[1][cont][j]=GreenX[j];//verde
                        Datos[2][cont][j]=BlueX[j];//azul
                    }
                    cont++;
                }
                contY++;
            }
            else{
                for(int i=0;i < cantPixRepY;i++){
                    for(int j=0;j<longitud;j++){
                        Datos[0][cont][j]=RedX[j];//rojo
                        Datos[1][cont][j]=GreenX[j];//verde
                        Datos[2][cont][j]=BlueX[j];//azul
                    }
                 cont++;
                }
            }
        }
    }
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
  
    ///MEDIDAS IMAGEN  DIVISIBLES ENTRE 16 (MEDIDAS MATRIZ RGB'S)
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

void Submuestreo1( array<array<array<int,8>,8>,3> &Datos){

    string filename = "../submuestreo/Imagenes/cosa.jpg";
    QImage imag( filename.c_str() );



        unsigned int ancho = imag.width();
        unsigned int largo = imag.height();

        int dimension = 8;
        int residuoX = ancho % dimension, residuoY = largo % dimension;

        int fil= largo/dimension;
        int colum = ancho/dimension;


        int cont=0,contC=0,contPosiMa=0;

        int contadorX=0,contadorY=0;

        int espacioY = 0;
        for(int index=0; index<dimension*dimension; index++){
            int  pixelR=0,pixelG=0,pixelB=0;

            if (cont < residuoY){
             int espacioX=0;
             for(int elem=0; elem<fil+1; elem++){

                 if(contC<residuoX){
                     for(int i=0; i<colum+1; i++){
                        pixelR+= imag.pixelColor(i+contadorX,elem+contadorY).red();
                        pixelG+= imag.pixelColor(i+contadorX,elem+contadorY).green();  //Acumuladores info pixeles
                        pixelB+= imag.pixelColor(i+contadorX,elem+contadorY).blue();

                     }

                     espacioX++;

                 }
                 //cont++;
                 else{
                      for(int i=0; i<colum; i++){
                          pixelR+= imag.pixelColor(i+contadorX,elem+contadorY).red();
                          pixelG+= imag.pixelColor(i+contadorX,elem+contadorY).green();  //Acumuladores info pixeles
                          pixelB+= imag.pixelColor(i+contadorX,elem+contadorY).blue();

                      }
                 }
             }
                if (espacioX > 0 ){
                    contadorX+=(colum+1);
                }
                else{
                    contadorX+=colum;
                }

                espacioY++;
             }
            else{
                int espacioX=0;
                for(int elem=0; elem<fil; elem++){

                    if(contC<residuoX){
                        for(int i=0; i<colum+1; i++){
                            pixelR+= imag.pixelColor(i+contadorX,elem+contadorY).red();
                            pixelG+= imag.pixelColor(i+contadorX,elem+contadorY).green();  //Acumuladores info pixeles
                            pixelB+= imag.pixelColor(i+contadorX,elem+contadorY).blue();

                        }
                        espacioX++;
                    }

                    else{
                         for(int i=0; i<colum; i++){
                             pixelR+= imag.pixelColor(i+contadorX,elem+contadorY).red();
                             pixelG+= imag.pixelColor(i+contadorX,elem+contadorY).green();  //Acumuladores info pixeles
                             pixelB+= imag.pixelColor(i+contadorX,elem+contadorY).blue();

                         }
                    }
                }
                if (espacioX > 0 ){
                    contadorX+=(colum+1);
                }
                else{
                    contadorX+=colum;
                }
            }


            if(cont < residuoY and contC<residuoX){
                Datos[0][cont][contPosiMa] = pixelR/((fil+1)*(colum+1));
                Datos[1][cont][contPosiMa] = pixelG/((fil+1)*(colum+1));
                Datos[2][cont][contPosiMa] = pixelB/((fil+1)*(colum+1));
            }
            else if(cont < residuoY and contC>=residuoX){
                Datos[0][cont][contPosiMa] = pixelR/((fil+1)*(colum));
                Datos[1][cont][contPosiMa] = pixelG/((fil+1)*(colum));
                Datos[2][cont][contPosiMa] = pixelB/((fil+1)*(colum));
            }
            else if (cont >= residuoY and contC<residuoX){
                Datos[0][cont][contPosiMa] = pixelR/((fil)*(colum+1));
                Datos[1][cont][contPosiMa] = pixelG/((fil)*(colum+1));
                Datos[2][cont][contPosiMa] = pixelB/((fil)*(colum+1));
            }
            else{
                Datos[0][cont][contPosiMa] = pixelR/((fil)*(colum));
                Datos[1][cont][contPosiMa] = pixelG/((fil)*(colum));
                Datos[2][cont][contPosiMa] = pixelB/((fil)*(colum));
            }
            if ((index+1) % 8 == 0 and (index+1 )!= 0){
                contadorX=0;
                contC=-1;

                if (espacioY < residuoY ){
                    contadorY+=(fil+1);
                }
                else{
                    contadorY+=fil;
                }
                cont++;
            }

            contC++;
            contPosiMa++;
            if(contPosiMa==8){
                contPosiMa=0;
            }

        }

}

