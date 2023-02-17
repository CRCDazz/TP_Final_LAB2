#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED


void peliculaMasVista();
void diaMayorVenta();
void mesMayorVenta();
void productoMasComprado();
void listarCompraDetalle();
void recaudacionAnual();
int buscarMayorValor(float *vec,int tam);
int buscarMayorValor(int *vec,int tam);
int encontrarMayor(float *vec,int tam);
int encontrarMayor(int *vec,int tam);
int cantidadDeDias(int anio, int mes);
bool esBisiesto(int anio);


void menuReportes(){
    int opc;
    bool salir=true;
    while(salir){
        system("cls");
        cout<<"\n\t\t\t\t"<<"CINEMARK C&C "<<endl<<endl;
        cout<<"\t\t\t\t"<<"MENU REPORTES"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. PELICULA MAS VISTA EN CARTELERA"<<endl;
        cout<<"\t\t\t\t"<<"2. DIA DE MAYOR VENTA"<<endl;
        cout<<"\t\t\t\t"<<"3. MES DE MAYOR VENTA"<<endl;
        cout<<"\t\t\t\t"<<"4. PRODUCTO MAS COMPRADO"<<endl;
        cout<<"\t\t\t\t"<<"5. RECAUDACION ANUAL"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: peliculaMasVista();
                    break;
            case 2: diaMayorVenta();
                    break;
            case 3: mesMayorVenta();
                    break;
            case 4: productoMasComprado();
                    break;
            case 5: recaudacionAnual();
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

void peliculaMasVista(){
    pelicula regPeli,*vecPeli;
    compra regCompra;
    int cantPeli=cantidadPeliculas();   ///cuento cuantas peliculas hay
    int *vec;
    vecPeli=new pelicula[cantPeli];
    if(vecPeli==NULL){
        cout<<"\t\t\t\t"<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    vec=new int[cantPeli];
    if(vec==NULL){
        cout<<"\t\t\t\t"<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    for(int i=0;i<cantPeli;i++){
        vec[i]=0;
    }
    int posPeli=0;
    while(regPeli.leerDeDisco(posPeli)){///leo el archivo de peliculas
        if( regPeli.getEstado()==true ){
            vecPeli[posPeli]=regPeli;   ///guardo un registro solo si no fue dado de baja, no me importa si queda basura en las otras posiciones porque el vector acumulador con las posiciones de referencia queda en 0
            int posCompra=0;
            while(regCompra.leerDeDisco(posCompra)){ ///leo el archivo de compras
                if( regPeli.getIdPeli()==regCompra.getIdPeliComprada()  ){
                    vec[posPeli]=vec[posPeli]+regCompra.getCantEntradas();     ///acumulo cantidad de peliculas
                }
                posCompra++;
            }
        }
        posPeli++;
    }
    int maximo=encontrarMayor(vec,cantPeli);
    regPeli=vecPeli[maximo];
    cout<<"\t\t\t\t"<<"======================================="<<endl;
    cout<<"\t\t\t\t"<<"Pelicula En Cartelera Mas Vista: "<<regPeli.getNombrePeli()<<" Entradas Vendidas: "<<vec[maximo]<<endl;
    cout<<"\t\t\t\t"<<"======================================="<<endl;

    delete[] vecPeli;
    delete[] vec;
}

void diaMayorVenta(){
    compra regCompra;
    int mes,anio,dias;
    int *vecDias={0};
    cout<<"\t\t\t\t"<<"Ingrese el Mes y Año de ventas: "<<endl;
    cout<<"\t\t\t\t"<<"==========================="<<endl;
    cout<<endl;
    cout<<"\t\t\t\t"<<"MES: ";
    cin>>mes;
    cout<<"\t\t\t\t"<<"AÑO: ";
    cin>>anio;

    dias=cantidadDeDias(anio,mes); ///veo cuantos dias le corresponden al mes teniendo en cuenta si es año biciesto o no
    vecDias=new int[dias];
    if(vecDias==NULL){
        cout<<"\t\t\t\t"<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    for(int i=0;i<dias;i++){
        vecDias[i]=0;
    }

    int posCompra=0;
    while( regCompra.leerDeDisco(posCompra) ){  ///leemos el archivo compras
        if( regCompra.getFechaDeCompra().getAnio()==anio && regCompra.getFechaDeCompra().getMes()==mes )
            vecDias[regCompra.getFechaDeCompra().getDia()-1]+=regCompra.getMontoFinal();
        posCompra++;
    }
    int posMayor=encontrarMayor(vecDias,dias);
    if(vecDias[posMayor]==0){
        cout<<endl;
        cout<<"\t\t\t\t"<<"==========================="<<endl;
        cout<<"\t\t\t\t"<<"NO HAY VENTAS EN ESA FECHA"<<endl;
        cout<<"\t\t\t\t"<<"==========================="<<endl;
    }
    else{
        cout<<endl;
        cout<<"\t\t\t\t"<<"========================="<<endl;
        cout<<"\t\t\t\t"<<"DIA DE MAYOR VENTA: "<<posMayor+1<<endl;
        cout<<"\t\t\t\t"<<"========================="<<endl;
    }
    delete[] vecDias;
}

void mesMayorVenta(){
    compra regCompra;
    int anio;
    cout<<"\t\t\t\t"<<"Ingrese el Año de ventas: "<<endl;
    cout<<endl<<"\t\t\t\t"<<"AÑO: ";
    cin>>anio;
    int vecMeses[12]={0};
    int posCompra=0;
    while(regCompra.leerDeDisco(posCompra)){    ///leemos el archivo compras
        if( regCompra.getFechaDeCompra().getAnio()==anio ){
            vecMeses[regCompra.getFechaDeCompra().getMes()-1]+=regCompra.getMontoFinal();
        }
        posCompra++;
    }
    int posMayor=encontrarMayor(vecMeses,12);
    if(vecMeses[posMayor]==0){
        cout<<endl;
        cout<<"\t\t\t\t"<<"========================="<<endl;
        cout<<"\t\t\t\t"<<"NO HAY VENTAS ESE AÑO"<<endl;
        cout<<"\t\t\t\t"<<"========================="<<endl;
    }
    else{
        cout<<endl;
        cout<<"\t\t\t\t"<<"========================="<<endl;
        cout<<"\t\t\t\t"<<"MES DE MAYOR VENTA: "<<posMayor+1<<endl;
        cout<<"\t\t\t\t"<<"========================="<<endl;
    }
}
void productoMasComprado(){
    producto regProd;
    compraDetalle reg;
    int posProd=0;
    int cantProd;
    cantProd=cantidadProductos();///cuento la cantidad de productos en el archivo compraDetalle
    int *vec;
    vec=new int[cantProd];
    if(vec==NULL){
        cout<<"\t\t\t\t"<<"ERROR DE ASIGNACION DE MEMORIA"<<endl;
        return;
    }
    for(int i=0;i<cantProd;i++){
        vec[i]=0;
    }
    while(regProd.leerDeDisco(posProd)){        ///leo el archivo de productos  ///si algun producto fue dado de baja no lo voy a tener en cuenta para el informe
        if(regProd.getEstado()==true){
            int posCompra=0;
            while(reg.leerDeDisco(posCompra)){  ///leo el archivo de compraDetalle
                if( regProd.getIdProducto()==reg.getIdProduComprados() && reg.getEstado()==true ){
                    vec[posProd]++;
                }
                posCompra++;
            }
        }
        posProd++;
    }

    int posMax=0;
    int maximo=vec[0];
    for(int i=1;i<cantProd;i++){
        if(vec[i]>maximo){
            maximo=vec[i];
            posMax=i;
        }
    }
    if(maximo==0){
        cout<<"\t\t\t\t"<<"======================================="<<endl;
        cout<<"\t\t\t\t"<<"SIN VENTA DE PRODUCTOS..."<<endl;
        cout<<"\t\t\t\t"<<"======================================="<<endl;
    }else{
        regProd.leerDeDisco(posMax);
        cout<<"\t\t\t\t"<<"======================================="<<endl;
        cout<<"\t\t\t\t"<<"LA EL PRODUCTO MAS COMPRADO ES: "<<regProd.getNombreProducto()<<endl;
        cout<<"\t\t\t\t"<<"======================================="<<endl;
    }
    delete[] vec;
}
void recaudacionAnual(){
    compra regCompra;
    float acum=0;
    int anio,posCompra=0;
    cout<<"\t\t\t\t"<<"Ingrese el Año de ventas: "<<endl;
    cout<<endl<<"\t\t\t\t"<<"AÑO: ";
    cin>>anio;
    while(regCompra.leerDeDisco(posCompra)){    ///leo el archivo de compra
        if(regCompra.getFechaDeCompra().getAnio()==anio)
            acum+=regCompra.getMontoFinal();    ///acumulo las ventas
        posCompra++;
    }
    cout<<"\t\t\t\t"<<"========================="<<endl;
    cout<<"\t\t\t\t"<<"Recaudacion Anual: "<<acum<<endl;
    cout<<"\t\t\t\t"<<"========================="<<endl;
}
int buscarMayorValor(float *vec,int tam){
    int mayor;
    mayor=vec[0];
    for(int i=1;i<tam;i++){
        if(vec[i]>mayor)
            mayor=vec[i];
    }
    return mayor;
}
int buscarMayorValor(int *vec,int tam){
    int mayor;
    mayor=vec[0];
    for(int i=1;i<tam;i++){
        if(vec[i]>mayor)
            mayor=vec[i];
    }
    return mayor;
}
int encontrarMayor(float *vec,int tam){
    int mayor=0,posMayor=0;
    mayor=vec[0];
    for(int i=1;i<tam;i++){
        if(vec[i]>mayor){
            mayor=vec[i];
            posMayor=i;
        }
    }
    return posMayor;
}
int encontrarMayor(int *vec,int tam){
    int mayor=0,posMayor=0;
    mayor=vec[0];
    for(int i=1;i<tam;i++){
        if(vec[i]>mayor){
            mayor=vec[i];
            posMayor=i;
        }
    }
    return posMayor;
}

int cantidadDeDias(int anio, int mes){

    if( mes==1 || mes==3 || mes==5 || mes==7 || mes==10 || mes==12 )
        return 31;
    if( mes==4 || mes==6 || mes==8 || mes==9 || mes==11 )
        return 30;
    if( ( anio%4==0 && anio%100!=0 ) || anio%400==0 )
        return 29;
    return 28;
}

bool esBisiesto(int anio){
    if( ( anio%4==0 && anio%100!=0 ) || anio%400==0 )
        return true;
    return false;
}
/***********************
///version que solo busca al primer mayor

void peliculaMasVista(){
    peliculas regPeli,regAux;
    compras regCompra;
    int posPeli=0,mayor=0;
    int cantPeli=cantidadPeliculas();
    int *vec={0};
    vec=new int[cantPeli];
    while(regPeli.leerDeDisco(posPeli)){
        int posCompra=0;
        if( regPeli.getEstado()==true ){
            vecPeli[posPeli]=regPeli;
            while(regCompra.leerDeDisco(posCompra)){
                if( regPeli.getIdPeli()==regCompra.getIdPeliComprada() ){
                    vec[posPeli]++;
                }
                posCompra++;
            }
            if( vec[posPeli]>mayor ){
                mayor=vec[posPeli];
                regAux=regPeli;
            }
        }
        posPeli++;
    }
    cout<<"Pelicula mas vista: "<<regAux.getNombrePeli()<<" Cantidad de veces: "<<vec[i]<<endl;
    delete vec;
}

***********************/

#endif // REPORTES_H_INCLUDED
