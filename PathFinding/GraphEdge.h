#ifndef _H_GRAPH_EDGE_H
#define _H_GRAPH_EDGE_H

/// <summary>Class that represents an edge in the graph</summary>
class GraphEdge
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] iFrom the id of the starting node
	/// \param[in] iTo the id of the ending node
	GraphEdge(int iFrom, int iTo);

public:
	/// <summary>Method that set the weight of the edge, e.g., distance</summary>
	/// \param[in] cost the weight of the edge
	void SetCost(float cost) { m_cost=cost; }
	/// <summary>Method that returns the weight of the edge</summary>
	/// <returns>The weight of the edge</returns>
	float GetCost() const { return m_cost; }
	/// <summary>Method that increase the weight of the edge</summary>
	/// \param[in] inc the weight increment
	void IncCost(float inc) { m_cost+=inc; }

public:
	/// <summary>Method that returns the id of the starting node</summary>
	/// <returns>The id of the starting node</returns>
	int GetFrom() const { return m_iFrom; }
	/// <summary>Method that returns the id of the ending node</summary>
	/// <returns>The id of the ending node</returns>
	int GetTo() const { return m_iTo; }

private:
	/// <summary>The id of the starting node</summary>
	int m_iFrom;
	/// <summary>The id of the ending node</summary>
	int m_iTo;
	/// <summary>The weight of the edge</summary>
	float m_cost;
};

#endif