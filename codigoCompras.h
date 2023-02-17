#ifndef CODIGOCOMPRAS_H_INCLUDED
#define CODIGOCOMPRAS_H_INCLUDED
/*
#include "claseCompras.h"
#include "cargarCadena.h"
#include "clasePelicula.h"
#include "claseProductos.h"
*/
void verCartelera();
bool agregarCompraEntradas();
bool agregarCompraProductos();
bool agregarCompraProductos(compraDetalle *v, int tam, compra regCompra);

int buscarIdCompras( int);
int buscarIdDetalle(int id);
int cantidadCompras();
int cantidadCompraDetallada();

void grabarVectorRegistroDetalle(compraDetalle *v, int tam);
void clearVector(int *v, int tam);
void clearVector(compraDetalle *v, int tam);
int cantidadProductosActivos();
void vectorProductosActivos(producto *v);
void ordenarVectorPorCategoria(producto *v, int tam);
void clearCantidadDetalle(compraDetalle *vecDetalle,int tam);
bool eliminarRegistroDetalle(int id);

int elegirCantidadEntradas();

void menuComprar(){
    int opc;
    bool salir=true;
    while(salir){
        system("cls");
        cout<<"\n\t\t\t\t"<<"CINEMARK C&C "<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. VER CARTELERA"<<endl;
        cout<<"\t\t\t\t"<<"2. COMPRAR ENTRADAS"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
                verCartelera();
                break;
            case 2:
                if(!agregarCompraEntradas())
                    cout<<"\t\t\t\t"<<"Compra Cancelada"<<endl;
                else
                    cout<<"\t\t\t\t"<<"Compra agregada."<<endl;
                break;
            case 0:
                cout<<"\t\t\t\t"<<"Presione una tecla para continuar......";
                salir=false;
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

void verCartelera(){
    pelicula regPelicula;
    int posPelicula=0;
    cout<<"\t\t\t\t"<<"==========================="<<endl;
    while(regPelicula.leerDeDisco(posPelicula)){
        regPelicula.mostrar();
    cout<<"\t\t\t\t"<<"==========================="<<endl;
        posPelicula++;
    }
}

bool agregarCompraEntradas(){
    pelicula regPeli;
    compra regCompra,regAuxCompra;
    int posPeli=0;
    system("cls");
    cout<<"\t\t\t\t"<<"CINEMARK C&C "<<endl<<endl;
    cout<<"\t\t\t\t"<<"CARTELERA"<<endl;
    cout<<"\t\t\t\t"<<"==================="<<endl;
    while(regPeli.leerDeDisco(posPeli)){    ///leo el archivo de peliculas
        if(regPeli.getEstado()==true)
            cout<<"\t\t\t\t"<<"ID: "<<regPeli.getIdPeli()<<" - NOMBRE: "<<regPeli.getNombrePeli()<<" - PRECIO: "<<regPeli.getPrecioEntrada()<<"$"<<endl;
        posPeli++;
    }
    cout<<"\t\t\t\t"<<"==================="<<endl;
    cout<<"\t\t\t\t"<<"0. VOLVER AL MENU ANTERIOR"<<endl<<endl;
    int idPeli;
    cout<<"\t\t\t\t"<<"Eligir PELICULA  por  ID: ";
    cin >>idPeli;
    if(idPeli==0)
        return false;
    if(buscarIdPelicula(idPeli)==-1 ){
        cout<<"\t\t\t\t"<<"ID INCORRECTO, PELICULA NO EXISTE..."<<endl;
        return false;
    }
    regPeli.leerDeDisco(buscarIdPelicula(idPeli));
    if(regPeli.getEstado()==false){
        cout<<"\t\t\t\t"<<"ID INCORRECTO, PELICULA NO EXISTE..."<<endl;
        return false;
    }
    int cantEntradas=elegirCantidadEntradas();  ///elijo cuantas entradas quiero comprar
    if(cantEntradas==-1)
        return false;
    int cantRegCompra=cantidadCompras();        ///busco cuantos registros hay en el archivo compras
    if(cantRegCompra<=0){                       ///para setear el numero de ID
        regCompra.setIdCompra(1);
    }else{
        regAuxCompra.leerDeDisco(cantRegCompra-1);
        regCompra.setIdCompra(regAuxCompra.getIdCompra()+1);
    }
    cout<<"\t\t\t\t"<<"Nombre del Cliente: ";
    char nombre[30]={0};
    cargarCadena(nombre,29);
    regCompra.setNombreComprador( nombre);
    fecha fechaCompra;
    regCompra.setFechaCompra( fechaCompra.hoy() );
    regCompra.setIdPeliComprada(idPeli);
    regCompra.setCantEntradas(cantEntradas);
    regCompra.setEstado(true);
    int cantProdAct=cantidadProductosActivos(); ///cuento cuantos productos estan activos
    compraDetalle *vecDetalle;                  ///para asignarle un tamaño al vector detalle
    vecDetalle = new compraDetalle[cantProdAct];///creo vector detalle de compras
    if(vecDetalle==NULL){
        cout<<"\t\t\t\t"<<"PROBLEMAS DE ASIGNACION DE MEMORIA"<<endl;
        return false;
    }
    clearCantidadDetalle(vecDetalle,cantProdAct);///dejo en 0 el campo cantidad de productos
    if( !agregarCompraProductos(vecDetalle,cantProdAct,regCompra) ){
        delete[] vecDetalle;
        return false;
    }
    compraDetalle regAuxCompraDetallada;
    float montoFinal=0;
        int id;
        int cantReg=cantidadCompraDetallada();  ///cuento cuantos registros tengo en el archivo compraDetalle
        if(cantReg<=0){                         ///para luego asignarle un valor de ID al nuevo registro
            id=1;
        }else{
            regAuxCompraDetallada.leerDeDisco(cantReg-1);   ///leo el ultimo registro del archivo
            id=regAuxCompraDetallada.getIdDetalle()+1;      ///le asigno un valor al nuevo ID ( ID anterior + 1 )
        }
        int varAux=0;
        for(int i=0; i<cantProdAct; i++){
            if(vecDetalle[i].getCantProductos()>0){
                vecDetalle[i].setIdDetalle(id+varAux);      ///varAux me aumenta el valor de ID por cada producto distinto que tenga en el vector
                vecDetalle[i].setEstado(true);
                int posIdAux=buscarIdProducto(vecDetalle[i].getIdProduComprados()); ///busco la posicion del producto en el archivo productos
                producto regAuxProd;                                                ///luego leo el archivo productos en esa posicion y obtengo el valor de
                regAuxProd.leerDeDisco(posIdAux);                                   ///producto para multiplicarlo por la cantidad de productos en el vector
                montoFinal += ( regAuxProd.getPrecioProducto()*vecDetalle[i].getCantProductos() );
                varAux++;
            }
        }
        regPeli.leerDeDisco( buscarIdPelicula(regCompra.getIdPeliComprada()) );     ///uso el ID de la pelicula comprada para luego buscar en el archivo peliculas su precio
        montoFinal += ( regPeli.getPrecioEntrada()*regCompra.getCantEntradas() );
        regCompra.setMontoFinal(montoFinal);
        cout<<endl;
        cout<<"\t\t\t\t"<<"======================================"<<endl;
        cout<<"\t\t\t\t"<<"EL MONTO FINAL A PAGAR ES DE: "<<regCompra.getMontoFinal()<<"$"<<endl;
        cout<<"\t\t\t\t"<<"======================================"<<endl;
        cout<<endl;
        regCompra.setEstado(true);
        regCompra.grabarEnDisco();
        for(int i=0; i<cantProdAct; i++){
            if(vecDetalle[i].getCantProductos()>0){
            vecDetalle[i].setIdCompra(regCompra.getIdCompra()); ///vecDetalle[i].setIdCompra(regAuxCompra.getIdCompra()+1); ///tambien puede ser  vecDetalle[i].setIdCompra(regCompra.getIdCompra());
            vecDetalle[i].grabarEnDisco();
            }
        }
        delete[] vecDetalle;
        return true;
}


bool agregarCompraProductos(compraDetalle *vecDetalle, int tam,compra regCompra){

    int cantProdAct=cantidadProductosActivos();
    producto *vecProducto;
    vecProducto = new producto[cantProdAct];///creo vector con los productos en venta activos
    if(vecProducto==NULL){
        cout<<"\t\t\t\t"<<"PROBLEMAS DE ASIGNACION DE MEMORIA"<<endl;
        Sleep(1000);
        menuComprar();
    }
    vectorProductosActivos(vecProducto);
    ordenarVectorPorCategoria(vecProducto,cantProdAct);
    for(int i=0;i<tam;i++){
        vecDetalle[i].setIdProduComprados( vecProducto[i].getIdProducto() );
    }
    int tecla;
    bool opc=true;
    while(opc){
        system("cls");
        cout<<"\t\t\t\t"<<"CINEMARK C&C "<<endl<<endl;
        cout<<"\t\t\t\t"<<"** ¿COMPRAR ALIMENTOS Y BEBIDAS? **"<<endl;
        cout<<"\t\t\t\t"<<"========================================="<<endl;
        for(int i=0; i<tam; i++){
            cout<<"\t\t\t\t"<<i+1<<". "<<vecProducto[i].getNombreProducto()<<" - Precio: "<<vecProducto[i].getPrecioProducto()<<"$ -"<<" AGREGADOS AL CARRITO: ["<<vecDetalle[i].getCantProductos()<<"]"<<endl;

        }
        float montoMostrar=0;
        for(int i=0; i<tam; i++){
        montoMostrar += ( vecProducto[i].getPrecioProducto()*vecDetalle[i].getCantProductos() );
        }
        cout<<endl;
        cout<<"\t\t\t\t"<<"COSTO: "<<montoMostrar<<"$"<<endl;
        cout<<"\t\t\t\t"<<"========================================="<<endl;
        cout<<"\t\t\t\t"<<tam+1<<". ELEGIR PRODUCTOS DE NUEVO"<<endl;
        cout<<"\t\t\t\t"<<"0. TERMINAR COMPRA"<<endl;
        cout<<"\t\t\t\t"<<"========================================="<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>tecla;
        if( tecla>0 && tecla<=tam ){
            int cant;
            cout<<endl;
            cout<<"\t\t\t\t"<<"CUANTOS COMPRAS?: ";
            cin>>cant;
            vecDetalle[tecla-1].setCantProductos(cant);
        }
        if( tecla==(tam+1) )
            clearCantidadDetalle(vecDetalle,tam);
        if(tecla==0)
            opc=false;
        if( tecla<0 || tecla>(tam+1) ){
            cout<<"\t\t\t\t"<<"OPCION INCORRECTA..."<<endl;
            Sleep(1000);
        }
    }
    system("cls");
    pelicula regPeli;
    unsigned char opcion;
    bool sinElementos=true;
    cout<<"\t\t\t\t"<<"SU COMPRA"<<endl;
    int posPeli=buscarIdPelicula(regCompra.getIdPeliComprada());
    regPeli.leerDeDisco(posPeli);
    cout<<"\t\t\t\t"<<"========================"<<endl;
    cout<<"\t\t\t\t"<<"PELICULA: "<<regPeli.getNombrePeli()<<endl;
    cout<<"\t\t\t\t"<<"ENTRADAS COMPRADAS: "<<regCompra.getCantEntradas()<<endl;
    cout<<"\t\t\t\t"<<"========================"<<endl;
    for(int i=0;i<cantProdAct;i++){
        if(vecDetalle[i].getCantProductos()>0){
            cout<<"\t\t\t\t"<<vecProducto[i].getNombreProducto()<<": "<<vecDetalle[i].getCantProductos()<<endl;
            sinElementos=false;
        }
    }
    if(sinElementos==true){
        cout<<"\t\t\t\t"<<"========================================="<<endl;
        cout<<"\t\t\t\t"<<"CONFIRMAR COMPRA SIN PRODUCTOS [Y]/[N]? "<<endl;
        cout<<"\t\t\t\t"<<"========================================="<<endl;
    }else{
        cout<<endl;
        cout<<"\t\t\t\t"<<"========================================="<<endl;
        cout<<"\t\t\t\t"<<"CONFIRMAR COMPRA DE PRODUCTOS [Y]/[N]? "<<endl;
        cout<<"\t\t\t\t"<<"========================================="<<endl;
    }
    cout<<"\t\t\t\t"<<"OPCION: ";
    cin>>opcion;
    cout<<endl;
    if(opcion=='y' || opcion=='Y'){
        delete[] vecProducto;
        return true;
    }
    delete[] vecProducto;
    return false;
}

int buscarIdCompras(int id){
    compra obj;
    int pos=0;
    while(obj.leerDeDisco(pos)){
        if( (id == obj.getIdCompra()) && (obj.getEstado() == true) )
            return pos;
        pos++;
    }
    return -1;
}

int buscarIdDetalle(int id){
    compraDetalle obj;
    int pos=0;
    while(obj.leerDeDisco(pos)){
        if( (id == obj.getIdProduComprados()) && (obj.getEstado() == true) )
            return pos;
        pos++;
    }
    return -1;
}

int cantidadCompras(){
    FILE *archivo;
    archivo=fopen("compraCabecera.dat","rb");
    if(archivo==NULL){return -1;}
    fseek(archivo,0,SEEK_END);
    if(ftell(archivo) == 0){
        fclose(archivo);
        return 0;
    }
    int cantidad=(ftell(archivo)/sizeof(compra));
    fclose(archivo);
    return cantidad;
}
int cantidadCompraDetallada(){
    FILE *archivo;
    archivo=fopen("compraDetalle.dat","rb");
    if(archivo==NULL){return -1;}
    fseek(archivo,0,SEEK_END);
    if(ftell(archivo) == 0){
        fclose(archivo);
        return 0;
    }
    int cantidad=(ftell(archivo)/sizeof(compraDetalle));
    fclose(archivo);
    return cantidad;
}

void grabarVectorRegistroDetalle(compraDetalle *v, int tam){
    compraDetalle regCompraDetalle,auxCompraDetalle;

    int cant=cantidadCompraDetallada();
    auxCompraDetalle.leerDeDisco(cant-1);
    regCompraDetalle.setIdDetalle( auxCompraDetalle.getIdDetalle()+1 );
    for(int i=0; i<tam; i++){
        if(v[i].getCantProductos()>0)
            regCompraDetalle.grabarEnDisco();
    }
}

void clearVector(compraDetalle *v, int tam){
    for(int i=0; i<tam; i++){
        v[i].setCantProductos(0);
    }
}

void clearVector(int *v, int tam){
    for(int i=0; i<tam; i++){
        v[i]=0;
    }
}

int elegirCantidadEntradas(){
    int cantEntradas;
    cout<<"\t\t\t\t"<<"Elegir Cantidad de Entradas: ";
    cin >>cantEntradas;
    if(cantEntradas<=0){
        cout<<"\t\t\t\t"<<"CANTIDAD INCORRECTA..."<<endl;
        return -1;
    }
    return cantEntradas;
}

int cantidadProductosActivos(){
    producto regProducto;
    int cantActivos=0,pos=0;
    while(regProducto.leerDeDisco(pos)){
        if(regProducto.getEstado()==true)
            cantActivos++;
        pos++;
    }
    return cantActivos;
}

void vectorProductosActivos(producto *v){
    producto regProducto;
    int pos=0;
    while(regProducto.leerDeDisco(pos)){
        if(regProducto.getEstado()==true)
            v[pos]=regProducto;
        pos++;
    }
}

void clearCantidadDetalle(compraDetalle *v,int tam){
    for(int i=0; i<tam; i++){
        v[i].setCantProductos(0);
    }
}

void ordenarVectorPorCategoria(producto *v, int tam){
    producto aux;
    for(int i=1; i<tam; i++){
        if( v[i].getCategoria()<v[i-1].getCategoria() ){
            aux=v[i-1];
            v[i-1]=v[i];
            v[i]=aux;
        }
    }
}

bool eliminarRegistroDetalle(int id){
    compraDetalle obj;
    int pos=buscarIdDetalle(id);
    if( pos<0 ){
        obj.leerDeDisco(pos);
        obj.setEstado(false);
        bool modifico=obj.modificarEnDisco(pos);
        if(modifico)
            cout<<"funciona el modificar detalle"<<endl;
        return true;
    }else{
        cout<<"\t\t\t\t"<<"ID Inexistente."<<endl;
        return false;
    }
}
#endif // CODIGOCOMPRAS_H_INCLUDED
