#include "stu.h"

tea_t teachers[MAX_TEACHERS];
stu_t students[MAX_STUDENTS];
int tea_count = 0;
int stu_count = 0;
const char *subjects[MAX_SUBJECTS] = {"语文", "数学", "外语"};

//清空缓冲区
void clear_input_buffer(void)
{
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}


//主菜单
void main_menu(void)
{
	int choice;

	do
	{
		system("clear");
		printf("*********学生成绩管理系统***********\n");
		printf("1.教师登录\n");
		printf("2.学生登录\n");
		printf("0.退出系统\n");
		printf("************************************\n");
		printf("请选择登录方式: ");
		if(scanf("%d", &choice) != 1)
		{
			printf("输入有误，请输入0到2的整数!\n");
			clear_input_buffer();
			sleep(1);
			continue;
		}
		clear_input_buffer();

		switch(choice)
		{
			case 1: 
				tea_login();//进入教师登录流程
				break;
			case 2: 
				stu_login();//进入学生登录流程
				break;
			case 0: printf("感谢使用，再见!\n"); break;
			default: 
				printf("无此功能，请重新输入!\n"); 
				sleep(1);
				break;
		}

	}while(choice != 0);
}


//从终端获取用户名和密码
void get_data(char *username, char *passwd, const char *user)
{
	printf("%s: ", user);
	scanf("%19s", username);
	clear_input_buffer();

	printf("密码: ");
	scanf("%19s", passwd);
	clear_input_buffer();
}


//教师登录
void tea_login(void)
{
	char username[20];
	char passwd[20];
	int is_teacher = 0;

	while(1)
	{
		//从终端获取用户名和密码
		get_data(username, passwd, "教师");

		//优先从文件验证
		if(tea_count > 0)
		{
			for(int i = 0; i < tea_count; i++)
			{
				if(strcmp(username, teachers[i].username) == 0 &&
						strcmp(passwd, teachers[i].passwd) == 0)
				{
					is_teacher = 1;
					break;
				}
			}
		}
		else//如果文件中没有内容，使用默认账号和密码
		{
			if(strcmp(username, "admin") == 0 &&
					strcmp(passwd, "1") == 0)
				is_teacher = 1;
		}
		if(is_teacher)
		{
			printf("教师 %s 登录成功!\n", username);
			tea_menu(username);//进入教师子菜单
			break;
		}

		printf("账号或密码错误，请重新输入!\n\n");
	}
}

//教师子菜单
void tea_menu(const char *username)
{
	int choice;

	do
	{
		//system("clear");
		printf("***********学生成绩管理系统(教师模式)*************\n");
		printf("1.管理学生(添加/删除/修改/查询)\n");
		printf("2.显示所有学生\n");
		printf("3.成绩排名\n");
		printf("4.保存数据到文件\n");
		printf("0.返回上一级菜单\n");
		printf("*************************************************\n");
		printf("请选择: ");

		if(scanf("%d", &choice) != 1)
		{
			printf("输入有误，请输入一个0到5的整数!\n");
			clear_input_buffer();
			sleep(1);
			continue;
		}
		clear_input_buffer();

		switch(choice)
		{
			case 1: manage_stu(); break;
			case 2: show_all_stu_by_default(); break;
			case 3: rank_menu(); break;
			case 4: save_stu_to_file(); break;
			case 0: 
				printf("教师 %s 已退出!\n", username);
				//sleep(1);
				break;
			default:
				printf("无此功能，请重新输入!\n");
				//sleep(1);
				break;
		}

	}while(choice != 0);
}

//查找学生，如果找到返回索引，未找到返回-1
int find_stu_by_id(long long id)
{
	for(int i = 0; i < stu_count; i++)
	{
		if(id == students[i].id)
			return i;
	}

	return -1;
}

//学生登录
void stu_login(void)
{
	char username[20];
	char passwd[20];
	long long stu_id;
	int stu_index;

	while(1)
	{
		//从终端获取学生的账号和密码
		get_data(username, passwd, "学生");

		if(strcmp(username, passwd) == 0)
		{
			sscanf(username, "%lld", &stu_id);	
			stu_index = find_stu_by_id(stu_id);

			if(stu_index != -1)
			{
				printf("学生 %s 登录成功!\n", username);
				stu_menu(username);//进入学生子菜单
				break;
			}
			else
			{
				if(stu_count == 0)
				{
					printf("暂无学生数据! 已返回上一级菜单!\n\n");
					sleep(1);
					return;
				}
				else
					printf("查无此人，请联系老师!\n\n");
			}
		}
		else
			printf("账号或密码错误，请重新输入!\n\n");
	}
}


//学生子菜单
void stu_menu(const char *username)
{
	int choice;

	do
	{
		system("clear");
		printf("************学生个人中心***********\n");
		printf("1.查询信息\n");
		printf("0.返回上一级菜单\n");
		printf("***********************************\n");
		printf("请选择: ");

		if(scanf("%d", &choice) != 1)
		{
			printf("输入有误，请输入0到1的整数!\n");
			clear_input_buffer();
			sleep(1);
			continue;
		}
		clear_input_buffer();
		switch(choice)
		{
			case 1: break;
			case 0:
				printf("学生 %s 已退出!\n", username);
				sleep(1);
				break;
			default:
				printf("无此功能，请重新输入!\n");
				sleep(1);
				break;
		}
	}while(choice != 0);
}


// --- 教师功能 ---
//管理学生
void manage_stu(void)
{
	int choice;
	do
	{
		//system("clear");
		printf("***************管理学生**************\n");
		printf("1.添加学生\n");
		printf("2.删除学生\n");
		printf("3.修改学生\n");
		printf("4.查询学生\n");
		printf("0.返回上一级菜单\n");
		printf("*************************************\n");
		printf("请选择: ");
		if(scanf("%d", &choice) != 1)
		{
			printf("输入有误，请输入一个0到4的整数!\n");
			clear_input_buffer();
			sleep(1);
			continue;
		}
		clear_input_buffer();

		switch(choice)
		{
			case 1: add_stu(); break;
			case 2: del_stu(); break;
			case 3: modify_stu(); break;
			case 4: search_stu(); break;
			case 0: 
				printf("返回上一级菜单!\n");
				//sleep(1);
				break;
			default: 
				printf("无此功能，请重新输入!\n");
				//sleep(1);
				break;
		}
	}while(choice != 0);
}

//添加学生
void add_stu(void)
{
	printf("\n------- 添加学生 ---------\n");
	if(stu_count >= MAX_STUDENTS)
	{
		printf("学生数量已到达上限!\n");
		return;
	}
	long long id;

	printf("请输入学号: ");
	if(scanf("%lld", &id) != 1)
	{
		printf("输入有误，请输入一个整数作为学号: ");
		clear_input_buffer();
	}
	clear_input_buffer();

	//检查学号是否已存在
	if(find_stu_by_id(id) != -1)
	{
		printf("错误: 学号为 %lld 的学生已存在! 请使用其他学号!\n\n", id);
		return;
	}

	students[stu_count].id = id;
	sprintf(students[stu_count].passwd, "%lld", id);//默认密码和id一致

	printf("请输入姓名(无空格): ");
	scanf("%19s", students[stu_count].name);
	clear_input_buffer();
	printf("请输入各科成绩(0-100): \n");
	for(int i = 0; i < MAX_SUBJECTS; i++)
	{
		printf("请输入 %s 成绩: ", subjects[i]);
		float score;
		while(scanf("%f", &score) != 1 || score < 0 || score > 100)
		{
			printf("输入错误，请输入一个0到100的数字!\n");
			clear_input_buffer();
		}
		clear_input_buffer();

		students[stu_count].scores[i] = score;
	}
	stu_count++;
	printf("添加成功! 默认密码和账号相同\n\n");
}

//删除学生:根据学号删除
void del_stu(void)
{
	long long id;

	printf("\n-------- 删除学生 --------\n");
	if(stu_count == 0)
	{
		printf("当前没有学生可删除!\n");
		return;
	}

	printf("请输入要删除学生的学号: ");
	while(scanf("%lld", &id) != 1) 
	{
		printf("输入无效，请输入一个整数作为学号!\n");
		clear_input_buffer();
	}
	clear_input_buffer();

	int index = find_stu_by_id(id);
	if(index == -1)
	{
		printf("未找到学号 %lld 的学生!\n\n", id);	
		return;
	}
	//覆盖的方式删除学生
	for(int i = index; i < stu_count-1; i++)
		students[i] = students[i+1];
	stu_count--;
	printf("学号为 %lld 的学生已被删除!\n\n", id);
}

//修改学生
void modify_stu(void)
{
	long long id;

	printf("\n------------- 修改学生 -------------\n");
	if(stu_count == 0)
	{
		printf("当前没有学生信息可修改!\n\n");
		return;
	}

	printf("请输入要修改的学生的学号: ");
	while(scanf("%lld", &id) != 1)
	{
		printf("输入无效，请输入一个整数作为学号!\n");
		clear_input_buffer();
	}
	clear_input_buffer();

	int index = find_stu_by_id(id);
	if(index == -1)
	{
		printf("未找到学号为 %lld 的学生!\n\n", id);
		return;
	}
	//打印原有信息
	printf("找到了学号为%lld的学生，信息如下:\n", id);
	printf("%-s: %lld\n", "学号", id);
	printf("%-s: %s\n", "姓名", students[index].name);
	for(int i = 0; i < MAX_SUBJECTS; i++)
		printf(" - %-8s: %.2f\n", subjects[i], students[index].scores[i]);
	
	//输入新的信息
	printf("请输入新的学号: ");
	while(scanf("%lld", &id) != 1)
	{
		printf("输入无效，请输入一个整数作为学号!\n");
		clear_input_buffer();
	}
	clear_input_buffer();
	//检查学号是否重复
	if(id != students[index].id && find_stu_by_id(id) != -1)//新学号不等于旧学号
	{
		printf("错误: 新学号 %lld 已被其他学生使用，修改失败!\n\n", id);
		return;
	}
	students[index].id = id;
	printf("请输入新的姓名(无空格,敲回车保持原有值): ");
	char newname[MAX_NAME_LEN];
	fgets(newname, MAX_NAME_LEN, stdin);
	if(strlen(newname) == MAX_NAME_LEN - 1 && newname[MAX_NAME_LEN-2] != '\n')
		clear_input_buffer();
	if(strlen(newname) > 1)
	{
		newname[strlen(newname)-1] = '\0';
		strcpy(students[index].name, newname);
	}
	printf("请依次输入各科成绩:\n");
	for(int i = 0; i < MAX_SUBJECTS; i++)
	{
		printf("请输入新的 %s 成绩(0-100, 输入-1保持原值): ", subjects[i]);
		float newscore;
		while(scanf("%f", &newscore) != 1 || (newscore != -1 && (newscore < 0 || newscore > 100)))
		{
			printf("输入无效，请输入一个0到100的数字!\n");
			clear_input_buffer();
		}
		clear_input_buffer();
		if(newscore != -1)
			students[index].scores[i] = newscore;
	}
	printf("学生信息修改成功!\n");
}

//查询学生
void search_stu(void)
{
	long long id;

	printf("\n------------ 查询学生 --------------\n");
	if(stu_count == 0)
	{
		printf("当前没有学生信息可查询!\n");
		return;
	}

	printf("请输入要查找的学生学号: ");	
	while(scanf("%lld", &id) != 1)
	{
		printf("输入无效，请输入一个整数作为学号!\n");
		clear_input_buffer();
	}
	clear_input_buffer();
	int index = find_stu_by_id(id);
	if(index == -1)
	{
		printf("未找到学号为 %lld 的学生!\n", id);
		return;
	}
	else
	{
		printf("找到了学生! 信息如下:\n");
		printf("%s: %lld\n", "学号", id);
		printf("%s: %s\n", "姓名", students[index].name);
		printf("各科成绩:\n");
		for(int i = 0; i < MAX_SUBJECTS; i++)
			printf(" - %-8s: %.2f\n", subjects[i], students[index].scores[i]);
		float average = caculate(&students[index]);
		printf("--------------------------------\n");
		printf("%-10s: %.2f\n\n", "平均分", average);
	}
}

//排名功能的子菜单
void rank_menu(void)
{
	int choice;

	do
	{
		printf("\n----------------------成绩排名子菜单----------------------\n");
		printf("1.按序号排名（默认）\n");
		printf("2.按平均分排名\n");
		printf("3.按单科成绩排名\n");
		printf("0.返回上一级菜单\n");
		printf("------------------------------------------------------------\n");
		printf("请选择排名方式: ");
		while(scanf("%d", &choice) != 1)
		{
			printf("输入无效，请输入一个整数!\n");
			clear_input_buffer();
		}
		clear_input_buffer();

		switch(choice)
		{
			case 1: show_all_stu_by_default(); break;	//和教师功能的显示所有学生是同一个函数
			case 2: rank_stu_by_average(); break;		//按平均分排序
			case 3: rank_stu_by_subject(); break;		//按单科成绩排序
			case 0: printf("返回上一级菜单\n"); break;
			default: printf("无此功能，请重新输入!\n"); break;
		}
		if(choice != 0)
		{
			printf("\n按回车键继续...");
			clear_input_buffer();
		}

	}while(choice != 0);
}


//按平均分排序（降序）
void rank_stu_by_average(void)
{
	stu_t temp[MAX_STUDENTS];

	if(stu_count == 0)
	{
		printf("当前没有学生可排名!\n\n");
		return;
	}

	//创建临时数组，避免原始数据被修改
	for(int i = 0; i < stu_count; i++)
		temp[i] = students[i];

	//冒泡排序
	for(int i = 0; i < stu_count-1; i++)
	{
		for(int j = 0; j < stu_count -i - 1; j++)
		{
			if(caculate(&temp[j]) < caculate(&temp[j+1]))
				swap_stu(&temp[j], &temp[j+1]);
		}
	}
	//显示排序结果
	show_stu_list(temp, stu_count, "---------- 学生成绩列表(按平均分排名) ---------\n");
	printf("\n[%s:%d]\n", __FUNCTION__, __LINE__);
}


//按单科成绩排序(降序)
void rank_stu_by_subject(void)
{
	stu_t temp[MAX_STUDENTS];
	int choice;

	if(stu_count == 0)
	{
		printf("当前没有学生可排名!\n\n");
		return;
	}

	printf("\n请选择要排名的科目: \n");
	for(int i = 0; i < MAX_SUBJECTS; i++)
		printf("%d. %s\n", i+1, subjects[i]);
	printf("请输入科目序号: ");
	while(scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
	{
		printf("输入无效，请输入一个 1 到 %d 之间的数字!\n", MAX_SUBJECTS);
		clear_input_buffer();
	}
	clear_input_buffer();

	for(int i = 0; i < stu_count; i++)
		temp[i] = students[i];	

	int index = choice - 1;
	for(int i = 0; i < stu_count; i++)
	{
		for(int j = 0; j < stu_count - i - 1; j++)
		{
			if(temp[j].scores[index] < temp[j+1].scores[index])
				swap_stu(&temp[j], &temp[j+1]);
		}
	}

	//显示排序结果
	char title[100];
	sprintf(title, "---------- 学生成绩列表(按%s排名) ---------------\n", subjects[index]);
	show_stu_list(temp, stu_count, title);
}


// --- 文件操作 ---
// 保存学生数据到文件
void save_stu_to_file(void)
{
	FILE *fp = fopen(FILENAME, "w");	
	if(!fp)
	{
		printf("错误: 无法打开 %s 文件进行写入!\n", FILENAME);
		return;
	}

	fprintf(fp, "%d\n", stu_count);
	for(int i  = 0; i < stu_count; i++)
	{
		fprintf(fp, "%lld %s ", students[i].id, students[i].name);
		for(int j = 0; j < MAX_SUBJECTS; j++)
			fprintf(fp, "%.2f ", students[i].scores[j]);
		fprintf(fp, "\n");
	}
	
	fclose(fp);
	printf("学生数据已成功保存到 %s 文件!\n", FILENAME);
}

// 从文件加载学生数据
void load_stu_from_file(void)
{
	int student_count = 0;

	FILE *fp = fopen(FILENAME, "r");
	if(!fp)	//文件不存在是正常情况，不报错
	{
		stu_count = 0;
		return;
	}

	//读取学生总数
	if(fscanf(fp, "%d\n", &student_count) != 1)
	{
		stu_count = 0;
		fclose(fp);
		return;
	}

	//防止数组溢出
	if(student_count > MAX_STUDENTS)
		student_count = MAX_STUDENTS;

	stu_count = 0;
	int success = 0;
	//读取一行
	for(int i = 0; i < student_count; i++)
	{
		if(fscanf(fp, "%lld %19s", &students[i].id, students[i].name) == 2)
		{
			success = 1;
			for(int j = 0; j < MAX_SUBJECTS; j++)
			{
				if(fscanf(fp, "%f ", &students[i].scores[j]) != 1) //如果这一行读取失败了，立即停止读取
				{
					success = 0;
					break;
				}
			}
			if(success)//读取完一行之后，自动生成密码
			{
				sprintf(students[i].passwd, "%lld", students[i].id);
				stu_count++;
			}
			else
			{
				printf("警告: 文件 %s 格式错误，加载部分数据.\n", FILENAME);
				break;
			}
		}
		else
			break;//无法读取姓名和学号，立即停止读取
	}

	fclose(fp);
	printf("成功从文件 %s 加载数据到数组!\n", FILENAME);
}


//从文件加载教师数据到数组
void load_tea_from_file(void)
{
	FILE *fp = fopen(TEA_FILENAME, "r");
	if(!fp)
	{
		printf("提示: 未找到教师列表文件 %s,将使用默认教师账号(admin/passwd)!\n", TEA_FILENAME);
		tea_count = 0;
		return;
	}

	tea_count = 0;
	
	//循环读取教师的账号密码，直到达到文件末尾或达到最大数量
	while(tea_count < MAX_TEACHERS && fscanf(fp, "%s %s", teachers[tea_count].username, teachers[tea_count].passwd) == 2)
		tea_count++;

	fclose(fp);
}

// --- 通用函数 ---
//计算学生平均分
float caculate(const stu_t *s)
{
	float total = 0.0f;

	if(MAX_SUBJECTS == 0) return 0.0f;
	for(int i = 0; i < MAX_SUBJECTS; i++)
		total += s->scores[i];
	return total / MAX_SUBJECTS;
}

//交换两个结构体
void swap_stu(stu_t *a, stu_t *b)
{
	stu_t temp = *a;
	*a = *b;
	*b  = temp;
}

//按默认顺序（按学号）显示所有学生
void show_all_stu_by_default(void)
{
	show_stu_list(students, stu_count, "--- 学生列表信息(按序号) ---");
}

void show_stu_list(const stu_t *list, int count, const char *title)
{
	printf("\n%s\n", title);
	if(count == 0)
	{
		printf("当前没有学生可显示!\n\n");
		return;
	}

	//打印表头
	printf("%-4s %-16s %-12s ", "排名", "学号", "姓名");
	for(int i = 0; i < MAX_SUBJECTS; i++)
		printf("%-10s ", subjects[i]);
	printf("%-10s\n", "平均分");
	printf("-------------------------------------------------------------------\n");

	for(int i = 0; i < count; i++)
	{
		printf("%-4d %-14lld %-10s ", i+1, list[i].id, list[i].name);
		for(int j = 0; j < MAX_SUBJECTS; j++)
			printf("%-8.2f ", list[i].scores[j]);
		float average = caculate(&list[i]);
		printf("%-10.2f\n", average);
	}
	printf("--------------------------------------------------------------------\n");
	printf("总计 %d 名学生!\n\n", count);
}

