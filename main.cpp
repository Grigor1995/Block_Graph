#include "graph.hpp"

//Function for inputing size for thise graph
int Input_Size_Graph ()
{
    int size = 0;
    while (size <= 0)
    {
        system ("clear");
        std::cout<<"\t\tPleas enter Graph size"<<std::endl;
        std::cout<<"Graph size = ";
        std::cin>>size;
    }
    return size;
}


/******************************************/
/****Function Main For Call Graph Class****/
/******************************************/

int main ()
{
    int size = Input_Size_Graph();
    Graph gr(size);
}
