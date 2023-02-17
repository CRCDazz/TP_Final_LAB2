#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include <limits>

using namespace std;

#include "cargarCadena.h"
#include "claseFecha.h"

#include "clasePelicula.h"
#include "codigoPeliculas.h"

#include "claseProductos.h"
#include "codigoProductos.h"

#include "claseCompras.h"
#include "claseCompraDetalle.h"

#include "codigoCompras.h"
#include "CodigoVentas.h"
#include "Reportes.h"


void menuEmpleados();
void menuVentas();
void mostarArchivoVentaEntradas();
void mostrarArchivoVentaProductos();

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    //system("color 57");
    int opc;
    while(true){
        system("cls");
        cout<<"\n\t\t\t\t"<<"CINEMARK C&C "<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. PELICULAS"<<endl;
        cout<<"\t\t\t\t"<<"2. EMPLEADOS"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. FIN DEL PROGRAMA"<<endl;
        cout<<endl;
        cout<<"\t\t\t\tOPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: menuComprar();
                    break;
            case 2: menuEmpleados();
                    break;
            case 0:
                cout<<"\t\t\t\t"<<"================="<<endl;
                cout<<"\t\t\t\t"<<"   HASTA LUEGO   "<<endl;
                cout<<"\t\t\t\t"<<"================="<<endl;
                return 0;
            break;
            default:cout<<"\t\t\t\t"<<"OPCION INCORRECTA"<<endl;
                    break;
        }
        cout<<endl;
        system("pause>>null");
    }
	return 0;
}


void menuEmpleados(){
    int opc;
    while(true){
        system("cls");
        cout<<"\n\t\t\t\t"<<"MENU EMPLEADOS "<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. MENU PELICULAS"<<endl;
        cout<<"\t\t\t\t"<<"2. MENU PRODUCTOS"<<endl;
        cout<<"\t\t\t\t"<<"3. MENU VENTAS"<<endl;
        cout<<"\t\t\t\t"<<"4. MENU REPORTES"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. VOLVER"<<endl;
        cout<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>opc;
        switch(opc){
            case 1: menuPeliculas();
                    break;
            case 2: menuProductos();
                    break;
            case 3: menuVentas();
                    break;
            case 4: menuReportes();
                    break;
            case 0: cout<<"\n\t\t\t\t"<<"Presione una tecla para continuar......";
                    return;
                    break;
            default:cout<<"\n\t\t\t\t"<<"OPCION INCORRECTA"<<endl;
                    break;
        }
    }
}



