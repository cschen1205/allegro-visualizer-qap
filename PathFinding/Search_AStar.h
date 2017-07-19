#ifndef _H_SEARCH_A_STAR_H
#define _H_SEARCH_A_STAR_H

#include "GraphEdge.h"
#include "Graph.h"
#include <vector>
#include <list>

/// <summary>Class that represent the A* search algorithm solver</summary>
class Search_AStar
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] g the graph
	/// \param[in] start_index the id of the starting node of the search
	/// \param[in] end_index the id of the ending node of the search
	Search_AStar(Graph& g, int start_index, int end_index);

	/// <summary>Method that performs the search</summary>
	/// <returns>The boolean flag indicating whether the shortest path between the starting and ending nodes</returns>
	bool Search();

	/// <summary>Method that returns the shortest path</summary>
	/// \param[out] path the shortest path from the starting to the ending points
	void GetPathToTarget(std::list<GraphEdge*>& path) const;

private:
	/// <summary>Method that returns heuristic value between two nodes, which is the euclidean distance
	/// \param[in] node1 id of the starting node 
	/// \param[in] node2 id of the ending node
	/// <returns>The distance between node1 and node2</returns>
	float Heuristic_Euclid(int node1, int node2);

private:
	/// <summary>The graph which holds the starting and ending point as well as the shortest path to be found</summary>
	Graph& m_Graph;
	/// <summary>The id of the starting node</summary>
	int m_start_index;
	/// <summary>The id of the ending node</summary>
	int m_end_index;
	/// <summary>the queue of nodes arranged basedon the heuristic value of distance</summary>
	std::vector<GraphEdge*> m_SearchFront;
	/// <summary>The shortest search path tree</summary>
	std::vector<GraphEdge*> m_ShortestPathTree;
	/// <summary>The vector that stores the heuristic distance of each node to the ending point</summary>
	std::vector<float> m_FCost;
	/// <summary>The vecor that stores the shortest distance of each node from the starting point</summary>
	std::vector<float> m_GCost;

};
#endif