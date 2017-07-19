#include "GraphEdge.h"

/// <summary>Constructor method</summary>
/// \param[in] iFrom the id of the starting node
/// \param[in] iTo the id of the ending node
GraphEdge::GraphEdge(int iFrom, int iTo) : m_cost(0)
{
	m_iFrom=iFrom;
	m_iTo=iTo;
}
