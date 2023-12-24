#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <windows.h>
#include <stdlib.h>
using namespace std;
# define MAX 100
// 结构体定义
//1.餐桌 
struct table{
	int tabledroom;//餐桌所在餐厅编号 
	int tablenum;//餐桌编号
	int seat;//餐桌座位数
	int state;//餐桌是否空闲 0表示空闲 1表示占用 2表示预定 
	struct table* next;
};
//2.菜单 
struct menu{
	int menunum;//菜的编号 
	char dishesname[20];//菜名 
	int dishesprice;//菜的价格 
	struct menu *next; 
};
//3.顾客订单 
struct order{
	char name[20];//用户名 
    int menu_num; // 菜品编号
    int quantity; // 数量
    char dishesname[20];//菜名 
    int dishesprice;//菜的价格 
    int tablenum;//	所选餐桌编号
    struct order* next;
};
//6.顾客账户 
struct Customer {
    char CustName[20];  // 顾客名称
    char CustCode[20];  // 密码
};
struct Customer cust[MAX];//顾客最大数量(账户注册数量)
//2个主登录函数 
void loginCustomer(); //顾客登录 里面包含注册 // 顾客信息相关函数声明
void loginManager();//管理员登录 // 管理员信息相关函数声明 
void custoperate(char name[]);//顾客操作 
void manageoperate();//管理员操作 
void menucontrol(); //管理菜单 
void ordercontrol();//管理订单 
void tablecontrol();//管理餐桌  
int readCustomer(); // 方便查看顾客注册数 
//餐桌管理相关函数
table* Create_table_Doc(); //从文件中创建餐桌数据链表
void Printf_Table_Doc(struct table *mhead); //打印空的餐桌信息
table *Insert_table_Doc(struct table *thead); //新增餐桌数据
table *Delete_table_Doc(struct table *thead); //删除餐桌数据
void After_table_Doc(struct table *thead); //修改餐桌信息
void InTablefile(struct table *thead); //餐桌数据写入文件
void printf_table_Doc(struct table *thead);//打印全部餐桌信息
void sortTable(struct table *thead); //餐桌数据排序
//菜单管理相关函数
menu*Create_menu_Doc(); //从文件中创建菜单数据链表
void Printf_menu_Doc(struct menu *mhead); //打印菜单信息
void InMenufile(struct menu *mhead); //菜单数据写入文件
void After_menu_Doc(struct menu *mhead); //修改菜单信息
menu *Insert_menu_Doc(struct menu *mmhead); //新增菜单数据
menu *Delete_menu_Doc(struct menu *mmhead); //删除菜单数据
void sortMenu(struct menu *mmhead); //菜单数据排序
//订单管理相关函数
void createorder(char name[],order* ohead);//点菜 
order* Create_Order_Doc(); //从文件中创建订单数据链表 
void Printf_order_Doc(order *ohead,char name[]); //打印订单信息
struct order *Insert_order_Doc(order *ohead, char name[], int num); //新增订单数据
struct order *Delete_order_Doc(order *ohead,char name[]); //删除订单数据
void InorderFile(order*ohead); //订单数据写入文件
void after_table_Doc(struct table *thead,int num); //修改餐桌状态
void ordercheak(const char* name); //查看指定用户订单
int main(){
	onceagain:
	//首先输入自己的身份
	int userType;  // 1表示顾客，2.表示老板 3.服务员 
	printf("====================\n");
	printf("   请输入身份      \n");
	printf("    1.顾客          \n");
	printf("    2.管理员        \n");
	printf("=====================\n");
	printf("请输入您想要进行的操作： ");
	scanf("%d",&userType);
	system ("cls"); 
	if(userType==1)
	{
		loginCustomer();//顾客登录函数 
	}
	else if(userType==2)
	{
		loginManager(); //管理员登陆 
		manageoperate();//管理员操作
	} 
	else
	{
    printf("\n\n\t\t\t您的输入有误，请重新选择\n");
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
	//初始化一组密码 fprintf(fp, "zhanghaobo 123456\n");//初始化完直接注释 
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
	printf("      欢迎来到无敌美少女餐厅       \n");
	printf("\n");
	printf("    1. 登录\t  2.注册              \n");
	printf("\n");
	printf("***********************************\n");
	printf("请输入您的选择:   ");
	int t=0;
	while (!inputValid)
	{
	scanf("%d", &choice);
	int flag =1,time=0;
	switch (choice) {
		case 1:
				// 执行登录操作 
				again_2:
				custCount = readCustomer(); 
				printf("\n请输入用户名: ");
    			scanf("%s", name);
    			printf("\n请输入密码: ");
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
	 			printf("账号或密码错误，请重新输入！ \n");
	 			t++;if(t>5){printf("错误次数过多，程序退出");exit(0);}
	 			goto again_2;
			}
			else 
			{
				printf("登录成功！\n");
				system("pause"); //  可以实现冻结屏幕，便于观察程序执行结果 
	 			system ("cls");  // 清屏命令 
			}	
				inputValid = 1; // 输入有效，退出循环
				break;
		case 2:
				// 执行注册操作
				again_3:
				printf("请输入您的用户名：  ");
				scanf("%s",name);
					for (int i=0;i<custCount;i++)
				{
						if (strcmp(name,cust[i].CustName) == 0)   //  比较两个参数的大小，相同返回零 
						{
						printf("该用户名已存在");
						system("pause"); //  可以实现冻结屏幕，便于观察程序执行结果 
				   		goto  again_3;		 
						}	
				}
					printf("请输入密码： ");
					scanf("%s",code);
					strcpy (cust[custCount].CustName,name);
					strcpy (cust[custCount].CustCode,code);	//fscanf  从文件中读取数据保存到前面的链表中去 
					fprintf(fp,"%s   %s\n",cust[custCount].CustName,cust[custCount].CustCode);
					//   将新增加的用户的用户名和密码写入文件中去 
					printf("注册成功！\n");
					system("pause"); //  可以实现冻结屏幕，便于观察程序执行结果 
	 				system ("cls");	
					inputValid = 1; // 输入有效，退出循环
					goto again_2; 
					break;
		default:
			printf("您的输入有误，请重新选择想要操作的内容 :  ");
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
	//开始进入顾客选项页面，选择操作 
	custoperate(name);
}
void loginManager(){
	FILE *fp = fopen("manage.txt", "a+");
	if (fp==NULL)
	{
		printf(" file open error!\n");
		exit (0);
	}
	//初始化我们组5个人管理员账户，初始化完直接注释 
	/*fprintf(fp, "zhanghaobo    123456\n");
	fprintf(fp, "zhengyabo     123456\n");
	fprintf(fp, "zhangjiahui   123456\n");
	fprintf(fp, "zhaoxinkai    123456\n");
	fprintf(fp, "liuran        123456\n");*/
	char storedName[20], storedCode[20];
    char Name[20], Code[20];int ii=0;//用于记录输入次数，过多就返回最初始页面 
	again_4:
    printf("\n请输入用户名: ");
    scanf("%s", Name);
    printf("\n请输入密码: ");
    scanf("%s", Code);

    int found = 0; // 标记是否找到匹配的账户

    fseek(fp, 0, SEEK_SET); // 将文件指针重新定位到文件开头

    while (fscanf(fp, "%s %s", storedName, storedCode) == 2) {
        if (strcmp(Name, storedName) == 0 && strcmp(Code, storedCode) == 0) {
            found = 1; // 找到匹配的账户
            break;
        }
    }
    if (!found)
	{
	 	printf("账号或密码错误，请重新输入！ \n");
	 	ii++; if(ii>5){printf("错误次数过多，程序退出");exit(0);}
	 	goto again_4;
	}
	else 
	{
		printf("登录成功！\n");
		system("pause"); //  可以实现冻结屏幕，便于观察程序执行结果 
		system ("cls");  // 清屏命令 
	}
    fclose(fp); 
}
int readCustomer(){//查看注册顾客账户 
    FILE *fp;
    int custCount = 0;

    if ((fp = fopen("cust.txt", "r")) == NULL) {
        printf("文件打开失败!\n");
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
	printf("     1. 开始点菜        \n"); 
	printf("     2. 查看订单        \n");
	printf("     0. 退出            \n");
	printf("==================================\n");
	int choose;
	printf("请输入您的选择:  ");
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
	    		printf("您的输入错误，请重新选择！ ");
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
	printf("     1. 查看菜单并修改  \n"); 
	printf("     2. 查看订单        \n");
	printf("     3. 管理餐桌        \n");
	printf("     0. 退出            \n");
	printf("==================================\n");
	int choose;
	printf("请输入您的选择:  ");
	scanf("%d",&choose);
	switch(choose)
	{
		case 1:	menucontrol();goto again_6; 
		case 2: ordercontrol();goto again_6;
		case 3: tablecontrol();goto again_6;
		case 0:return;break;
		default:
	    	{
	    		printf("您的输入错误，请重新选择！ ");
	    		Sleep(1000);
	    		system ("cls");
	    		goto again_6;
	    	    break;
			}
	}
}
table* Create_table_Doc() {
    FILE *fp = fopen("table.txt", "rt"); // 使用正确的文件名
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

    // 读取文件数据并创建链表
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

        // 删除最后一个节点
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
order* Create_Order_Doc() {// 创建订单链表和文件进入链表
    FILE *fp = fopen("order.txt", "rt");
    if (fp == NULL) {
        printf("文件打开错误");
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
    printf("1. 增加菜品\n");
    printf("2. 删除菜品\n");
    printf("3. 修改菜品价格\n");
    printf("4. 输出菜单信息\n");
    printf("0. 退出\n");
    printf("****************************************\n");
    int choice;
    printf("请输入您的选择：\n");
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
    printf("1. 增加餐桌\n");
    printf("2. 删除餐桌\n");
    printf("3. 修改餐桌状态\n");
    printf("4. 输出餐桌信息\n");
    printf("0. 退出\n");
    printf("****************************************\n");
    int choice;
    printf("请输入您的选择：\n");
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
    FILE *fp = fopen("order.txt", "rt"); // 以只读文本模式打开文件
    if (fp == NULL) {
        printf("文件打开错误。\n");
        return;
    }
    printf("所有订单信息：\n");
    printf("===================================\n");
    printf("姓名  菜单编号  数量  菜品名称  菜品价格  桌号\n");

    char name[50], dishesname[50];
    int menu_num, quantity, dishesprice, tablenum;

    // 逐行读取文件中的订单信息并输出到控制台
    while (fscanf(fp, "%s %d %d %s %d %d", name, &menu_num, &quantity, dishesname, &dishesprice, &tablenum) != EOF) {
        printf("%s\t%d\t%d\t%s\t%d\t%d\n", name, menu_num, quantity, dishesname, dishesprice, tablenum);
    }
    printf("===================================\n");
    fclose(fp); // 关闭文件
}	
void createorder(char name[],order* ohead){
	table* thead;
	thead = Create_table_Doc();
	printf("\n请按照您的人数先选择位置\n");
	sortTable(thead);
	Printf_Table_Doc(thead);
	int num;
	scanf("%d",&num);
	after_table_Doc(thead,num);
    again_9:
    //继续写 
    printf("==================================\n");
	printf("     1. 点菜或加菜 \n"); 
	printf("     2. 删菜       \n");
	printf("     3. 查看       \n");
	printf("     0. 退出       \n");
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
	    		printf("您的输入错误，请重新选择！ ");
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
void Printf_Table_Doc(table *mhead){//大写P只打印空闲的 
    printf("===========================\n");
    printf("   现在空闲的餐桌\n");
    printf("===========================\n");
    printf("餐厅编号\t餐桌编号\t座位数\t状态\n");
    table *ptr;
    for (ptr = mhead->next; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->state == 0) { // 只打印空闲的餐桌信息
            printf("%d\t\t%d\t\t%d\t%d\n", ptr->tabledroom, ptr->tablenum, ptr->seat, ptr->state);
        }
    }
}
void Printf_menu_Doc(struct menu *mhead) {
    printf("===========================\n");
    printf("   菜单信息\n");
    printf("===========================\n");
    printf("编号\t     名称\t 价格\n");
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
    printf("\n请输入你想要增加的菜品数目：\n ");
    scanf("%d", &n);

    while (n) {
        p = (struct menu *)malloc(sizeof(struct menu));
        printf("请输入菜品的 编号，名字，价格：\n");
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
    printf("\n请输入你想要删除的菜品的数目：  ");
    scanf("%d", &n);
    ptr1 = (struct menu *)malloc(sizeof(struct menu));
    ptr2 = (struct menu *)malloc(sizeof(struct menu));
    ptr1 = mmhead;
    ptr2 = mmhead->next;

    int num;
    while (n) {
        printf("请输入你想要删除的菜品的编号：  ");
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
void After_menu_Doc(struct menu *mhead) { // 修改菜单信息
    int choice;
    int num;
    struct menu *ptr;
    printf("请输入你想要修改的菜品编号： ");
    scanf("%d", &num);
    printf("===========================\n");
    printf("1. 价格\n");
    printf("===========================\n");
    printf("\n请输入你想要修改的信息： ");
    scanf("%d", &choice);
    for (ptr = mhead->next; ptr != NULL; ptr = ptr->next) {
        if (ptr->menunum == num) {
            switch (choice) {
                case 1:
                    int price;
                    printf("请输入你想要修改成为的价格：");
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
void InMenufile(struct menu *mhead) { // 将菜单信息写入文件，实现文件的更新 
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
    printf("\n请输入你想要增加的餐桌数目：\n");
    scanf("%d", &n);

    while (n) {
        p = (struct table *)malloc(sizeof(struct table));
        printf("请输入餐桌的所在餐厅编号，餐桌编号，座位数，状态（0表示空闲，1表示占用，2表示预定）：\n");
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
    printf("\n请输入你想要删除的餐桌的数目：  ");
    scanf("%d", &n);
    ptr1 = (struct table *)malloc(sizeof(struct table));
    ptr2 = (struct table *)malloc(sizeof(struct table));
    ptr1 = thead;
    ptr2 = thead->next;

    int tableNum;
    while (n) {
        printf("请输入你想要删除的餐桌的编号：  ");
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

    printf("请输入你想要修改的餐桌编号： ");
    scanf("%d", &num);

    printf("===========================\n");
    printf("1. 状态\n");
    printf("===========================\n");
    printf("\n请输入你想要修改的状态： ");
    scanf("%d", &choice);

    for (ptr = thead->next; ptr != NULL; ptr = ptr->next) {
        if (ptr->tablenum == num) {
            switch (choice) {
                case 1:
                    int newState;
                    printf("请输入你想要修改成的状态：");
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
    printf("   餐桌信息\n");
    printf("===========================\n");
    printf("所在餐厅 餐桌编号 座位数 状态\n");
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
    printf("菜单如下请选择\n");
    Printf_menu_Doc(mhead); // 输出菜单供选择
	printf("\n请输入您想点的菜品编号和数量：（点完换行输出0 0 结尾结束点餐）\n");
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
            printf("找不到该菜品编号，请重新选择。\n");
            free(p); // 释放当前订单节点的内存
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
    	printf("点单已完成。\n");
    return ohead;
}
struct order *Delete_order_Doc(struct order *ohead,char name[]) {
    struct order *ptr1, *ptr2;
    int n;
    printf("\n请输入你想要删除的订单的数目：  ");
    scanf("%d", &n);
    ptr1 = (struct order *)malloc(sizeof(struct order));
    ptr2 = (struct order *)malloc(sizeof(struct order));
    ptr1 = ohead;
    ptr2 = ohead->next;

    while (n) {
        printf("请输入你想要删除的订单的编号：  ");
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
    int found = 0; // 标记是否找到了对应顾客的订单

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) { // 检查订单的顾客名字是否匹配
            if (!found) {
                printf("顾客 %s 的订单：\n", name);
                printf("餐桌位置: %d\n", temp->tablenum);
                printf("菜号     菜名     价格     数量:\n");
                found = 1; // 找到了对应顾客的订单
            }
            printf("%d\t%s%6d%6d \n", temp->menu_num,temp->dishesname,temp->dishesprice,temp->quantity);
            totalAmount += temp->dishesprice*temp->quantity;
        }
        temp = temp->next;
    }

    if (found) {
        printf("总金额: %d\n", totalAmount);
    } else {
        printf("未找到顾客 %s 的订单。\n", name);
    }
}
void InorderFile(order*ohead) {
    FILE *fp;
    if ((fp = fopen("order.txt", "a+")) == NULL) {
        printf("文件打开错误");
        exit(0);
    }

    order *ptr;
    for (ptr = ohead->next; ptr != NULL; ptr = ptr->next) {
        fprintf(fp, "%s %d %d %s %d %d\n", ptr->name, ptr->menu_num, ptr->quantity,ptr->dishesname,ptr->dishesprice,ptr->tablenum);
    }

    if (fclose(fp)) {
        printf("无法关闭文件\n");
        exit(0);
    }
}
void after_table_Doc(struct table *thead,int num){ //修改指定餐桌
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
    FILE *fp = fopen("order.txt", "rt"); // 以只读文本模式打开文件
    if (fp == NULL) {
        printf("文件打开错误。\n");
        return;
    }
    printf("姓名  菜单编号  数量  菜品名称  菜品价格  桌号\n");
    printf("===================================\n");

    char order_name[50], dishesname[50];
    int menu_num, quantity, dishesprice, tablenum;

    // 逐行读取文件中的订单信息并输出到控制台
    while (fscanf(fp, "%s %d %d %s %d %d", order_name, &menu_num, &quantity, dishesname, &dishesprice, &tablenum) != EOF) {
        if (strcmp(order_name, name) == 0) {
            printf("%s\t%d\t%d\t%s\t%d\t%d\n", order_name, menu_num, quantity, dishesname, dishesprice, tablenum);
        }
    }
    printf("===================================\n");
    fclose(fp); // 关闭文件
}



