#ifndef CLASECOMPRAS_H_INCLUDED
#define CLASECOMPRAS_H_INCLUDED
/*
#include "clasePelicula.h"
#include "claseProductos.h"
#include "codigoPeliculas.h"
#include "codigoProductos.h"
#include "claseFecha.h"
#include "cargarCadena.h"
*/

class compra{
    private:
        int IdCompra;
        char nombreComprador[30];
        fecha FechaDeCompra;
        int idPeliComprada;
        int cantEntradas;
        float MontoFinal;
        bool estado;
    public:
        bool cargar(int contId);
        bool mostrar();

        void setIdCompra(int id){IdCompra=id;}
        void setNombreComprador(const char *nom){strcpy(nombreComprador,nom);}
        bool setFechaCompra(fecha f){
            int cont=0;
            fecha comp;
            comp=comp.hoy();
            if(f.getDia()>comp.getDia()){cont++;}
            if(f.getMes()>=comp.getMes()){cont++;}
            if(f.getAnio()>=comp.getAnio()){cont++;}
            if((f.getMes()==2)&&(f.getDia()>28)){return false;}
            if((f.getDia()>31)||(f.getDia()<1)){return false;}
            if((f.getMes()>12)||(f.getMes()<1)){return false;}
            if((f.getAnio()>2022)||(f.getAnio()<1)){return false;}
            if(cont==3){return false;}
            else{
                FechaDeCompra=f;;
                return true;
            }
        }
        bool setIdPeliComprada(int idP){
            pelicula reg;
            FILE *p;
            int cont=0;
            p=fopen("peliculas.dat","rb");
            while(fread(&reg,sizeof reg, 1, p)==1){
                if(reg.getIdPeli()==idP){
                    cont=1;
                }
            }
            if(cont==0){return false;}
            else{
                idPeliComprada=idP;
                fclose(p);
               return true;
            }
        }
        bool setCantEntradas(int ent){
            if(ent<=0){return false;}
            else {
                cantEntradas=ent;
                return true;
            }
        }
        void setMontoFinal(float mf){MontoFinal=mf;}
        void setEstado(bool est){estado=est;}

        int getIdCompra(){return IdCompra;}
        const char *getNombreComprador(){return nombreComprador;}
        fecha getFechaDeCompra(){return FechaDeCompra;}
        int getIdPeliComprada(){return idPeliComprada;}
        int getCantEntradas(){return cantEntradas;}
        float getMontoFinal(){return MontoFinal;}
        bool getEstado(){return estado;}

        bool leerDeDisco(int posLectura){
            FILE *p;
            p=fopen("compraCabecera.dat","rb");
            if(p==NULL) return false;
            fseek(p,posLectura*sizeof *this, 0);
            bool leyo=fread(this, sizeof *this, 1, p);
            fclose(p);
            return leyo;
        }
        bool grabarEnDisco(){
            FILE *p;
            p=fopen("compraCabecera.dat","ab");
            if(p==NULL) return false;
            bool escribio = fwrite(this, sizeof (compra), 1, p);
            fclose(p);
            return escribio;
        }
        bool modificarEnDisco(int pos){
            FILE *p;
            p=fopen("compraCabecera.dat","rb+");
            if(p==NULL) return false;
            fseek(p, pos * sizeof(compra), 0);
            bool escribio=fwrite(this, sizeof (compra), 1, p);
            fclose(p);
            return escribio;
        }

};

bool compra::cargar(int contId){
    char nom[30];
    int idpeli,posPeli,ent,monto=0;
    pelicula reg;
    fecha f;
    cout<<"\t\t\t\t"<<"ID DE LA COMPRA: "<<contId<<endl;
    setIdCompra(contId);
    cout<<"\t\t\t\t"<<"NOMBRE DEL COMPRADOR: ";
    cargarCadena(nom,29);
    setNombreComprador(nom);
    cout<<"\t\t\t\t"<<"FECHA DE HOY: ";
    f.Cargar();
    if(setFechaCompra(f)==false){
        cout<<"\t\t\t\t"<<"FECHA INVALIDA"<<endl;
        return false;
    }
    cout<<"\t\t\t\t"<<"ID DE LA PELICULA QUE DESEA VER: ";
    cin>>idpeli;
    if(setIdPeliComprada(idpeli)==false){
        cout<<"\t\t\t\t"<<"LA ID INGRESADA NO EXISTE"<<endl;
        return false;
    }
    posPeli=buscarIdPelicula(idpeli);
    reg=leerRegistroPelicula(posPeli);
    cout<<"\t\t\t\t"<<"NOMBRE DE LA PELICULA QUE ELIGIO: "<<reg.getNombrePeli()<<endl;
    cout<<"\t\t\t\t"<<"CUANTAS ENTRADAS DESEA COMPRAR: ";
    cin>>ent;
    if(setCantEntradas(ent)==false){
        cout<<"\t\t\t\t"<<"LA CANTIDAD DE ENTRADAS ES INVALIDA"<<endl;
        return false;
    }
    monto=ent*reg.getPrecioEntrada();
    setMontoFinal(monto);
    setEstado(true);
    return true;
}

bool compra::mostrar(){
    if(getEstado()==true){
        cout<<"\t\t\t\t"<<"ID DE LA COMPRA: "<<IdCompra<<endl;
        cout<<"\t\t\t\t"<<"NOMBRE DEL COMPRADOR: "<<nombreComprador<<endl;
        cout<<"\t\t\t\t"<<"FECHA DE COMPRA: ";
        FechaDeCompra.Mostrar();
        cout<<"\t\t\t\t"<<"ID DE LA PELICULA: "<<idPeliComprada<<endl;
        int posPeli=buscarIdPelicula(idPeliComprada);
        pelicula reg=leerRegistroPelicula(posPeli);
        cout<<"\t\t\t\t"<<"NOMBRE DE LA PELICULA: "<<reg.getNombrePeli()<<endl;
        cout<<"\t\t\t\t"<<"ENTRADAS COMPRADAS: "<<cantEntradas<<endl;
        return true;
    }
    return false;
}

#endif // CLASECOMPRAS_H_INCLUDED
