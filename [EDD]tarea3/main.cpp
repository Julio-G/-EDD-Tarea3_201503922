#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;
string contenido="digraph G {  node [shape=record, color=blue]";
string contenido2="imagen.dot";
int cont2=0;
int cont3=0;
struct Nodo{
string dato;
Nodo *der;
Nodo *izq;
Nodo *padre;
};

void eliminar(Nodo*,string);
void eliminarN(Nodo*);
Nodo* minimo(Nodo*);
void reemplazar(Nodo*,Nodo*);
void destruir(Nodo*);

void insertar(Nodo *&arbol, string n,Nodo *padre){
    if(arbol==NULL){
        Nodo *nuevo_nodo=new Nodo();
        nuevo_nodo->dato=n;
        nuevo_nodo->der =NULL;
        nuevo_nodo->izq=NULL;
        nuevo_nodo->padre=padre;
        arbol = nuevo_nodo;
    }else{
        string valorRaiz = arbol->dato;
        if(n<valorRaiz){
            insertar(arbol->izq,n,arbol);
        }else{
            insertar(arbol->der,n,arbol);
        }
    }
}
void eliminar(Nodo* arbol,string n){
if(arbol==NULL){
    return;
}else if(n<arbol->dato){
    eliminar(arbol->izq,n);
}else if(n>arbol->dato){
    eliminar(arbol->der,n);
}else{
    eliminarN(arbol);
}
}
void eliminarN(Nodo* neliminar){
    if(neliminar->izq!=NULL && neliminar->der!=NULL){
        Nodo *menor=minimo(neliminar->der);
        neliminar->dato=menor->dato;
        eliminarN(menor);
    }else if(neliminar->izq!=NULL){
        reemplazar(neliminar,neliminar->izq);
        destruir(neliminar);
    }else if(neliminar->der!=NULL){

        reemplazar(neliminar,neliminar->der);

        destruir(neliminar);
    }else{

        reemplazar(neliminar,NULL);
        destruir(neliminar);
    }
}

Nodo *minimo(Nodo *arbol){
    if(arbol==NULL){
        return NULL;
    }
    if(arbol->izq!=NULL){
        return minimo(arbol->izq);
    }
    else{
        return arbol;
    }
}

void reemplazar(Nodo* arbol, Nodo* nuevo){
    if(arbol->padre!=NULL){
        cout<<"encontro"<<endl;
        if(arbol->padre->izq!=NULL){

            if(arbol->dato== arbol->padre->izq->dato&&(arbol->padre->izq!=NULL)){
                arbol->padre->izq=nuevo;
            }else if(arbol->dato==arbol->padre->der->dato){

            arbol->padre->der=nuevo;
            }
        }else if(arbol->padre->der!=NULL){

            if(arbol->dato==arbol->padre->der->dato){

                arbol->padre->der=nuevo;
            }
        }

    }
    if(nuevo!=NULL){
        nuevo->padre=arbol->padre;
    }
}

void destruir(Nodo* nodo){
    nodo->izq=NULL;
    nodo->der=NULL;
    delete nodo;
}
void mostrarArbol(Nodo *arbol){
    cout<<arbol->dato<<endl;
if(arbol->der==NULL && arbol->izq==NULL){

        contenido+=" node"+arbol->dato+" [style=filled fillcolor=blue  label=\""+arbol->dato+"\"] ";
    }
    else{
        if(arbol->izq!=NULL){

            contenido+=" node"+arbol->dato+" [style=filled fillcolor=blue label=\"<C0>|"+arbol->dato+"|<C1>\"] node"+arbol->dato+":C0->node"+arbol->izq->dato+":C1";
            mostrarArbol(arbol->izq);
          }

        if(arbol->der!=NULL){
            contenido+=" node"+arbol->dato+" [style=filled fillcolor=blue label=\"<C0>|"+arbol->dato+"|<C1>\"] node"+arbol->dato+":C1->node"+arbol->der->dato+":C0";
            mostrarArbol(arbol->der);
          }
    }

}

int main()
{
   Nodo *arbol=NULL;
   int opcion,contador=0;
   string dato="";
    do{
        cout<<"\t.:MENU"<<endl;
        cout<<"1. Insertar un nuevo nodo"<<endl;
        cout<<"2. Eliminar nodo"<<endl;
        cout<<"3. Mostrar arbol"<<endl;
        cout<<"4. Salir"<<endl;
        cin>>opcion;

        switch(opcion){
            case 1: cout<<"Escriba el nombre del nodo "<<endl;
                    cin>>dato;
                    insertar(arbol,dato,NULL);
                    cout<<"\n";
                break;
            case 2:
                    cout<<"Escriba el nombre del nodo a eliminar: "<<endl;
                    cin>>dato;
                    eliminar(arbol,dato);
                    cout<<"\n";
                break;
            case 3:
                cout<<"\nMostrando:\n\n";
                if(arbol!=NULL){
                mostrarArbol(arbol);
                contador=0;
                contenido+="}";
                ofstream fs(contenido2.c_str());
                fs << contenido << endl;
                fs.close();
                system("dot -Tpng imagen.dot -o imagen.png");
                system("imagen.png");
                contenido="digraph G {  node [shape=record, color=blue]";
                }else{
                    cout<<"sfsadfsadf: ";
                }
                break;
        }

    }while(opcion!=4);

    return 0;
}

