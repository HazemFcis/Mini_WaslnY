#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<cstring>
#include<stack>
//#include<bits/stdc++.h>
using namespace std;
map<string, bool> found_in_total;
bool is_number(string x)
{
	int n = x.size();
	for (int i = 0; i<n; i++)
	{
		if (x[i]<'0' || x[i]>'9')
			return false;
	}
	return true;
}
int to_dec(string x)
{
	int power = 1;
	int cnt = 0;
	int n = x.size();
	for (int i = n - 1; i >= 0; i--)
	{
		cnt += ((x[i] - 48)*power);
		power *= 10;
	}
	return cnt;
}
template<class T>
class Node
{
public:
	T data;
	Node<T> *next;
	Node()
	{
		data = 0;
		next = NULL;
	}
	Node(T val)
	{
		data = val;
		next = NULL;
	}
};
template<class T>
class stack2
{
	int n;
	Node<T> *Top;
public:
	stack2()
	{
		n = 0;
		Top = NULL;
	}
	~stack2()
	{
		clear();
	}
	int size()
	{
		return n;
	}
	void pop()
	{
		if (Top == NULL)  // aw n==0;
		{
			cout << "The stack is empty";
			return;
		}
		Node<T> *temp = Top;
		Top = Top->next;
		delete temp;
		n--;
	}
	T top()
	{
		return (Top->data);
	}
	void push(T val)
	{
		Node<T> *temp = new Node<T>(val);
		temp->next = Top;
		Top = temp;
		n++;
	}
	void clear()
	{
		while (size())
		{
			pop();
		}
	}
};
class Graph
{
	map<string, vector<pair<string, int> > > graph_content;
	map<int, int> num_of_towns, num_of_roads; // number of towns
	map<string, int> pos_of_town, first_map;
	map<int, string> second_map;
	long long dp[50][50];
	int town_num;
	int oo = int(1e9);
	bool ok, done, Floyd_done;
public:
	Graph()
	{
		town_num = 0;
		/*for(int i=0; i<500; i++)
		{
		for(int j=0; j<500; j++)
		{
		weight[i][j]=oo;
		sp[i][j]=-1;
		}
		}*/
	}
	~Graph()
	{
		graph_content.clear();
		num_of_towns.clear();
		pos_of_town.clear();
		first_map.clear();
		second_map.clear();
	}
	int get_town_num(int graph_id)
	{
		return num_of_towns[graph_id];
	}
	void Insert_Graph(int graph_id)   // Done
	{
		cout << "Number of towns : ";
		string ss;
		cin >> ss;
		while (!is_number(ss))
		{
			cout << "this is invalid input \n";
			cin >> ss;
		}
		int Number_of_towns = to_dec(ss);
		for (int i = 0; i<Number_of_towns; i++)
		{
			insert_new_town(graph_id);
		}
		int stop = ((Number_of_towns*(Number_of_towns - 1)) / 2); // Nc2
		cout << "Number of roads : ";
		cin >> ss;
		int Number_of_roads;
		while (true)
		{
			if (!is_number(ss))
			{
				cout << "this is invalid value \n";
				cin >> ss;
				continue;
			}
			else if (is_number(ss))
			{
				Number_of_roads = to_dec(ss);
				//cout<<Number_of_roads<<endl;
				//cout<<stop<<endl;
				if (Number_of_roads>stop)
				{
					cout << "the number of roads is more than the total number of roads of complete graph\n\n";
					cout << "re-enter the valid number of roads \n";
					cin >> ss;
					continue;
				}
			}
			break;
		}
		for (int i = 0; i < Number_of_roads; i++)
		{
			done = false;
			insert_new_road(graph_id);
			if (!done)
				i--;
		}
		cout << "the graph number : " << graph_id << " is successfully created.\n";
	}
	bool is_road_exist(string start, string end)   // Done
	{
		int n = graph_content[start].size();
		for (int i = 0; i < n; i++)
		{
			if (graph_content[start][i].first == end)
			{
				return true;
			}
		}
		return false;
	}
	int get_distance(string start, string end) {
		int n = graph_content[start].size();
		for (int i = 0; i < n; i++)
		{
			if (graph_content[start][i].first == end)
			{
				return graph_content[start][i].second;
			}
		}
	}
	void update_distance(string v, string u, int w)   // Done
	{
		int n = graph_content[v].size();
		for (int i = 0; i < n; i++)
		{
			if (graph_content[v][i].first == u)
			{
				graph_content[v][i].second = w;
			}
		}
		int m = graph_content[u].size();
		for (int i = 0; i < m; i++)
		{
			if (graph_content[u][i].first == v)
			{
				graph_content[u][i].second = w;
			}
		}
		Floyd_done = false;
	}
	void insert_new_road(int graph_id) // Done
	{
		int w;
		string u, v, ww;
		cout << "Insert first town: ";
		cin >> v;
		while (pos_of_town.find(v) == pos_of_town.end())
		{
			cout << "the first town not found in the graph\n";
			cout << "if you want to cancel this operation enter CLOSE else enter town name\n";
			cin >> v;
			if (v == "CLOSE")
				return;
		}
		cout << "Insert second town: ";
		cin >> u;
		while (pos_of_town.find(u) == pos_of_town.end())
		{
			cout << "the second town not found in the graph\n";
			cout << "if you want to cancel this operation enter CLOSE else enter town name\n";
			cin >> u;
			if (u == "CLOSE")
				return;
		}
		cout << "Insert the distance: ";
		cin >> ww; // string
		while (!is_number(ww))
		{
			cout << "you entered invalid value re-enter correct value\n";
			cin >> ww;
		}
		w = to_dec(ww);
		if (is_road_exist(v, u))
		{
			cout << "the road has been exist\n";
			cout << "if you want to update this distance enter YES else enter any key(s) \n";
			string ss;
			cin >> ss;
			if (ss == "YES")
				update_distance(u, v, w);
			return;
		}
		graph_content[v].push_back(make_pair(u, w));
		graph_content[u].push_back(make_pair(v, w));
		num_of_roads[graph_id]++;
		ok = done = true;
		Floyd_done = false;
	}
	void delete_road(int graph_id) // Done
	{
		string u, v;
		cout << "Insert first town: ";
		cin >> v;
		while (pos_of_town.find(v) == pos_of_town.end())
		{
			cout << "the first town not found in the graph\n";
			cout << "if you want to cancel this operation enter CLOSE else enter town name\n";
			cin >> v;
			if (v == "CLOSE")
				return;
		}
		cout << "Insert second town: ";
		cin >> u;
		while (pos_of_town.find(u) == pos_of_town.end())
		{
			cout << "the first town not found in the graph\n";
			cout << "if you want to cancel this operation enter CLOSE else enter town name\n";
			cin >> u;
			if (u == "CLOSE")
				return;
		}
		if (!is_road_exist(u, v))
		{
			cout << "el tareq m4 mawgod\n";
			return;
		}
		delete_road(u, v);
		num_of_roads[graph_id]--;
		ok = true;
		Floyd_done = false;
	}
	void delete_road(string start, string end) // Done
	{
		int n = graph_content[start].size();
		int m = graph_content[end].size();
		for (int i = 0; i < n; i++)
		{
			if (graph_content[start][i].first == end)
			{
				graph_content[start].erase(graph_content[start].begin() + i);
				break;
			}
		}
		for (int i = 0; i < m; i++)
		{
			if (graph_content[end][i].first == start)
			{
				graph_content[end].erase(graph_content[end].begin() + i);
				break;
			}
		}
		Floyd_done = false;
	}
	void insert_new_town(int  graph_id) // Done
	{
		string v;
		cout << "enter your town name: ";
		cin >> v;
		while (found_in_total.find(v) != found_in_total.end()) // check town found in total graphs
		{
			cout << "this town is already exist .. re-enter the valid town : ";
			cin >> v;
		}
		first_map[v] = town_num, second_map[town_num++] = v; // mynf3sh ( i ) 3l4an bara mafrod yb2a m3aia ( i )
		pos_of_town[v] = graph_id;
		num_of_towns[graph_id]++; // hzwed towns wa7d
		found_in_total[v] = true;
		Floyd_done = false;
	}
	void delete_town(int graph_id) // Done
	{
		string v;
		cout << "insert town name : ";
		cin >> v; //check existed town
		while (pos_of_town.find(v) == pos_of_town.end())
		{
			cout << "this town isn't exsit .. re-enter the valid town : ";
			cin >> v;
		}
		int n = graph_content[v].size();
		for (int i = 0; i<n; i++)
		{
			delete_road(v, graph_content[v][0].first);
		}
		int temp = first_map[v];
		second_map.erase(temp);
		first_map.erase(v);
		pos_of_town.erase(v);
		num_of_towns[graph_id]--;
		found_in_total.erase(v);
		ok = true;
	}
	void Update_Graph(int graph_id) // Done
	{
		Display_Graph(graph_id);
	HOSSAM:
		cout << "if you want to insert new road enter 1\n";
		cout << "if you want to delete road enter 2\n";
		cout << "if you want to insert new town enter 3\n";
		cout << "if you want to delete town enter 4\n";
		string x;
		cin >> x;
		if (x == "1")    // insert new road
		{
			ok = false;
			insert_new_road(graph_id);
			if (ok)
				Floyd_done = false, cout << "the road is added sucfuly\n";
		}
		else if (x == "2")    // delete road
		{
			ok = false;
			delete_road(graph_id);
			if (ok)
				Floyd_done = false, cout << "the road is removed sucfuly\n";
		}
		else if (x == "3")    // insert new town
		{
			ok = false;
			insert_new_town(graph_id);
			if (ok)
				Floyd_done = false, cout << "the town added suc\n";
		}
		else if (x == "4")    //delete town
		{
			delete_town(graph_id);
			if (ok)
				Floyd_done = false, cout << "the town deleted suc\n";
		}
		else if (x == "5") {
			map<string, vector<pair<string, int> > >::iterator it, it2;
			for (it = graph_content.begin();it != graph_content.end();it++) {
				for (it2 = it, it2++;it2 != graph_content.end();it2++) {
					if (is_road_exist(it->first, it2->first)) {
						delete_road(it->first, it2->first);
					}
				}
			}
			for (it = graph_content.begin();it != graph_content.end();it++) {
				second_map.erase(first_map[it->first]);
				first_map.erase(it->first);
				pos_of_town.erase(it->first);
				num_of_towns[graph_id]--;
				found_in_total.erase(it->first);
				graph_content.erase(it->first);
			}
			cout << "the graph is deleted\n\n";
			Floyd_done = false;
		}
		else
		{
			cout << "this is invalid input \n";
			goto HOSSAM;
		}
		Display_Graph(graph_id);
		cout << "\n\nenter any key(s) to back to main page\n\n";
		string ooo;
		cin >> ooo;
		system("cls");
	}
	void Display_Graph(int graph_id) // Done
	{
		map<string, vector<pair<string, int> > >::iterator it;
		for (it = graph_content.begin(); it != graph_content.end(); it++)
		{
			int n = graph_content[(it->first)].size();
			for (int j = 0; j < n; j++)
			{
				cout << "the distance between ( ";
				cout << (it->first) << " ) and ( ";
				cout << graph_content[(it->first)][j].first << " ) is : ";
				cout << graph_content[(it->first)][j].second << endl;
			}
		}
	}
	void Dijkstera(string start, string end)
	{
		if (pos_of_town.find(start) == pos_of_town.end())
		{
			cout << "the first town isn't exist \n";
			return;
		}
		if (pos_of_town.find(end) == pos_of_town.end())
		{
			cout << "the second town isn't exist \n";
			return;
		}
		if (pos_of_town[start] != pos_of_town[end])
		{
			cout << "two towns are not found in the same graph\n";
			return;
		}
		if (start == end)
		{
			cout << "anta fel town ely 3ayz tro7ha spa7 el fol\n\n";
			return;
		}
		int graph_id = pos_of_town[start];
		int n = first_map[end];
		vector<int> dis, parent;
		dis.resize(num_of_towns[graph_id] + 2);
		parent.resize(num_of_towns[graph_id] + 2);
		for (int i = 0; i <= num_of_towns[graph_id]; i++)
			dis[i] = oo;
		dis[first_map[start]] = 0;
		priority_queue<pair<int, int> > pq;
		pq.push(make_pair(first_map[start], 0));
		pair<int, int> x;
		int w;
		string v;
		string u = start;
		parent[first_map[u]] = -1;
		while (!pq.empty())
		{
			x = pq.top();
			u = second_map[x.first];
			pq.pop();
			int si = graph_content[u].size();
			for (int i = 0; i<si; i++)
			{
				v = graph_content[u][i].first;
				w = graph_content[u][i].second;
				if (dis[first_map[u]] + w < dis[first_map[v]])
				{
					dis[first_map[v]] = dis[first_map[u]] + w;
					parent[first_map[v]] = first_map[u];
					pq.push(make_pair(first_map[v], dis[first_map[v]]));
				}
			}
		}
		if (dis[n] == oo)
		{
			cout << "there is no path between this two towns\n";
			return;
		}
		int j = n;
		stack<string> st;
		while (j != -1)
		{
			st.push(second_map[j]);
			j = parent[j];
		}
		cout << "\n";
		cout << "the shortest distance is : " << dis[n] << "\n";
		cout << "\nthe shortest path between " << start << " and " << end << " is : ";
		while (st.size())
		{
			cout << st.top() << " ";
			st.pop();
		}
		cout << "\n\n";
	}
	void floyed(string start, string end) {
		if (Floyd_done) {
			//cout << first_map[start] << " " << first_map[end] << endl;
			cout << "the shortest distance is : " << dp[first_map[start]][first_map[end]];
			return;
		}
		if (pos_of_town.find(start) == pos_of_town.end())
		{
			cout << "the first town isn't exist \n";
			return;
		}
		if (pos_of_town.find(end) == pos_of_town.end())
		{
			cout << "the second town isn't exist \n";
			return;
		}
		if (pos_of_town[start] != pos_of_town[end])
		{
			cout << "two towns are not found in the same graph\n";
			return;
		}
		if (start == end)
		{
			cout << "anta fel town ely 3ayz tro7ha spa7 el fol\n\n";
			return;
		}
		map<string, int>::iterator it4, it5;
		map<string, vector<pair<string, int> > >::iterator it, it2, it3;
		for (it4 = pos_of_town.begin();it4 != pos_of_town.end();it4++) {
			for (it5 = pos_of_town.begin();it5 != pos_of_town.end();it5++) {
				if (is_road_exist(it4->first, it5->first)) {
					dp[first_map[it4->first]][first_map[it5->first]] = get_distance(it4->first, it5->first);
				}
				else {
					dp[first_map[it4->first]][first_map[it5->first]] = oo;
				}
			}
		}
		for (it = graph_content.begin();it != graph_content.end();it++) {
			for (it2 = graph_content.begin();it2 != graph_content.end();it2++) {
				for (it3 = graph_content.begin();it3 != graph_content.end();it3++) {
					dp[first_map[it->first]][first_map[it2->first]] = min(dp[first_map[it->first]][first_map[it2->first]], dp[first_map[it->first]][first_map[it3->first]] + dp[first_map[it3->first]][first_map[it2->first]]);
				}
			}
		}
		Floyd_done = true;
		//cout << first_map[start] << " " << first_map[end] << endl;
		cout << "the shortest distance is : " << dp[first_map[start]][first_map[end]] << endl;
	}
};
int main()
{
	map<int, Graph> g;
	int graph_id;
	string n;
	while (true)
	{
		cout << "To add new graph enter 1\n\n";
		cout << "To update graph enter 2\n\n";
		cout << "To display graph enter 3\n\n";
		cout << "To display the shortest path between any two town enter use Dijkstera 4\n\n";
		cout << "To display the shortest path between any two town enter use floyed 5\n\n";
		cout << "To exit enter any key(s)\n\n";
		cin >> n;
		system("cls");
		if (n == "1")
		{
			cout << "enter graph id : ";
			cin >> graph_id;
			if (g.find(graph_id) != g.end())
			{
				cout << "the graph exist\n\n";
				continue;
			}
			g[graph_id].Insert_Graph(graph_id);
		}
		else if (n == "2")
		{
			cout << "enter graph id : ";
			cin >> graph_id;
			if (g.find(graph_id) == g.end())
			{
				cout << "the graph doesn't exist\n\n";
				continue;
			}
			g[graph_id].Update_Graph(graph_id);
		}
		else if (n == "3")
		{
			cout << "enter graph id : ";
			cin >> graph_id;
			if (g.find(graph_id) == g.end())
			{
				cout << "the graph doesn't exist\n\n";
				continue;
			}
			g[graph_id].Display_Graph(graph_id);
		}
		else if (n == "4")
		{
			cout << "enter graph id : ";
			cin >> graph_id;
			if (g.find(graph_id) == g.end())
			{
				cout << "the graph doesn't exist\n\n";
				continue;
			}
			if (g[graph_id].get_town_num(graph_id)<2)
			{
				cout << "mynf3sh\n";
				continue;
			}
			string first, second;
			cout << "enter the first town : ";
			cin >> first;
			cout << "enter the second town : ";
			cin >> second;
			g[graph_id].Dijkstera(first, second);
		}
		else if (n == "5") {
			cout << "enter graph id : ";
			cin >> graph_id;
			if (g.find(graph_id) == g.end())
			{
				cout << "the graph doesn't exist\n\n";
				continue;
			}
			if (g[graph_id].get_town_num(graph_id)<2)
			{
				cout << "mynf3sh\n";
				continue;
			}
			string first, second;
			cout << "enter the first town : ";
			cin >> first;
			cout << "enter the second town : ";
			cin >> second;
			g[graph_id].floyed(first, second);
		}
		else
		{
			return 0;
		}
	}
	cin >> n;
	return 0;
}
