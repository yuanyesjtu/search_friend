#include<iostream>
#include<vector>
using namespace std;

struct friends
{
	// 定义结构体
	int idx = 0;
	int weight = 0;
};

bool my_compare(int idx, vector<int>& searched_idx)
{
	// 判断当前节点是否已经遍历过
	for (int row = 0; row < searched_idx.size(); row++)
	{
		if (idx == searched_idx[row])
		{
			return false;
		}
	}
	return true;
}

void sortfun(vector<friends> &fri_vec)
{
	friends fri_temp;
	for (int row = 0; row < fri_vec.size() - 1; row++)
	{
		for (int col = 0; col < fri_vec.size() - 1 - row; col++)
		{
			if ((fri_vec[col].idx < fri_vec[col + 1].idx) || 
				(fri_vec[col].idx = fri_vec[col + 1].idx && fri_vec[col].weight < fri_vec[col + 1].weight))
			{
				fri_temp = fri_vec[col];
				fri_vec[col] = fri_vec[col + 1];
				fri_vec[col + 1] = fri_temp;
			}
		}
	}

	return;
}



bool search_friend(int** r, int m, vector<friends>& fri_vec1, vector<int>& searched_idx)
{
	// 寻找friends_idx列表中的人的好友
	// r是关系矩阵（m*m），m是总人数，friends_idx是好友编号以及熟悉程度，searched_idx是已经搜索过的人
	// friends_idx是vector，其内部又包含两个vector，第一个是编号，第二个是权重

	vector<friends> fri_vec2;
	for (int row = 0; row < fri_vec1.size(); row++)
	{
		for (int col = 0; col < m; col++)
		{
			if (r[fri_vec1[row].idx][col] > 0 && my_compare(col, searched_idx))
			{
				friends fri;
				fri.idx = col;
				fri.weight = fri_vec1[row].weight + r[fri_vec1[row].idx][col];
				fri_vec2.push_back(fri);
			}
		}
	}

	// 检查是否找到好友
	if (fri_vec2.size() == 0)
	{
		fri_vec1.clear();
		friends fri;
		fri.idx = -1;
		fri.weight = -1;
		fri_vec1.push_back(fri);
		return false;
	}
		
	// 按编号从大到小排序
	sortfun(fri_vec2);

	// 删除编号相同但权重较小的点
	vector<friends> fri_vec3;
	bool flag = true;
	for (int row = 0; row < fri_vec2.size(); row++)
	{
		flag = true;
		for (int col = 0; col < fri_vec3.size(); col++)
		{
			if (fri_vec2[row].idx == fri_vec3[col].idx)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			friends fri;
			fri.idx = fri_vec2[row].idx;
			fri.weight = fri_vec2[row].weight;
			fri_vec3.push_back(fri);
			
			searched_idx.push_back(fri_vec2[row].idx);
		}
	}

	fri_vec1 = fri_vec3;
	return true;
}

int main()
{
	int T; //测试组数
	cin >> T;

	vector<vector<friends>> fri_vec_output;
	
	while (T--)
	{
		int m, i, n;
		cin >> m >> i >> n; //总共m个人，寻找第i个人的n度好友

		int k;
		cin >> k; // 总共有k对关系，由接下来输入的k个三元组决定

		int** r = new int* [m]; // 动态分配二维数组r，用于存储m个人的关系
		for (int row = 0; row < m; row++)
			r[row] = new int[m];

		while (k--)
		{
			int p, q, w;
			cin >> p >> q >> w; // 第p个人与第q个人熟悉，熟悉程度为w(0<=w<=10)
			r[p][q] = w;
			r[q][p] = w;
		}

		friends fri;
		fri.idx = i;
		fri.weight = 0;
		vector<friends> fri_vec1;
		fri_vec1.push_back(fri);

		vector<int> searched_idx;
		searched_idx.push_back(i);

		while (n--) // 循环寻找第i个人的n度好友
			if (!search_friend(r, m, fri_vec1, searched_idx))
				break;
		fri_vec_output.push_back(fri_vec1);
	}

	for (int row = 0; row < fri_vec_output.size(); row++)
	{
		for (int col = 0; col < fri_vec_output[row].size(); col++)
			cout << fri_vec_output[row][col].idx << " ";

		cout << endl;

		for (int col = 0; col < fri_vec_output[row].size(); col++)
			cout << fri_vec_output[row][col].weight << " ";

		cout << endl << endl;
	}

	system("pause");
	return 0;
}