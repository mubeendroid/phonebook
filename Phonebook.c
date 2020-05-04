#include<stdio.h>
#include<string.h>
struct contact
{
    char name[30];
    int number;
    char address[50];
    int age;
};
void menu();
void addcontact();
void showcontact();
void deletecontact();
void searchcontact();
int main()
{
    menu();
    return 0;
}
void menu()
{
    int choice;
    printf("\n\n\t\t**********WELCOME TO DIGITAL PHONEBOOK*************");
    printf("\n\n\t\t\t\t\tMENU\t\t\n\n");
    printf("\t1.Create a new contact\n\t2.Search a contact using name\n\t3.Delete a contact\n\t4.Show all the contact\n\t5.Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case  1: addcontact();
                 break;
        case  2: searchcontact();
                 break;
        case  3: deletecontact();
                 break;
        case  4: showcontact();
                 break;
        case  5: printf("\n\nThanks for using the program.\n\n");
                 exit(0);
                 break;
        default: printf("Please enter between 1-5\n");
                 menu();
    }
}
void addcontact()
{
    char ch;
    int i,j,temp;
    FILE *f;
    struct contact p;
    f=fopen("Phone book.dat","ab");
    scanf("%c",&ch);
    printf("\nEnter name: ");
    gets(p.name);
    printf("\nEnter address: ");
    gets(p.address);
    printf("\nEnter phone no.:");
    scanf("%d",&p.number);
    printf("\nEnter age: ");
    scanf("%d",&p.age);
    fwrite(&p,sizeof(p),1,f);
    printf("\nrecord saved\n");
    fclose(f);
    printf("\n");
    menu();
}
void showcontact()
{
    struct contact p;
    int flag=0;
    FILE *f;
    f=fopen("Phone book.dat","rb");
    if(f==NULL)
    {
        printf("\nUnable to open the file\n");
        menu();
    }
    else
    {
        while(fread(&p,sizeof(p),1,f)==1)
        {
            printf("\nName=%s\nAddress=%s\nMobile no=%d\nAge=%d\n",p.name,p.address,p.number,p.age);
            flag=1;
        }
        if(flag==0)
            printf("\nNo contact found\n");
        fclose(f);
        printf("\n");
        menu();
    }
}
void searchcontact()
{
    char ch;
    int flag=0;
    scanf("%c",&ch);
    struct contact p;
    FILE *f;
    char name[30];
    f=fopen("Phone book.dat","rb");
    if(f==NULL)
    {
        printf("\nUnable to open the file.\n");
        menu();
    }
    else
    {
        printf("\nEnter name of the contact to search: ");
        gets(name);
        while(fread(&p,sizeof(p),1,f)==1)
        {
            if(strcmp(p.name,name)==0)
            {
                printf("\n\tDetail Information About %s",name);
                printf("\nName:%s\naddress:%s\nMobile no:%d\nAge:%d\n",p.name,p.address,p.number,p.age);
                flag=1;
            }
        }
        if(flag==0)
            printf("\nContact not found.\n");
        fclose(f);
        printf("\n");
        menu();
    }
}
void deletecontact()
{
    char ch;
    scanf("%c",&ch);
    struct contact p;
    FILE *f,*ft;
	int flag=0;
	char name[30];
	f=fopen("Phone book.dat","rb");
	if(f==NULL)
        printf("\nUnable to open the file.\n");
	else
	{
		ft=fopen("temp.dat","wb+");
		if(ft==NULL)
            printf("\nUnable to open the file.\n");
		else
        {
            printf("\nEnter name of the contact to delete: ");
            gets(name);
            while(fread(&p,sizeof(p),1,f)==1)
            {
                if(strcmp(p.name,name)!=0)
                    fwrite(&p,sizeof(p),1,ft);
                if(strcmp(p.name,name)==0)
                    flag=1;
            }
            fclose(f);
            fclose(ft);
            if(flag!=1)
            {
                printf("\nContact name did not match\n");
                remove("temp.dat");
            }
            else
            {
                remove("Phone book.dat");
                rename("temp.dat","Phone book.dat");
                printf("\nRECORD DELETED SUCCESSFULLY.");
            }
        }
    }
    printf("\n");
    menu();
}

