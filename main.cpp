#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int g_type;
char g_ID[10], g_passWd[10];

struct Course
{
	char number[6];		// 课程编号
	char name[11];	// 课程名称
	//char tpye[6];	// 课程性质
	int period;		// 学时
	//int clas;		// 授课学时
	//int test;		// 实验学时
	int score;		// 学分
	int term;		// 学期
public:
	void add();
	void select();
	void grade();
	void query();
	void query1();
};

struct Stu
{
	char ID[10];		// 学号
	char number[6];	// 课程信息
	char grade[4];	// 成绩

public:
	void choose();
	void look();
};

struct Man
{
public:
	Stu *stu[10];

public:
	void sort(Man* man);
	void sort1(Man* man);
	void sort2(Man* man);
	void all(Man* man);
};

void Course::add()
{
	printf("请输入课程编号：");
	scanf("%s", number);
	printf("请输入课程名称：");
	scanf("%s", name);
	/*printf("请输入课程性质：");
	scanf("%s", tpye);*/
	printf("请输入学时：");
	/*scanf("%d", &period);
	printf("请输入授课学时：");
	scanf("%d", &clas);
	printf("请输入实验学时：");
	scanf("%d", &test);*/
	printf("请输入学分：");
	scanf("%d", &score);
	printf("请输入学期：");
	scanf("%d", &term);

	// 以附加的模式打开文件，添加添加课程信息
	FILE *fp = fopen("test.txt", "a+");
	fprintf(fp, "\n%s\t%s\t\t%d\t%d\t%d", number, name, period, score, term);
	fclose(fp);
}
void Course::select()
{
	Course cou;
	FILE *fp = fopen("test.txt", "r");

	// 读取文件信息并输出到屏幕
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s %d %d %d %d %d", cou.number, cou.name);
		printf("%s\t%s\t\t%s\t%d\t%d\t%d\t%d\t%d\n", cou.number, cou.name);
	}
	fclose(fp);
}
void Course::grade()
{
	char num[10], num_read[10], kc[10], kc_read[10], gr[4];
	printf("请输入要录入成绩的学号：");
	scanf("%s", num);
	printf("请输入要录入成绩的课程：");
	scanf("%s", kc);
	printf("请录入成绩：");
	scanf("%s", gr);
	FILE *fp = fopen("choose.txt", "r+");
	rewind(fp);
	while (!feof(fp))
	{
		if (strcmp(num_read, num) == 0)
		{
			fscanf(fp, "%s ", kc_read);
			if (strcmp(kc, kc_read) == 0)
				break;
		}
		fscanf(fp, "%s ", num_read);
	}
	fseek(fp, 0, SEEK_CUR);

	fprintf(fp, "%s", gr);
	fclose(fp);
}
void Course::query()
{
	char str[10];
	printf("请输入要查询的学号：");
	scanf("%s", str);
	char t[10], a[10], b[10];
	FILE *fp = fopen("choose.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s ", t);
		if (strcmp(str, t) == 0) {
			fscanf(fp, "%s %s ", a, b);
			printf("%s\t%s\t%s\n", str, a, b);
		}
	}
	fclose(fp);
}
void Course::query1()
{
	char str[10];
	printf("请输入要查询的课程：");
	scanf("%s", str);
	char old[10], t[10], b[10];
	FILE *fp = fopen("choose.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s ", t);
		if (strcmp(str, t) == 0) {
			fscanf(fp, "%s ", b);
			printf("%s\t%s\t%s\n", old, t, b);
		}
		strcpy(old, t);
	}
	fclose(fp);
}
void Man::sort(Man* man)	// 排序
{
	FILE *fp = fopen("choose.txt", "r");
	int i = 0;

	while (!feof(fp))
	{
		man->stu[i] = (Stu*)malloc(sizeof(Stu));		// 为指针分配空间
		fscanf(fp, "%s %s %s", man->stu[i]->ID, man->stu[i]->number, man->stu[i]->grade);
		i++;
		//printf("%s\t%s\t%s\n", g_ID, a, b);
	}
	fclose(fp);
	i--;
	for (int j = 0; j < i; j++)		// 遍历排序
	{
		for (int k = 1; k < i; k++)
		{
			if (strcmp(man->stu[k - 1]->number, man->stu[k]->number) > 0)
			{
				Stu *temp = man->stu[k];
				man->stu[k] = man->stu[k - 1];
				man->stu[k - 1] = temp;
			}
		}
	}
	for (int a = 0; a < i; a++)		// 输出到屏幕
	{
		printf("%s\t%s\t%s\n", man->stu[a]->ID, man->stu[a]->number, man->stu[a]->grade);
	}
}
void Man::sort1(Man* man)
{
	FILE *fp = fopen("choose.txt", "r");
	int i = 0;

	while (!feof(fp))
	{
		man->stu[i] = (Stu*)malloc(sizeof(Stu));
		fscanf(fp, "%s %s %s", man->stu[i]->ID, man->stu[i]->number, man->stu[i]->grade);
		i++;
		//printf("%s\t%s\t%s\n", g_ID, a, b);
	}
	fclose(fp);
	i--;
	for (int j = 0; j < i; j++)
	{
		for (int k = 1; k < i; k++)
		{
			if (strcmp(man->stu[k - 1]->ID, man->stu[k]->ID) > 0)
			{
				Stu *temp = man->stu[k];
				man->stu[k] = man->stu[k - 1];
				man->stu[k - 1] = temp;
			}
		}
	}
	for (int a = 0; a < i; a++)
	{
		printf("%s\t%s\t%s\n", man->stu[a]->ID, man->stu[a]->number, man->stu[a]->grade);
	}
}
void Man::sort2(Man* man)
{
	FILE *fp = fopen("choose.txt", "r");
	int i = 0;

	while (!feof(fp))
	{
		man->stu[i] = (Stu*)malloc(sizeof(Stu));
		fscanf(fp, "%s %s %s", man->stu[i]->ID, man->stu[i]->number, man->stu[i]->grade);
		i++;
		//printf("%s\t%s\t%s\n", g_ID, a, b);
	}
	fclose(fp);
	i--;
	for (int j = 0; j < i; j++)
	{
		for (int k = 1; k < i; k++)
		{
			if (strcmp(man->stu[k - 1]->grade, man->stu[k]->grade) < 0)
			{
				Stu *temp = man->stu[k];
				man->stu[k] = man->stu[k - 1];
				man->stu[k - 1] = temp;
			}
		}
	}
	for (int a = 0; a < i; a++)
	{
		printf("%s\t%s\t%s\n", man->stu[a]->ID, man->stu[a]->number, man->stu[a]->grade);
	}
}

void a(Man* man, int i)
{
	char h[5], l[5];
	double sum = 0;
	int good = 0, well = 0, fail = 0;

	for (int k = 1; k < i; k++)
	{
		strcpy(h, man->stu[k - 1]->grade);
		strcpy(l, man->stu[k - 1]->grade);
		if (strcmp(man->stu[k - 1]->grade, man->stu[k]->grade) > 0)
		{
			strcpy(l, man->stu[k]->grade);		// 取成绩最高
		}
		if (strcmp(man->stu[k - 1]->grade, man->stu[k]->grade) < 0)
		{
			strcpy(h, man->stu[k]->grade);		// 去成绩最低
		}

	}
	//i--;
	for (int k = 0; k < i; k++)
	{
		if (strcmp(man->stu[k]->grade, "80  ") > 0)
		{
			good++;
		}
		if (strcmp(man->stu[k]->grade, "60  ") > 0 && strcmp(man->stu[k]->grade, "80  ") < 0)
		{
			well++;
		}
		if (strcmp(man->stu[k]->grade, "60  ") < 0)
		{
			fail++;
		}
		sum += atoi(man->stu[k]->grade);
	}
	sum /= i;

	printf("课程%s\t", man->stu[0]->number);
	printf("最高成绩%s\t最低成绩%s\t平均成绩%f\n", h, l, sum);
	printf("优秀%d\t良好%d\t平均成绩不及格%d\n", good, well, fail);
}
void Man::all(Man* man)
{

	FILE *fp = fopen("choose.txt", "r");
	int i = 0, i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;

	while (!feof(fp))
	{
		man->stu[i] = (Stu*)malloc(sizeof(Stu));	// 为每个指向Stu的指针分配内存
		fscanf(fp, "%s %s %s", man->stu[i]->ID, man->stu[i]->number, man->stu[i]->grade);	// 读取文件中的信息
		i++;
		//printf("%s\t%s\t%s\n", g_ID, a, b);
	}
	fclose(fp);

	Man *man1 = (Man*)malloc(sizeof(Man));
	Man *man2 = (Man*)malloc(sizeof(Man));
	Man *man3 = (Man*)malloc(sizeof(Man));
	Man *man4 = (Man*)malloc(sizeof(Man));
	Man *man5 = (Man*)malloc(sizeof(Man));
	for (int b = 0; b < i; b++)
	{
		if (strcmp(man->stu[b]->number, "10001") == 0) {
			man1->stu[i1] = (Stu*)malloc(sizeof(Stu));
			strcpy(man1->stu[i1]->ID, man->stu[b]->ID);
			strcpy(man1->stu[i1]->number, man->stu[b]->number);
			strcpy(man1->stu[i1]->grade, man->stu[b]->grade);
			i1++;
		}
		if (strcmp(man->stu[b]->number, "10002") == 0) {
			man2->stu[i2] = (Stu*)malloc(sizeof(Stu));
			strcpy(man2->stu[i2]->ID, man->stu[b]->ID);
			strcpy(man2->stu[i2]->number, man->stu[b]->number);
			strcpy(man2->stu[i2]->grade, man->stu[b]->grade);
			i2++;
		}
		if (strcmp(man->stu[b]->number, "10003") == 0) {
			man3->stu[i3] = (Stu*)malloc(sizeof(Stu));
			strcpy(man3->stu[i3]->ID, man->stu[b]->ID);
			strcpy(man3->stu[i3]->number, man->stu[b]->number);
			strcpy(man3->stu[i3]->grade, man->stu[b]->grade);
			i3++;
		}
		if (strcmp(man->stu[b]->number, "10004") == 0) {
			man4->stu[i4] = (Stu*)malloc(sizeof(Stu));
			strcpy(man4->stu[i4]->ID, man->stu[b]->ID);
			strcpy(man4->stu[i4]->number, man->stu[b]->number);
			strcpy(man4->stu[i4]->grade, man->stu[b]->grade);
			i4++;
		}
		if (strcmp(man->stu[b]->number, "10005") == 0) {
			man5->stu[i5] = (Stu*)malloc(sizeof(Stu));
			strcpy(man5->stu[i5]->ID, man->stu[b]->ID);
			strcpy(man5->stu[i5]->number, man->stu[b]->number);
			strcpy(man5->stu[i5]->grade, man->stu[b]->grade);
			i5++;
		}
	}

	if (i1 != 0)a(man1, i1);
	if (i2 != 0)a(man2, i2);
	if (i3 != 0)a(man3, i3);
	if (i4 != 0)a(man4, i4);
	if (i5 != 0)a(man5, i5);
}

void Stu::choose()
{
	strcpy(ID, g_ID);
	printf("请输入课程编号");
	scanf("%s", number);
	strcpy(grade, "00  ");

	FILE *fp = fopen("choose.txt", "a+");
	fprintf(fp, "\n%s\t%s\t%s", ID, number, grade);
	fclose(fp);
}

void Stu::look()
{
	char t[10], a[10], b[10];
	FILE *fp = fopen("choose.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s ", t);
		if (strcmp(g_ID, t) == 0) {
			fscanf(fp, "%s %s ", a, b);
			printf("%s\t%s\t%s\n", g_ID, a, b);
		}
	}
	fclose(fp);
}

bool manLogin()
{
	FILE *fp = fopen("man.txt", "r+");

	while (!feof(fp))
	{
		char a[10], b[10];
		fgets(a, 9, fp);
		fgets(b, 8, fp);

		if (strcmp(g_ID, a) == 0) {
			if (strcmp(g_passWd, b) == 0) {
				printf("登录成功\n");
				return true;
			}
		}
		fgets(b, 2, fp);
	}
	fclose(fp);
	return false;
}

bool stuLogin()
{
	FILE *fp = fopen("stu.txt", "r+");
	while (!feof(fp))
	{
		char a[10], b[10];
		fgets(a, 9, fp);
		fgets(b, 10, fp);

		if (strcmp(g_ID, a) == 0) {
			if (strcmp(g_passWd, b) == 0) {
				printf("登录成功\n");
				return true;
			}
		}
		fgets(b, 2, fp);
	}
	fclose(fp);
	return false;
}

int main()
{
	Man *man = (Man*)malloc(sizeof(Man));
	Course C;
	Stu S;
	printf("请输入账号：");
	scanf("%s", g_ID);
	printf("请输入密码：");
	scanf("%s", g_passWd);
	if (manLogin() == true)
	{
		printf("管理员登录\n");
		g_type = 1;
		int m;
		//Course S;
		while (1)
		{
			printf("\n\n课程录入\t1");		   //输出操作提示
			printf("\n\n浏览课程\t2");
			printf("\n\n成绩录入\t3");
			printf("\n\n按学号查询\t4");
			printf("\n\n按课程查询\t5");
			printf("\n\n课程号排序\t6");
			printf("\n\n学号排序\t7");
			printf("\n\n成绩排序\t8");
			printf("\n\n成绩汇总\t9\n");
			printf("\n\n退出\t0\n");

			scanf("%d", &m);                         //接受要操作的步骤    if(m>='0'&&m<='5')
			if (m < 10 && m >= 0)
			{
				switch (m)
				{
				case 1: C.add();
					break;				//选1 课程录入
				case 2: C.select();
					break;				//选2 浏览
				case 3: C.grade();
					break;				//选3 成绩录入
				case 4: C.query();
					break;				//选4 学号查询
				case 5: C.query1();
					break;				//选5 课程查询
				case 6: man->sort(man);
					break;				//选6 课程号排序
				case 7: man->sort1(man);
					break;				//选7 学号排序
				case 8: man->sort2(man);
					break;				//选6 成绩排序
				case 9: man->all(man);
					break;				//选7 成绩汇总
				case 0: exit(0);	    //选0结束
				}
				printf("\n\n操作完毕，请再次选择！");
			}
			else printf("\n\n选择错误，请再次选择！");
		}
	}
	else if (stuLogin() == true)
	{
		printf("学生登录\n");
		g_type = 2;
		int m;
		while (1)
		{
			printf("\n\n浏览课程信息\t1");
			printf("\n\n学生选课\t2");
			printf("\n\n查看选课\t3");

			scanf("%d", &m);                         //接受要操作的步骤    if(m>='0'&&m<='5')
			if (m < 4 && m >= 0)
			{
				switch (m)
				{
				case 1: C.select();
					break;				//选1 浏览
				case 2: S.choose();
					break;				//选1 浏览
				case 3: S.look();
					break;				//选1 浏览
				case 0: exit(0);	    //选0结束
				}
				printf("\n\n操作完毕，请再次选择！");
			}
			else printf("\n\n选择错误，请再次选择！");
		}
	}
	else
	{
		printf("账号或密码错误！");
	}

	return 0;
}
