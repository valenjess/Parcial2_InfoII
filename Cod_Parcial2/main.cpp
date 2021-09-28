#include <iostream>
#include <QImage>
#include <vector>
<<<<<<< HEAD
#include <fstream>

#define dimension 8



using namespace std;


void SobreMuestreo( array<array<array<int,8>,8>,3> &Datos);
void EscrituraArchivo(array<array<array<int,8>,8>,3> Datos);


int main()
{


    array<array<array<int,8>,8>,3> Datos{};

    SobreMuestreo(Datos);

    EscrituraArchivo(Datos);


    return 0;
}

void SobreMuestreo(array<array<array<int,8>,8>,3> &Datos)
{
    string filename = "../Cod_Parcial2/Imagenes/cosa.jpg";
    QImage imag( filename.c_str() );

=======

using namespace std;

int main()
{
    string filename = "../Cod_Parcial2/Imagenes/imagen.jpg";
    QImage imag( filename.c_str() );
    vector<int> Red,Green,Blue;


    unsigned int X = 10;
    unsigned int Y = 19;
>>>>>>> origin/main

    unsigned int ancho = imag.width();
    unsigned int largo = imag.height();

<<<<<<< HEAD
    int cantPixRepx=dimension/ancho;
    int cantPixRepY=dimension/largo;

    int residuoX = dimension % ancho, residuoY = dimension % largo;


    if (residuoX == 0 && residuoY ==0){
        int cont=0;
=======


    unsigned int dimensionX=16;
    unsigned int dimensionY=16;

    int cantPixRepx=dimensionX/ancho;
    int cantPixRepY=dimensionY/largo;

    int residuoX = dimensionX % ancho, residuoY = dimensionY % largo;

    if (residuoX == 0 && residuoY ==0){
>>>>>>> origin/main
        for (int i =0;i < imag.width();i++){
            vector<int> RedX,GreenX,BlueX;
            for (int j =0; j < imag.height();j++){

<<<<<<< HEAD

                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(j,i).red());
                    GreenX.push_back(imag.pixelColor(j,i).green());
                    BlueX.push_back(imag.pixelColor(j,i).blue());
=======
                cout<<"[ "<<imag.pixelColor(j,i).red() <<" , "<<imag.pixelColor(j,i).green()<<" , "<<imag.pixelColor(j,i).blue()<<endl;
                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(i,j).red());
                    GreenX.push_back(imag.pixelColor(i,j).green());
                    BlueX.push_back(imag.pixelColor(i,j).blue());
>>>>>>> origin/main
                }

            }
            int longitud=RedX.size();
            for(int i=0;i < cantPixRepY;i++){
                for(int j=0;j<longitud;j++){
<<<<<<< HEAD
                    Datos[0][cont][j]=RedX[j];//roj
                    Datos[1][cont][j]=GreenX[j];//verde
                    Datos[2][cont][j]=BlueX[j];//azul
                }
                cont++;
=======
                    Red.push_back(RedX[j]);
                    Green.push_back(GreenX[j]);
                    Blue.push_back(BlueX[j]);
                }
>>>>>>> origin/main
            }
        }
    }

    else {
<<<<<<< HEAD
        int cont=0,contY=0;
        for (unsigned int i =0;i < largo;i++){
            vector<int> RedX,GreenX,BlueX;
            int contX = 0;
            for (unsigned int j =0; j < ancho;j++){

                for (int l=0;l<cantPixRepx;l++){
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
=======

        for (int i =0;i < imag.width();i++){
            vector<int> RedX,GreenX,BlueX;
            int contX = 0;
            for (int j =0; j < imag.height();j++){

                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(i,j).red());
                    GreenX.push_back(imag.pixelColor(i,j).green());
                    BlueX.push_back(imag.pixelColor(i,j).blue());
                }
                if (contX < residuoX){
                    RedX.push_back(imag.pixelColor(i,j).red());
                    GreenX.push_back(imag.pixelColor(i,j).green());
                    BlueX.push_back(imag.pixelColor(i,j).blue());
                    contX++;
                }
            }
            int longitud=RedX.size(),contY=0;
            if(contY < residuoY){
                for( int i = 0; i < ( cantPixRepY + 1 ); i++){
                    for( int j = 0; j < longitud; j++){
                        Red.push_back(RedX[j]);
                        Green.push_back(GreenX[j]);
                        Blue.push_back(BlueX[j]);
                    }
                }
>>>>>>> origin/main
            }
            else{
                for(int i=0;i < cantPixRepY;i++){
                    for(int j=0;j<longitud;j++){
<<<<<<< HEAD
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



=======
                        Red.push_back(RedX[j]);
                        Green.push_back(GreenX[j]);
                        Blue.push_back(BlueX[j]);
                    }
                }
            }
            contY++;
        }
    }



    return 0;
>>>>>>> origin/main
}
