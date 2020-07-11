#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

	start_node = &m_Model.FindClosestNode(start_x, start_y);
	end_node = &m_Model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
	return end_node->distance(*node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node) {
	current_node->FindNeighbors();
	for (auto* node : current_node->neighbors) {
		node->parent = current_node;
		node->h_value = CalculateHValue(node);
		node->g_value = current_node->g_value + current_node->distance(*node);
		node->visited = true;
		open_list.emplace_back(node);
		// std::cout << "Node: " << node << ", parent: " << node->parent << ", sum: " << node->h_value + node->g_value << "\n";
	}
}

// Deprecating this in favor of lambda expression within the sort function
bool RoutePlanner::CompareNode(RouteModel::Node* one, RouteModel::Node* two) {
	return one->h_value + one->g_value > two->h_value + two->g_value;
}

RouteModel::Node *RoutePlanner::NextNode() {
	sort(open_list.begin(), open_list.end(), [] (RouteModel::Node* one, RouteModel::Node* two) { return one->h_value + one->g_value > two->h_value + two->g_value; });
	RouteModel::Node* ptr = open_list.back();
	open_list.pop_back();
	return ptr;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

	RouteModel::Node * current = end_node;
	while(current != start_node) {
		path_found.push_back(*current);
		if(current->parent == nullptr) break;
		distance += current->distance(*current->parent);
		current = current->parent;
	}
	path_found.emplace_back(*current);
	std::reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

	current_node = start_node;
	current_node->visited = true;

	while (current_node != end_node) {
		AddNeighbors(current_node);
		// std::cout << "Getting NextNode()\n";
		current_node = NextNode();
	}

	// store path in Mode.path
	m_Model.path = ConstructFinalPath(end_node);
}