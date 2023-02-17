#ifndef CLASEPRODUCTOS_H_INCLUDED
#define CLASEPRODUCTOS_H_INCLUDED

//#include "cargarCadena.h"


class producto{
    private:
        int idProducto;
        char nombreProducto[40];
        int categoria;
        float precioProducto;
        bool estado;
    public:
        bool mostrar();
        bool cargar(int contId);

        void setIdProducto(int id){idProducto=id;}
        void setNombreProducto(const char *nom){strcpy(nombreProducto,nom);}
        bool setCategoria(int _categoria){
            if(_categoria<1 && _categoria>2)
                return false;
            categoria=_categoria;
            return true;
        }
        bool setPrecioProducto(float pre){
            if(pre<=0){return false;}
            else {
                precioProducto=pre;
                return true;
            }
        }
        void setEstado(bool e){estado=e;}

        int getIdProducto(){return idProducto;}
        const char *getNombreProducto(){return nombreProducto;}
        int getCategoria(){return categoria;}
        float getPrecioProducto(){return precioProducto;}
        bool getEstado(){return estado;}

        bool leerDeDisco(int posLectura){
            FILE *p;
            p=fopen("productos.dat","rb");
            if(p==NULL) return false;
            fseek(p,posLectura*sizeof *this, 0);
            bool leyo=fread(this, sizeof *this, 1, p);
            fclose(p);
            return leyo;
        }
        bool grabarEnDisco(){
            FILE *p;
            p=fopen("productos.dat","ab");
            if(p==NULL) return false;
            bool escribio = fwrite(this, sizeof (producto), 1, p);
            fclose(p);
            return escribio;
        }
        bool modificarEnDisco(int pos){
            FILE *p;
            p=fopen("productos.dat","rb+");
            if(p==NULL) return false;
            fseek(p, pos * sizeof(producto), 0);
            bool escribio=fwrite(this, sizeof (producto), 1, p);
            fclose(p);
            return escribio;
        }
};

bool producto::cargar(int contId){
    cout<<"\t\t\t\t"<<"ID DEL PRODUCTO: "<<contId<<endl;
    setIdProducto(contId);
    cout<<"\t\t\t\t"<<"NOMBRE DEL PRODUCTO: ";
    cargarCadena(nombreProducto,39);
    cout<<"\t\t\t\t"<<"CATEGORIA DEL PRODUCTO (1.COMESTIBLE O 2.BEBIDA): ";
    cin>>categoria;
    if( !setCategoria(categoria) ){
        cout<<"\t\t\t\t"<<"CATEGORIA INVALIDA"<<endl;
        return false;
    }
    cout<<"\t\t\t\t"<<"PRECIO DEL PRODUCTO: ";
    cin>>precioProducto;
    if(setPrecioProducto(precioProducto)==false){
        cout<<"\t\t\t\t"<<"EL PRECIO INGRESADO ES INVALIDO"<<endl;
        return false;
    }
    estado=true;
    return true;
}

bool producto::mostrar(){
    if(getEstado()==true){
        cout<<"\t\t\t\t"<<" ID DEL PRODUCTO: "<<idProducto<<endl;
        cout<<"\t\t\t\t"<<" NOMBRE DEL PRODUCTO: "<<nombreProducto<<endl;
        cout<<"\t\t\t\t"<<" CATEGORIA DEL PRODUCTO: "<<categoria<<endl;
        cout<<"\t\t\t\t"<<" PRECIO : "<<precioProducto<<"$"<<endl;
        return true;
    }
    else{return false;}
}

#endif // CLASEPRODUCTOS_H_INCLUDED
