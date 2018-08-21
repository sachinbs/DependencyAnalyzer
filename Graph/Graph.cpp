/////////////////////////////////////////////////////////////////////
//	Project#2:		Type-based Dependency Analysis				   //
//					To create a Type-based dependency analyzer	   //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Graph.cpp:	    Test-stub for Graph					           //
//  *************************************************************  //
//	Version:		1.0											   //
//  Date:			03/15/2017									   //
//  Language:       Visual C++, Version 11.						   //
//  Platform:       Visual Studio Community Edition				   //
//					HP ENVY, Windows 10				               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Sachin Basavani Shivashankara				   //
//	SUID:			267871645									   //
//  Ph:, email:     (315)751-5895, sbasavan@syr.edu				   //
/////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// Graph.cpp - Graph Library                                 //
// Ver 1.6                                                   //
// Language:    Visual C++ 2012                              //
// Platform:    Lenova ThinkPad E420s, Windows 7             //
// Application: Help for CSE687 - OOD, Pr#1, Spring 2013     //
// Author:      Jim Fawcett, CST 4-187, Syracuse University  //
//              (315) 443-3948, jfawcett@twcny.rr.com        //
///////////////////////////////////////////////////////////////

// Augmented the Graph package with functions to find strong components.
// Created functions after referring to http://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
// Modified the Graph package on 03/15/2017

#include "Graph.h"

using namespace std;
using namespace CodeAnalysis;
using namespace GraphLib;

using Rslt = Logging::StaticLogger<0>;
using Demo = Logging::StaticLogger<1>;
using Dbug = Logging::StaticLogger<2>;
using TypeTableMap = std::map<std::string, std::vector<CodeAnalysis::TypeInfo>>;
using DepTableMap = std::map<string, DepInfo>;

typedef Graph<std::string, std::string> graph;
typedef Vertex<std::string, std::string> vertex;
typedef Display<std::string, std::string> display;

void showVert(Vertex<std::string, std::string>& v)
{
  std::cout << "\n  " << v.id();
}

template<typename V, typename E>
void TshowVert(Vertex<V,E>& v)
{
  std::cout << "\n  " << v.id();
}

#ifdef TEST_GRAPH

// Test stub for Graph
int main()
{

  std::cout << "\n  Testing Graph Library";
  std::cout << "\n =======================\n";
  try
  {
    std::cout << "\n  Constructing Graph instance";
    std::cout << "\n -----------------------------";
    graph g;
    vertex v1("v1");
    vertex v2("v2");
    vertex v3("v3");
    vertex v4("v4");
    vertex v5("v5", 50);
    g.addVertex(v2);
    g.addVertex(v1);
    g.addVertex(v3);
    g.addVertex(v4);
    g.addVertex(v5);
    g.addEdge("e1",v1,v2);
    g.addEdge("e2",v1,v3);
    g.addEdge("e3",v2,v3);
    g.addEdge("e4",v4,v3);
    g.addEdge("e5",v5,v2);

    display::show(g);
    std::cout << "\n";

    std::cout << "\n  Making copy of instance";
    std::cout << "\n -------------------------";
    graph gcopy = g;
    display::show(gcopy);
    std::cout << "\n";

    std::cout << "\n  Modifying copy's values";
    std::cout << "\n -------------------------";
    for(auto& v : gcopy)
      v.value() += "copy";

    display::show(gcopy);
    std::cout << "\n";

    std::cout << "\n  Assigning original instance to copy";
    std::cout << "\n -------------------------------------";
    gcopy = g;
    display::show(gcopy);
    std::cout << "\n";

    std::cout << "\n  Vertices with no Parents:";
    std::cout << "\n ---------------------------";

    std::vector< vertex > verts = display::vertsWithNoParents(g);
    std::cout << "\n  ";
    for(size_t i=0; i<verts.size(); ++i)
      std::cout << verts[i].value().c_str() << " ";
    std::cout << "\n";

    std::cout << "\n  Testing Depth First Search with function pointer";
    std::cout << "\n --------------------------------------------------";
    for(auto& vert : g)
    {
      std::cout << "\n  starting at id " << vert.id();
      g.dfs(vert, TshowVert<std::string, std::string>);
      // this works too: 
      // g.dfs(vert, showVert);
    }
    std::cout << "\n";

    std::cout << "\n  Testing Depth First Search with Functor";
    std::cout << "\n -----------------------------------------";

    class showFunctor
    {
    public:
      void operator()(Vertex<std::string, std::string>& vert)
      {
        std::cout << "\n  From functor: vertix id = " << vert.id();
        std::cout << ", number of edges = " << vert.size();
      }
    };

    g.dfs(g[0], showFunctor());
    std::cout << "\n";

    std::cout << "\n  Testing Serialization to XML";
    std::cout << "\n ------------------------------";
    std::string str = GraphToXmlString(g);
    std::cout << str << "\n";
    std::ofstream out("testGraph.xml");
    out << str << "\n";

    std::cout << "\n  Testing Graph construction from XML";
    std::cout << "\n -------------------------------------";
    graph gtest;
    GraphFromXmlString(gtest, str);
    display::show(gtest);
    std::cout << "\n\n";
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what() << "\n\n";
  }
  std::cout << "\n\n";
  system("pause");
  return 0;
}

#endif