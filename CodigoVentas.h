#ifndef CODIGOVENTAS_H_INCLUDED
#define CODIGOVENTAS_H_INCLUDED

void listarCompras();
bool listarCompraPorID();
bool eliminarVenta();

void menuVentas(){
    int opc;
    while(true){
        system("cls");
        cout<<"\n\t\t\t\t"<<"MENU VENTAS "<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"1. MOSTRAR TODAS LAS VENTAS"<<endl;
        cout<<"\t\t\t\t"<<"2. MOSTRAR VENTA POR ID"<<endl;
        cout<<"\t\t\t\t"<<"3. ELIMINAR VENTA POR ID"<<endl;
        cout<<"\t\t\t\t"<<"============================="<<endl;
        cout<<"\t\t\t\t"<<"0. VOLVER"<<endl;
        cout<<endl;
        cout<<"\t\t\t\t"<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
                listarCompras();
            break;
            case 2:
                if(listarCompraPorID()==false){
                cout<<"\t\t\t\t"<<"NO EXISTE ID INGRESADO."<<endl;
                }
            break;
            case 3:
                if( eliminarVenta() )
                    cout<<"\t\t\t\t"<<"ELIMINACION EXITOSA"<<endl;
            break;
            case 0:
                cout<<"\t\t\t\t"<<"Presione una tecla para continuar......";
                return;
            break;
            default:
                cout<<"\t\t\t\t"<<"OPCION INCORRECTA"<<endl;
            break;
        }
        system("pause>>null");
    }

}

void listarCompras(){
    compra regCompra;
    compraDetalle regDetalle;
    int pos1=0,pos2=0;
    while(regCompra.leerDeDisco(pos1++)){
        cout<<"\t\t\t\t"<<"========================"<<endl;
        regCompra.mostrar();
        while(regDetalle.leerDeDisco(pos2++)){
            if( regCompra.getIdCompra()==regDetalle.getIdCompra() && regCompra.getEstado()==true ){
                //if(regDetalle.getEstado()==true){
                    cout<<"\t\t\t\t"<<"========"<<endl;
                    regDetalle.mostrar();
                //}
            }
        }
        pos2=0;
        if(regCompra.getEstado()==true && regDetalle.getEstado()==true){
            cout<<endl;
            cout<<"\t\t\t\t"<<"MONTO FINAL: "<<regCompra.getMontoFinal()<<"$"<<endl;
            cout<<"\t\t\t\t"<<"========================"<<endl;
            cout<<endl;
        }
    }
}

bool listarCompraPorID(){
    compra regCompra;
    compraDetalle regDetalle;
    int id,IdBuscar,pos=0;
    cout<<"\t\t\t\t"<<"INGRESAR EL ID DE LA COMPRA: ";
    cin>>id;
    IdBuscar=buscarIdCompras(id);
    system("cls");
    if(IdBuscar<0)
        return false;
    regCompra.leerDeDisco(IdBuscar);
    cout<<"\t\t\t\t"<<"========================"<<endl;
    regCompra.mostrar();
    while(regDetalle.leerDeDisco(pos++)){
        if(regCompra.getIdCompra()==regDetalle.getIdCompra()){
            if(regDetalle.getEstado()==true){
                cout<<"\t\t\t\t"<<"========"<<endl;
                regDetalle.mostrar();
                }
        }
    }
    cout<<"\t\t\t\t"<<"========================"<<endl;
    return true;
}

bool eliminarVenta(){
    compra regCompra;
    compraDetalle regDetalle;
    int posDetalle=0,id;

    cout<<"\t\t\t\tIngrese ID de la compra a Eliminar: ";
    cin>>id;
    int posIdCompra=buscarIdCompras(id);
    if( posIdCompra<0 ){
        cout<<"\t\t\t\t"<<"NO EXISTE EL NÚMERO DE ID INGRESADO..."<<endl;
        return false;
    }
    regCompra.leerDeDisco(posIdCompra);
    cout<<"\t\t\t\t"<<"========================"<<endl;
    regCompra.mostrar();
    while( regDetalle.leerDeDisco(posDetalle) ){
        if( regCompra.getIdCompra()==regDetalle.getIdCompra() && regDetalle.getEstado()==true ){
            cout<<"\t\t\t\t"<<"========"<<endl;
            regDetalle.mostrar();
        }
        posDetalle++;
    }

    char opcion;
    cout<<"\t\t\t\t"<<"==================================================================="<<endl;
    cout<<"\t\t\t\t"<<"ESTA POR ELIMINAR UNA VENTA PRESIONE CONFIRMAR [Y]/ CANCELAR [N]..."<<endl;
    cout<<"\t\t\t\t"<<"==================================================================="<<endl;
    cout<<"\t\t\t\t"<<"OPCION: ";
    cin>>opcion;
    cout<<endl;
    if(opcion=='n' || opcion=='N'){
        cout<<"\t\t\t\t"<<"OPERACION CANCELADA..."<<endl;
        return false;
    }
    posDetalle=0;
    while( regDetalle.leerDeDisco(posDetalle) ){
        if( regCompra.getIdCompra()==regDetalle.getIdCompra() && regDetalle.getEstado()==true ){
            regDetalle.setEstado(false);
            regDetalle.modificarEnDisco(posDetalle);
        }
        posDetalle++;
    }
    regCompra.setEstado(false);
    regCompra.modificarEnDisco(posIdCompra);
    return true;
}

#endif // CODIGOVENTAS_H_INCLUDED
