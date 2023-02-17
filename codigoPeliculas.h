#ifndef CODIGOPELICULAS_H_INCLUDED
#define CODIGOPELICULAS_H_INCLUDED

//#include "clasePelicula.h"
//#include "cargarCadena.h"

bool agregarPelicula();
void listarPelicula();
void listarPeliculas();
bool modificarFechaDeEstreno();
bool eliminarPelicula();
int buscarIdPelicula( int);
int cantidadPeliculas();
pelicula leerRegistroPelicula( int);


void menuPeliculas(){
    int opc;
    bool salir=true;
    while(salir){
        system("cls");
        cout<<"\n\t\t\t\t"<<"MENU PELICULAS"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. AGREGAR PELICULA"<<endl;
        cout<<"\t\t\t\t"<<"2. LISTAR PELICULA POR ID"<<endl;
        cout<<"\t\t\t\t"<<"3. LISTAR TODAS LAS PELICULAS"<<endl;
        cout<<"\t\t\t\t"<<"4. MODIFICAR FECHA DE ESTRENO"<<endl;
        cout<<"\t\t\t\t"<<"5. ELIMINAR PELICULA"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: if(!agregarPelicula())
                        cout<<"\t\t\t\t"<<"ERROR al intentar agregar Pelicula."<<endl;
                    else
                        cout<<"\t\t\t\t"<<"Pelicula Agregada."<<endl;
                    break;
            case 2: listarPelicula();
                    break;
            case 3: listarPeliculas();
                    break;
            case 4: if(!modificarFechaDeEstreno())
                        cout<<"\t\t\t\t"<<"ERROR al intentar Modificar Fecha."<<endl;
                    else
                        cout<<"\t\t\t\t"<<"Modificancion de Fecha Exitosa."<<endl;
                    break;
            case 5: if(!eliminarPelicula())
                        cout<<"\t\t\t\t"<<"ERROR al eliminar Pelicula."<<endl;
                    else
                        cout<<"\t\t\t\t"<<"Pelicula eliminada."<<endl;
                    break;
            case 0: salir=false;
                    break;
            default:cout<<"\t\t\t\t"<<"OPCION INCORRECTA"<<endl;
                    break;
        }
        cout<<endl;
        if(salir!=false){
        system("pause>>null");
        }
    }
}

bool agregarPelicula(){
    pelicula obj,aux;
    if(cantidadPeliculas() <= 0){
        obj.setIdPeli(1);
    }else{
        aux.leerDeDisco(cantidadPeliculas()-1);
        int ultimoID = aux.getIdPeli();
        obj.setIdPeli(ultimoID+1);
    }
    if( !obj.cargar(obj.getIdPeli()) )
        return false;
    return obj.grabarEnDisco();
}

void listarPelicula(){
    pelicula reg;
    int id,pos;
    cout<<"\t\t\t\t"<<"Ingresar ID de la Pelicula: ";
    cin>>id;
    pos=buscarIdPelicula(id);
    system("cls");
    if(pos!=-1){
        cout<<"\t\t\t\t"<<"======================"<<endl;
        reg.leerDeDisco(pos);
        reg.mostrar();
        cout<<"\t\t\t\t"<<"======================"<<endl;
    }else
        cout<<"\t\t\t\t"<<"NO EXISTE ID ingresado."<<endl;
}

void listarPeliculas(){
    pelicula regPeliculas;
    int pos=0;
    while(regPeliculas.leerDeDisco(pos++)){
        cout<<"\t\t\t\t"<<"======================"<<endl;
        regPeliculas.mostrar();
        cout<<"\t\t\t\t"<<"======================"<<endl;
    }
}

bool modificarFechaDeEstreno(){
    pelicula regPeliculas;
    fecha nuevaFecha;
    int id,pos;
    cout<<"\t\t\t\t"<<"Ingresar ID de la Pelicula: ";
    cin>>id;
    pos=buscarIdPelicula(id);
    system("cls");
    if(pos!=-1){
        regPeliculas.leerDeDisco(pos);
        cout<<"\t\t\t\t"<<"Ingresar Nueva FECHA de ESTRENO."<<endl;
        cout<<"\t\t\t\t"<<"======================"<<endl;
        nuevaFecha.Cargar();

        if(regPeliculas.setFechaEstreno(nuevaFecha))
            return regPeliculas.modificarEnDisco(pos);
    }else
        cout<<"\t\t\t\t"<<"NO EXISTE ID ingresado."<<endl;
    return false;
}

bool eliminarPelicula(){
    pelicula regPeliculas;
    int id,pos;
    cout<<"\t\t\t\t"<<"Ingresar ID de la Pelicula: ";
    cin>>id;
    pos=buscarIdPelicula(id);
    if(pos!=-1){
        regPeliculas.leerDeDisco(pos);
        regPeliculas.setEstado(false);
        return regPeliculas.modificarEnDisco(pos);
    }else
        cout<<"\t\t\t\t"<<"NO EXISTE ID ingresado."<<endl;
    return false;
}

int buscarIdPelicula(int id){
    pelicula reg;
    FILE *p;
    int pos=0;
    p=fopen("peliculas.dat","rb");
    if(p==NULL){
        return -1;
    }
    while(fread(&reg,sizeof reg, 1, p)==1){
        if(reg.getIdPeli()==id){
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

pelicula leerRegistroPelicula(int pos){
    pelicula reg;
    FILE *p;
    p=fopen("peliculas.dat","rb");
    if(p==NULL){
        return reg;
    }
    int desplazamiento=pos*sizeof reg;
    fseek(p,desplazamiento,0);
    fread(&reg, sizeof reg, 1,p);
    fclose(p);
    return reg;
}

int cantidadPeliculas(){
FILE *archivo;
    int cantidad;
    archivo=fopen("peliculas.dat","rb");
    if(archivo==NULL){return -1;}
    fseek(archivo,0,SEEK_END);
    if(ftell(archivo) == 0){
        fclose(archivo);
        return 0;
    }
    cantidad=(ftell(archivo)/sizeof(pelicula));
    fclose(archivo);
    return cantidad;
}

#endif // CODIGOPELICULAS_H_INCLUDED
