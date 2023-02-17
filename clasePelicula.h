#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED
/*
#include "claseFecha.h"
#include "cargarCadena.h"
*/
class pelicula{
    private:
        int idPeli;
        char nombrePeli [40];
        char genero[30];
        fecha fechaDeEstreno;
        int duracion;
        float precioEntrada;
        bool estado;
    public:
        bool mostrar();
        bool cargar(int contId);

        void setIdPeli(int id){idPeli=id;}
        void setNombrePeli(const char *n){strcpy(nombrePeli,n);}
        void setGenero(const char *g){strcpy(genero,g);}
        bool setFechaEstreno(fecha f){
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
                fechaDeEstreno=f;;
                return true;
            }
        }
        bool setDuracion(int d){
            if(d<=0){return false;}
            else{
                duracion=d;
                return true;
            }
        }
        bool setPrecioEntrada(float c){
            if(c<0){return false;}
            else{
                precioEntrada=c;
                return true;
            }
        }
        void setEstado(bool e){estado=e;}

        int getIdPeli(){return idPeli;}
        const char *getNombrePeli(){return nombrePeli;}
        const char *getGenero(){return genero;}
        fecha getFechaEstreno(){return fechaDeEstreno;}
        int getDuracion(){return duracion;}
        float getPrecioEntrada(){return precioEntrada;}
        bool getEstado(){return estado;}

        bool leerDeDisco(int pos){
            FILE *p;
            p=fopen("peliculas.dat","rb");
            if(p==NULL) return false;
            fseek(p,pos*sizeof *this, 0);
            bool leyo=fread(this, sizeof *this, 1, p);
            fclose(p);
            return leyo;
        }
         bool grabarEnDisco(){
            FILE *p;
            p=fopen("peliculas.dat","ab");
            if(p==NULL) return false;
            bool escribio = fwrite(this, sizeof (pelicula), 1, p);
            fclose(p);
            return escribio;
        }
        bool modificarEnDisco(int pos){
            FILE *p;
            p=fopen("peliculas.dat","rb+");
            if(p==NULL) return false;
            fseek(p, pos * sizeof(pelicula), 0);
            bool escribio=fwrite(this, sizeof (pelicula), 1, p);
            fclose(p);
            return escribio;
        }
};

bool pelicula::cargar(int contId){
    char nom[40],genero[30];
    float precio;
    int dur;
    fecha f;
    cout<<"\t\t\t\t"<<"ID DE PELICULA: "<<contId<<endl;
    setIdPeli(contId);
    cout<<"\t\t\t\t"<<"NOMBRE DE LA PELICULA: ";
    cargarCadena(nom,39);
    setNombrePeli(nom);
    cout<<"\t\t\t\t"<<"GENERO: ";
    cargarCadena(genero,39);
    setGenero(genero);
    cout<<"\t\t\t\t"<<"FECHA DE ESTRENO: ";
    f.Cargar();
    if(setFechaEstreno(f)==false){
        cout<<"\t\t\t\t"<<"FECHA INVALIDA"<<endl;
        return false;
    }
    cout<<"\t\t\t\t"<<"DURACION DE LA PELICULA: ";
    cin>>dur;
    if(setDuracion(dur)==false){
        cout<<"\t\t\t\t"<<"LA DURACION INGRESADA ES INVALIDA"<<endl;
        return false;
    }
    cout<<"\t\t\t\t"<<"PRECIO DE ENTRADA: ";
    cin>>precio;
    if(setPrecioEntrada(precio)==false){
        cout<<"\t\t\t\t"<<"EL PRECIO DE ENTRADA INGRESADO ES INVALIDO"<<endl;
        return false;
    }
    setEstado(true);
    return true;
}

bool pelicula::mostrar(){
    if(getEstado()==true){
        int horas,minutos;
        horas=duracion/60;
        minutos=duracion%60;
        cout<<"\t\t\t\t"<<" ID: "<<idPeli<<endl;
        cout<<"\t\t\t\t"<<" NOMBRE: "<<nombrePeli<<endl;
        cout<<"\t\t\t\t"<<" GENERO: "<<genero<<endl;
        cout<<"\t\t\t\t"<<" FECHA DE ESTRENO: ";
        fechaDeEstreno.Mostrar();
        cout<<"\t\t\t\t"<<" DURACION: "<<horas<<"h "<<minutos<<"m"<<endl;
        cout<<"\t\t\t\t"<<" PRECIO DE ENTRADA: "<<precioEntrada<<"$"<<endl;
        return true;
    }
    else{return false;}
}

#endif // CLASES_H_INCLUDED
