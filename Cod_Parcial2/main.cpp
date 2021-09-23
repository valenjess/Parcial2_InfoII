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



    unsigned int dimensionX=16;
    unsigned int dimensionY=16;

    int cantPixRepx=dimensionX/ancho;
    int cantPixRepY=dimensionY/largo;

    if (dimensionX%ancho==0 && dimensionY%largo==0){
        for (int i =0;i < imag.width();i++){
            vector<int> RedX;
            for (int j =0; j < imag.height();j++){

                //cout<<"[ "<<imag.pixelColor(j,i).red() <<" , "<<imag.pixelColor(j,i).green()<<" , "<<imag.pixelColor(j,i).blue()<<endl;
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



    return 0;
}
