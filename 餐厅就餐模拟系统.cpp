#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <windows.h>
#include <stdlib.h>
using namespace std;
# define MAX 100
// �ṹ�嶨��
//1.���� 
struct table{
	int tabledroom;//�������ڲ������ 
	int tablenum;//�������
	int seat;//������λ��
	int state;//�����Ƿ���� 0��ʾ���� 1��ʾռ�� 2��ʾԤ�� 
	struct table* next;
};
//2.�˵� 
struct menu{
	int menunum;//�˵ı�� 
	char dishesname[20];//���� 
	int dishesprice;//�˵ļ۸� 
	struct menu *next; 
};
//3.�˿Ͷ��� 
struct order{
	char name[20];//�û��� 
    int menu_num; // ��Ʒ���
    int quantity; // ����
    char dishesname[20];//���� 
    int dishesprice;//�˵ļ۸� 
    int tablenum;//	��ѡ�������
    struct order* next;
};
//6.�˿��˻� 
struct Customer {
    char CustName[20];  // �˿�����
    char CustCode[20];  // ����
};
struct Customer cust[MAX];//�˿��������(�˻�ע������)
//2������¼���� 
void loginCustomer(); //�˿͵�¼ �������ע�� // �˿���Ϣ��غ�������
void loginManager();//����Ա��¼ // ����Ա��Ϣ��غ������� 
void custoperate(char name[]);//�˿Ͳ��� 
void manageoperate();//����Ա���� 
void menucontrol(); //����˵� 
void ordercontrol();//������ 
void tablecontrol();//�������  
int readCustomer(); // ����鿴�˿�ע���� 
//����������غ���
table* Create_table_Doc(); //���ļ��д���������������
void Printf_Table_Doc(struct table *mhead); //��ӡ�յĲ�����Ϣ
table *Insert_table_Doc(struct table *thead); //������������
table *Delete_table_Doc(struct table *thead); //ɾ����������
void After_table_Doc(struct table *thead); //�޸Ĳ�����Ϣ
void InTablefile(struct table *thead); //��������д���ļ�
void printf_table_Doc(struct table *thead);//��ӡȫ��������Ϣ
void sortTable(struct table *thead); //������������
//�˵�������غ���
menu*Create_menu_Doc(); //���ļ��д����˵���������
void Printf_menu_Doc(struct menu *mhead); //��ӡ�˵���Ϣ
void InMenufile(struct menu *mhead); //�˵�����д���ļ�
void After_menu_Doc(struct menu *mhead); //�޸Ĳ˵���Ϣ
menu *Insert_menu_Doc(struct menu *mmhead); //�����˵�����
menu *Delete_menu_Doc(struct menu *mmhead); //ɾ���˵�����
void sortMenu(struct menu *mmhead); //�˵���������
//����������غ���
void createorder(char name[],order* ohead);//��� 
order* Create_Order_Doc(); //���ļ��д��������������� 
void Printf_order_Doc(order *ohead,char name[]); //��ӡ������Ϣ
struct order *Insert_order_Doc(order *ohead, char name[], int num); //������������
struct order *Delete_order_Doc(order *ohead,char name[]); //ɾ����������
void InorderFile(order*ohead); //��������д���ļ�
void after_table_Doc(struct table *thead,int num); //�޸Ĳ���״̬
void ordercheak(const char* name); //�鿴ָ���û�����
int main(){
	onceagain:
	//���������Լ������
	int userType;  // 1��ʾ�˿ͣ�2.��ʾ�ϰ� 3.����Ա 
	printf("====================\n");
	printf("   ���������      \n");
	printf("    1.�˿�          \n");
	printf("    2.����Ա        \n");
	printf("=====================\n");
	printf("����������Ҫ���еĲ����� ");
	scanf("%d",&userType);
	system ("cls"); 
	if(userType==1)
	{
		loginCustomer();//�˿͵�¼���� 
	}
	else if(userType==2)
	{
		loginManager(); //����Ա��½ 
		manageoperate();//����Ա����
	} 
	else
	{
    printf("\n\n\t\t\t������������������ѡ��\n");
	Sleep(1000);
	system ("cls");
	goto  onceagain;
    }
} 
void loginCustomer(){
	FILE *fp = fopen("cust.txt", "a+");
	if (fp==NULL)
	{
		printf(" file open error!\n");
		exit (0);
	}
	//��ʼ��һ������ fprintf(fp, "zhanghaobo 123456\n");//��ʼ����ֱ��ע�� 
	/*fprintf(fp, "zhanghaobo    123456\n");
	fprintf(fp, "zhengyabo     123456\n");
	fprintf(fp, "zhangjiahui   123456\n");
	fprintf(fp, "zhaoxinkai    123456\n");
	fprintf(fp, "liuran         123456\n");
	*/
	int custCount = readCustomer();
	char name[20],code[20];
	int choice,inputValid=0;
	again_1:
	printf("*********************************\n");
	printf("      ��ӭ�����޵�����Ů����       \n");
	printf("\n");
	printf("    1. ��¼\t  2.ע��              \n");
	printf("\n");
	printf("***********************************\n");
	printf("����������ѡ��:   ");
	int t=0;
	while (!inputValid)
	{
	scanf("%d", &choice);
	int flag =1,time=0;
	switch (choice) {
		case 1:
				// ִ�е�¼���� 
				again_2:
				custCount = readCustomer(); 
				printf("\n�������û���: ");
    			scanf("%s", name);
    			printf("\n����������: ");
    			scanf("%s", code);
			for (int i=0;i<=custCount;i++) 
			{
				if ((strcmp(name,cust[i].CustName)==0) && (strcmp(code,cust[i].CustCode) == 0))
				{
					flag=0;
					break;
				}
			}	
			if (flag)
			{
	 			printf("�˺Ż�����������������룡 \n");
	 			t++;if(t>5){printf("����������࣬�����˳�");exit(0);}
	 			goto again_2;
			}
			else 
			{
				printf("��¼�ɹ���\n");
				system("pause"); //  ����ʵ�ֶ�����Ļ�����ڹ۲����ִ�н�� 
	 			system ("cls");  // �������� 
			}	
				inputValid = 1; // ������Ч���˳�ѭ��
				break;
		case 2:
				// ִ��ע�����
				again_3:
				printf("�����������û�����  ");
				scanf("%s",name);
					for (int i=0;i<custCount;i++)
				{
						if (strcmp(name,cust[i].CustName) == 0)   //  �Ƚ����������Ĵ�С����ͬ������ 
						{
						printf("���û����Ѵ���");
						system("pause"); //  ����ʵ�ֶ�����Ļ�����ڹ۲����ִ�н�� 
				   		goto  again_3;		 
						}	
				}
					printf("���������룺 ");
					scanf("%s",code);
					strcpy (cust[custCount].CustName,name);
					strcpy (cust[custCount].CustCode,code);	//fscanf  ���ļ��ж�ȡ���ݱ��浽ǰ���������ȥ 
					fprintf(fp,"%s   %s\n",cust[custCount].CustName,cust[custCount].CustCode);
					//   �������ӵ��û����û���������д���ļ���ȥ 
					printf("ע��ɹ���\n");
					system("pause"); //  ����ʵ�ֶ�����Ļ�����ڹ۲����ִ�н�� 
	 				system ("cls");	
					inputValid = 1; // ������Ч���˳�ѭ��
					goto again_2; 
					break;
		default:
			printf("������������������ѡ����Ҫ���������� :  ");
			Sleep(1000);
			system ("cls");
			goto again_1;
				break;
		}
	}
	
	if (fclose(fp))
	{
		printf("can not close the file \n");
		exit(0);
	}
	//��ʼ����˿�ѡ��ҳ�棬ѡ����� 
	custoperate(name);
}
void loginManager(){
	FILE *fp = fopen("manage.txt", "a+");
	if (fp==NULL)
	{
		printf(" file open error!\n");
		exit (0);
	}
	//��ʼ��������5���˹���Ա�˻�����ʼ����ֱ��ע�� 
	/*fprintf(fp, "zhanghaobo    123456\n");
	fprintf(fp, "zhengyabo     123456\n");
	fprintf(fp, "zhangjiahui   123456\n");
	fprintf(fp, "zhaoxinkai    123456\n");
	fprintf(fp, "liuran        123456\n");*/
	char storedName[20], storedCode[20];
    char Name[20], Code[20];int ii=0;//���ڼ�¼�������������ͷ������ʼҳ�� 
	again_4:
    printf("\n�������û���: ");
    scanf("%s", Name);
    printf("\n����������: ");
    scanf("%s", Code);

    int found = 0; // ����Ƿ��ҵ�ƥ����˻�

    fseek(fp, 0, SEEK_SET); // ���ļ�ָ�����¶�λ���ļ���ͷ

    while (fscanf(fp, "%s %s", storedName, storedCode) == 2) {
        if (strcmp(Name, storedName) == 0 && strcmp(Code, storedCode) == 0) {
            found = 1; // �ҵ�ƥ����˻�
            break;
        }
    }
    if (!found)
	{
	 	printf("�˺Ż�����������������룡 \n");
	 	ii++; if(ii>5){printf("����������࣬�����˳�");exit(0);}
	 	goto again_4;
	}
	else 
	{
		printf("��¼�ɹ���\n");
		system("pause"); //  ����ʵ�ֶ�����Ļ�����ڹ۲����ִ�н�� 
		system ("cls");  // �������� 
	}
    fclose(fp); 
}
int readCustomer(){//�鿴ע��˿��˻� 
    FILE *fp;
    int custCount = 0;

    if ((fp = fopen("cust.txt", "r")) == NULL) {
        printf("�ļ���ʧ��!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s", cust[custCount].CustName, cust[custCount].CustCode) == 2) {
        custCount++;
    }
    fclose(fp);
    return custCount;
}
void custoperate(char name[]) {
	again_5: 
	printf("==================================\n");
	printf("     1. ��ʼ���        \n"); 
	printf("     2. �鿴����        \n");
	printf("     0. �˳�            \n");
	printf("==================================\n");
	int choose;
	printf("����������ѡ��:  ");
	scanf("%d",&choose);
	order* ohead;
	ohead = Create_Order_Doc();
	switch(choose)
	{
		case 1:createorder(name,ohead);
			   InorderFile(ohead);goto again_5;
		case 2:	ordercheak(name);
			   	goto again_5; 
		case 0:return;break;
		default:
	    	{
	    		printf("�����������������ѡ�� ");
	    		Sleep(1000);
	    		system ("cls");
	    		goto again_5;
	    	    break;
			}
	}
 } 
void manageoperate(){
	again_6: 
	printf("==================================\n");
	printf("     1. �鿴�˵����޸�  \n"); 
	printf("     2. �鿴����        \n");
	printf("     3. �������        \n");
	printf("     0. �˳�            \n");
	printf("==================================\n");
	int choose;
	printf("����������ѡ��:  ");
	scanf("%d",&choose);
	switch(choose)
	{
		case 1:	menucontrol();goto again_6; 
		case 2: ordercontrol();goto again_6;
		case 3: tablecontrol();goto again_6;
		case 0:return;break;
		default:
	    	{
	    		printf("�����������������ѡ�� ");
	    		Sleep(1000);
	    		system ("cls");
	    		goto again_6;
	    	    break;
			}
	}
}
table* Create_table_Doc() {
    FILE *fp = fopen("table.txt", "rt"); // ʹ����ȷ���ļ���
    if (fp == NULL) {
        printf("File open error");
        exit(-1);
    }
    table *mhead;
    mhead = (table *)malloc(sizeof(table));
    mhead->next = NULL;
    table *p, *p1, *q;
    p = (table *)malloc(sizeof(table));
    p = mhead;
    p1 = (table *)malloc(sizeof(table));
    p1->next = NULL;

    // ��ȡ�ļ����ݲ���������
    if (fscanf(fp, "%d %d %d %d", &p1->tabledroom, &p1->tablenum, &p1->seat, &p1->state) != EOF) {
        p->next = p1;
        while (p->next) {
            p = p->next;
        }
        while (fgetc(fp) != EOF) {
            q = (table *)malloc(sizeof(table));
            fscanf(fp, "%d %d %d %d", &q->tabledroom, &q->tablenum, &q->seat, &q->state);
            p->next = q;
            q->next = NULL;
            p = p->next;
        }

        // ɾ�����һ���ڵ�
        table *p2 = (table *)malloc(sizeof(table));
        p2 = mhead;
        while (p2->next->next) {
            p2 = p2->next;
        }
        p2->next = NULL;
    } else {
        return NULL;
    }
    fclose(fp);
    return mhead;
}
order* Create_Order_Doc() {// ��������������ļ���������
    FILE *fp = fopen("order.txt", "rt");
    if (fp == NULL) {
        printf("�ļ��򿪴���");
        exit(-1);
    }

    order *ohead = (order *)malloc(sizeof(order));
    ohead->next = NULL;
    order *p, *q;

    while (1) {
        p = (order *)malloc(sizeof(order));
        if (fscanf(fp, "%s %d %d %s %d %d", p->name, &p->menu_num, &p->quantity,&p->dishesname,&p->dishesprice,&p->tablenum) != 4) {
            free(p);
            break;
        }

        p->next = NULL;

        if (ohead->next == NULL) {
            ohead->next = p;
        } else {
            q = ohead;
            while (q->next != NULL) {
                q = q->next;
            }
            q->next = p;
        }
    }

    fclose(fp);
    return ohead;
}
void menucontrol() {
    struct menu *mmhead;
    mmhead = (menu*)malloc(sizeof(menu));
	mmhead->next =NULL;
    mmhead = Create_menu_Doc();
    sortMenu(mmhead);
    again_7:
    printf("****************************************\n");
    printf("1. ���Ӳ�Ʒ\n");
    printf("2. ɾ����Ʒ\n");
    printf("3. �޸Ĳ�Ʒ�۸�\n");
    printf("4. ����˵���Ϣ\n");
    printf("0. �˳�\n");
    printf("****************************************\n");
    int choice;
    printf("����������ѡ��\n");
    scanf("%d", &choice);
    system("cls");
    switch (choice) {
        case 1: 
        	Printf_menu_Doc(mmhead);
            Insert_menu_Doc(mmhead);
            system("cls");
            sortMenu(mmhead);
            InMenufile(mmhead);
            Printf_menu_Doc(mmhead);
            goto again_7;
            break;
        case 2:
            Printf_menu_Doc(mmhead);
            Delete_menu_Doc(mmhead);
            InMenufile(mmhead);
            system("cls");
            Printf_menu_Doc(mmhead);
            goto again_7;
            break;
        case 3: 
            Printf_menu_Doc(mmhead);
            After_menu_Doc(mmhead);
            system("cls");
            InMenufile(mmhead);
            Printf_menu_Doc(mmhead);
            goto again_7;
            break;
        case 4: 
        	sortMenu(mmhead);
            Printf_menu_Doc(mmhead);
            system("pause");
            system("cls"); 
            goto again_7;
            break;
        case 0:  
            return;
            break;
    }
}
void tablecontrol(){
 struct table *thead;
    thead = (struct table *)malloc(sizeof(struct table));
    thead->next = NULL;
    thead = Create_table_Doc();
    again_8:
    printf("****************************************\n");
    printf("1. ���Ӳ���\n");
    printf("2. ɾ������\n");
    printf("3. �޸Ĳ���״̬\n");
    printf("4. ���������Ϣ\n");
    printf("0. �˳�\n");
    printf("****************************************\n");
    int choice;
    printf("����������ѡ��\n");
    scanf("%d", &choice);
    system("cls");
    switch (choice) {
        case 1: 
        	printf_table_Doc(thead);
            Insert_table_Doc(thead);
            system("cls");
            InTablefile(thead);
            sortTable(thead);
            printf_table_Doc(thead);
            goto again_8;
            break;
        case 2:
        	printf_table_Doc(thead);
            Delete_table_Doc(thead);
            system("cls");
            InTablefile(thead);
            printf_table_Doc(thead);
            goto again_8;
            break;
        case 3: 
        	printf_table_Doc(thead);
            After_table_Doc(thead);
            InTablefile(thead);
            system("cls");
            printf_table_Doc(thead);
            goto again_8;
            break;
        case 4: 
            printf_table_Doc(thead);
            system("pause");
            system("cls"); 
            goto again_8; 
            break;
        case 0: 
            return;
            break;
    }	
}
void ordercontrol(){
    FILE *fp = fopen("order.txt", "rt"); // ��ֻ���ı�ģʽ���ļ�
    if (fp == NULL) {
        printf("�ļ��򿪴���\n");
        return;
    }
    printf("���ж�����Ϣ��\n");
    printf("===================================\n");
    printf("����  �˵����  ����  ��Ʒ����  ��Ʒ�۸�  ����\n");

    char name[50], dishesname[50];
    int menu_num, quantity, dishesprice, tablenum;

    // ���ж�ȡ�ļ��еĶ�����Ϣ�����������̨
    while (fscanf(fp, "%s %d %d %s %d %d", name, &menu_num, &quantity, dishesname, &dishesprice, &tablenum) != EOF) {
        printf("%s\t%d\t%d\t%s\t%d\t%d\n", name, menu_num, quantity, dishesname, dishesprice, tablenum);
    }
    printf("===================================\n");
    fclose(fp); // �ر��ļ�
}	
void createorder(char name[],order* ohead){
	table* thead;
	thead = Create_table_Doc();
	printf("\n�밴������������ѡ��λ��\n");
	sortTable(thead);
	Printf_Table_Doc(thead);
	int num;
	scanf("%d",&num);
	after_table_Doc(thead,num);
    again_9:
    //����д 
    printf("==================================\n");
	printf("     1. ��˻�Ӳ� \n"); 
	printf("     2. ɾ��       \n");
	printf("     3. �鿴       \n");
	printf("     0. �˳�       \n");
	printf("==================================\n");
	int choice;
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:Insert_order_Doc(ohead,name,num);goto again_9;
		case 2:Delete_order_Doc(ohead,name);goto again_9;
		case 3:Printf_order_Doc(ohead,name);goto again_9;
		case 0:return;break;
		default:
	    	{
	    		printf("�����������������ѡ�� ");
	    		Sleep(1000);
	    		system ("cls");
	    		goto again_9;
	    	    break;
			}	
	} 
}
struct menu *Create_menu_Doc() {
    FILE *fp = fopen("menu.txt", "rt");
    if (fp == NULL) {
        printf("file open error");
        exit(-1);
    }

    struct menu *mhead = (struct menu *)malloc(sizeof(struct menu));
    mhead->next = NULL;
    struct menu *p, *q;

    while (1) {
        p = (struct menu *)malloc(sizeof(struct menu));
        if (fscanf(fp, "%d %s %d", &p->menunum, p->dishesname, &p->dishesprice) != 3) {
            free(p);
            break;
        }

        p->next = NULL;
        if (mhead->next == NULL) {
            mhead->next = p;
        } else {
            q = mhead;
            while (q->next != NULL) {
                q = q->next;
            }
            q->next = p;
        }
    }

    fclose(fp);
    return mhead;
}
void Printf_Table_Doc(table *mhead){//��дPֻ��ӡ���е� 
    printf("===========================\n");
    printf("   ���ڿ��еĲ���\n");
    printf("===========================\n");
    printf("�������\t�������\t��λ��\t״̬\n");
    table *ptr;
    for (ptr = mhead->next; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->state == 0) { // ֻ��ӡ���еĲ�����Ϣ
            printf("%d\t\t%d\t\t%d\t%d\n", ptr->tabledroom, ptr->tablenum, ptr->seat, ptr->state);
        }
    }
}
void Printf_menu_Doc(struct menu *mhead) {
    printf("===========================\n");
    printf("   �˵���Ϣ\n");
    printf("===========================\n");
    printf("���\t     ����\t �۸�\n");
    struct menu *ptr;
    for (ptr = mhead->next; ptr != NULL; ptr = ptr->next) {
        printf("%d\t%10s%8d\n", ptr->menunum, ptr->dishesname, ptr->dishesprice);
    }	
}
void sortMenu(menu *mmhead) {
    struct menu *p, *q, *r;
    r = NULL;
    while (r != mmhead->next) {
        p = mmhead;
        q = p->next;
        while (q->next != r) {
            if (p->next->menunum > q->next->menunum) {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
                q = p->next;
            } else {
                p = p->next;
                q = p->next;
            }
        }
        r = q;
    }
}
menu *Insert_menu_Doc(struct menu *mmhead) {
    struct menu *ptr, *p;
    ptr = mmhead;
    int n;
    printf("\n����������Ҫ���ӵĲ�Ʒ��Ŀ��\n ");
    scanf("%d", &n);

    while (n) {
        p = (struct menu *)malloc(sizeof(struct menu));
        printf("�������Ʒ�� ��ţ����֣��۸�\n");
        scanf("%d %s %d", &p->menunum, p->dishesname, &p->dishesprice);
        if (ptr->next == NULL) {
            ptr->next = p;
            p->next = NULL;
        } else {
            p->next = ptr->next;
            ptr->next = p;
        }
        n--;
    }
    return mmhead;
}
menu *Delete_menu_Doc(struct menu *mmhead) {
    struct menu *ptr1, *ptr2;
    int n;
    printf("\n����������Ҫɾ���Ĳ�Ʒ����Ŀ��  ");
    scanf("%d", &n);
    ptr1 = (struct menu *)malloc(sizeof(struct menu));
    ptr2 = (struct menu *)malloc(sizeof(struct menu));
    ptr1 = mmhead;
    ptr2 = mmhead->next;

    int num;
    while (n) {
        printf("����������Ҫɾ���Ĳ�Ʒ�ı�ţ�  ");
        scanf("%d", &num);
        while (ptr2 != NULL) {
            if (ptr2->menunum == num) {
                ptr1->next = ptr2->next;
                free(ptr2);
                break;
            }
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
        n--;
    }
    return mmhead;
}
void After_menu_Doc(struct menu *mhead) { // �޸Ĳ˵���Ϣ
    int choice;
    int num;
    struct menu *ptr;
    printf("����������Ҫ�޸ĵĲ�Ʒ��ţ� ");
    scanf("%d", &num);
    printf("===========================\n");
    printf("1. �۸�\n");
    printf("===========================\n");
    printf("\n����������Ҫ�޸ĵ���Ϣ�� ");
    scanf("%d", &choice);
    for (ptr = mhead->next; ptr != NULL; ptr = ptr->next) {
        if (ptr->menunum == num) {
            switch (choice) {
                case 1:
                    int price;
                    printf("����������Ҫ�޸ĳ�Ϊ�ļ۸�");
                    scanf("%d", &price);
                    ptr->dishesprice = price;
                    break;
                // Add other cases for additional modifications if needed
            }
            break;
        }
    }
    InMenufile(mhead);
}
void InMenufile(struct menu *mhead) { // ���˵���Ϣд���ļ���ʵ���ļ��ĸ��� 
    FILE *fp;
    if ((fp = fopen("menu.txt", "w")) == NULL) {
        printf("file open error");
        exit(0);
    }

    struct menu *ptr;
    for (ptr = mhead->next; ptr != NULL; ptr = ptr->next) {
        fprintf(fp, "%d %s %d\n", ptr->menunum, ptr->dishesname, ptr->dishesprice);
    }

    if (fclose(fp)) {
        printf("con not close the file\n");
        exit(0);
    }
}
struct table *Insert_table_Doc(struct table *thead) {
    struct table *ptr, *p;
    ptr = thead;
    int n;
    printf("\n����������Ҫ���ӵĲ�����Ŀ��\n");
    scanf("%d", &n);

    while (n) {
        p = (struct table *)malloc(sizeof(struct table));
        printf("��������������ڲ�����ţ�������ţ���λ����״̬��0��ʾ���У�1��ʾռ�ã�2��ʾԤ������\n");
        scanf("%d %d %d %d", &p->tabledroom, &p->tablenum, &p->seat, &p->state);
        
        if (ptr->next == NULL) {
            ptr->next = p;
            p->next = NULL;
        } else {
            p->next = ptr->next;
            ptr->next = p;
        }
        n--;
    }
    return thead;
}
struct table *Delete_table_Doc(struct table *thead) {
    struct table *ptr1, *ptr2;
    int n;
    printf("\n����������Ҫɾ���Ĳ�������Ŀ��  ");
    scanf("%d", &n);
    ptr1 = (struct table *)malloc(sizeof(struct table));
    ptr2 = (struct table *)malloc(sizeof(struct table));
    ptr1 = thead;
    ptr2 = thead->next;

    int tableNum;
    while (n) {
        printf("����������Ҫɾ���Ĳ����ı�ţ�  ");
        scanf("%d", &tableNum);
        while (ptr2 != NULL) {
            if (ptr2->tablenum == tableNum) {
                ptr1->next = ptr2->next;
                free(ptr2);
                break;
            }
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
        n--;
    }
    return thead;
}
void After_table_Doc(struct table *thead) {
    int num, choice;
    struct table *ptr;

    printf("����������Ҫ�޸ĵĲ�����ţ� ");
    scanf("%d", &num);

    printf("===========================\n");
    printf("1. ״̬\n");
    printf("===========================\n");
    printf("\n����������Ҫ�޸ĵ�״̬�� ");
    scanf("%d", &choice);

    for (ptr = thead->next; ptr != NULL; ptr = ptr->next) {
        if (ptr->tablenum == num) {
            switch (choice) {
                case 1:
                    int newState;
                    printf("����������Ҫ�޸ĳɵ�״̬��");
                    scanf("%d", &newState);
                    ptr->state = newState;
                    break;
                // Add other cases for additional modifications if needed
            }
            break;
        }
    }
    InTablefile(thead);
}
void InTablefile(struct table *thead) {
    FILE *fp;
    if ((fp = fopen("table.txt", "w")) == NULL) {
        printf("file open error");
        exit(0);
    }

    struct table *ptr;
    for (ptr = thead->next; ptr != NULL; ptr = ptr->next) {
        fprintf(fp, "%d %d %d %d\n", ptr->tabledroom, ptr->tablenum, ptr->seat, ptr->state);
    }

    if (fclose(fp)) {
        printf("con not close the file\n");
        exit(0);
    }
}
void printf_table_Doc(struct table *thead) {
    printf("===========================\n");
    printf("   ������Ϣ\n");
    printf("===========================\n");
    printf("���ڲ��� ������� ��λ�� ״̬\n");
    struct table *ptr;
    for (ptr = thead->next; ptr != NULL; ptr = ptr->next) {
        printf("%d%14d%6d%6d\t\n", ptr->tabledroom, ptr->tablenum, ptr->seat, ptr->state);
    }
}
void sortTable(struct table *thead) {
    struct table *p, *q, *r;
    r = NULL;
    while (r != thead->next) {
        p = thead;
        q = p->next;
        while (q->next != r) {
            if (p->next->tabledroom > q->next->tabledroom ||
                (p->next->tabledroom == q->next->tabledroom && p->next->tablenum > q->next->tablenum)) {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
                q = p->next;
            } else {
                p = p->next;
                q = p->next;
            }
        }
        r = q;
    }
}
struct order *Insert_order_Doc(struct order *ohead, char name[],int num) {
    struct menu *mhead;
    mhead = (menu*)malloc(sizeof(menu));
	mhead->next =NULL;
    mhead = Create_menu_Doc();
    struct order *ptr, *p;
    ptr = ohead;
    printf("�˵�������ѡ��\n");
    Printf_menu_Doc(mhead); // ����˵���ѡ��
	printf("\n�����������Ĳ�Ʒ��ź������������껻�����0 0 ��β������ͣ�\n");
	int menuNum,quantity;
    while (scanf("%d %d", &menuNum, &quantity)&&menuNum!=0&&quantity!=0) {
        p = (struct order *)malloc(sizeof(struct order));
        struct menu *temp = mhead;
        while (temp != NULL) {
            if (temp->menunum == menuNum) {
                p->menu_num = menuNum;
                strcpy(p->name, name);
                strcpy(p->dishesname,temp->dishesname);
                p->quantity = quantity;
                p->tablenum =num;
                p->dishesprice=temp->dishesprice;
                p->next = NULL;
                break;
            }
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("�Ҳ����ò�Ʒ��ţ�������ѡ��\n");
            free(p); // �ͷŵ�ǰ�����ڵ���ڴ�
            continue;
        }

        if (ptr->next == NULL) {
            ptr->next = p;
        } else {
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = p;
        }
	
    }
    	printf("�㵥����ɡ�\n");
    return ohead;
}
struct order *Delete_order_Doc(struct order *ohead,char name[]) {
    struct order *ptr1, *ptr2;
    int n;
    printf("\n����������Ҫɾ���Ķ�������Ŀ��  ");
    scanf("%d", &n);
    ptr1 = (struct order *)malloc(sizeof(struct order));
    ptr2 = (struct order *)malloc(sizeof(struct order));
    ptr1 = ohead;
    ptr2 = ohead->next;

    while (n) {
        printf("����������Ҫɾ���Ķ����ı�ţ�  ");
        int num;
        scanf("%d", &num);
        while (ptr2 != NULL) {
            if (ptr2->menu_num == num && strcmp(ptr2->name, name) == 0) {
                ptr1->next = ptr2->next;
                free(ptr2);
                break;
            }
            ptr1 = ptr2;
            ptr2 = ptr2->next;
        }
        n--;
    }
    return ohead;
}
void Printf_order_Doc(order *ohead, char name[]) {
    order *temp = ohead->next;
    int totalAmount = 0;
    int found = 0; // ����Ƿ��ҵ��˶�Ӧ�˿͵Ķ���

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) { // ��鶩���Ĺ˿������Ƿ�ƥ��
            if (!found) {
                printf("�˿� %s �Ķ�����\n", name);
                printf("����λ��: %d\n", temp->tablenum);
                printf("�˺�     ����     �۸�     ����:\n");
                found = 1; // �ҵ��˶�Ӧ�˿͵Ķ���
            }
            printf("%d\t%s%6d%6d \n", temp->menu_num,temp->dishesname,temp->dishesprice,temp->quantity);
            totalAmount += temp->dishesprice*temp->quantity;
        }
        temp = temp->next;
    }

    if (found) {
        printf("�ܽ��: %d\n", totalAmount);
    } else {
        printf("δ�ҵ��˿� %s �Ķ�����\n", name);
    }
}
void InorderFile(order*ohead) {
    FILE *fp;
    if ((fp = fopen("order.txt", "a+")) == NULL) {
        printf("�ļ��򿪴���");
        exit(0);
    }

    order *ptr;
    for (ptr = ohead->next; ptr != NULL; ptr = ptr->next) {
        fprintf(fp, "%s %d %d %s %d %d\n", ptr->name, ptr->menu_num, ptr->quantity,ptr->dishesname,ptr->dishesprice,ptr->tablenum);
    }

    if (fclose(fp)) {
        printf("�޷��ر��ļ�\n");
        exit(0);
    }
}
void after_table_Doc(struct table *thead,int num){ //�޸�ָ������
    struct table *ptr;
    for (ptr = thead->next; ptr != NULL; ptr = ptr->next) {
        if (ptr->tablenum == num) {
				ptr->state = 1;
                break;
            }
    }
    InTablefile(thead);
}
void ordercheak(const char* name) {
    FILE *fp = fopen("order.txt", "rt"); // ��ֻ���ı�ģʽ���ļ�
    if (fp == NULL) {
        printf("�ļ��򿪴���\n");
        return;
    }
    printf("����  �˵����  ����  ��Ʒ����  ��Ʒ�۸�  ����\n");
    printf("===================================\n");

    char order_name[50], dishesname[50];
    int menu_num, quantity, dishesprice, tablenum;

    // ���ж�ȡ�ļ��еĶ�����Ϣ�����������̨
    while (fscanf(fp, "%s %d %d %s %d %d", order_name, &menu_num, &quantity, dishesname, &dishesprice, &tablenum) != EOF) {
        if (strcmp(order_name, name) == 0) {
            printf("%s\t%d\t%d\t%s\t%d\t%d\n", order_name, menu_num, quantity, dishesname, dishesprice, tablenum);
        }
    }
    printf("===================================\n");
    fclose(fp); // �ر��ļ�
}



