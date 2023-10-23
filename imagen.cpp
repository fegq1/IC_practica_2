#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <math.h>
using namespace std;
int alto;
int ancho;
//Funcion que aplica una mascara de convolucion a una imagen.
//Resalta los bordes de la imagen.
int*** convolucion(int *** imagen){
    int*** imagen_convolucionada = new int**[ancho];
/*2*/    for (int i = 0; i < ancho; i++) {
        imagen_convolucionada[i] = new int*[alto];
/*4*/        for (int j = 0; j < alto; j++) {
            imagen_convolucionada[i][j] = new int[3];
/*6*/        }
/*7*/    }
    int kernel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernel_y[3][3] = {{1, 2, 1}, {0,0,0}, {-1, -2, -1}};
/*10*/    for (int i = 0; i < ancho ; i++) {
/*11*/        for (int j = 0; j < alto; j++) {
            int red_x = 0;
            int green_x = 0;
            int blue_x = 0;
            int red_y = 0;
            int green_y = 0;
            int blue_y = 0;
/*18*/            for (int k = -1; k <= 1; k++) {
/*19*/                for (int l = -1; l <= 1; l++) {
/*20*/                     if (i + k >= 0 && i + k < ancho && j + l >= 0 && j + l < alto) {
                        red_x += imagen[i + k][j + l][0] * kernel_x[k + 1][l + 1];
                        green_x += imagen[i + k][j + l][1] * kernel_x[k + 1][l + 1];
                        blue_x += imagen[i + k][j + l][2] * kernel_x[k + 1][l + 1];

                        red_y += imagen[i + k][j + l][0] * kernel_y[k + 1][l + 1];
                        green_y += imagen[i + k][j + l][1] * kernel_y[k + 1][l + 1];
                        blue_y += imagen[i + k][j + l][2] * kernel_y[k + 1][l + 1];
/*27*/                    }
/*28*/                }
/*29*/            }

            int red = sqrt(red_x * red_x + red_y * red_y);
            int green = sqrt(green_x * green_x + green_y * green_y);
            int blue = sqrt(blue_x * blue_x + blue_y * blue_y);
/*33*/            if (red > 255) {
                red = 255;
/*35*/            }
/*36*/            if (green > 255) {
                green = 255;
/*38*/            }
/*39*/            if (blue > 255) {
                blue = 255;
/*41*/            }
/*42*/            if (red < 0) {
                red = 0;
/*44*/            }
/*45*/            if (green < 0) {
                green = 0;
/*47*/            }
/*48*/            if (blue < 0) {
                blue = 0;
/*50*/            }

            imagen_convolucionada[i][j][0] = red;
            imagen_convolucionada[i][j][1] = green;
            imagen_convolucionada[i][j][2] = blue;
/*54*/        }
/*55*/    }
    return imagen_convolucionada;
/*57*/}

//Funcion que aplica un filtro de desenfoque a una imagen.
//Suaviza la imagen. La hace mas borrosa.    
int*** desenfocar(int*** imagen){
    int*** imagen_borrosa = new int**[ancho];
/*2*/    for (int i = 0; i < ancho; i++) {
        imagen_borrosa[i] = new int*[alto];
/*4*/        for (int j = 0; j < alto; j++) {
            imagen_borrosa[i][j] = new int[3];
/*6*/        }
/*7*/    }
    

/*8*/    for (int i = 0; i < ancho ; i++) {
/*9*/        for (int j = 0; j < alto; j++) {
            int red = 0;
            int green = 0;
            int blue = 0;
/*13*/            for (int k = -1; k <= 1; k++) {
/*14*/                for (int l = -1; l <= 1; l++) {
/*15*/                     if (i + k >= 0 && i + k < ancho && j + l >= 0 && j + l < alto) {
                    red += imagen[i + k][j + l][0];
                    green += imagen[i + k][j + l][1];
                    blue += imagen[i + k][j + l][2];
                    //cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<" l: "<<l<<endl<<flush;
/*19*/                }
/*20*/                }
/*21*/            }
            red = red / 9;
            blue = blue / 9;
            green = green / 9;
/*25*/            if (red > 255) {
                red = 255;
/*27*/            }
/*28*/            if (green > 255) {
                green = 255;
/*30*/            }
/*31*/            if (blue > 255) {
                blue = 255;
/*33*/            }
            imagen_borrosa[i][j][0] = red;
            imagen_borrosa[i][j][1] = green;
            imagen_borrosa[i][j][2] = blue;
    /*37*/    }
/*38*/    }
    return imagen_borrosa;
/*40*/}

//Funcion que combina las dos imagenes anteriores.
//Resta la imagen con mascara de convolucion a la imagen con filtro de desenfoque.
//El resultado es una imagen borrosa con los bordes resaltados.
int*** combinar(int*** imagen_convolucionada, int*** imagen_borrosa){
    int*** resultado = new int**[ancho];
/*2*/    for (int i = 0; i < ancho; i++) {
        resultado[i] = new int*[alto];
/*4*/        for (int j = 0; j < alto; j++) {
            resultado[i][j] = new int[3];
/*6*/        }
/*7*/    }
/*8*/    for(int i=0;i<ancho;i++){
/*9*/        for(int j=0;j<alto;j++){
/*10*/            for(int k=0;k<3;k++){
                int aux = imagen_borrosa[i][j][k] - imagen_convolucionada[i][j][k];
/*12*/                if(aux<0){
                    aux=0;
/*14*/                }
                resultado[i][j][k]=aux;
/*16*/            }
/*17*/        }
/*18*/    }
    return resultado;
/*20*/}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <ancho> <alto>" << endl;
        return 1;
    }
     ancho = atoi(argv[1]);
     alto = atoi(argv[2]);

    /*
    Una imagen es una matriz bidimensional de pixeles. (alto x ancho)
    Cada pixel tiene 3 valores: rojo, verde y azul. (profundo)
    Lo que nos deja una matriz tridimensional. (alto x ancho x profundo)
    */
    //Crear las variables que almacenen los datos de las imagenes
    std::cout<<"alto: "<<alto<<" ancho: "<<ancho<<endl;
    //std::cout<<"Creacion de variables"<<endl;
    int*** imagen_original = new int**[ancho];
    int*** imagen_convolucionada = new int**[ancho];
    int*** imagen_borrosa = new int**[ancho];
    int*** resultado = new int**[ancho];

    //Reservar memoria dinamica
    //std::cout<<"Reserva de memoria"<<endl;
/*8*/ for (int i = 0; i < ancho; i++) {
        imagen_original[i] = new int*[alto];
        imagen_convolucionada[i] = new int*[alto];
        imagen_borrosa[i] = new int*[alto];
        resultado[i] = new int*[alto];
/*13*/        for (int j = 0; j < alto; j++) {
            imagen_original[i][j] = new int[3];
            imagen_convolucionada[i][j] = new int[3];
            imagen_borrosa[i][j] = new int[3];
            resultado[i][j] = new int[3];

/*18*/        }
/*19*/    }



    //La imagen original se llena con valores aleatorios simulando una imagen real.
    //El resto de imagenes se llenan con ceros
    //std::cout<<"\"Leer\" imagen"<<endl;
/*21*/    for(int i=0;i<ancho;i++){
/*22*/        for(int j=0;j<alto;j++){
/*23*/            for(int k=0;k<3;k++){
                    imagen_original[i][j][k]=rand()%255;
                    imagen_convolucionada[i][j][k]=0;
                    imagen_borrosa[i][j][k]=0;
                    resultado[i][j][k]=0;
/*28*/            }
/*29*/        }
/*30*/    }

    //Empieza el cronometro
    //std::cout<<"Empieza el cronometro"<<endl;
    auto start = chrono::high_resolution_clock::now();

    //Paso 1: Aplicar una mascara de convolucion a la imagen original.
    //Este paso es independiente.
    //std::cout<<"Paso 1"<<endl;
    imagen_convolucionada=convolucion(imagen_original);
    
    //Paso 2: Aplicar un filtro de desenfoque a la imagen original.
    //Este paso es independiente.
    //std::cout<<"Paso 2"<<endl;
    imagen_borrosa=desenfocar(imagen_original);

    //Paso 3: Aplicar una mascara de convolucion a la imagen con mascara anterior.
    //Este paso es dependiente del paso 1.
    //std::cout<<"Paso 3"<<endl;
    imagen_convolucionada=convolucion(imagen_convolucionada);
    
    //Paso 4: Aplicar un filtro de desenfoque a la imagen con filtro de desenfoque anterior.
    //Este paso es dependiente del paso 2.
    //std::cout<<"Paso 4"<<endl;
    imagen_borrosa=desenfocar(imagen_borrosa);


    //Paso 5: Restar la imagen con mascara convolucion a la imagen con filtro de desenfoque.
    //El resultado es una imagen borrosa con los bordes resaltados.
    //Este paso es dependiente del paso 3 y 4.
    //std::cout<<"Paso 5"<<endl;
    resultado = combinar(imagen_convolucionada,imagen_borrosa);

    //Termina el cronometro
    //std::cout<<"Termina el cronometro"<<endl;
    auto finish = chrono::high_resolution_clock::now();
    std::cout << "Tiempo de ejecución: ";
    std::cout << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << endl;
/*47*/    for (int i = 0; i < ancho; i++) {
/*48*/        for (int j = 0; j < alto; j++) {
            delete[] imagen_original[i][j];
            delete[] imagen_convolucionada[i][j];
            delete[] imagen_borrosa[i][j];
            delete[] resultado[i][j];
/*53*/        } 
        delete[] imagen_original[i];
        delete[] imagen_convolucionada[i];
        delete[] imagen_borrosa[i];
        delete[] resultado[i];
/*58*/    }
    delete[] imagen_original;
    delete[] imagen_convolucionada;
    delete[] imagen_borrosa;
    delete[] resultado;
    return 0;
}
