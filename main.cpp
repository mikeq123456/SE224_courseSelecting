#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int g_type;
char g_ID[10], g_passWd[10];

struct Course
{
	char number[6];		// �γ̱��
	char name[11];	// �γ�����
	char tpye[6];	// �γ�����
	int period;		// ѧʱ
	int clas;		// �ڿ�ѧʱ
	int test;		// ʵ��ѧʱ
	int score;		// ѧ��
	int term;		// ѧ��
public:
	void add();
	void select();
	void grade();
	void query();
	void query1();
};

struct Stu
{
	char ID[10];		// ѧ��
	char number[6];	// �γ���Ϣ
	char grade[4];	// �ɼ�

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
	printf("������γ̱�ţ�");
	scanf("%s", number);
	printf("������γ����ƣ�");
	scanf("%s", name);
	printf("������γ����ʣ�");
	scanf("%s", tpye);
	printf("������ѧʱ��");
	scanf("%d", &period);
	printf("�������ڿ�ѧʱ��");
	scanf("%d", &clas);
	printf("������ʵ��ѧʱ��");
	scanf("%d", &test);
	printf("������ѧ�֣�");
	scanf("%d", &score);
	printf("������ѧ�ڣ�");
	scanf("%d", &term);

	// �Ը��ӵ�ģʽ���ļ��������ӿγ���Ϣ
	FILE *fp = fopen("test.txt", "a+");
	fprintf(fp, "\n%s\t%s\t\t%s\t%d\t%d\t%d\t%d\t%d", number, name, tpye, period, clas, test, score, term);
	fclose(fp);
}
void Course::select()
{
	Course cou;
	FILE *fp = fopen("test.txt", "r");

	// ��ȡ�ļ���Ϣ���������Ļ
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
	printf("������Ҫ¼��ɼ���ѧ�ţ�");
	scanf("%s", num);
	printf("������Ҫ¼��ɼ��Ŀγ̣�");
	scanf("%s", kc);
	printf("��¼��ɼ���");
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
	printf("������Ҫ��ѯ��ѧ�ţ�");
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
	printf("������Ҫ��ѯ�Ŀγ̣�");
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
void Man::sort(Man* man)	// ����
{
	FILE *fp = fopen("choose.txt", "r");
	int i = 0;

	while (!feof(fp))
	{
		man->stu[i] = (Stu*)malloc(sizeof(Stu));		// Ϊָ�����ռ�
		fscanf(fp, "%s %s %s", man->stu[i]->ID, man->stu[i]->number, man->stu[i]->grade);
		i++;
		//printf("%s\t%s\t%s\n", g_ID, a, b);
	}
	fclose(fp);
	i--;
	for (int j = 0; j < i; j++)		// ��������
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
	for (int a = 0; a < i; a++)		// �������Ļ
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
			strcpy(l, man->stu[k]->grade);		// ȡ�ɼ����
		}
		if (strcmp(man->stu[k - 1]->grade, man->stu[k]->grade) < 0)
		{
			strcpy(h, man->stu[k]->grade);		// ȥ�ɼ����
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

	printf("�γ�%s\t", man->stu[0]->number);
	printf("��߳ɼ�%s\t��ͳɼ�%s\tƽ���ɼ�%f\n", h, l, sum);
	printf("����%d\t����%d\tƽ���ɼ�������%d\n", good, well, fail);
}
void Man::all(Man* man)
{

	FILE *fp = fopen("choose.txt", "r");
	int i = 0, i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;

	while (!feof(fp))
	{
		man->stu[i] = (Stu*)malloc(sizeof(Stu));	// Ϊÿ��ָ��Stu��ָ������ڴ�
		fscanf(fp, "%s %s %s", man->stu[i]->ID, man->stu[i]->number, man->stu[i]->grade);	// ��ȡ�ļ��е���Ϣ
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
	printf("������γ̱��");
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
				printf("��¼�ɹ�\n");
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
				printf("��¼�ɹ�\n");
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
	printf("�������˺ţ�");
	scanf("%s", g_ID);
	printf("���������룺");
	scanf("%s", g_passWd);
	if (manLogin() == true)
	{
		printf("����Ա��¼\n");
		g_type = 1;
		int m;
		//Course S;
		while (1)
		{
			printf("\n\n�γ�¼��\t1");		   //���������ʾ
			printf("\n\n����γ�\t2");
			printf("\n\n�ɼ�¼��\t3");
			printf("\n\n��ѧ�Ų�ѯ\t4");
			printf("\n\n���γ̲�ѯ\t5");
			printf("\n\n�γ̺�����\t6");
			printf("\n\nѧ������\t7");
			printf("\n\n�ɼ�����\t8");
			printf("\n\n�ɼ�����\t9\n");
			printf("\n\n�˳�\t0\n");

			scanf("%d", &m);                         //����Ҫ�����Ĳ���    if(m>='0'&&m<='5')
			if (m < 10 && m >= 0)
			{
				switch (m)
				{
				case 1: C.add();
					break;				//ѡ1 �γ�¼��
				case 2: C.select();
					break;				//ѡ2 ���
				case 3: C.grade();
					break;				//ѡ3 �ɼ�¼��
				case 4: C.query();
					break;				//ѡ4 ѧ�Ų�ѯ
				case 5: C.query1();
					break;				//ѡ5 �γ̲�ѯ
				case 6: man->sort(man);
					break;				//ѡ6 �γ̺�����
				case 7: man->sort1(man);
					break;				//ѡ7 ѧ������
				case 8: man->sort2(man);
					break;				//ѡ6 �ɼ�����
				case 9: man->all(man);
					break;				//ѡ7 �ɼ�����
				case 0: exit(0);	    //ѡ0����
				}
				printf("\n\n������ϣ����ٴ�ѡ��");
			}
			else printf("\n\nѡ��������ٴ�ѡ��");
		}
	}
	else if (stuLogin() == true)
	{
		printf("ѧ����¼\n");
		g_type = 2;
		int m;
		while (1)
		{
			printf("\n\n����γ���Ϣ\t1");
			printf("\n\nѧ��ѡ��\t2");
			printf("\n\n�鿴ѡ��\t3");

			scanf("%d", &m);                         //����Ҫ�����Ĳ���    if(m>='0'&&m<='5')
			if (m < 4 && m >= 0)
			{
				switch (m)
				{
				case 1: C.select();
					break;				//ѡ1 ���
				case 2: S.choose();
					break;				//ѡ1 ���
				case 3: S.look();
					break;				//ѡ1 ���
				case 0: exit(0);	    //ѡ0����
				}
				printf("\n\n������ϣ����ٴ�ѡ��");
			}
			else printf("\n\nѡ��������ٴ�ѡ��");
		}
	}
	else
	{
		printf("�˺Ż��������");
	}

	return 0;
}