#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int distance(const vvi& graph, int v1, int v2){
	std::queue<int> q;
	vi d(graph.size(), INT_MAX);

	d[v1] = 0;
	q.push(v1);
	while(!q.empty()){
		int v = q.front();
		q.pop();

		for(vi::const_iterator it = graph[v].begin(); it != graph[v].end(); ++it){
			if(d[*it] > d[v] + 1){
				d[*it] = d[v] + 1;
				q.push(*it);
			}
		}
	}
	return d[v2];
}

bool isConnected2(const vvi& graph, int v1, int v2){
	if(v1 == v2)
		return true;

	for(vi::const_iterator it = graph[v1].begin(); it != graph[v1].end(); ++it){
		if(isConnected2(graph, *it, v2))
			return true;
	}
	return false;
}

void test(){
	vvi graph(6);
	graph[1].push_back(2);
	graph[2].push_back(3);
	graph[3].push_back(0);
	graph[3].push_back(5);
	graph[4].push_back(3);

	for(int i = 0; i < 6; ++i){
		for(int j= 0; j < 6; ++j){
			int d = distance(graph, i, j);
			if(d == INT_MAX)
				std::cout << 'X';
			else
				std::cout << d;
		}
		std::cout << std::endl;
	}

	for(int i = 0; i < 6; ++i){
		for(int j= 0; j < 6; ++j){
			if(isConnected2(graph, i, j))
				std::cout << 'O';
			else
				std::cout << 'X';
		}
		std::cout << std::endl;
	}
}

#endif /* GRAPH_H_ */
