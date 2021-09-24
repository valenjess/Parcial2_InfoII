#include <iostream>
#include <QImage>
#include <vector>

using namespace std;

int main()
{
    string filename = "../Cod_Parcial2/Imagenes/cosa.jpg";
    QImage imag( filename.c_str() );
    vector<int> Red;


    unsigned int X = 10;
    unsigned int Y = 19;

    unsigned int ancho = imag.width();
    unsigned int largo = imag.height();



    unsigned int dimensionX=18;
    unsigned int dimensionY=16;

    int cantPixRepx=dimensionX/ancho;
    int cantPixRepY=dimensionY/largo;

    int residuoX = dimensionX % ancho, residuoY = dimensionY % largo;

    if (residuoX == 0 && residuoY ==0){
        for (int i =0;i < imag.width();i++){
            vector<int> RedX;
            for (int j =0; j < imag.height();j++){

                cout<<"[ "<<imag.pixelColor(i,j).red() <<" , "<<imag.pixelColor(i,j).green()<<" , "<<imag.pixelColor(i,j).blue()<<endl;
                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(i,j).red());
                }

            }
            int longitud=RedX.size();
            for(int i=0;i < cantPixRepY;i++){
                for(int j=0;j<longitud;j++){
                    Red.push_back(RedX[j]);
                }
            }
        }
    }

    else {
        int contX = 0;
        for (int i =0;i < imag.width();i++){
            vector<int> RedX;
            for (int j =0; j < imag.height();j++){

                for (int l=0;l<cantPixRepx;l++){
                    RedX.push_back(imag.pixelColor(i,j).red());
                }
                if (contX < residuoX){
                    RedX.push_back(imag.pixelColor(i,j).red());
                    contX++;
                }
            }
            int longitud=RedX.size(),contY=0;
            if(contY < residuoY){
                for( int i = 0; i < ( cantPixRepY + 1 ); i++){
                    for( int j = 0; j < longitud; j++){
                        Red.push_back(RedX[j]);
                    }
                }
            }
            else{
                for(int i=0;i < cantPixRepY;i++){
                    for(int j=0;j<longitud;j++){
                        Red.push_back(RedX[j]);
                    }
                }
            }
            contY++;
        }
    }



    return 0;
}
