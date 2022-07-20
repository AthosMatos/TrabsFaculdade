#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <typeinfo>

using namespace std;

struct GData
{
	map <string, float> connections;
	bool hasKids()
	{
		if (connections.size())return true;
		else return false;
	}
	bool hasKids(string exclude)
	{
		for (auto& c : connections)
		{
			if ((c.first!= exclude))return true;
		}
		return false;
	}
};

class Grafo
{
	map <string, GData*> items;
	
public:
	void add(int amount)
	{
		for (int i = 65, i2 = 0; (i < 90) && (i2 < amount); i++, i2++)
		{
			char a = i;
			string s;
			s.push_back(a);
			add(s);
		}
	}
	bool add(string name = "")
	{
		if (items.find(name) == items.end())
		{
			GData* gdata = new GData;
			string Nname;

			if (!name.length())Nname = "V" + to_string(items.size() + 1);
			else Nname = name;

			items.insert(pair<string, GData*>(Nname, gdata));
			return true;
		}
		else return false;
	}
	bool connect(string from, string to, float connectionWeight,bool directioned = false)
	{
		if (items.find(from) != items.end())
		{
			if (items[from]->connections.find(to) != items[from]->connections.end())
			{
				return true;
			}

			pair<string,float> con;
			con.first = to;
			con.second = connectionWeight;

			items[from]->connections.insert(con);
			
			if (!directioned)connect(to, from, connectionWeight, directioned);
			return true;
		}
		return false;
	}
	bool BrFS(string start, string end)
	{
		if (items.find(start) != items.end() && items.find(end) != items.end())
		{
			vector <string> exclude;
			vector <string> queue;
			string SearchIndex = start;

			while (true)
			{
				cout << SearchIndex << endl;

				if (SearchIndex == end)return true;

				for (auto& i : items[SearchIndex]->connections)
				{
					bool isInside = false;
					for (auto& x : exclude)
					{
						if (x == i.first) { isInside = true; break; }
					}
					if(!isInside)queue.push_back(i.first);
				}

				int index = 0;
				for (auto& q : queue)
				{
					if (q == SearchIndex)
					{
						queue.erase(queue.begin() + index);
						break;
					}
					index++;
				}

				for (int i = 0; i < queue.size(); i++)
				{
					if (items[queue[i]]->hasKids(SearchIndex))
					{
						exclude.push_back(SearchIndex);
						SearchIndex = queue[i];
						break;
					}

					queue.erase(queue.begin() + i);
					i = -1;
				}
			}
		}
		return false;
		
		
	}
	bool UCS(string start, string end)
	{
		if (items.find(start) != items.end() && items.find(end) != items.end())
		{
			vector <string> queue;
			vector <string> exclude;
			string SearchIndex = start;
			string smallerIndex;
			
			queue.push_back(SearchIndex);

			while (true)
			{
				if (SearchIndex == end)return true;

				float smaller = 0;

				bool hasChanged = false;
				for (auto& c : items[SearchIndex]->connections)
				{
					if (!smaller)
					{
						bool isInside = false;
						for (auto& x : exclude)
						{
							if (x == c.first) { isInside = true; break; }
						}
						if (!isInside)
						{
							smallerIndex = c.first;
							smaller = c.second;
							hasChanged = true;
						}
					}
					else
					{
						if (c.second < smaller)
						{
							bool isInside = false;
							for (auto& x : exclude)
							{
								if (x == c.first) { isInside = true; break; }
							}
							if (!isInside)
							{
								smallerIndex = c.first;
								smaller = c.second;
								hasChanged = true;
							}
						}
					}
				}
				if(hasChanged)queue.push_back(smallerIndex);

				if (items[smallerIndex]->hasKids(SearchIndex))
				{
					exclude.push_back(SearchIndex);
					SearchIndex = smallerIndex;
				}
				else
				{
					exclude.push_back(smallerIndex);
					queue.pop_back();
				}
			}
		}
		return false;
	}
};

