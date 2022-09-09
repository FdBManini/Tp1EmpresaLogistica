#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CargarDatos(float Datos[4][120],int colm) {
    ifstream file;
    file.open("Datos.txt");

    if (!file || file.fail()) {
            cout << "Error al tratar de abrir el archivo de produccion" << endl;
    } else{
            for (int a = 0; a < colm; a++){
                file >> Datos[0][a] >> Datos[1][a] >> Datos[2][a] >> Datos[3][a];
            }                
    }   
    file.close();
            
           cout << "Datos Cargados " << endl;

}

void CargarNombres(string Nombres[],string Productos[], int TotalCant , int CantNom) {
    ifstream file2;
    file2.open("Nombres.txt");

    if (!file2 || file2.fail()) {
            cout << "Error al tratar de abrir el archivo de produccion" << endl;
    } else{
            for (int i = 0; i < TotalCant; i++){
               if (i < CantNom) {
                   file2 >> Nombres[i] ;
                } else {
                        file2 >> Productos[i-CantNom];// i(9)-9 = 0; asi empieza desde la posc 0;
               }
            }                
    }   
    file2.close();    
    cout << "Nombres Cargados " << endl;

}

void Mostra_Datos_String(string data[], int cant ) {
    cout << "---------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < cant; i++){
            cout << i <<") Dato = " << data[i] <<endl;
        }   
    cout << "---------------------------------------------------------------------------------" << endl;

}


int main(){
    const int colm = 120;// Cantidad de columnas 
    const int fila = 4;// Cantidad de Filas

    const int CantNom = 8; //Cantidad de nombres
    const int CantProd = 5;//Cantidad de Productos
    const int TotalCant = CantNom + CantProd;//Cantidad total de nombres y productos

    const float max = 13000;//Total Maximo de peso
    float MaxPeso = 0;  //Cantidad total de peso 
    int VectPers[CantNom]; //Vector donde pones a las personas que superan el max
    int cant = 0; // El indice del VectPers[] 
    int datoAux; // donde va el codigo del producto (Datos[1][j]) para pasarselo al Productos[datoAux]

    float Datos[fila][colm];//Donde se ponen los datos de Datos.txt


    string Nombres[CantNom];//Donde se ponen los nombres datos de Nombres.txt
    string Productos[CantProd];//Donde se ponen los Productos datos de Nombres.txt

    float KmRec[CantProd]; // Vector de la suma de todos los km de los clientes cliente 
    float KmMax = 0; // Variable donde se suman la todos los km de 1 cliente y se los pasa al vector 
    const int dimKm = 2;// Tamaño del vector del KmAux
    float KmAux [dimKm][CantProd]; // km[0][x] = IdProd y km[1][x] = total del km de ese IdProd 
    int KmAux2; //Guarda el KmAux[0][i] para pasarselo a Productos[]
   
    float Maxkm ; //El mayor km
    int MaxkmIdProd = 0; // El id del producto con mas km
    int cantEnvios = 0;

    CargarDatos(Datos,colm);
    CargarNombres(Nombres,Productos,TotalCant,CantNom);

    // Mostra_Datos_String(Nombres,CantNom);
    // Mostra_Datos_String(Productos,CantProd);


//Punto 1 -----------------------------------------------------------------------------------------------------------------------------
    for (int j = 0; j < CantNom ; j++){ //Punto 1 Recorre el vector Datos y guarda el id de las personas en VectPers[]
        for (int i = 0; i < colm; i++){
            if(Datos[0][i] == j){
                //cout <<"Dato[2][" <<colm<< "]  = " << Datos[2][i] <<endl;
                MaxPeso += Datos[2][i];
            }
        }
        if(MaxPeso > max){
            VectPers[cant] = j;
            ++cant;
        }
        MaxPeso = 0;
    }
    cout <<"Listado por clientes, de los tipos de productos que superen los " << max << " Kg acumulados:" <<endl;


    for (int i = 0; i < cant; i++){ //Muestra el VectPers[] 
        cout << VectPers[i] << ") "<<Nombres[VectPers[i]]  << " : ";
            for (int s = 0; s < CantProd; s++){
                for (int j = 0; j < colm; j++){
                    if (Datos[0][j] == VectPers[i] && Datos[1][j] == s){ // No se me ocurrio como hacer para que no se repitan    
                        datoAux = Datos[1][j];   
                        cout << Productos[datoAux] << ", ";
                    }              
                }

            }
                cout << endl; 
    }    
                cout << endl;
//Punto 1 -----------------------------------------------------------------------------------------------------------------------------

//Punto 2 -----------------------------------------------------------------------------------------------------------------------------

    for (int s = 0; s < CantProd; s++){ // Guarda la suma de los km en el vector KmRec[] y lo guarda en el indice "S"
        for (int i = 0; i < colm; i++){
            for (int j = 0; j < cant; j++){
                if ( VectPers[j] == Datos[0][i] &&  s == Datos[1][i] ){
                    KmMax += Datos[3][i];
                }
            }  
        }
        KmRec[s] = KmMax;
        KmMax = 0;
    }
    cout <<"Sin ordenar los km" << endl;
    for (int i = 0; i < CantProd; i++){ // Muestra los valores de los vectores VectPers[] y KmRec[]
        cout << VectPers[i] << ") "<<Productos[VectPers[i]]  << " : ";
        cout << KmRec[i] << " km" << endl;
    }
    cout << endl;
    cout <<"Ordenados los km" << endl;

    for (int i = 0; i < CantProd; i++){ // Guarda en KmAux[] los valores de id prodc y km mayor
        KmAux[0][i] =  VectPers[i];
        KmAux[1][i] =  KmRec[i];
    }
    
    for (int j = 0; j < CantProd; j++){ // Ordenar los valores de KmAux[]
            for (int i = 1; i < CantProd; i++){ 
                //cout << KmAux[1][i] << " > "<< KmAux[1][i-1] << endl;
                if ( KmAux[1][i] <  KmAux[1][i-1]){
                    swap( KmAux[1][i], KmAux[1][i-1]);
                    swap( KmAux[0][i], KmAux[0][i-1]);
                }     
            } 
    }
    Maxkm = KmAux[1][0];      
    for (int i = 0; i < CantProd; i++){ // Muestra los valores de KmAux[] 
        KmAux2 = KmAux[0][i];
        cout << KmAux[0][i] << ") "<<Productos[KmAux2]  << " : ";
        cout << KmAux[1][i] << " km" << endl;
        if ( KmAux[1][i] > Maxkm){// Punto 3 Tomo los valores mayores de km y Id del Producto
            Maxkm = KmAux[1][i];
            MaxkmIdProd  = KmAux[0][i];
        }   
    }

//Punto 2 -----------------------------------------------------------------------------------------------------------------------------

//Punto 3 -----------------------------------------------------------------------------------------------------------------------------
 
    cout << endl;
    cout << "Producto Mayor = "  << Productos[MaxkmIdProd] << endl;
    cout << "Km Mayor = "  << Maxkm << endl;
    for (int i = 0; i < colm; i++){
        if (Datos[1][i] == MaxkmIdProd ){
            cantEnvios++;
        }
    }
    cout << "La cantidad de envios de "<< Productos[MaxkmIdProd] <<" es de "<< cantEnvios << endl;

//Punto 3 -----------------------------------------------------------------------------------------------------------------------------
       
    return 0;
}
