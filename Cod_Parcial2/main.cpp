#include <iostream>
#include <QImage>
#include <vector>
#include <array>

using namespace std;

int main()
{
    string filename = "../Cod_Parcial2/Imagenes/cosa.jpg";
    QImage imag( filename.c_str() );
    vector<int> Red,Green,Blue;

    array<array<array<int,16>,16>,3> Datos{};

    unsigned int ancho = imag.width();
    unsigned int largo = imag.height();


    unsigned int dimensionX=16;
    unsigned int dimensionY=16;

    int cantPixRepx=dimensionX/ancho;
    int cantPixRepY=dimensionY/largo;

    int residuoX = dimensionX % ancho, residuoY = dimensionY % largo;


    if (residuoX == 0 && residuoY ==0){
        int cont=0;
        for (int i =0;i < imag.width();i++){
            vector<int> RedX,GreenX,BlueX;
            for (int j =0; j < imag.height();j++){

                cout<<"[ "<<imag.pixelColor(j,i).red() <<" , "<<imag.pixelColor(j,i).green()<<" , "<<imag.pixelColor(j,i).blue()<<endl;
                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(i,j).red());
                    GreenX.push_back(imag.pixelColor(i,j).green());
                    BlueX.push_back(imag.pixelColor(i,j).blue());
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
        int cont=0;
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
                        Datos[0][cont][j]=RedX[j];//rojo
                        Datos[1][cont][j]=GreenX[j];//verde
                        Datos[2][cont][j]=BlueX[j];//azul
                    }
                }
            }
            else{
                for(int i=0;i < cantPixRepY;i++){
                    for(int j=0;j<longitud;j++){
                        Datos[0][cont][j]=RedX[j];//rojo
                        Datos[1][cont][j]=GreenX[j];//verde
                        Datos[2][cont][j]=BlueX[j];//azul
                    }
                }
            }
            contY++;
        }
    }



    return 0;
}
