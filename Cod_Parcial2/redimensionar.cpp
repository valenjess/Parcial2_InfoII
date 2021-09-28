#include "redimensionar.h"
#include <QImage>

using namespace std;

void Redimensionar::setFilename(const string &newFilename)
{
    filename = newFilename;
}

const string &Redimensionar::getFilename() const
{
    return filename;
}

Redimensionar::Redimensionar(string txt)
{
     filename += txt;

}

void Redimensionar::SobreMuestreo()
{

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

    EscrituraArchivo();

}

void Redimensionar::EscrituraArchivo()
{
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


void Redimensionar::Submuestreo1()
{

    QImage imag( filename.c_str() );



        unsigned int ancho = imag.width();
        unsigned int largo = imag.height();

        //int dimension = 8;
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
       EscrituraArchivo();

}

void Redimensionar::SobreSub()
{
    QImage imag( filename.c_str() );

    int ancho = imag.width();
    int largo = imag.height();

    if(ancho < dimension){
        int cantPixRepx=dimension/ancho;
        int cantPixRepY= largo/largo;

        int residuoX = dimension % ancho, residuoY = 0;


        if (residuoX == 0 && residuoY ==0){
            vector<vector<int>> FilR,FilG,FilB;

            for (int i =0;i < imag.width();i++){
                vector<int> RedX,GreenX,BlueX;

                for (int j =0; j < imag.height();j++){

                    for (int l=0;l<cantPixRepx;l++){
                        RedX.push_back(imag.pixelColor(j,i).red());
                        GreenX.push_back(imag.pixelColor(j,i).green());
                        BlueX.push_back(imag.pixelColor(j,i).blue());
                    }
                }
                for(int i=0;i < cantPixRepY;i++){
                        FilR.push_back(RedX);
                        FilG.push_back(GreenX);
                        FilB.push_back(BlueX);
                }
            }
        }

        else {
            vector<vector<int>> FilR,FilG,FilB;
            int contY=0;
            for ( int i =0;i < largo;i++){
                vector<int> RedX,GreenX,BlueX;
                int contX = 0;
                for (int j =0; j < ancho;j++){

                    for (int l=0;l<cantPixRepx;l++){
                        //cout<<"[ "<<imag.pixelColor(j,i).red() <<" , "<<imag.pixelColor(j,i).green()<<" , "<<imag.pixelColor(j,i).blue()<<endl;
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
                if(contY < residuoY){
                    for( int i = 0; i < ( cantPixRepY + 1 ); i++){

                            FilR.push_back(RedX);
                            FilG.push_back(GreenX);
                            FilB.push_back(BlueX);
                            //Datos[0][cont][j]=RedX[j];//rojo
                            //Datos[1][cont][j]=GreenX[j];//verde
                            //Datos[2][cont][j]=BlueX[j];//azul
                    }
                    contY++;
                }
                else{
                    for(int i=0;i < cantPixRepY;i++){
                        FilR.push_back(RedX);
                        FilG.push_back(GreenX);
                        FilB.push_back(BlueX);

                    }
                }
            }
            Dat[0]=FilR;

            Dat[1]=FilG;

            Dat[2]=FilB;

        }
        residuoX = 0, residuoY = largo % dimension;

        int fil= largo/dimension;
        int colum = ancho/ancho;


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
                        pixelR+= Dat[0][elem+contadorY][i+contadorX];
                        pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                        pixelB+= Dat[2][elem+contadorY][i+contadorX];
                     }

                     espacioX++;
                 }
                 //cont++;
                 else{
                      for(int i=0; i<colum; i++){
                          pixelR+= Dat[0][elem+contadorY][i+contadorX];
                          pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                          pixelB+= Dat[2][elem+contadorY][i+contadorX];
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
                            pixelR+= Dat[0][elem+contadorY][i+contadorX];
                            pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                            pixelB+= Dat[2][elem+contadorY][i+contadorX];
                        }
                        espacioX++;
                    }

                    else{
                         for(int i=0; i<colum; i++){
                             pixelR+= Dat[0][elem+contadorY][i+contadorX];
                             pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                             pixelB+= Dat[2][elem+contadorY][i+contadorX];

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
      EscrituraArchivo();
    }
    else{
        int cantPixRepx=ancho/ancho;
        int cantPixRepY= dimension/largo;

        int residuoX = 0, residuoY = dimension % largo;


        if (residuoX == 0 && residuoY ==0){
            vector<vector<int>> FilR,FilG,FilB;

            for (int i =0;i < imag.width();i++){
                vector<int> RedX,GreenX,BlueX;

                for (int j =0; j < imag.height();j++){

                    for (int l=0;l<cantPixRepx;l++){
                        RedX.push_back(imag.pixelColor(j,i).red());
                        GreenX.push_back(imag.pixelColor(j,i).green());
                        BlueX.push_back(imag.pixelColor(j,i).blue());
                    }
                }
                for(int i=0;i < cantPixRepY;i++){
                        FilR.push_back(RedX);
                        FilG.push_back(GreenX);
                        FilB.push_back(BlueX);
                }
            }
        }

        else {
            vector<vector<int>> FilR,FilG,FilB;
            int contY=0;
            for ( int i =0;i < largo;i++){
                vector<int> RedX,GreenX,BlueX;
                int contX = 0;
                for (int j =0; j < ancho;j++){

                    for (int l=0;l<cantPixRepx;l++){
                        //cout<<"[ "<<imag.pixelColor(j,i).red() <<" , "<<imag.pixelColor(j,i).green()<<" , "<<imag.pixelColor(j,i).blue()<<endl;
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
                if(contY < residuoY){
                    for( int i = 0; i < ( cantPixRepY + 1 ); i++){

                            FilR.push_back(RedX);
                            FilG.push_back(GreenX);
                            FilB.push_back(BlueX);

                    }
                    contY++;
                }
                else{
                    for(int i=0;i < cantPixRepY;i++){
                        FilR.push_back(RedX);
                        FilG.push_back(GreenX);
                        FilB.push_back(BlueX);
                    }
                }
            }
            Dat[0]=FilR;
            Dat[1]=FilG;
            Dat[2]=FilB;
        }


        residuoX = 0, residuoY = largo % dimension;

        int fil= largo/dimension;
        int colum = ancho/ancho;


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
                        pixelR+= Dat[0][elem+contadorY][i+contadorX];
                        pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                        pixelB+= Dat[2][elem+contadorY][i+contadorX];
                     }

                     espacioX++;

                 }
                 //cont++;
                 else{
                      for(int i=0; i<colum; i++){
                          pixelR+= Dat[0][elem+contadorY][i+contadorX];
                          pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                          pixelB+= Dat[2][elem+contadorY][i+contadorX];

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
                            pixelR+= Dat[0][elem+contadorY][i+contadorX];
                            pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                            pixelB+= Dat[2][elem+contadorY][i+contadorX];

                        }
                        espacioX++;
                    }

                    else{
                         for(int i=0; i<colum; i++){
                             pixelR+= Dat[0][elem+contadorY][i+contadorX];
                             pixelG+= Dat[1][elem+contadorY][i+contadorX];  //Acumuladores info pixeles
                             pixelB+= Dat[2][elem+contadorY][i+contadorX];

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

      EscrituraArchivo();
    }

}
