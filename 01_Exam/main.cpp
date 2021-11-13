#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stack>
#include <fstream>
#include <sstream>

#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

#define PROG_INTRO "                                    \n                                    \n   __   __  _    __      ___ ___    \n /'__`\\/\\ \\/'\\ /'__`\\  /' __` __`\\  \n/\\  __/\\/>  <//\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\ \n\\ \\____\\/\\_/\\_\\ \\__/.\\_\\ \\_\\ \\_\\ \\_\\\n \\/____/\\//\\/_/\\/__/\\/_/\\/_/\\/_/\\/_/\n                                    \n                                    \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n====================================\n! This is a program to manage exam students.\n! Can also save student info to a file.\n! Input command 'i insert_position No. name gender age subject' to insert a student.\n! Input command 'f No.' to find info about a student.\n! Input command 'd No.' to delete a student.\n! Input command 'm No. new_No. new_name new_gender new_age new_subject' to modify student info.\n! Input command 's' to show statistcal data.\n! Input command 'l' to list all students.\n! Use 'w' WITH CAUTION to save data to student_data.txt because it can overwrite existing file.\n"
#define INSERT_HELP "Insert a new candidate to the table.\n Format 'i insert_position No name gender age subject'\n"
#define DEL_HELP "Delete a candidate from the table.\n Format 'd No'\n"
#define LIST_HELP "List all the students.\n"
#define FIND_HELP "Find a candidate in the table.\n Format 'f No'\n"
#define MODI_HELP "Modify a candidate in the table.\n Format 'm No No_nww name_new gender_new age_new subject_new'\n"
#define STAT_HELP "Show statistic data.\n Format 's'\n"
#define SAVE_HELP "Save data.\n Format 'w'\n"
using namespace std;

bool isNumber(const string &str)
{
	for (char const &c : str)
	{
		if (std::isdigit(c) == 0)
			return false;
	}
	return true;
}

static CMDF_RETURN insert_student(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide info like 'i insert_position No name gender age subject'" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 6)
	{
		cout << " [Sytax Error] Please provide info like 'i insert_position No name gender age subject'" << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[0]))
	{
		cout << " [Sytax Error] insert_position must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[0]) <= 0)
	{
		cout << " [Sytax Error] insert_position must > 0." << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[1]))
	{
		cout << " [Sytax Error] No. must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[1]) <= 0)
	{
		cout << " [Sytax Error] No. must > 0." << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[4]))
	{
		cout << " [Sytax Error] Age must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[4]) <= 0)
	{
		cout << " [Sytax Error] Age must > 0." << endl;
		return CMDF_OK;
	};
	if (find_candidate(stoi(arglist->args[0])) == NULL && head->next != NULL)
	{
		cout << " [Error] Insert position not in list." << endl;
		return CMDF_OK;
	};
	if (find_candidate(stoi(arglist->args[1])) != NULL)
	{
		cout << " [Error] No. already in list." << endl;
		return CMDF_OK;
	};
	if (!(strcmp(arglist->args[3], "M") == 0 || strcmp(arglist->args[3], "F") == 0))
	{
		cout << " [Error] Gneder must be M (Male) or F (Female)." << endl;
		return CMDF_OK;
	};
	exam_candidate *tmp = new exam_candidate;
	tmp->No = stoi(arglist->args[1]);
	tmp->name = arglist->args[2];
	tmp->Gender = arglist->args[3];
	tmp->Age = stoi(arglist->args[4]);
	tmp->subject = arglist->args[5];
	if (head->next == NULL)
	{
		insert_candidate_after(0, tmp);
	}
	else
	{
		insert_candidate_after(stoi(arglist->args[0]), tmp);
	};

	return CMDF_OK;
};

static CMDF_RETURN find_student(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide info like 'f No'" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide info like 'f No'" << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[0]))
	{
		cout << " [Sytax Error] No. must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[0]) <= 0)
	{
		cout << " [Sytax Error] No. must > 0." << endl;
		return CMDF_OK;
	};
	exam_candidate *res = find_candidate(stoi(arglist->args[0]));
	if (res == NULL)
	{
		cout << " [Error] Candidate not found." << endl;
		return CMDF_OK;
	}
	else
	{
		exam_candidate *ptr = res;
		cout << " No." << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Subject" << '\t' << endl;
		cout << " [" << ptr->No << "]" << '\t'
			 << ptr->name << '\t'
			 << ptr->Gender << '\t'
			 << ptr->Age << '\t'
			 << ptr->subject << '\t' << endl;
	};
	return CMDF_OK;
};

static CMDF_RETURN list_student(cmdf_arglist *arglist)
{
	if (head->next == NULL)
	{
		cout << " [Error] Table empty." << endl;
		return CMDF_OK;
	};
	exam_candidate *ptr = head->next;
	cout << " No." << '\t' << "Name" << '\t' << "Gender" << '\t' << "Age" << '\t' << "Subject" << '\t' << endl;
	while (ptr != NULL)
	{
		cout << " [" << ptr->No << "]" << '\t'
			 << ptr->name << '\t'
			 << ptr->Gender << '\t'
			 << ptr->Age << '\t'
			 << ptr->subject << '\t' << endl;
		ptr = ptr->next;
	}
	return CMDF_OK;
};

static CMDF_RETURN remove_student(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide info like 'd No'" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 1)
	{
		cout << " [Sytax Error] Please provide info like 'd No'" << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[0]))
	{
		cout << " [Sytax Error] No. must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[0]) <= 0)
	{
		cout << " [Sytax Error] No. must > 0." << endl;
		return CMDF_OK;
	};
	exam_candidate *res = find_candidate(stoi(arglist->args[0]));
	if (res = NULL)
	{
		cout << " [Error] Candidate not found." << endl;
		return CMDF_OK;
	}
	else
	{
		remove_candidate(stoi(arglist->args[0]));
	};
	return CMDF_OK;
};

static CMDF_RETURN modify_student(cmdf_arglist *arglist)
{
	if (!arglist)
	{
		cout << " [Sytax Error] No arguments provided!\n [Tip] Please provide info like 'm No No_nww name_new gender_new age_new subject_new'" << endl;
		return CMDF_OK;
	};
	if (arglist->count != 6)
	{
		cout << " [Sytax Error] Please provide info like 'm No No_nww name_new gender_new age_new subject_new'" << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[0]))
	{
		cout << " [Sytax Error] No. must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[0]) <= 0)
	{
		cout << " [Sytax Error] No. must > 0." << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[1]))
	{
		cout << " [Sytax Error] No. must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[1]) <= 0)
	{
		cout << " [Sytax Error] No. must > 0." << endl;
		return CMDF_OK;
	};
	if (!isNumber(arglist->args[4]))
	{
		cout << " [Sytax Error] Age must be an intiger." << endl;
		return CMDF_OK;
	};
	if (stoi(arglist->args[4]) <= 0)
	{
		cout << " [Sytax Error] Age must > 0." << endl;
		return CMDF_OK;
	};
	if (find_candidate(stoi(arglist->args[0])) == NULL)
	{
		cout << " [Error] The student to modify is not in list." << endl;
		return CMDF_OK;
	};
	if (find_candidate(stoi(arglist->args[1])) != NULL && (arglist->args[1] != arglist->args[0]))
	{
		cout << " [Error] Another No. already in list." << endl;
		return CMDF_OK;
	};
	if (!(strcmp(arglist->args[3], "M") == 0 || strcmp(arglist->args[3], "F") == 0))
	{
		cout << " [Error] Gneder must be M (Male) or F (Female)." << endl;
		return CMDF_OK;
	};
	exam_candidate *tmp = find_candidate(stoi(arglist->args[0]));
	tmp->No = stoi(arglist->args[1]);
	tmp->name = arglist->args[2];
	tmp->Gender = arglist->args[3];
	tmp->Age = stoi(arglist->args[4]);
	tmp->subject = arglist->args[5];
	cout << " [Done] Modified candidate No. " << arglist->args[0] << ". " << endl;
	return CMDF_OK;
};

static CMDF_RETURN stat_student(cmdf_arglist *arglist)
{
	if (head->next == NULL)
	{
		cout << " [Error] Table empty." << endl;
		return CMDF_OK;
	};
	map<int, int> age_count;
	map<string, int> gender_count, subject_count;
	exam_candidate *ptr = head->next;
	while (ptr != NULL)
	{
		if (age_count.find(ptr->Age) != age_count.end())
		{
			age_count[ptr->Age]++;
		}
		else
		{
			age_count.insert({ptr->Age, 1});
		};
		if (gender_count.find(ptr->Gender) != gender_count.end())
		{
			gender_count[ptr->Gender]++;
		}
		else
		{
			gender_count.insert({ptr->Gender, 1});
		};
		if (subject_count.find(ptr->subject) != subject_count.end())
		{
			subject_count[ptr->subject]++;
		}
		else
		{
			subject_count.insert({ptr->subject, 1});
		};
		ptr = ptr->next;
	};
	cout << " [Age Stat]" << endl;
	for (auto iter = age_count.begin(); iter != age_count.end(); iter++)
	{
		cout << "  - " << iter->first << " : " << iter->second << endl;
	};
	cout << " [Gender Stat]" << endl;
	for (auto iter = gender_count.begin(); iter != gender_count.end(); iter++)
	{
		cout << "  - " << iter->first << " : " << iter->second << endl;
	};
	cout << " [Subject Stat]" << endl;
	for (auto iter = subject_count.begin(); iter != subject_count.end(); iter++)
	{
		cout << "  - " << iter->first << " : " << iter->second << endl;
	};
	return CMDF_OK;
};

static CMDF_RETURN save_student(cmdf_arglist *arglist)
{
	if (head->next == NULL)
	{
		cout << " [Error] Table empty." << endl;
		return CMDF_OK;
	};
	ofstream out("student_data.txt");
	exam_candidate *ptr = head->next;
	out << "i " << 1 << ' ';
	if (out.is_open())
	{
		while (ptr != NULL)
		{
			out << ptr->No << ' '
				<< ptr->name << ' '
				<< ptr->Gender << ' '
				<< ptr->Age << ' '
				<< ptr->subject << ' ' << endl;
			if (ptr->next != NULL)
				out << "i " << ptr->No << ' ';
			ptr = ptr->next;
		}
		out.close();
	}
	return CMDF_OK;
};

int main()
{
	head = new exam_candidate;
	cmdf_init("network> ", PROG_INTRO, NULL, NULL, 0, 1);

	/* Register our custom commands */
	cmdf_register_command(insert_student, "i", INSERT_HELP);
	cmdf_register_command(find_student, "f", FIND_HELP);
	cmdf_register_command(list_student, "l", LIST_HELP);
	cmdf_register_command(remove_student, "d", DEL_HELP);
	cmdf_register_command(modify_student, "m", DEL_HELP);
	cmdf_register_command(stat_student, "s", STAT_HELP);
	cmdf_register_command(save_student, "w", SAVE_HELP);

	cmdf_commandloop();
	return 0;
}

/*
i 1 25 jwy M 21 SE
i 25 19 zkx F 21 AC
i 25 2 ly M 21 SE
i 25 9 dyy F 21 SE
l
*/