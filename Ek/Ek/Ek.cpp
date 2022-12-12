
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
const int INF=1e9;

class Edge
{
public:

	int from;
	int to;
	int f;
	int c;
	Edge(int from = 0, int to = 0, int f = 0, int c = 0) :from(from), to(to), f(f), c(c) {}
		
		

	int c1()
	{
		return c - f;
	}

};
vector <Edge> edges; //список ребер
vector <vector <int>> gr; //прямые и обратные ребра


void add(int u, int v, int c)
{
	gr[u].push_back(edges.size());
	edges.push_back(Edge(u, v, 0, c));
	gr[v].push_back(edges.size()); //обратное ребро
		edges.push_back(Edge(u, v, 0, c));
}


void push(int i, int f)
{
	edges[i].f += f;
		edges[i ^ 1].f -= f;
}

vector<bool> used;
int n;
int ans = 0;
bool bfs(int n)
{
	vector <int>dist(n, INF);
	vector<int> p(n, -1); 
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (auto& i : gr[v])
		{
			Edge e = edges[i];
			if (dist[e.to] > dist[v] + 1 && e.c1() > 0)
			{
				dist[e.to] = dist[v] + 1;
				q.push(e.to);
				p[e.to] = i;
			}
		}
	}
	if (dist[n - 1] == INF)
	{
		return false;
	}
	int v = n - 1;
	int f = INF;
	while (v != 0)
	{
		f = min(f, edges[p[v]].c1());
		v = edges[p[v]].from;
	}
	ans += f;
	v = n - 1;
	while (v != 0)
	{
		push(p[v],f);
		v = edges[p[v]].from;
	}
	return true;


}

int main()
{
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);
	//cout.tie(0);
	//cout.setf(ios::fixed);
	//cout.precision(10);
	int n, m;
	cin >> n >> m;
	gr.resize(n);
	used.resize(n, 0);
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		add(u - 1, v - 1, w);
	}
	while (bfs(n)) {}
	cout << ans << endl;
}