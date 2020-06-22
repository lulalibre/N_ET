#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<random>
#include<set>

namespace bt {


	struct tuple
	{
		std::uint32_t a, b;
		tuple(int a, int b) :a(a), b(b) {}
		tuple():a(0),b(0){}
	};
	inline bool operator< (const tuple& lhs, const tuple& rhs) {
		if (lhs.a < rhs.a) return true;
		else if (lhs.a == rhs.a) {
			if (lhs.b < rhs.b) return true;
			else return false;
		}
		return false;
	}
	inline bool operator> (const tuple& lhs, const tuple& rhs) {
		if (lhs.a > rhs.a) return true;
		else if (lhs.a == rhs.a) {
			if (lhs.b > rhs.b) return true;
			else return false;
		}
		return false;
	}
	inline bool operator==(const tuple& lhs, const tuple& rhs) {
		if ((lhs.a == rhs.a) && (lhs.b == rhs.b)) return true;
		
		else return false;
	}

	struct node
	{
		std::vector<node>& repo;
		std::uint32_t smaller;
		std::uint32_t bigger;
		tuple data;
		node(tuple d, std::vector<node>& ns) :data(d), repo(ns), smaller(0), bigger(0) { }
		node(const node& t):repo(t.repo) {
			smaller = t.smaller;
			bigger = t.bigger;
			data = t.data;
		}
		void operator =(const node& t) {
			repo = t.repo;
			smaller = t.smaller;
			bigger = t.bigger;
			data = t.data;
		}
		bool insert(tuple in) {
			if (data == in) return false;
			else {
				if (data > in) {
					if (smaller == 0) {
						node newNode(in, repo);
						repo.push_back(newNode);
						smaller = repo.size() - 1;
						
						return true;
					}
					else return repo.at(smaller).insert(in);
				}
				else {
					if (bigger == 0) {
						node newNode(in, repo);
						repo.push_back(newNode);
						bigger = repo.size() - 1;
						
						return true;
					}
					else return repo[bigger].insert(in );
				}
			}
		}
	};

	struct tree {
		std::set<uint32_t> synapses;
		std::uint32_t current_biggest_node;
		std::vector<node> nodes;
		bool insert(tuple in) {
			if (in.a > current_biggest_node) current_biggest_node = in.a;
			if (in.b > current_biggest_node) current_biggest_node = in.b;
			bool forward = false;
			bool backward = false;
			if (nodes.size() == 0) {
				nodes.push_back(node(in, nodes));
				return true;
			}
			else {
				forward = nodes[0].insert(in);
				tuple in_bw(in.b, in.a);
				backward = nodes[0].insert(in_bw);
				return(forward && backward);
			}
		}


		tree():current_biggest_node(0) {
			nodes.reserve(1000);
			
		}

		tree(const tree& t) {
			nodes = t.nodes;
			current_biggest_node = t.current_biggest_node;
			synapses = t.synapses;
		}
		void operator=(const tree& t) {
			nodes = t.nodes;
			current_biggest_node = t.current_biggest_node;
			synapses = t.synapses;
		}
		std::uint32_t biggest_node() {
			return current_biggest_node;
		}

	};
}

