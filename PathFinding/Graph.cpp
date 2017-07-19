#include "Graph.h"
#include "../Util/Point2D.h"
#include <cassert>
#include <sstream>
#include <string>

/// <summary>Method that initialize the graph</summary>
/// \param[in] left the left of the graph
/// \param[in] top the top of the graph
/// \param[in] right the right of the graph
/// \param[in] bottom the bottom of the graph
/// \param[in] vg vertical interval between two nodes / stations
/// \param[in] hg horizontal interval between two nodes / stations
void Graph::Init(float left, float top, float right, float bottom, float vg, float hg)
{
	int counter=0;
	m_RowCount=0;
	for(float y=top; y<= bottom; y+=vg)
	{
		for(float x=left; x <= right; x+=hg)
		{
			GraphNode* pNode=new GraphNode(counter);
			pNode->SetPosition(Point2D(x, y));
		
			m_nodes.push_back(pNode);
			counter++;
		}

		m_RowCount++;
	}

	assert(m_RowCount>0);
	m_ColCount=m_nodes.size() / m_RowCount;

	for(int i=0; i<m_RowCount; i++)
	{
		for(int j=0; j<m_ColCount; j++)
		{
			GraphNode* pNode=m_nodes[j+m_ColCount * i];
			for(int i1=i-1; i1 <= i+1; i1++)
			{
				if(i1<0 || i1>= m_RowCount)
				{
					continue;
				}
				for(int j1=j-1; j1 <= j+1; j1++)
				{
					if(j1<0 || j1>=m_ColCount || (i1==i && j1==j))
					{
						continue;
					}
					pNode->Connect2(m_nodes[j1 + i1 * m_ColCount]);
				}
			}
		}
	}

	m_TopLeft=Point2D(left, top);
	m_BottomRight=Point2D(right, bottom);
	m_Gap=Size2D(hg, vg);
}

/// <summary>Method that returns the nearest graph node from a position on the game world</summary>
/// \param[in] pos a position on the game world
/// <returns>The graph node on the graph that is the closest to the position</returns>
GraphNode* Graph::GetNearestNode(Point2D pos)
{
	Point2D pos1=pos-m_TopLeft;
	int r=static_cast<int>(pos.GetY() / m_Gap.GetY());
	int c=static_cast<int>(pos.GetX() / m_Gap.GetX());

	int index=c + r * m_ColCount;
	assert(index>=0 && index<m_nodes.size());

	return m_nodes[index];
}

void Graph::ConnectEntity(BaseGameEntity* pEntity)
{
	Point2D pos=pEntity->GetPosition();
	
	GraphNode* pNode=GetNearestNode(pos);

	/*
	std::ostringstream oss;
	oss << "id: " << pNode->GetID();
	std::string message=oss.str();
	allegro_message(message.c_str());
	*/

	assert(pNode!=NULL);

	pNode->ConnectEntity(pEntity);
}

/// <summary>Method that render the graph on the game screen</summary>
/// \param[in] buffer the buffer image onto which the graph is rendered and displayed using the double-buffer technique
void Graph::Render(BITMAP* buffer)
{
	for(int i=0; i<m_nodes.size(); i++)
	{
		if(i % 2 ==0)
		{
			continue;
		}

		GraphNode* pNode=m_nodes[i];
		assert(pNode->GetEntity()==NULL);
		Point2D pos=pNode->GetPositionOnSimulator();
		circle(buffer, pos.GetX(), pos.GetY(), 3, makecol(255, 0, 0));
		for(int j=0; j<pNode->GetEdgeCount(); j++)
		{
			GraphEdge* pEdge=pNode->GetEdge(j);
			GraphNode* pNeighborNode=GetNode(pEdge->GetTo());
			Point2D pos1=pNeighborNode->GetPositionOnSimulator();
			line(buffer, pos.GetX(), pos.GetY(), pos1.GetX(), pos1.GetY(), makecol(255, 255, 255));
		}
	}
}

/// <summary>Constructor method</summary>
Graph::Graph()
{

}

/// <summary>Destructor method</summary>
Graph::~Graph()
{
	std::vector<GraphNode*>::iterator pos;
	for(pos=m_nodes.begin(); pos!=m_nodes.end(); ++pos)
	{
		delete (*pos);
	}
	m_nodes.clear();
}
