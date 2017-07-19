#ifndef _H_PATH_PLANNER_H
#define _H_PATH_PLANNER_H

#include "Graph.h"
#include "GraphEdge.h"
#include <list>

class BaseGameEntity;

/// <summary>Class that represents the path planner</summary>
class PathPlanner
{
public:
	/// <summary>Constructor method</summary>
	/// \param[in] pOwner the vehicle that owns the planner
	PathPlanner(BaseGameEntity* pOwner);
	/// <summary>Constructor method</summary>
	/// \param[in] g on which the planner apply A* to find the shortest path
	/// \param[in] pTarget the vehicle that owns the planner
	/// \param[in] path the shortest path travelled by the vehicle
	void PlanPath(Graph& g, BaseGameEntity* pTarget, std::list<GraphEdge*>& path);

private:
	/// <summary>The vehicle agent that owns the planner</summary>
	BaseGameEntity* m_pOwner;
};
#endif