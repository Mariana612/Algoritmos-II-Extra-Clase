#include <bits/stdc++.h>
using namespace std;

class Collector  // Clase Collector
{
    private:
    void *espacio;
    Collector *after;

    public:

    // GETTERS & SETTERS 

    void set_espacio(void *space){ this->espacio= space;}
    void set_after(Collector *next){ this->after= next;}

    void *get_espacio(){return espacio;}
    Collector *get_after(){return after;}
    
    
};

Collector *collect;  // Variable Global del Collector

class Node{  // Clase Node
    private:
    int num;
    Node *next;

    public:
    void *operator new(size_t size)  // Overload del metodo New
    {
        if(collect==NULL) //Verifica que no haya ningun elemento en el Collector
        {           
            void *memory_space = malloc(size);
            cout<<memory_space;
            return memory_space;
        }
        else  // Reutiliza el espacio de memoria almacenado en el Collector
        {
            void *temp = collect->get_espacio();
            collect = collect->get_after();
            cout<<temp;
            return temp;
        }
     }

    // GETTERS & SETTERS 
    
    void set_num(int num){ this->num = num;}
    void set_next(Node *node){ this->next= node;}

    int get_num(){return num;}
    Node *get_next(){return next;}
};

class Lista{  //Clase Lista
    private:
    Node *first;

    public:
    Lista() // Constructor
    { 
        first = NULL;
        collect = NULL;
    }

    void insert_start(int new_num) // Permite agregar Nodos al Inicio
    {
        Node *new_node = new Node();

        new_node->set_num(new_num);
        new_node->set_next(first);
        first = new_node;

        cout<<"   int: "<<new_num<<endl;
    }

    void delete_end()  // Permite eliminar Nodos al final
    { 
        Node *temp= first;

        while(temp->get_next()->get_next()!=NULL) // Verifica que no este en el penultimo Nodo
            temp = temp->get_next();

        Node *end_node = temp->get_next();
        temp->set_next(NULL);

        delete(end_node);
        
    }

    void print_list(Node *node) // imprime el numero que se inserto en la lista
    {
        cout<<"LISTA:"<<endl;

        while(node != NULL)
        {
            cout<<node<<"   int:"<<node->get_num()<<endl;
            node = node->get_next();
        }
    }

    // GETTER & SETTER

    void set_first(Node *first){ this->first = first;}
    Node *get_first(){return first;}
};

void operator delete(void*p) // Overload del metodo Delete
{   
    Collector *new_collect= new Collector();

    new_collect->set_espacio(p); //Ingresa el espacio de memoria al colletor para ser reutilizado
    new_collect->set_after(collect);

    collect = new_collect; 
}

void print_collector() // Imprime los espacios de memoria dentro del collector
{
    cout<<"Espacios de memoria dentro de collector:"<<endl;

    Collector *temp = new Collector();
    temp = collect;

    while(temp!= NULL)
        {
            cout<<temp->get_espacio()<<endl;
            temp = temp->get_after();
        }
    if(collect == NULL)
        cout<<"no hay elementos dentro del collector"<<endl;
}


int main()
{
    Lista *lista = new Lista();
    cout<<"MEMORIA QUE SE UTILIZA PARA CADA VARIABLE"<<endl;
    lista->insert_start(1);
    lista->insert_start(2);
    lista->insert_start(3);
    cout<<"\n"<<"SE ELIMINAN ELEMENTOS Y SE INCERTAN EN COLLECTOR"<<endl;
    lista->delete_end();
    lista->delete_end();
    print_collector();
    cout<<"\n"<<"CANTIDAD DE ELEMENTOS DENTRO DE LA LISTA"<<endl;
    lista->print_list(lista->get_first());
    cout<<"\n"<<"SE AGREGAN NUEVOS ELEMENTOS Y SE REUTILIZA MEMORIA ANTIGUA"<<endl;
    lista->insert_start(4);
    lista->insert_start(5);
    cout<<"\n"<<"AL REUTILIAR LA MEMORIA DEL COLLECTOR YA NO HAY EPSACIOS DE MEMORIA DENTRO"<<endl;
    print_collector();
    cout<<"\n"<<"LISTA FINAL"<<endl;
    lista->print_list(lista->get_first());
    return 0; 
} 

