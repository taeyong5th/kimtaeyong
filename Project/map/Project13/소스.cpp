#include <iostream>
#include <queue>
#include <map>

using namespace std;

class Astar
{
private:
	int f, g, h; 

public:
	Astar() { f = g = h = 0; };
	Astar(int g, int h) { this->f = g + h; this->g = g; this->h = h; };
	~Astar() {};
	void print() const
	{
		cout << f << endl;
	};
	bool operator > (const Astar& r) const { return f > r.f; }
	bool operator < (const Astar& r) const { return f < r.f; }
};

bool compare(int a, int b)
{
	return a < b;
}


bool compareAstar(pair<int, Astar> a, pair<int, Astar> b)
{
	return a.second < b.second;
}

int main()
{
	map<int, Astar> mm;
	mm.insert(make_pair(1, Astar(2, 25)));
	mm.insert(make_pair(3, Astar(4, 15)));
	mm.insert(make_pair(2, Astar(12, 5)));
	
	for (auto iter = mm.begin(); iter != mm.end(); ++iter)
	{
		//cout << iter->first << ", " << iter->second << endl;
		cout << iter->first << ", ";
		iter->second.print();
	}
	
	vector<pair<int, Astar>> v(mm.begin(), mm.end());
	sort(v.begin(), v.end(), compareAstar);
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i].first << " ";
		v[i].second.print();
	}
	cout << endl;

	return 0;
}