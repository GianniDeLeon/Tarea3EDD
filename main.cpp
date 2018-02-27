#include <QCoreApplication>
#include <iostream>
//biblioteca para escritura de archivo
#include <fstream>
using namespace std;
//Estructura de arbol
typedef struct Nodo
{
    int id;
    char car;
    Nodo *izq = NULL;
    Nodo *der = NULL;
}Nodo;

//Estructura de cola
typedef struct Cola
{
    Nodo *nodo;
    Cola *siguiente;
}Cola;

//Metodos
void menu();
Nodo *crearNodo(int id, char car);
void incertarNodo(char car, int id, Nodo *&root);
void agregarACola(Cola *&inicio,Cola *&fin, Nodo *nodo);
void recorridoAnchura();
Cola *sacarCola(Cola *&inicio);
void recorrerCola(Cola *inicio);
void graficaArbol();

//Varibles globales
Nodo *raiz=NULL;
Cola *inicio1=NULL,*fin1=NULL,*inicio2=NULL,*fin2=NULL;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    menu();
    return 0;
}

void menu()
{
    bool opt = true;
    int op = 0;
    while(opt)
    {
        system("clear");
        cout << "1) Incertar nodo" << endl;
        cout << "2) Recorrido por Anchura" << endl;
        cout << "3) Salir" <<endl;
        cin >> op;
        system("clear");
        switch (op) {
        case 1:
            int id;
            char car;
            cout << "Ingrese ID del nodo" << endl;
            cin >> id;
            cout << "Ingrese el Char representativo" << endl;
            cin >> car;
            //string car2(1, car);
            incertarNodo(car, id, raiz);
            system("read -rs");
            break;
        case 2:
            recorridoAnchura();
            break;
        case 3:
            opt = false;
            break;
        default:
            break;
        }
    }
}

void recorridoAnchura()
{
    if(raiz != NULL)
    {
        agregarACola(inicio1,fin1,raiz);
        while(inicio1 != NULL)
        {
            Cola *cola;
            cola = sacarCola(inicio1);
            Nodo *aux;
            aux = cola->nodo;
            agregarACola(inicio2,fin2,cola->nodo);
            if(aux->izq != NULL)
            {
                agregarACola(inicio1,fin1,aux->izq);
            }
            if(aux->der != NULL)
            {
                agregarACola(inicio1,fin1,aux->der);
            }
        }
        graficaArbol();
        recorrerCola(inicio2);
    }
}

void graficaArbol()
{
    ofstream ficheroSalida;
    ficheroSalida.open ("arbol.dot");
    ficheroSalida << "digraph Arbol{";
    Cola *inicio = inicio2;
    //char car;
    while(inicio != NULL)
    {
        Nodo *aux;
        aux = inicio->nodo;
        if(aux->der != NULL)
        {
            ficheroSalida << aux->car << " -> " << aux->der->car << ";\n";
        }
        if(aux->izq != NULL)
        {
            ficheroSalida << aux->car << " -> " << aux->izq->car << ";\n";
        }
        inicio = inicio->siguiente;
    }
    ficheroSalida << "}";
    ficheroSalida.close();
    system("dot -Tpng arbol.dot -o arbol.png");
    system("nomacs arbol.png");
}

Nodo *crearNodo(int id, char car)
{
    Nodo *nuevo = new Nodo;
    nuevo->id = id;
    nuevo->car = car;
    nuevo->der = NULL;
    nuevo->izq = NULL;
}

void incertarNodo(char car, int id, Nodo *&root)
{
    if(root == NULL)
    {
        root = crearNodo(id,car);
    }
    else
    {
        if(id < root->id)
        {
            cout << "Incertando A la Izquierda " << id << endl;
            incertarNodo(car,id,root->izq);

        }
        else
        {
            cout << "Incertando A la Derecha " << id << endl;
            incertarNodo(car,id,root->der);

        }
    }
}

void agregarACola(Cola *&inicio,Cola *&fin, Nodo *nodo)
{
    Cola *nuevo = new Cola;
    nuevo->nodo = nodo;
    nuevo->siguiente = NULL;
    if(inicio != NULL)
    {
        fin->siguiente = nuevo;
        fin = nuevo;
    }
    else
    {
        inicio = nuevo;
        fin = nuevo;
    }
}

Cola *sacarCola(Cola *&inicio)
{
    Cola *nodo;
    nodo = inicio;
    inicio = inicio->siguiente;
    return nodo;
}

void recorrerCola(Cola *inicio)
{
    ofstream ficheroSalida;
    ficheroSalida.open ("anchura.dot");
    ficheroSalida << "digraph anchura{\n";
    while(inicio != NULL)
    {
        Nodo *aux;
        aux = inicio->nodo;
        ficheroSalida << aux->car;
        inicio = inicio->siguiente;
        if(inicio != NULL)
        {
            ficheroSalida << " -> ";
        }
    }
    ficheroSalida << ";\n}";
    ficheroSalida.close();
    system("dot -Tpng anchura.dot -o anchura.png");
    system("nomacs anchura.png");
}
