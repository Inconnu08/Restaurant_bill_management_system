#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *Restaurant Bill Management System*
// Functions
void menu();   // Displays main menu.
void create(); // For creating new bill records and saving them.
void read();   // Display the full list of all the bills saved.
void update(); // Update a bill record.
void delete(); // Delete a single bill record by name.
void search(); // Search by name for specific bill record.

// Bill record
struct  Bill
{
    int id;
    char name[255];
    float bill;
};


void main()
{
    int choice = 1;

    printf("================== Restaurant Billing System ===================\n");

    while(choice != 6)
    {
        printf("\n\n1) Create new bill\n2) View bills\n3) Update bill\n4) Delete bill\n5) Search bill\n6) Exit\n");
        scanf("%d", &choice);
        menu(choice);
    }
}

void menu(int choice)
{
    switch(choice)
    {
        case 1:
            printf("CREATE:\n");
            create();
            break;

        case 2:
            printf("RETRIEVE:\n");
            read();
            break;

        case 3:
            printf("\nUPDATE");
            update();
            break;

        case 4:
            printf("DELETE\n");
            delete();
            break;

        case 5:
           search();
           break;
        case 6:
            exit(1);

        default:
            printf("\nInvalid input");
            break;
    }
}

void create()
{
    int i, num, n;
    struct Bill b[100];

    FILE *file;
    file=(fopen("D:\\bill.dat","a"));
    if(file==NULL){
       fprintf(stderr, "Error: 404.\n Create and save bill.dat file to your C root.");
    }

    printf ("\nHow many entries would like to make (0 to exit)?: ");
    scanf("%d", &n);
    if(n<=0) return;

    for(i=0; i<n; i++){
        printf ("\nEnter name (just hit enter to stop):\n");
        scanf("%s", b[i].name);
        if(strcmp(b[i].name,"\n")==0) break;
        fflush(stdin);
        printf ("\nEnter ID: ");
        scanf("%d", &b[i].id);
        fflush(stdin);
        printf ("\nEnter Bill:");
        scanf("%f", &b[i].bill);
        fflush(stdin);
    }
    num = i;
    fwrite(b, sizeof(struct Bill), i, file);
    fclose(file);

    printf("%d entries added successfully!\n ", n);
}

void read()
{
    FILE *file;
    file=(fopen("D:\\bill.dat", "r"));
    if(file==NULL){
       fprintf(stderr, "Error: 404.\n Create and save bill.dat file to your C root.");
    }

    int i, num;
    struct Bill b[100];
    num = fread(b, sizeof(struct Bill), 100, file);
    for(i=0; i<num; i++)
    {
        printf ("__________________________________");
        printf ("\nID: %d\nName: %s\nBill: %0.2f\n",
        b[i].id, b[i].name, b[i].bill);
    }
    fclose(file);
}

void search()
{
    char skeyword[50];
    printf("\nEnter name to search:");
    scanf("%s", skeyword);

    FILE *file;
    file=(fopen("D:\\bill.dat","r"));
    if(file==NULL){
       fprintf(stderr, "Error: 404.\n Create and save bill.dat file to your C root.");
    }

    int i, num;
    struct Bill b[100];
    num = fread (b, sizeof(struct Bill), 100, file);
    for(i=0; i<num; i++)
    {
        if(strcmp(b[i].name, skeyword) == 0){
            printf ("ID: %d\nName: %s\nBill: %0.2f\n",
            b[i].id, b[i].name, b[i].bill);
            return;
        }
    }
    printf ("\n%s was not found!", skeyword);
    fclose(file);
}

void delete()
{
    int i, num, pos, found = 0;
    char skeyword[50];

    printf("\nEnter name to delete: ");
    scanf("%s", skeyword);

    FILE *file;
    file =( fopen("D:\\bill.dat","r"));
    if(file==NULL){
       fprintf(stderr, "Error: 404.\n Create and save bill.dat file to your C root.");
    }

    struct Bill b[100];
    num = fread (b, sizeof(struct Bill), 100, file);
    for(i=0; i<num; i++)
    {
        if(strcmp(b[i].name, skeyword) == 0){
            found = 1;
            pos = i;
            break;
        }
    }

    if (found == 1)
    {
        for (i=pos; i<num-1; i++)
        {
            b[i] = b[i + 1];
        }
        file = (fopen("D:\\bill.dat","w"));
        fwrite(b, sizeof(struct Bill), i, file);
        printf ("\nDeleted successfully!", skeyword);
    }
    else printf ("\n%s was not found!", skeyword);
    fclose(file);
}

void update()
{
    int i, num, pos, found = 0;
    char skeyword[50];

    printf("\nEnter name of customer to update: ");
    scanf("%s", skeyword);

    FILE *file;
    file =( fopen("D:\\bill.dat","r"));
    if(file==NULL){
       fprintf(stderr, "Error: 404.\n Create and save bill.dat file to your C root.");
    }

    struct Bill b[100];
    num = fread (b, sizeof(struct Bill), 100, file);
    for(i=0; i<num; i++)
    {
        if(strcmp(b[i].name, skeyword) == 0){
            printf ("\nEnter name: \n");
            scanf("%s", b[i].name);
            fflush(stdin);
            printf ("\nEnter ID: ");
            scanf("%d", &b[i].id);
            fflush(stdin);
            printf ("\nEnter Bill:");
            scanf("%f", &b[i].bill);
            fflush(stdin);
            found = 1;
        }
    }

    if (found == 1)
    {
        file = (fopen("D:\\bill.dat","w"));
        fwrite(b, sizeof(struct Bill), i, file);
        printf ("\nUpdated successfully!", skeyword);
    }
    else printf ("\n%s was not found!", skeyword);

    fclose(file);
}
