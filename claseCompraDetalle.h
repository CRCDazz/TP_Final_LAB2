#ifndef CLASECOMPRADETALLE_H_INCLUDED
#define CLASECOMPRADETALLE_H_INCLUDED
/*
#include "claseProductos.h"
#include "codigoProductos.h"
#include "claseFecha.h"
#include "cargarCadena.h"
#include "claseCompras.h"
*/
class compraDetalle{
    private:
        int idDetalle;
        int IdCompra;
        int idProduComprados;
        int cantProducto;
        bool estado;
    public:
        bool cargar(int contId);
        bool mostrar();

        void setIdDetalle(int id){idDetalle=id;}
        bool setIdCompra(int id){
            compra regCompra;
            int pos=0;
            while(regCompra.leerDeDisco(pos)){
                if(regCompra.getIdCompra()==id){
                    IdCompra=id;
                    return true;
                }
                pos++;
            }
            return false;
        }

        bool setIdProduComprados(int idPr){
            producto reg;
            FILE *p;
            int cont=0;
            p=fopen("productos.dat","rb");
            while(fread(&reg,sizeof reg, 1, p)==1){
                if(reg.getIdProducto()==idPr){
                    if(reg.getEstado()==true){
                        cont=1;
                    }
                }
            }
            if(cont==0){return false;}
            else{
                idProduComprados=idPr;
                fclose(p);
                return true;
            }

        }
        bool setCantProductos(int pro){
            if(pro<0){return false;}
            else{
                cantProducto=pro;
                return true;
            }
        }
        void setEstado(bool est){estado=est;}

        int getIdDetalle(){return idDetalle;}
        int getIdCompra(){return IdCompra;}
        int getIdProduComprados(){return idProduComprados;}
        int getCantProductos(){return cantProducto;}
        bool getEstado(){return estado;}

        bool leerDeDisco(int pos){
            FILE *p;
            p=fopen("compraDetalle.dat","rb");
            if(p==NULL) return false;
            fseek(p,pos*sizeof *this, 0);
            bool leyo=fread(this, sizeof *this, 1, p);
            fclose(p);
            return leyo;
        }
        bool grabarEnDisco(){
            FILE *p;
            p=fopen("compraDetalle.dat","ab");
            if(p==NULL) return false;
            bool escribio = fwrite(this, sizeof (compraDetalle), 1, p);
            fclose(p);
            return escribio;
        }
        bool modificarEnDisco(int pos){
            FILE *p;
            p=fopen("compraDetalle.dat","rb+");
            if(p==NULL) return false;
            fseek(p, pos * sizeof(compraDetalle), 0);
            bool escribio=fwrite(this, sizeof (compraDetalle), 1, p);
            fclose(p);
            return escribio;
        }
};

bool compraDetalle::cargar(int contId){
    int id,idprod,posProd,prod;
    producto datos;
    cout<<"\t\t\t\t"<<"ID DETALLE: "<<contId<<endl;
    setIdCompra(contId);
    cout<<"\t\t\t\t"<<"ID DE COMPRA: ";
    cin>>id;
    if(setIdCompra(id)==false){
        cout<<"\t\t\t\t"<<"LA ID INGRESADA NO EXISTE"<<endl;
        return false;
    }
    cout<<"\t\t\t\t"<<"ID DEL PRODUCTO QUE DESEA COMPRAR: ";
    cin>>idprod;
    if(setIdProduComprados(idprod)==false){
        cout<<"\t\t\t\t"<<"LA ID INGRESADA NO EXISTE"<<endl;
        return false;
    }
    posProd=buscarIdProducto(idprod);
    datos=leerRegistroProducto(posProd);
    cout<<"\t\t\t\t"<<"NOMBRE DEL PRODUCTO QUE ELEGIO: "<<datos.getNombreProducto()<<endl;
    cout<<"\t\t\t\t"<<"CUANTAS UNIDADES DESEA COMPRAR: ";
    cin>>prod;
    if(setCantProductos(prod)==false){
        cout<<"\t\t\t\t"<<"LA CANTIDAD DE PRODUCTOS ES INVALIDA"<<endl;
        return false;
    }
    setEstado(true);
    return true;
}

bool compraDetalle::mostrar(){
    if(getEstado()==true){
        producto datos;
        int posProd;
        cout<<"\t\t\t\t"<<"ID DETALLE: "<<getIdDetalle()<<endl;
        cout<<"\t\t\t\t"<<"ID COMPRA: "<<getIdCompra()<<endl;
        cout<<"\t\t\t\t"<<"ID PRODUCTO COMPRADO: "<<idProduComprados<<endl;
        posProd=buscarIdProducto(idProduComprados);
        datos=leerRegistroProducto(posProd);
        cout<<"\t\t\t\t"<<"NOMBRE DEL PRODUCTO: "<<datos.getNombreProducto()<<endl;
        cout<<"\t\t\t\t"<<"CUANTAS UNIDADES COMPRO: "<<cantProducto<<endl;
        return true;
    }
    return false;
}



#endif // CLASECOMPRADETALLE_H_INCLUDED
