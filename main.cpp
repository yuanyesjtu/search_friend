#include<iostream>
#include<vector>
using namespace std;

struct friends
{
	// ����ṹ��
	int idx = 0;
	int weight = 0;
};

bool my_compare(int idx, vector<int>& searched_idx)
{
	// �жϵ�ǰ�ڵ��Ƿ��Ѿ�������
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
	// Ѱ��friends_idx�б��е��˵ĺ���
	// r�ǹ�ϵ����m*m����m����������friends_idx�Ǻ��ѱ���Լ���Ϥ�̶ȣ�searched_idx���Ѿ�����������
	// friends_idx��vector�����ڲ��ְ�������vector����һ���Ǳ�ţ��ڶ�����Ȩ��

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

	// ����Ƿ��ҵ�����
	if (fri_vec2.size() == 0)
	{
		fri_vec1.clear();
		friends fri;
		fri.idx = -1;
		fri.weight = -1;
		fri_vec1.push_back(fri);
		return false;
	}
		
	// ����ŴӴ�С����
	sortfun(fri_vec2);

	// ɾ�������ͬ��Ȩ�ؽ�С�ĵ�
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
	int T; //��������
	cin >> T;

	vector<vector<friends>> fri_vec_output;
	
	while (T--)
	{
		int m, i, n;
		cin >> m >> i >> n; //�ܹ�m���ˣ�Ѱ�ҵ�i���˵�n�Ⱥ���

		int k;
		cin >> k; // �ܹ���k�Թ�ϵ���ɽ����������k����Ԫ�����

		int** r = new int* [m]; // ��̬�����ά����r�����ڴ洢m���˵Ĺ�ϵ
		for (int row = 0; row < m; row++)
			r[row] = new int[m];

		while (k--)
		{
			int p, q, w;
			cin >> p >> q >> w; // ��p�������q������Ϥ����Ϥ�̶�Ϊw(0<=w<=10)
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

		while (n--) // ѭ��Ѱ�ҵ�i���˵�n�Ⱥ���
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