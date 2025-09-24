#include "stu.h"


int main()
{
	//从文件加载学生数据
	load_stu_from_file();
	//从文件加载教师数据
	load_tea_from_file();

	printf("欢迎使用学生成绩管理系统!\n");
	printf("按回车键键进入登录界面...");
	clear_input_buffer();

	main_menu();//进入主菜单

	return 0;
}
