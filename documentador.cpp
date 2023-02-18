#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int main(){
    //Declaracion de variables
    ifstream archivoEntrada;
    ofstream archivoSalida;
    string linea[999], etiqueta, nombreArchivo, nombreArchivoHtml, nombreArchivoCpp, respuesta;
    int i, lugarInicio, lugarFinal, tipoEtiqueta, longitudNombre;
    bool archivoAbierto = false;

    //Pedir el nombre del archivo que se quiere documentar
    cout<<"Ingresa el nombre del archivo que quieres documentar (sin extension): ";
    getline(cin, nombreArchivo);

    //Se obtiene la longitud del nombre y apartir de ahi se inserta la terminacion .cpp
    longitudNombre=nombreArchivo.length();
    nombreArchivoCpp=nombreArchivo.insert(longitudNombre, ".cpp");
    
    //Se intenta abrir el archivo si lo puede abrir continua, si no, se pregunta a el usuario si quiere ingresarlo de nuevo y en caso de que no termina el programa
    //En ambos casos se escribe un mensaje si se completo o no correctamente
    while (!archivoAbierto) {
        archivoEntrada.open(nombreArchivoCpp);
        if (!archivoEntrada) {
            cout<<"\nNo se pudo abrir el archivo "<<nombreArchivoCpp<<endl;
            cout<<"\nQuieres ingresar el nombre del archivo de nuevo? (si/no): ";
            cin>>respuesta;
            if (respuesta == "si") {
                cout<<"Ingresa el nombre del archivo que quieres documentar (sin extension): ";
                cin.ignore();
                getline(cin, nombreArchivo);
            }
            else {
                return 0;
            }
        }
        else {
            archivoAbierto = true;
            break;
        }
        longitudNombre=nombreArchivo.length();
        nombreArchivoCpp=nombreArchivo.insert(longitudNombre, ".cpp");
    }
    cout<<"\nEl archivo "<<nombreArchivoCpp<<" se ha abierto exitosamente"<<endl;

    //Se obtienen todas las lineas del archivo y se guardan en un array de string llamado linea[]
    while (!archivoEntrada.eof()){
        for(i=0;i<999;i++){
            getline(archivoEntrada, linea[i]);
        }
    }
    archivoEntrada.close();

    //Se obtiene la longitud del archivo, se elimina "cpp" y se inserta "html" en su lugar
    longitudNombre=nombreArchivo.length();
    nombreArchivoHtml=nombreArchivo.erase(longitudNombre-3);
    nombreArchivoHtml=nombreArchivo.insert(longitudNombre-3, "html");

    //Se crea el archivo de salida con el mismo nombre pero con terminacion .html
    archivoSalida.open(nombreArchivoHtml);

    //Se escribe el inicio del html
    archivoSalida<<"<!DOCTYPE html>\n<html>\n<head>\n<title>\nDocumentaci&oacute;n del archivo "<<nombreArchivoCpp<<"\n</title>\n</head>\n<body>\n";
    
    //Ciclo for para identificar las etiquetas "@......." y segun la etiqueta escibir en el html de una forma u otra
    for(i=0;i<999;i++){

        //Si en la linea encuentra un @ empieza el proceso
        if(linea[i].find("@")!=-1){
            tipoEtiqueta=-1;

            //Busca el primer arroba y el primer espacio, si el espacio esta antes lo elimina y sigue el proceso hasta que encuentre el espacio despues del @
            lugarInicio=linea[i].find("@");
            lugarFinal=linea[i].find(" ");
            while(lugarFinal<lugarInicio){
                linea[i].erase(0, 1);
                lugarFinal=linea[i].find(" ");
            }
            //Se crea un substring donde se guarda la etiqueta @......
            etiqueta=linea[i].substr(0,lugarFinal);

            //Se borra la etiqueta y el espacio de linea[]
            linea[i].erase(0, lugarFinal+1);

            //Segun la etiqueta tipoEtiqueta toma un valor
            if (etiqueta=="@progName")
                tipoEtiqueta=0;
            else
            if (etiqueta=="@desc")
                tipoEtiqueta=1;
            else
            if (etiqueta=="@author")
                tipoEtiqueta=2;
            else
            if (etiqueta=="@date")
                tipoEtiqueta=3;
            else
            if (etiqueta=="@funcName")
                tipoEtiqueta=4;
            else
            if (etiqueta=="@param")
                tipoEtiqueta=5;
            else
            if (etiqueta=="@return")
                tipoEtiqueta=6;

            //Segun el valor de tipoEtiqueta escribe la linea de una forma u otra
            switch(tipoEtiqueta){
                case 0:
                archivoSalida<<"<h2>\nPrograma: "<<linea[i]<<"<br>\n</h2>\n";
                break;
                case 1:
                archivoSalida<<"<strong>Descripci&oacute;n: </strong>"<<linea[i]<<"<br>\n";
                break;
                case 2:
                archivoSalida<<"<strong> Autor: </strong>"<<linea[i]<<"<br>\n";
                break;
                case 3:
                archivoSalida<<"<strong> Fecha de elaboraci&oacute;n: </strong>"<<linea[i]<<"<br>\n";
                break;
                case 4:
                archivoSalida<<"<h3>\n<hr><br>Nombre de la Funci&oacute;n: "<<linea[i]<<"<br>\n</h3>\n";
                break;
                case 5:
                archivoSalida<<"<strong> Parametro: </strong>"<<linea[i]<<"<br>\n";
                break;
                case 6:
                archivoSalida<<"<strong> Valor de retorno: </strong>"<<linea[i]<<"<br>\n";
                break;
                default:
                break;
            }
        }
    }
    //Terminacion del Archivo html
    archivoSalida<<"</body>\n</html>";
    archivoSalida.close();

    cout<<"El archivo "<<nombreArchivoCpp<<" se ha documentado correctamente en "<<nombreArchivoHtml;
    return 0;
}