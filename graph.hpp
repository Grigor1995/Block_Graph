#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream> //for input and output streams
#include <stdlib.h> //for system("clear")
#include <vector>   //for std::vector conteyner
#include <set>      //for std::set conteyner

class Graph;        //Base class
class Veretx;       //Class for Vertex in Graph
class Edge;         //Class for Blocks in Graph

/******************************/
/********CLASS BLOCKS********/
/*****************************/

class Blocks
{
public:

    //Constructor
    Blocks (int a = 0,int b = 0,int c = 0):m_block1(a),m_block2(b),m_p_of_i(c) {}
    Blocks(const Blocks & ob):m_block1(ob.m_block1),m_block2(ob.m_block2),m_p_of_i(ob.m_p_of_i) {}

    //members
    int m_block1;
    int m_block2;
    int m_p_of_i;
};

/******************************/
/*********CLASS EDGE*********/
/*****************************/

class Edge
{
public:

    //constructor
    Edge (int a = 0,int b = 0):m_u(a),m_v(b) {}

    //members
    int m_u;
    int m_v;
};
/***************************/
/*****CLASS VERTEX********/
/**************************/

class Vertex
{
public:
  //typedef for vertex type
  typedef std::set<int> conteyner_type;

  //Constructor
  Vertex (const conteyner_type & obj = conteyner_type());

  //memeber-functions
  unsigned  get_node_size     () const;

  void      add_node       (const int);

  void      add_node_conect(const int);

  void      print_node_list         ();

  //conteyner for class vertex
  conteyner_type vertex;
};

/*****************************/
/*******CLASS GRAPH*********/
/*****************************/

class Graph
{
public:

    //Typedef for Grapg type
	typedef std::vector<Vertex> conteyner_type;
	typedef std::vector<Blocks> biconect_type;
    typedef std::vector<Edge>   bcc_type;
    typedef std::vector<bool>   conect_type;
    typedef std::vector<int>    arr_type;

    //Constructor
    Graph(int = 0);

private:

//member-functions
    //Input and Print functions
    void input              ();
    void print_graph        ();
    void print_conecting    ();
    void print_conect_graph ();
    void print_graph_block  ();
    void print_information  ();
    void print_param        ();
    void print_line         ();

    //conecting functions
    void dfs    (int);
    bool conecting ();

    //Bcc functions
    void BCCUtil(int, arr_type &, arr_type &, bcc_type *,arr_type &);
    void BCC                                                      ();

    //block graph functions
    void graph_block();

    //return min value from inputs
    int min (int,int);

    //D-functions
    unsigned d_max ();
    unsigned d_min ();

//Members
    //member-values
    unsigned m_my_size;
    unsigned m_edge_size;
    unsigned m_count;
    unsigned m_block_size;

    //conteyners type
    conteyner_type  graph;
    conteyner_type  conect_graph;
    conect_type     conect;
    biconect_type   block_graph;
};


#endif // GRAPH_HPP
