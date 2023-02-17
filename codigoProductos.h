#ifndef CODIGOPRODUCTOS_H_INCLUDED
#define CODIGOPRODUCTOS_H_INCLUDED

//#include "claseProductos.h"
//#include "cargarCadena.h"

bool agregarProducto();
void listarProducto();
void listarProductos();
bool modificarPrecio();
bool eliminarProducto();

int buscarIdProducto( int);
int cantidadProductos();
producto leerRegistroProducto( int);

void menuProductos(){
    int opc;
    bool salir=true;
    while(salir){
        system("cls");
        cout<<"\n\t\t\t\t"<<"MENU PRODUCTO"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. AGREGAR PRODUCTO"<<endl;
        cout<<"\t\t\t\t"<<"2. LISTAR PRODUCTO POR ID"<<endl;
        cout<<"\t\t\t\t"<<"3. LISTAR TODAS LOS PRODUCTOS"<<endl;
        cout<<"\t\t\t\t"<<"4. MODIFICAR PRECIO"<<endl;
        cout<<"\t\t\t\t"<<"5. ELIMINAR PRODUCTO"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: if(!agregarProducto())
                        cout<<"\t\t\t\t"<<"ERROR al intentar agregar Producto."<<endl;
                    else
                        cout<<"\t\t\t\t"<<"Producto Agregado."<<endl;
                    break;
            case 2: listarProducto();
                    break;
            case 3: listarProductos();
                    break;
            case 4: if(!modificarPrecio())
                        cout<<"\t\t\t\t"<<"ERROR al intentar Modificar Precio."<<endl;
                    else
                        cout<<"\t\t\t\t"<<"Precio Modificado."<<endl;
                    break;
            case 5: if(!eliminarProducto())
                        cout<<"\t\t\t\t"<<"ERROR al intentar Eliminar Producto."<<endl;
                    else
                        cout<<"\t\t\t\t"<<"Producto Eliminado."<<endl;
                    break;
            case 0:
                salir=false;
            break;
            default:
                cout<<"\t\t\t\t"<<"OPCION INCORRECTA"<<endl;
            break;
        }
        cout<<endl;
        if(salir!=false){
        system("pause>>null");
        }
    }
}


bool agregarProducto(){
    producto obj,aux;
    if(cantidadProductos() <= 0){
        obj.setIdProducto(1);
    }else{
        aux.leerDeDisco(cantidadProductos()-1);
        int ultimoID = aux.getIdProducto();
        obj.setIdProducto(ultimoID+1);
    }
    if( !obj.cargar(obj.getIdProducto()) )
        return false;
    return obj.grabarEnDisco();
}

void listarProducto(){
    producto reg;
    int id,pos;
    cout<<"\t\t\t\t"<<"Ingresar ID del Producto: ";
    cin>>id;
    pos=buscarIdProducto(id);
    system("cls");
    if(pos!=-1){
        cout<<"\t\t\t\t"<<"==================================="<<endl;
        reg.leerDeDisco(pos);
        reg.mostrar();
        cout<<"\t\t\t\t"<<"==================================="<<endl;
    }else
        cout<<"\t\t\t\t"<<"NO EXISTE ID ingresado."<<endl;
}

void listarProductos(){
    producto reg;
    int pos=0;
    while(reg.leerDeDisco(pos++)){
        cout<<"\t\t\t\t"<<"==================================="<<endl;
        reg.mostrar();
        cout<<"\t\t\t\t"<<"==================================="<<endl;
    }
}

bool modificarPrecio(){
    producto regProductos;
    float nuevoPrecio;
    int id,pos;
    cout<<"\t\t\t\t"<<"Ingresar ID del Producto: ";
    cin>>id;
    pos=buscarIdProducto(id);
    system("cls");
    if(pos!=-1){
        regProductos.leerDeDisco(pos);
        cout<<"\t\t\t\t"<<"Ingresar Nuevo Precio.";
        cin>>nuevoPrecio;
        if(regProductos.setPrecioProducto(nuevoPrecio))
            return regProductos.modificarEnDisco(pos);
    }else
        cout<<"\t\t\t\t"<<"NO EXISTE ID ingresado."<<endl;
    return false;
}

bool eliminarProducto(){
    producto regProductos;
    int id,pos;
    cout<<"\t\t\t\t"<<"Ingresar ID del Producto: ";
    cin>>id;
    pos=buscarIdProducto(id);
    if(pos!=-1){
        regProductos.leerDeDisco(pos);
        regProductos.setEstado(false);
        return regProductos.modificarEnDisco(pos);
    }else
        cout<<"\t\t\t\t"<<"NO EXISTE ID ingresado."<<endl;
    return false;
}

int buscarIdProducto(int id){
    producto reg;
    FILE *p;
    int pos=0;
    p=fopen("productos.dat","rb");
    if(p==NULL){
        return -1;
    }
    while(fread(&reg,sizeof reg, 1, p)==1){
        if(reg.getIdProducto()==id){
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

producto leerRegistroProducto(int pos){
    producto reg;
    FILE *p;
    p=fopen("productos.dat","rb");
    if(p==NULL){
        return reg;
    }
    int desplazamiento=pos*sizeof reg;
    fseek(p,desplazamiento,0);
    fread(&reg, sizeof reg, 1,p);
    fclose(p);
    return reg;
}

int cantidadProductos(){
    FILE *archivo;
    int cantidad;
    archivo=fopen("productos.dat","rb");
    if(archivo==NULL){return -1;}
    fseek(archivo,0,SEEK_END);
    if(ftell(archivo) == 0){
        fclose(archivo);
        return 0;
    }
    cantidad=(ftell(archivo)/sizeof(producto));
    fclose(archivo);
    return cantidad;
}

#endif // CODIGOPRODUCTOS_H_INCLUDED
