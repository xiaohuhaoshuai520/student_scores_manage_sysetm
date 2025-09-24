#ifndef STU_H__
#define STU_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME_LEN	20
#define MAX_SUBJECTS	3
#define MAX_TEACHERS	10
#define MAX_STUDENTS	100
#define FILENAME		"stu.dat"
#define TEA_FILENAME	"tea.dat"

//学生结构体
typedef struct student
{
	long long id;
	char name[MAX_NAME_LEN];
	float scores[MAX_SUBJECTS];
	char passwd[MAX_NAME_LEN];
}stu_t;

//教师结构体
typedef struct teacher
{
	char username[MAX_NAME_LEN];
	char passwd[MAX_NAME_LEN];
}tea_t;


//函数声明
void main_menu(void);
void clear_input_buffer(void);
void tea_login(void);
void stu_login(void);
void tea_menu(const char *username);
void get_data(char *username, char *passwd, const char *user);
int find_stu_by_id(long long id);
void stu_menu(const char *username);


//教师功能
void manage_stu(void);
void add_stu(void);
void del_stu(void);
void modify_stu(void);
void search_stu(void);
void show_all_stu_by_default(void);
void show_stu_list(const stu_t *list, int count, const char *title);
void rank_menu(void);
void rank_stu_by_average(void);
void rank_stu_by_subject(void);


//文件操作
void save_stu_to_file(void);
void load_stu_from_file(void);
void load_tea_from_file(void);


//通用函数
float caculate(const stu_t *s);
void swap_stu(stu_t *a, stu_t *b);

#endif
