#include "graph.hpp"

/****************************************/
/******CLASS VERTEX IMPLEMENTATION*******/
/****************************************/



//constructor
Vertex::Vertex(const conteyner_type &obj)
{
    std::set<int>::iterator i;
    for (i = obj.begin();i != obj.end();++i)
        vertex.insert(*i);
}

unsigned  Vertex::get_node_size() const
{
  return vertex.size();
}

void  Vertex::add_node(const int value)
{
  vertex.insert (value - 1);
}

void Vertex::add_node_conect (const int value)
{
        add_node (value);
}

void Vertex::print_node_list()
{
    std::set<int>::iterator i;
    const unsigned size = get_node_size();
    if (size != 0)
    {
    for (i = vertex.begin();i != vertex.end();++i)
        std::cout<<*i + 1<<"  ";
    std::cout<<std::endl;
    }
    else
        std::cout<<std::endl;
}



/****************************************/
/******CLASS GRAPH IMPLEMENTATION********/
/****************************************/



//constructor
Graph::Graph(int number):m_my_size(number),graph(number),conect_graph(number),block_graph(0),conect(m_my_size),m_edge_size(0),m_count(0),m_block_size(0)
{
  system ("clear");
  input ();
  system ("clear");



  BCC();



  graph_block ();

  print_information();
}

//input graph vertex
void Graph::input ()
{
  unsigned value = 0;
  unsigned j = 0;

  for (int i = 0;i < m_my_size;++i)
    {
      std::cout<<"\t\tVertex["<<i + 1<<"] conect to vertex "<<std::endl;
      std::cout<<"\t\t   Enter '0' for EXIT"<<std::endl;
      value = 0;

      std::cin>>value;
      while (value != 0 && value <= m_my_size)
		{
		  if(value == i + 1)
		  {
			  std::cin>>value;
			  continue;
          }
          graph[i].add_node (value);
          graph[value - 1].add_node(i + 1);
          ++m_edge_size;
		  std::cin>>value;
		}
      std::cout<<std::endl;
	}
}

//print functions
void Graph::print_conecting()
{
    std::cout<<"\t\t\tThe Graph is"<<std::endl;
    if (conecting())
      {
          std::cout<<"Conected"<<std::endl;
      }
    else
      {
        std::cout<<"Not connected"<<std::endl;
      }
    std::cout<<std::endl;
}

void Graph::print_param ()
{
    std::cout<<"\t\t\tThe parametrs for Graph"<<std::endl;
    std::cout<<"VERTEX NUMBER = "<<m_my_size<<std::endl;
    std::cout<<"D_MAX = "<<d_max()<<std::endl;
    std::cout<<"D_MIN = "<<d_min()<<std::endl;
}

void Graph::print_line()
{
    for (int i = 0;i < 63;++i)
    {
        std::cout<<"--";
    }
    std::cout<<std::endl;
}

void Graph::print_information()
{
    print_line();

    print_graph();

    print_line();

    print_param();

    print_line();

    print_conecting();

    print_line();


    print_conect_graph ();

    print_line();

    print_graph_block ();


    print_line();
    std::cout<<"\t\t\t\t\t END"<<std::endl;

}

void Graph::print_graph()
{
    std::cout<<"\t\t\tVertex from this Graph is conected in\n"<<std::endl;
    for (int i = 0;i < m_my_size;++i)
    {
      std::cout<<"Vertex["<<i + 1<<"] = ";
      graph[i].print_node_list();
	}
    std::cout<<std::endl;
}

void Graph::print_conect_graph ()
{
    std::cout<<"\t\t\tThe Block`s from Graph\n"<<std::endl;
    std::set<int>::iterator j;
    int v_size = 0;
    for (int i = 0;i < m_count;++i)
    {
        std::cout<<"Block["<<i + 1<<"] = " ;
        v_size = conect_graph[i].get_node_size();
        if (v_size != 0)
        {
            for (j = conect_graph[i].vertex.begin();j != conect_graph[i].vertex.end();++j)
            {
                std::cout<<*j + 1<<"  ";
            }
        }
        else
            std::cout<<std::endl;
        std::cout<<std::endl;
    }
}

//conect function in dfs algorithm
bool Graph::conecting()
{
    if (d_max() == m_my_size - 1)
		return true;
	if (d_min() == 0)
		return false;

    for (int i = 1;i < m_my_size;++i)
		conect[i] = 0;

	dfs (0);

    for (int i = 0;i < m_my_size;++i)
		if (!conect[i])
			return false;
	return true;
}

void Graph::dfs (int u)
{
    std::set<int>::iterator i;
	conect[ u ] = true;
    for ( i = graph[u].vertex.begin() ; i != graph[u].vertex.end(); ++i )
	{
        if( !conect[ *i ] )
		{
            dfs(*i);
		}
	}
}

//min and max edge size in graph
unsigned Graph::d_max ()
{
	unsigned val = graph[0].get_node_size();
    for (int i = 1;i < m_my_size;++i)
		if (val < graph[i].get_node_size())
			val = graph[i].get_node_size();
	return val;
}

unsigned Graph::d_min ()
{
	unsigned val = graph[0].get_node_size();
    for (int i = 1;i < m_my_size;++i)
		if (val > graph[i].get_node_size())
			val = graph[i].get_node_size();
	return val;
}

//search blocks in graph on BCC algorithm
void Graph::BCCUtil(int u, arr_type & disc, arr_type & low, bcc_type * obj,arr_type & parent)
{
	static int time = 0;
    std::set<int>::iterator i;
	disc[u] = low[u] = ++time;
	int children = 0;
	int op1 = 0;
	int op2 = 0;

    for (i = graph[u].vertex.begin(); i != graph[u].vertex.end(); ++i)
	{
        int v = *i;

		if (disc[v] == -1)
		{
			children++;
			parent[v] = u;
            obj->push_back(Edge(u,v));
            BCCUtil(v, disc, low, obj, parent);

			low[u]  = min(low[u], low[v]);

			if( (disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]) )
			{
                while(obj->back().m_u != u || obj->back().m_v != v)
				{
                    op1 = obj->back().m_u ;
                    op2 = obj->back().m_v;
                    conect_graph[m_count].add_node_conect(op1 + 1);
                    conect_graph[m_count].add_node_conect(op2 + 1);
                    obj->pop_back();
				}
                op1 = obj->back().m_u ;
                op2 = obj->back().m_v;
                conect_graph[m_count].add_node_conect(op1 + 1);
                conect_graph[m_count].add_node_conect(op2 + 1);
                obj->pop_back();
                ++m_count;
			}
		}

		else if(v != parent[u] && disc[v] < low[u])
		{
			low[u]  = min(low[u], disc[v]);
            obj->push_back(Edge(u,v));
		}
	}
}

void Graph::BCC()
{
    arr_type disc;
    arr_type low ;
    arr_type parent ;
    bcc_type * conteyner = new bcc_type[m_edge_size];
	int op1 = 0;
	int op2 = 0;

    for (int i = 0; i < m_my_size; i++)
	{
        disc.push_back(-1);
        low.push_back(-1);
        parent.push_back(-1);
	}

    for (int i = 0; i < m_my_size; i++)
	{
		if (disc[i] == -1)
            BCCUtil(i, disc, low, conteyner, parent);

		int j = 0;
        while(conteyner->size() > 0)
		{
			j = 1;
            op1 = conteyner->back().m_u;
            op2 = conteyner->back().m_v;
            conect_graph[m_count].add_node_conect(op1 + 1);
            conect_graph[m_count].add_node_conect(op2 + 1);
            conteyner->pop_back();
		}
		if(j == 1)
		{
            ++m_count;
		}
	}
    delete [] conteyner;
}

//function return min value from a and b
int Graph::min (int a, int b)
{
	if (a < b)
		return a;
	return b;
}

//creates new graph in old graph blocks
void Graph::graph_block ()
{
    std::set<int>::iterator j;
	int size = 0;
	int op1 = 0;
	int op2 = 0;
	int value = 0;

    for (int i = 0;i < m_count;++i)
	{
		op1 = i;
		size = conect_graph[i].get_node_size();
        for (j = conect_graph[i].vertex.begin();j != conect_graph[i].vertex.end();++j)
		{
            value = *j;
            for (int k = i + 1;k < m_count;++k)
			{
				op2 = k;
                if (conect_graph[k].vertex.find(value) != conect_graph[k].vertex.end())
				{
					block_graph.push_back(Blocks(op1,op2,value));
                    ++ m_block_size;
				}
			}
		}
    }
}

void Graph::print_graph_block ()
{
    std::cout<<"\t\t\tThe Block`s Graph is\n"<<std::endl;
        for (int i = 0;i < m_block_size;++i)
		{
            std::cout<<"B["<<block_graph[i].m_block1 + 1<<"] is conect to  B["<<block_graph[i].m_block2 + 1<<"] in vertex  "<<block_graph[i].m_p_of_i + 1<<std::endl;
		}
		std::cout<<std::endl;
}
