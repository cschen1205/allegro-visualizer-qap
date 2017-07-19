#ifndef _H_GRAPH_H
#define _H_GRAPH_H

#include "GraphNode.h"
#include <vector>
#include "../Util/Point2D.h"
#include "../GameEntity/BaseGameEntity.h"
#include "../allegro_include/allegro.h"

/// <summary>Class that represents the graph holding the stations as nodes and paths traveled by vehicles as edges</summary>
class Graph
{
public:
	/// <summary>Constructor method</summary>
	Graph();
	/// <summary>Destructor method</summary>
	virtual ~Graph();

public:
	/// <summary>Method that initialize the graph</summary>
	/// \param[in] left the left of the graph
	/// \param[in] top the top of the graph
	/// \param[in] right the right of the graph
	/// \param[in] bottom the bottom of the graph
	/// \param[in] vg vertical interval between two nodes / stations
	/// \param[in] hg horizontal interval between two nodes / stations
	void Init(float left, float top, float right, float bottom, float vg, float hg);
	/// <summary>Method that returns the nearest graph node from a position on the game world</summary>
	/// \param[in] pos a position on the game world
	/// <returns>The graph node on the graph that is the closest to the position</returns>
	GraphNode* GetNearestNode(Point2D pos);

	void ConnectEntity(BaseGameEntity* pEntity);

	/// <summary>Method that returns the number of rows in the graph grid</summary>
	/// <returns>The number of rows in the graph grid</returns>
	int GetRowCount() { return m_RowCount; }
	/// <summary>Method that returns the number of columns in the graph grid</summary>
	/// <returns>The number of columns in the graph grid</returns>
	int GetColCount() { return m_ColCount; }
	/// <summary>Method that returns the number of nodes in the graph grid</summary>
	/// <returns>The number of nodes in the graph grid</returns>
	int GetNodeCount() { return m_RowCount * m_ColCount; }

	/// <summary>Method that return a graph node by its id</summary>
	/// \param[in] id the id of the graph node to return
	/// <returns>The graph node associated with the id</returns>
	GraphNode* GetNode(int id) { return m_nodes[id]; }

	/// <summary>Method that render the graph on the game screen</summary>
	/// \param[in] buffer the buffer image onto which the graph is rendered and displayed using the double-buffer technique
	void Render(BITMAP* buffer);

private:
	/// <summary>The nodes in the graph grid</summary>
	std::vector<GraphNode*> m_nodes;
	/// <summary>The top left corner of the graph grid</summary>
	Point2D m_TopLeft;
	/// <summary>The bottom right corner of the graph grid</summary>
	Point2D m_BottomRight;
	/// <summary>The interval between two graph nodes in terms of horizontal and version distance</summary>
	Size2D m_Gap;
	/// <summary>The number of rows in the graph grid</summary>
	int m_RowCount;
	/// <summary>The number of columns in the graph grid</summary>
	int m_ColCount;
};
#endif