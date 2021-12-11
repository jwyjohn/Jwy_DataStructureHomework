/**
 * @file main.cpp
 * @author JwyJohn (1951510@tongji.edu.cn)
 * @brief 头文件中函数及主程序的实现
 * ! 务必使用支持C++11标准的编译器，仅保证在g++ 10.2.0 (GCC) 下编译通过。
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */




















#include "main_header.h"

#define _CRT_SECURE_NO_WARNINGS
#define LIBCMDF_IMPL

using namespace std;

/**
 * @brief 显示输出的内容以及命令的帮助。
 * 
 */

#define PROG_INTRO "                                    \n                                    \n   __   __  _    __      ___ ___    \n /'__`\\/\\ \\/'\\ /'__`\\  /' __` __`\\  \n/\\  __/\\/>  <//\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\ \n\\ \\____\\/\\_/\\_\\ \\__/.\\_\\ \\_\\ \\_\\ \\_\\\n \\/____/\\//\\/_/\\/__/\\/_/\\/_/\\/_/\\/_/\n                                    \n                                    \n\n - Free Software by 1951510 JiangWenyuan \nNov 2021\n====================================\n! This is a program to manage exam students.\n! Can also save student info to a file.\n! Input command 'i insert_position No. name gender age subject' to insert a student.\n! Input command 'f No.' to find info about a student.\n! Input command 'd No.' to delete a student.\n! Input command 'm No. new_No. new_name new_gender new_age new_subject' to modify student info.\n! Input command 's' to show statistcal data.\n! Input command 'l' to list all students.\n! Use 'w' WITH CAUTION to save data to student_data.txt because it can overwrite existing file.\n"
#define INSERT_HELP "Insert a new candidate to the table.\n Format 'i insert_position No name gender age subject'\n"
#define DEL_HELP "Delete a candidate from the table.\n Format 'd No'\n"
#define LIST_HELP "List all the students.\n"
#define FIND_HELP "Find a candidate in the table.\n Format 'f No'\n"
#define MODI_HELP "Modify a candidate in the table.\n Format 'm No No_nww name_new gender_new age_new subject_new'\n"
#define STAT_HELP "Show statistic data.\n Format 's'\n"
#define SAVE_HELP "Save data.\n Format 'w'\n"

/**
 * @brief 头文件中函数的实现
 * 
 */

int clear_link(exam_candidate *head)
{
	// 清空链表
	if (head->next == nullptr)
	{
		delete head;
	}
	else
	{
		clear_link(head->next); // 递归删除节点
	};
	return 0;
};

int init_link()
{
	// 初始化链表
	clear_link(head);
	head = new exam_candidate;
	head->No = -1;
};

int show_single_candidate(exam_candidate *candidate)
{
	// 打印单个人员信息
	if (candidate == NULL)
		return 1;
	cout << endl;
	cout
		<< "  [" << candidate->No << "] "
		<< "  Name: " << candidate->name
		<< "  Gender: " << candidate->Gender
		<< "  Age: " << candidate->Age
		<< "  Subject: " << candidate->subject << endl;
	return 0;
};

exam_candidate *find_candidate(int no)
{
	// 遍历链表以查找特定人员
	exam_candidate *ptr = head;
	if (no == 0)
		return ptr;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->No == no)
			return ptr;
	};
	return NULL;
};

int insert_candidate_after(int no, exam_candidate *candidate)
{
	// 在某编号后插入人员
	exam_candidate *insert_position = find_candidate(no);
	if (insert_position == NULL)
		return 0;
	if (insert_position->next != NULL)
	{
		exam_candidate *tmp = insert_position->next;
		insert_position->next = candidate;
		candidate->pre = insert_position;
		candidate->next = tmp;
		tmp->pre = candidate; // 经典的链表插入操作
	}
	else
	{
		insert_position->next = candidate;
		candidate->pre = insert_position;
	};
	return 1;
};

int remove_candidate(int no)
{
	// 移除人员
	exam_candidate *remove_position = find_candidate(no);
	if (remove_position == NULL)
		return 1;
	if (remove_position->next != NULL)
	{
		remove_position->pre->next = remove_position->next;
		remove_position->next->pre = remove_position->pre;
		delete remove_position;
	}
	else
	{
		remove_position->pre->next = NULL;
		delete remove_position;
	};
	// 经典的链表删除操作
	return 0;
};

bool isNumber(const string &str)
{
	/**
	 * @brief 判断字符串是否时纯数字，用于检测是否为合法输入。
	 * 
	 * @param str 
	 */
	for (char const &c : str)
	{
		if (std::isdigit(c) == 0)
			return false;
	}
	return true;
};

class Exam
{
	// 用类对这些操作进行包装
private:
public:
	exam_candidate *head;
	int init_link()
	{
		clear_link(head);
		head = new exam_candidate;
		head->No = -1;
	};
	Exam() { head = new exam_candidate; };
	int clear_link(exam_candidate *head)
	{
		if (head->next == nullptr)
		{
			delete head;
		}
		else
		{
			clear_link(head->next);
		};
		return 0;
	};
	int show_single_candidate(exam_candidate *candidate)
	{
		if (candidate == NULL)
			return 1;
		cout << endl;
		cout
			<< "  [" << candidate->No << "] "
			<< "  Name: " << candidate->name
			<< "  Gender: " << candidate->Gender
			<< "  Age: " << candidate->Age
			<< "  Subject: " << candidate->subject << endl;
		return 0;
	};
	exam_candidate *find_candidate(int no)
	{
		exam_candidate *ptr = head;
		if (no == 0)
			return ptr;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
			if (ptr->No == no)
				return ptr;
		};
		return NULL;
	};

	int insert_candidate_after(int no, exam_candidate *candidate)
	{
		exam_candidate *insert_position = find_candidate(no);
		if (insert_position == NULL)
			return 0;
		if (insert_position->next != NULL)
		{
			exam_candidate *tmp = insert_position->next;
			insert_position->next = candidate;
			candidate->pre = insert_position;
			candidate->next = tmp;
			tmp->pre = candidate;
		}
		else
		{
			insert_position->next = candidate;
			candidate->pre = insert_position;
		};
		return 1;
	};

	int remove_candidate(int no)
	{
		exam_candidate *remove_position = find_candidate(no);
		if (remove_position == NULL)
			return 1;
		if (remove_position->next != NULL)
		{
			remove_position->pre->next = remove_position->next;
			remove_position->next->pre = remove_position->pre;
			delete remove_position;
		}
		else
		{
			remove_position->pre->next = NULL;
			delete remove_position;
		};
		return 0;
	};
};

Exam E;

static CMDF_RETURN insert_student(cmdf_arglist *arglist)
{
	/**
	 * @brief 过滤用户输入，并按需调用函数，下面几个函数同样是这个作用。
	 * 
	 */
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
		E.insert_candidate_after(0, tmp);
	}
	else
	{
		E.insert_candidate_after(stoi(arglist->args[0]), tmp);
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
	exam_candidate *res = E.find_candidate(stoi(arglist->args[0]));
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
	if (E.head->next == NULL)
	{
		cout << " [Error] Table empty." << endl;
		return CMDF_OK;
	};
	exam_candidate *ptr = E.head->next;
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
	exam_candidate *res = E.find_candidate(stoi(arglist->args[0]));
	if (res = NULL)
	{
		cout << " [Error] Candidate not found." << endl;
		return CMDF_OK;
	}
	else
	{
		E.remove_candidate(stoi(arglist->args[0]));
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
	exam_candidate *tmp = E.find_candidate(stoi(arglist->args[0]));
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
	// 统计人员信息
	if (E.head->next == NULL)
	{
		cout << " [Error] Table empty." << endl;
		return CMDF_OK;
	};
	map<int, int> age_count;
	map<string, int> gender_count, subject_count;
	exam_candidate *ptr = E.head->next;
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
	// 将人员信息保存到文件
	if (E.head->next == NULL)
	{
		cout << " [Error] Table empty." << endl;
		return CMDF_OK;
	};
	ofstream out("student_data.txt");
	exam_candidate *ptr = E.head->next;
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
测试数据：
i 1 25 jwy M 21 SE
i 25 19 zkx F 21 AC
i 25 2 ly M 21 SE
i 25 9 dyy F 21 SE
l
*/