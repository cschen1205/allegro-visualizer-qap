#include "PathPlanner.h"
#include "Search_AStar.h"

/// <summary>Constructor method</summary>
/// \param[in] pOwner the vehicle that owns the planner
PathPlanner::PathPlanner(BaseGameEntity* pOwner) : m_pOwner(pOwner)
{

}

/// <summary>Constructor method</summary>
/// \param[in] g on which the planner apply A* to find the shortest path
/// \param[in] pTarget the vehicle that owns the planner
/// \param[in] path the shortest path travelled by the vehicle
void PathPlanner::PlanPath(Graph& g, BaseGameEntity* pTarget, std::list<GraphEdge*>& path)
{
	int start_index=g.GetNearestNode(m_pOwner->GetPosition())->GetID();
	int end_index=g.GetNearestNode(pTarget->GetPosition())->GetID();

	Search_AStar searcher(g, start_index, end_index);
	searcher.Search();
	
	searcher.GetPathToTarget(path);
}
