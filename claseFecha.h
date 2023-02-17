#ifndef CLASEFECHA_H_INCLUDED
#define CLASEFECHA_H_INCLUDED

class fecha{
    private:
        int dia, mes, anio;
    public:
    //SETS
        void setDia(int d){dia=d;}
        void setMes(int d){mes=d;}
        void setAnio(int d){anio=d;}
        //GETS
        int getDia(){return dia;}
        int getMes(){return mes;}
        int getAnio(){return anio;}

        void Cargar(){
            cout<<endl;
            cout<<"\t\t\t\t"<<"DIA: ";
            cin>>dia;
            cout<<"\t\t\t\t"<<"MES: ";
            cin>>mes;
            cout<<"\t\t\t\t"<<"AÑO: ";
            cin>>anio;
        }
        void Mostrar(){
            cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
        }

        fecha hoy(){
            time_t t;
            t=time(NULL);
            struct tm *FechaActual;
            FechaActual=localtime(&t);
            fecha aux;
            aux.anio=FechaActual->tm_year+1900;
            aux.mes=FechaActual->tm_mon+1;
            aux.dia=FechaActual->tm_mday;
            return aux;
        };
};

#endif // CLASEFECHA_H_INCLUDED
