#include "Search_AStar.h"
#include "GraphNode.h"
#include <algorithm>
#include "../Util/Point2D.h"
#include "../allegro_include/allegro.h"
/*
#include <string>
#include <sstream>
*/
#include <cassert>

Search_AStar::Search_AStar(Graph& graph, int start_index, int end_index) : 
m_Graph(graph), 
m_start_index(start_index), 
m_end_index(end_index),
m_SearchFront(graph.GetNodeCount(), NULL),
m_ShortestPathTree(graph.GetNodeCount(), NULL),
m_FCost(graph.GetNodeCount(), 0),
m_GCost(graph.GetNodeCount(), 0)
{
	
}

/// <summary>Method that performs the search</summary>
/// <returns>The boolean flag indicating whether the shortest path between the starting and ending nodes</returns>
bool Search_AStar::Search()
{
	std::list<int> pq;

	pq.push_back(m_start_index);

	while(!pq.empty())
	{
		int NextClosestNode=pq.front();

		pq.pop_front();

		m_ShortestPathTree[NextClosestNode]=m_SearchFront[NextClosestNode];

		if(NextClosestNode==m_end_index) return true;

		GraphNode* pNode=m_Graph.GetNode(NextClosestNode);
		for(int i=0; i<pNode->GetEdgeCount(); i++)
		{
			//allegro_message("test");
			GraphEdge* pEdge=pNode->GetEdge(i);

			GraphNode* pNeighborNode=m_Graph.GetNode(pEdge->GetTo());

			if(pNeighborNode->GetEntity()!=NULL && pNeighborNode->GetID()!=m_end_index)
			{
				//allegro_message(pNeighborNode->GetEntity()->GetID().c_str());
				continue;
			}
			
			/*
			std::ostringstream oss;
			oss << "id: " << pNeighborNode->GetID();
			std::string msg=oss.str();
			allegro_message(msg.c_str());
			*/

			float HCost=Heuristic_Euclid(m_end_index, pEdge->GetTo());
			float GCost=m_GCost[NextClosestNode]+pEdge->GetCost();
			float FCost=HCost+GCost;

			if(m_SearchFront[pEdge->GetTo()]==NULL)
			{
				m_SearchFront[pEdge->GetTo()]=pEdge;
				m_FCost[pEdge->GetTo()]=FCost;
				m_GCost[pEdge->GetTo()]=GCost;

				std::list<int>::iterator list_pos;
				for(list_pos=pq.begin(); list_pos!=pq.end(); ++list_pos)
				{
					int list_index=*list_pos;
					if(FCost<m_FCost[list_index])
					{
						break;
					}
				}
				if(list_pos==pq.end())
				{
					pq.push_back(pEdge->GetTo());
				}
				else
				{
					pq.insert(list_pos, pEdge->GetTo());
				}
			}
			else if(GCost < m_GCost[pEdge->GetTo()] && (m_ShortestPathTree[pEdge->GetTo()]==NULL))
			{
				m_GCost[pEdge->GetTo()]=GCost;
				m_FCost[pEdge->GetTo()]=FCost;
				m_SearchFront[pEdge->GetTo()]=pEdge;
				
				std::list<int>::iterator list_pos;
				list_pos=std::find(pq.begin(), pq.end(), pEdge->GetTo());
				pq.erase(list_pos);

				for(list_pos=pq.begin(); list_pos!=pq.end(); ++list_pos)
				{
					int list_index=*list_pos;
					if(FCost<m_FCost[list_index])
					{
						break;
					}
				}
				pq.insert(list_pos, pEdge->GetTo());
			}
		}
	}
	
	return true;
}

/// <summary>Method that returns the shortest path</summary>
/// \param[out] path the shortest path from the starting to the ending points
void Search_AStar::GetPathToTarget(std::list<GraphEdge*>& path) const
{
	if(m_end_index < 0) return;

	int nd=m_end_index;
	while((nd!=m_start_index) && (m_ShortestPathTree[nd] != NULL))
	{
		path.push_front(m_ShortestPathTree[nd]);
		nd=m_ShortestPathTree[nd]->GetFrom();

		/*
		std::ostringstream oss;
		oss << "id: " << nd;
		std::string msg=oss.str();
		allegro_message(msg.c_str());
		*/
		
	}

	assert(!path.empty());
}

/// <summary>Method that returns heuristic value between two nodes, which is the euclidean distance
/// \param[in] node1 id of the starting node
/// \param[in] node2 id of the ending node
/// <returns>The distance between node1 and node2</returns>
float Search_AStar::Heuristic_Euclid(int node1, int node2)
{
	Point2D pos1=m_Graph.GetNode(node1)->GetPosition();
	Point2D pos2=m_Graph.GetNode(node2)->GetPosition();
	Point2D d=pos1-pos2;
	return d.Length();
}
