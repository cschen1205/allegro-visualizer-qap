#ifndef _H_GRAPH_NODE_H
#define _H_GRAPH_NODE_H

#include "../Util/Point2D.h"
#include <vector>
#include "GraphEdge.h"

class BaseGameEntity;

/// <summary>Class that represent the graph node in the graph</summary>
class GraphNode
{

public:
	/// <summary>Constructor method</summary>
	/// \param[in] id the id of the graph node
	GraphNode(int id);
	/// <summary>Destructor method</summary>
	virtual ~GraphNode();

public:
	/// <summary>Method that sets the position of the graph node</summary>
	/// \param[in] point the positon of the graph node
	void SetPosition(Point2D point) { m_position=point; }
	/// <summary>Method that return the position of the graph node</summary>
	/// <returns>The position of the graph node</returns>
	Point2D GetPosition() { return m_position; }
	/// <summary>Method that return the position in relation to the game world</summary>
	/// <returns>The position in relation to the game world</returns>
	Point2D GetPositionOnSimulator();

	/// <summary>Method that forms the edge with another node</summary>
	/// \param[in] pNode another node to connect with
	void Connect2(GraphNode* pNode);
	/// <summary>Method that sets a game agent as the representation of the node in the game world</returns>
	/// \param[in] pEntity the game agemt that sits on the graph node
	void ConnectEntity(BaseGameEntity* pEntity);

	/// <summary>Method that returns the number of nodes connected to the graph node</summary>
	/// <returns>The number of nodes connected to the graph node<returns>
	int GetEdgeCount() { return m_edges.size(); }
	/// <summary>Method that return the edge connected to another node</summary>
	/// \param[in] id the id of the graph node to which the graph node has a connected edge
	/// <returns>The graph edge that forms the connection between the node associated with the id and the graph node</returns>
	GraphEdge* GetEdge(int id) { return m_edges[id]; }

	/// <summary>Method that returns the game agent sits on the graph node</summary>
	/// <returns>the game agent sitting on the graph node</returns>
	BaseGameEntity* GetEntity() { return m_pEntity; }

	/// <summary>Method that return the id of the graph node</summary>
	/// <returns>The id of the graph node</returns>
	int GetID() { return m_id; }

private:
	/// <summary>The position of the graph node</summary>
	Point2D m_position;
	/// <summary>The edges connected to the graph node</summary>
	std::vector<GraphEdge*> m_edges;
	/// <summary>The game agent sitting on the graph node</summary>
	BaseGameEntity* m_pEntity;
	/// <summary>The id of the graph node</summary>
	int m_id;
};

#endif