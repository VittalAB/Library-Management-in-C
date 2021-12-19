#include<stdio.h>
#include<stdlib.h>
#define hashsize 1000
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<Windows.h>

struct node                                                                   /* hash table structure */
{
    int roll;
    char name[100];
    char usn[100];
    bool is_purchase;
    struct node *next;
};

struct node *head[hashsize]={NULL},*c;

struct Date
{
    int dd, mm, yyyy;
};

struct IS
{
    char name[50], BookName[50], USN[15];
    int BookId;
    struct Date doi;
    struct Date dor;
    struct IS *next;
};
struct IS *start=NULL;
struct IS *temp;

struct book
{
    char b_name[100];
    int id;
    char a_name[100];
    struct book *right,*left;
};
struct Node
{
    char b_name[100];
    int id;
    char a_name[100];
    struct Node *next;
};
typedef struct book *bk;
typedef struct Node *Tiny;
bk xroot=NULL;
Tiny first=NULL;


/********************************************************************************START OF BST OPERATION************************************************************/

struct array
{
    int roll;
    char name[100];
    char usn[100];
};
typedef struct array array;
array a[100];


/*N newnode(char name[],char usn[],int roll)
{
    N t;
    t=(struct b_node *)malloc(sizeof(struct b_node));
    strcpy(t->name,name);
    strcpy(t->usn,usn);
    t->roll=roll;

    t->right=NULL;
    t->left=NULL;
    return t;
}
*/
/*N insert_in_BST(N root,char name[],char usn[],int roll)
{
    if(root==NULL)
        return newnode(name,usn,roll);

    int d;

    d=strcmp(root->name,name);

    if(d<0)
        root->right=insert_in_BST(root->right,name,usn,roll);
    if(d>0)
        root->left=insert_in_BST(root->left,name,usn,roll);

    return root;
}
*/
/*void display_b_node(N root)
{
    printf("\n\n");
    printf("|NAME OF THE STUDENT       :- %s\n",root->name);
    printf("|USN OF THE STUDENT        :- %s\n",root->usn);
    printf("|ROLL NO OF THE STUDENT IS :- %d\n\n",root->roll);

}*/

/*void inorder(struct b_node *root)
{
    if(root)
    {
        inorder(root->left);
        display_b_node(root);
        inorder(root->right);
    }
}

/*******************************************************************************END OF BST OPERATION****************************************************************************************/

FILE *fp_std;
FILE *fp_issue;
/******************************************************************************SORTING STUDENTS******************************************************************************************/

void sort_students()
{
     //N root=NULL;
    char name[101][101],usn[101][101];
    int roll[101];

    int i,j=0;
    for(i=0;i<hashsize;i++)
    {
        if(head[i]==NULL)
            continue;
        else
        {
            for(c=head[i];c!=NULL;c=c->next)
            {
                strcpy(name[j],c->name);
                strcpy(usn[j],c->usn);
                roll[j]=c->roll;
                j++;
            }
        }
    }
        for(int i=0;i<j;i++)
        {
            strcpy(a[i].name,name[i]);
            strcpy(a[i].usn,usn[i]);
            a[i].roll=roll[i];
        }



        int pass,swap;
    swap=1;
    //int i;
    for(pass=j-1;pass>=0 && swap ;pass--)
    {
        swap=0;

        for(i=0;i<=pass-1;i++)
        {
            if(a[i].roll > a[i+1].roll)
            {
                array t;
                t=a[i];
                a[i]=a[i+1];
                a[i+1]=t;
            }
        }
    }

    for(int i=0;i<j;i++)
    {
        printf("\n\n");
    printf("|NAME OF THE STUDENT       :- %s\n",a[i].name);
    printf("|USN OF THE STUDENT        :- %s\n",a[i].usn);
    printf("|ROLL NO OF THE STUDENT IS :- %d\n\n",a[i].roll);

    }

}

/******************************************************************************END OF SORTING STUDENTS******************************************************************************************/

void insert(char name[],char usn[],int roll)                        /******            inserting into hashtable              ******/
{
    int i;

    i=roll%hashsize;
                ///<<<<------                                   ///hasing function division method
    struct node *newnode=(struct node *)malloc(sizeof(struct node));
    strcpy(newnode->name,name);
    strcpy(newnode->usn,usn);
    newnode->roll=roll;
    newnode->next=NULL;


    if(head[i]==NULL)
        head[i]=newnode;
    else
    {
        c=head[i];
        while(c->next!=NULL)
            c=c->next;
        c->next=newnode;
    }
}
void display_data(struct node *n)                     /******* ************display hash data **************/
{
    printf("\n\n");
    printf("|NAME OF THE STUDENT       :- %s\n",n->name);
    printf("|USN OF THE STUDENT        :- %s\n",n->usn);
    printf("|ROLL NO OF THE STUDENT IS :- %d\n\n",n->roll);

}
void search(int roll)                                /********************* searching hashed data ****************************/
{
    //int roll;
    int i;
    i=roll%hashsize;
    if(head[i]==NULL)
        printf("NO STUDENT WITH ROLL NO %d EXIST IN OUR DATABASE \n",roll);
    else
    {
        for(c=head[i];c!=NULL;c=c->next)
        {
            if(c->roll==roll)
            {
                display_data(c);
                break;
            }
        }
        if(c==NULL)
           printf("NO STUDENT WITH ROLL NO %d EXIST IN OUR DATABASE \n",roll);

    }
}

void display()
{
    int i;
    for(i=0;i<hashsize;i++)
    {
        if(head[i]==NULL)
            continue;
        else
        {
            for(c=head[i];c!=NULL;c=c->next)
            {

                display_data(c);
                /** from here access the 3 file **/
            }
        }
    }
}
void load_data_from_file()
{
    printf("LOADING FILES PLEASE WAIT ...");
    printf(".... ");
    char name[100][100],usn[100][100];
    int roll[100];

    fp_std=fopen("std_rec.txt","r");


    if(!fp_std)
    {
        printf("oops file crashed !!!!\n");
        exit(1);
    }
    int n=0;

    while(!feof(fp_std))
    {
        fscanf(fp_std,"%s %s %d",name[n],usn[n],&roll[n]);
        n++;
    }

    int i=0;
    printf(".... ");

    while(i<n-1)
    {
        insert(name[i],usn[i],roll[i]);
        i++;
    }
    printf("\n");
    printf("NO OF LOADED FILES ..%d\n",n);

    fclose(fp_std);
}

void load_data_to_file()
{
    fp_std=fopen("std_rec.txt","w");


    int i;
    for(i=0;i<hashsize;i++)
    {
        if(head[i]==NULL)
            continue;
        else
        {
            for(c=head[i];c!=NULL;c=c->next)
            {
                fprintf(fp_std,"%s %s %d\n",c->name,c->usn,c->roll);
            }
        }
    }
    fclose(fp_std);
}

void delete_rec()
{
    printf("Enter RollNo \n");
    int roll;
    scanf("%d",&roll);
    int value=roll;

    int key = value % hashsize;

    //printf("KEY KEY KEY :- %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n",key);


    struct node *temp = head[key], *dealloc;
    if(temp != NULL)
    {
        if(temp->roll == value)
        {
            dealloc = temp->next;

            if(temp->next==NULL)
               {
                 head[key]=NULL;
                 return;
               }


            temp->roll = temp->next->roll;
            strcpy(temp->name,temp->next->name);
            strcpy(temp->usn,temp->next->usn);
            dealloc=temp->next;
            temp->next=dealloc->next;

            free(dealloc);
            //head[key]=NULL;
               return;
            //return 1;
        }
        else
        {
            while(temp->next)
            {
                if(temp->next->roll == value)
                {
                    dealloc = temp->next;
                    temp->next = temp->next->next;
                    free(dealloc);
                    return;
                }
                temp = temp->next;
            }
        }
    }
    return;
}

bk GETNODE()
{
	bk t;
	t=(bk)malloc(sizeof(struct book));
	if(t==NULL)
	{
		printf("Not created\n");
		exit(0);
	}
	t->right = t->left = NULL;
	return t;
}
Tiny Getnode()
{
	Tiny t;
	t=(Tiny)malloc(sizeof(struct Node));
	if(t==NULL)
	{
		printf("Not created\n");
		exit(0);
	}
	t->next = NULL;
	return t;
}
bk add_book(char bn[100],char an[100],int id)     // For adding the requested book
{
	bk t,c,p;
	t=GETNODE();
	strcpy(t->b_name,bn);
    strcpy(t->a_name,an);
    t->id=id;
	if(xroot ==NULL)
	{
	  return t;
    }
	c=xroot;
    p=NULL;
    while(c)
    {
        p=c;
        if(t->id<c->id)
        {
            c=c->left;
        }
        else
        {
            c=c->right;
        }
    }
    if(t->id<p->id)
    {
        p->left=t;
    }
    else
    {
        p->right=t;
    }
	FILE *ptr;
	ptr=fopen("BOOK.txt","a");
	if(ptr==NULL)
    {
        printf("File not found");
        return NULL;
    }
    fprintf(ptr,"%s\n%s\n%d\n\n",t->b_name,t->a_name,t->id);
    fclose(ptr);
	return xroot;
}
bk INSERT(char bn[100],char an[100],int id) //For adding the books from file
{
    bk t,c,p;
	t=GETNODE();
	strcpy(t->b_name,bn);
    strcpy(t->a_name,an);
    t->id=id;
	if(xroot ==NULL)
	  return t;
	c=xroot;
    p=NULL;
    while(c)
    {
        p=c;
        if(t->id<c->id)
        {
            c=c->left;
        }
        else
        {
            c=c->right;
        }
    }
    if(t->id<p->id)
    {
        p->left=t;
    }
    else
    {
        p->right=t;
    }
    return xroot;
}
Tiny INSERT_disp(char bn[100],char an[100],int id)  // For only linked list
{
	Tiny t,c;
	t=Getnode();
	strcpy(t->b_name,bn);
    strcpy(t->a_name,an);
    t->id=id;
	if(first ==NULL)
	  return t;
	c=first;
	while(c->next !=NULL)
	{
		c=c->next;
	}
	c->next = t;
	return first;
}
void LOAD_DATA_FROM_FILE()
{
    int n=0,a1;
    FILE *ptr;
	ptr=fopen("BOOK.txt","r");
    char t[100],t1[100];
	if(ptr==NULL)
    {
        printf("File not found");
        return;
    }
    while(fscanf(ptr,"%s\n%s\n%d\n\n",t,t1,&a1)!=EOF)
    {
        n++;
        xroot=INSERT(t,t1,a1);
        first=INSERT_disp(t,t1,a1);
    }
    fclose(ptr);
    printf("Number of loaded books: %d",n);
}
void ysearch(bk xroot)
{
    bk c=xroot;
    int k,flag=0;
    printf("Enter the book id to be ysearched:\n");
    scanf("%d",&k);
    while(c)
    {
        if(k==c->id)
        {
            flag=1;
            break;
        }
        else if(k<c->id)
        {
            c=c->left;
        }
        else
        {
            c=c->right;
        }
    }
    if(flag==1)
    {
		printf("%s\n%s\n%d\n\n",c->b_name,c->a_name,c->id);
    }
    else
    {
        printf("Element not found");
    }
}
void view_allbooks_onlyfile(Tiny first) //just from file
{
    Tiny t;
	if(first==NULL)
	{
		printf("Empty file\n");
		return;
	}
	t=first;
	while(t->next!=NULL)
	{
		printf("%s\n%s\n%d\n\n",t->b_name,t->a_name,t->id);
		t= t->next;
	}
	printf("%s\n%s\n%d\n\n",t->b_name,t->a_name,t->id);
}
void INORDER(bk xroot)
{
	if(xroot)
	{
		INORDER(xroot->left);
		printf("%s\n%s\n%d\n\n",xroot->b_name,xroot->a_name,xroot->id);
		INORDER(xroot->right);
	}
}
void xissue()
{
    FILE *fptr;
    fptr = fopen("IssueList.txt","a");
    int ch;
    do{
            struct IS *temp,*ptr;
            temp=(struct IS *)malloc(sizeof(struct IS));
            if(temp==NULL)
            {
                    printf("nOut of Memory Space:n");
                    return;
            }
            printf("Enter Name, USN, BookName, BookID and Date(mm/dd/yyyy)\n");
            scanf("%s%s%s%d%d%d%d",temp->name,temp->USN,temp->BookName,&temp->BookId,&temp->doi.dd, &temp->doi.mm, &temp->doi.yyyy);
            temp->next =NULL;
            if(start==NULL)
            {
                    start=temp;
            }
            else
            {
                    ptr=start;
                    while(ptr->next !=NULL)
                    {
                            ptr=ptr->next ;
                    }
                    ptr->next =temp;
            }
           if(fptr==NULL)
            {
                printf("Error\n");
            }
            else
            {
                while(temp!=NULL)
                {
                    fprintf(fptr,"\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d", temp->name,temp->USN,temp->BookName,temp->BookId,temp->doi.dd, temp->doi.mm, temp->doi.yyyy);
                    temp=temp->next;
                }
            }
            printf("Continue(1/0)?\n");
            scanf("%d",&ch);
        }while(ch);
            fclose(fptr);

}
int valid_date(int day, int mon, int year)
{
    int is_valid = 1, is_leap = 0;

    if (year >= 1800 && year <= 9999)
    {

        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if(mon >= 1 && mon <= 12)
        {
            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if(day > 28)
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}
int xsearch(char name[],struct IS *p)
{
    struct IS *r;
    FILE *fp;
    fp = fopen("ReturnList.txt","a");
    int year_diff, mon_diff, day_diff;
    if(!strcmp(name,p->name))
    {
            r=(struct IS *)malloc(sizeof(struct IS));
            printf("Name:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d\n", p->name,p->USN,p->BookName, p->BookId, p->doi.mm, p->doi.dd, p->doi.yyyy);
            printf("Date of Return(mm/dd/yyyy):\n");
            scanf("%d%d%d",&r->dor.mm,&r->dor.dd,&r->dor.yyyy);
            fprintf(fp,"\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d\nDateofReturn:%d/%d/%d", p->name, p->USN, p->BookName, p->BookId, p->doi.mm, p->doi.dd, p->doi.yyyy,r->dor.mm,r->dor.dd,r->dor.yyyy);
    {
                    if(!valid_date(p->doi.dd, p->doi.mm, p->doi.yyyy))
                {
                    printf("First date is invalid.\n");
                }

                if(!valid_date(r->dor.dd, r->dor.mm, r->dor.yyyy))
                {
                    printf("Second date is invalid.\n");
                    exit(0);
                }

                if(r->dor.dd < p->doi.dd)
                {
                    // borrow days from february
                    if (r->dor.mm == 3)
                    {
                        //  check whether year is a leap year
                        if ((r->dor.yyyy % 4 == 0 && r->dor.yyyy % 100 != 0) || (r->dor.yyyy % 400 == 0))
                        {
                            r->dor.dd += 29;
                        }
                        else
                        {
                            r->dor.dd += 28;
                        }
                    }
                    // borrow days from April or June or September or November
                    else if (r->dor.mm == 5 || r->dor.mm == 7 || r->dor.mm == 10 || r->dor.mm == 12)
                    {
                       r->dor.dd += 30;
                    }
                    // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
                    else
                    {
                       r->dor.dd += 31;
                    }
                    r->dor.mm = r->dor.mm - 1;
                }
                if (r->dor.mm < p->doi.mm)
                {
                    r->dor.mm += 12;
                    r->dor.yyyy -= 1;
                }
                day_diff = r->dor.dd - p->doi.dd;
                mon_diff = r->dor.mm - p->doi.mm;
                year_diff = r->dor.yyyy - p->doi.yyyy;
                printf("Difference: %d years, %d months, %d days.", year_diff, mon_diff, day_diff);
                if(day_diff <= 7 && mon_diff==0 && year_diff==0)
                    printf("\nNo Fine\n");
                else if((day_diff>7 || day_diff==0) && (mon_diff>0 || mon_diff==0) && (year_diff>0 || year_diff==0))
                    printf("\nFine:%d\n",(((year_diff*365)*2)+((mon_diff*30)*2)+((day_diff)*2)-(7*2)));
                return 0;
        }

     }
    /* else
            {
                printf("...............\n");
            }*/
    fclose(fp);

}

void Return_book()
{
    FILE * fptr;
    struct IS *p,*r;
    char name[50];
    printf("Enter the Name\n");
    scanf("%s",name);
    fptr = fopen("IssueList.txt","r");
    if((fptr = fopen("IssueList.txt","r")) != NULL)
    {
        p=(struct IS *)malloc(sizeof(struct IS));
        while(!feof(fptr))
            {
                fscanf(fptr,"\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d", p->name,p->USN,p->BookName,&p->BookId,&p->doi.mm, &p->doi.dd, &p->doi.yyyy);
                xsearch(name,p);
            }
            fclose(fptr);
    }
     else
    {
       printf("Error! opening file");
       exit(1);
    }
}

void showlist()
{
        struct IS *ptr;
        if(start==NULL)
        {
                printf("List is empty");
                return;
        }
        else
        {
                ptr=start;
                while(ptr!=NULL)
                {
                        printf("\nName:%s\nUSN:%s\nBookName:%s\nBookId:%d\nDateofIssue:%d/%d/%d\n\n",ptr->name,ptr->USN,ptr->BookName,ptr->BookId,ptr->doi.dd,ptr->doi.mm,ptr->doi.yyyy);
                        ptr=ptr->next ;
                }
        }
}
int Display_Issuebook()
{
    struct IS *xt;
    FILE *fptr;
    fptr = fopen("IssueList.txt","r");
	if(fptr==NULL)
	{
		printf("Empty file\n");
		return 0;
	}
	xt=start;
	while(xt->next!=NULL)
	{
        fscanf(fptr,"\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d",xt->name,xt->USN,xt->BookName,xt->BookId,xt->doi.mm,xt->doi.dd,xt->doi.yyyy);
		printf("\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d",xt->name,xt->USN,xt->BookName,xt->BookId,xt->doi.mm,xt->doi.dd,xt->doi.yyyy);
		xt= xt->next;
	}
		printf("\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d",xt->name,xt->USN,xt->BookName,xt->BookId,xt->doi.mm,xt->doi.dd,xt->doi.yyyy);
    fclose(fptr);
}

int Display_Returnbook()
{
    char name[50],BookName[50],USN[15];
    int BookId,date1,mon1,year1,date2,mon2,year2;
    FILE *fptr;
    fptr = fopen("ReturnList.txt","r");
    if((fptr=fopen("ReturnList.txt","r")) == NULL)
    {
        printf("No Data\n");
    }
    else
    {
        while(!feof(fptr))
        {
            fscanf(fptr,"\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d\nDateofReturn:%d/%d/%d",name,USN,BookName,&BookId,&mon1,&date1,&year1,&mon2,&date2,&year2);
            printf("\n\nName:%s\nUSN:%s\nBookName:%s\nBookID:%d\nDateofIssue:%d/%d/%d\nDateofReturn:%d/%d/%d",name,USN,BookName,BookId,mon1,date1,year1,mon2,date2,year2);
        }
    }
    fclose(fptr);
}


void display_time()
{
        time_t current_time = time(NULL);
        struct tm *tm = localtime(&current_time);
        printf("  \nDATE & TIME: ");
        printf("%s\n", asctime(tm));
}
int minimain();
int main();
void minimain1()
{
    int n;
    printf("\n\t\t\t\t\t\t\t\t\t                WELCOME TO STUDENT SECTION\n");

    printf("\n\t\t\t\t\t\t                PRESS ZERO TO CONTINUE .\n");
    for(;;)
    {
         printf("\n\t\t\t\t\t\t\t\t\t               ==========================");
         printf("\n\t\t\t\t\t\t\t\t\t              | 1:Display Student Record  | "); //to see student record
         printf("\n\t\t\t\t\t\t\t\t\t               ==========================");
         printf("\n\t\t\t\t\t\t\t\t\t              | 2:Insert Student Record   |");// to insert student record
         printf("\n\t\t\t\t\t\t\t\t\t               ==========================");
         printf("\n\t\t\t\t\t\t\t\t\t              | 3:Search Students         |");// to search
         printf("\n\t\t\t\t\t\t\t\t\t               ==========================");
         printf("\n\t\t\t\t\t\t\t\t\t              | 4:Remove Students         |");// to remove student
         printf("\n\t\t\t\t\t\t\t\t\t               ==========================");
         printf("\n\t\t\t\t\t\t\t\t\t              | 5:Binary Sort Students    |");// to sort students based on name
         printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
         printf("\n\t\t\t\t\t\t\t\t\t              | 6:Return To Main          |");// to sort students based on name
         printf("\n\t\t\t\t\t\t\t\t\t               ===========================\n");

        scanf("%d",&n);
        switch(n)
        {
        case 0:
            load_data_from_file();
            break;
        case 2:
            {
                    char name[100],usn[100];
                    int roll;
                    printf("Enter Name, USN, RollNo\n");
                    scanf("%s %s %d",name,usn,&roll);
                    insert(name,usn,roll);
            }
            break;
        case 1:
            display();
            break;
        case 3:
            {
                int roll;
                printf("Enter RollNo\n");
                scanf("%d",&roll);
                search(roll);
            }
            break;
        case 4:
            delete_rec();
            break;
        case 5:
            sort_students();
            break;
        case 6:
            load_data_to_file();
            minimain();
            break;
        }
    }
}
void minimain3()
{
    int id;
    char bn[100],an[100];
    printf("\n\t\t\t\t\t\t\t\t\t                WELCOME TO BOOK SECTION\n");
    LOAD_DATA_FROM_FILE();
    printf("\n");
    int n;
    for(;;)
    {
         printf("\n\t\t\t\t\t\t\t\t                 =======================================");
         printf("\n\t\t\t\t\t\t\t\t                | 1:VIEW ALL BOOKS AVAILABLE FROM FILE  | "); //to see student record
         printf("\n\t\t\t\t\t\t\t\t                 =======================================");
         printf("\n\t\t\t\t\t\t\t\t                | 2:SEARCH FOR BOOK                     |");// to insert student record
         printf("\n\t\t\t\t\t\t\t\t                 =======================================");
         printf("\n\t\t\t\t\t\t\t\t                | 3:REQUEST FOR A NEW BOOK              |");// to search
         printf("\n\t\t\t\t\t\t\t\t                 =======================================");
         printf("\n\t\t\t\t\t\t\t\t                | 4:DISPLAY BOOKS                       |");// to remove student
         printf("\n\t\t\t\t\t\t\t\t                 =======================================");
         printf("\n\t\t\t\t\t\t\t\t                | 5:EXIT                                |");// to sort students based on name
         printf("\n\t\t\t\t\t\t\t\t                 =======================================");
         printf("\n\t\t\t\t\t\t\t\t                | 6:Return To Main                      |");// to sort students based on name
         printf("\n\t\t\t\t\t\t\t\t                 =======================================\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1 : view_allbooks_onlyfile(first);
                    break;
            case 2 : ysearch(xroot);
            printf("\n");
                     break;
            case 3 :{ printf("Enter Book Name, Author Name and Book Id:\n");
                     scanf("%s%s%d",bn,an,&id);
                    xroot = add_book(bn,an,id);
				}
                    break;
            case 5 : exit(0);
                     break;
            case 4 : INORDER(xroot);
                     break;
            case 6:  minimain();
                     break;
        }
    }
}
void minimain2()
{
    int n;
    printf("\n\t\t\t\t\t\t\t\t\t                WELCOME TO ISSUE SECTION\n");
    for(;;)
    {
             //printf("\t\t\t\t\t\t\t ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
             printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
             printf("\n\t\t\t\t\t\t\t\t\t              |  1:Issue Book             | "); // to issue books to student
              printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
             printf("\n\t\t\t\t\t\t\t\t\t              |  2:Recently Issued Book   | "); //recently issued book
             printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
             printf("\n\t\t\t\t\t\t\t\t\t              |  3:Display IssueList      |");//to see borrowers list
             printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
             printf("\n\t\t\t\t\t\t\t\t\t              |  4:Display ReturnList     |");//display returned books
             printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
             printf("\n\t\t\t\t\t\t\t\t\t              |  5:Return Book            |");// to return borrowed books
             printf("\n\t\t\t\t\t\t\t\t\t               ===========================");
             printf("\n\t\t\t\t\t\t\t\t\t              |  6:Return To Main         |");// to return borrowed books
             printf("\n\t\t\t\t\t\t\t\t\t               ===========================\n");
             //printf("\t\t\t\t\t\t\t ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                xissue();
                break;
            case 2:
                showlist();
                break;
            case 3:
                Display_Issuebook();
                break;
            case 4:
                Display_Returnbook();
                break;
            case 5:
                Return_book();
                break;
            case 6:
                minimain();
                break;
        }
    }
}
int minimain()
{
    //load_data_from_file();       //read content of file
    //issue root=NULL;
    int n;
     printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
     printf("\n\t\t\t\t\t\t\t\t\t\t               WELCOME TO MAIN\n");
     printf("\n\t\t\t\t\t\t\t\t\t     =====================================================");
     printf("\n\t\t\t\t\t\t\t\t\t    |            1:STUDENT RECORD SECTIONS                | ");
     printf("\n\t\t\t\t\t\t\t\t\t     =====================================================");
     printf("\n\t\t\t\t\t\t\t\t\t    |            2:BOOK RECORD SECTIONS                   |");
     printf("\n\t\t\t\t\t\t\t\t\t     =====================================================");
     printf("\n\t\t\t\t\t\t\t\t\t    |            3:BORROW/RETURN BOOK SECTIONS            |");
     printf("\n\t\t\t\t\t\t\t\t\t     =====================================================");
     printf("\n\t\t\t\t\t\t\t\t\t    |            4:EXIT                                   |");
     printf("\n\t\t\t\t\t\t\t\t\t     =====================================================\n");
     printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            minimain1();
            break;
        case 2:
            minimain3();
            break;
        case 3:
            minimain2();
            break;
        default:
            exit(0);
            break;
            }
}

int main()
{
       display_time();
                printf("\t\t\t\t\t\t\t\t###########################################################################");
                printf("\n\t\t\t\t\t\t\t\t############                                                   ############");
                printf("\n\t\t\t\t\t\t\t\t############      Library management System Project in C       ############");
                printf("\n\t\t\t\t\t\t\t\t############                                                   ############");
                printf("\n\t\t\t\t\t\t\t\t###########################################################################");
                printf("\n\t\t\t\t\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
                printf("\n\t\t\t\t\t\t\t\t\t        =                 WELCOME                   =");
                printf("\n\t\t\t\t\t\t\t\t\t        =                   TO                      =");
                printf("\n\t\t\t\t\t\t\t\t\t        =                 LIBRARY                   =");
                printf("\n\t\t\t\t\t\t\t\t\t        =               MANAGEMENT                  =");
                printf("\n\t\t\t\t\t\t\t\t\t        =                 SYSTEM                    =");
                printf("\n\t\t\t\t\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                minimain();
}
