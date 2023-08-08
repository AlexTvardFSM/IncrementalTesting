#include <iostream>
#include <fstream>
#include <string>
#include "FSMTimeout.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <sstream> 

using namespace std;

bool main(int argc, char* argv[])
{
	if (argc < 3)
	{
		return 0;
	}
	else
	{
		FSMTimeout TFSM;
		ifstream in(argv[1]);
		TFSM.In(in);
		in.close();

		int c = 0, num = 0, num_of_seq = 0, t = 0;
		int * arr = new int[100000];
		int * arr_all = new int[100000];
		ifstream inptest(argv[2]);
		string ts_str;
		while (getline(inptest, ts_str))
		{
			arr[num] = 0;
			arr_all[num] = 0;
			istringstream ss(ts_str);
			while (ss >> c)
			{
				if (c < TFSM.NumOfInputs())
				{
					arr[num]++;
				}
				arr_all[num]++;
			}
			num++;
		}
		inptest.close();
		num_of_seq += num;
		inptest.open(argv[2]);
		time_sequence* test = new time_sequence[num];
		for (unsigned int i = 0; i < num; i++)
		{
			test[i].length = arr[i];
			test[i].sym = new unsigned int[test[i].length];
			test[i].time = new unsigned int[test[i].length];
			int k = 0;
			for (int l = 0; l < arr_all[i]; l++)
			{
				inptest >> c;
				if (c == TFSM.NumOfInputs()) t++;
				else
				{
					test[i].sym[k] = c;
					test[i].time[k] = t;
					t = 0;
					k++;
				}

			}
		}

		string str = argv[2];
		str.erase(str.size() - 4, str.size());
		str.append("_res.txt");
		if (argc == 4)
		{
			LongVector trans_f(TFSM.NumOfTransitions());
			LongVector time_f(TFSM.NumOfStates());
			ifstream in_mod(argv[3]);
			string mod_str;
			getline(in_mod, mod_str);
			istringstream ss1(mod_str);
			while (ss1 >> c)
			{
				trans_f.set(c);
			}
			getline(in_mod, mod_str);
			istringstream ss2(mod_str);
			while (ss2 >> c)
			{
				time_f.set(c);
			}

			
			ofstream out(str);
			for (unsigned int i = 0; i < num; i++)
			{
				if (TFSM.coverage(test[i], trans_f, time_f))
				{
					for (int j = 0; j < test[i].length; j++)
						out << "(" << test[i].sym[j] << ", " << test[i].time[j] << ") ";
					out << endl;
				}
			}

			out.close();
		}
		else
		{
			ofstream out(str);
			for (unsigned int i = 0; i < num; i++)
			{
				for (int j = 0; j < test[i].length; j++)
					out << "(" << test[i].sym[j] << ", " << test[i].time[j] << ") ";
				out << endl;
			}
			out.close();
		}
		return 1;
	}
}