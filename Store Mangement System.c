/*
Electronic Store Management system to insert, display, delete,update and sale product
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define USERNAME "admin"
#define PASSWORD "admin123"
#define MAX 20

typedef struct items
{
    char product_code[MAX];
    char product_name[MAX];
    int rate;
    int quantity;
    float weight;
    char description[30];

} ITEM;

ITEM item;

// function to check if the given product code is available
int isCodeAvailable(char code[])
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (strcmp(code, item.product_code) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to check the quentity during the sale product.
int isProductAvailable(int quantity)
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (item.quantity >= quantity)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// function to check the choice is integer or not
int get_int(int input)
{
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
        {
        }
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\tMust be positive integer.\n");
        printf("\033[0m");
        printf("\t\t\t\t\tEnter Positive integer value, such as 1,2,3,4: ");
    }

    return input;
}

int check_rate()

{
    int input;
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
        {
        }
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\tRate should be positive Integer.\n");
        printf("\033[0m");
        printf("\t\t\t\t\tEnter rate of the product in positive integer: ");
    }

    return input;
}

//function to insert the product to the file.
void addProduct()
{
    printf("\v\v\t\t\t\t\t\t\tAdd Product\n");
    printf("\t\t\t\t\t\t==============================\n");
    FILE *file;
    char code[MAX];
    char x[4] = {0};
    int a;
    file = fopen("Record.txt", "ab");
    printf("\n\t\t\t\t\tEnter the \" end \" to exit for here");
    printf("\n\t\t\t\t\tEnter Product code: ");
    scanf("%s", code);
    // scanf("%s", x);
    if (strcmp(code, "end") == 0)
    {
        system("cls");
        options();
    }
    int available;
    available = isCodeAvailable(code); // return 1 if code id found and return 0 if the code is not available.
    if (available == 1)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Product is already there.\n");
        printf("\033[0m");
        options();
    }
    strcpy(item.product_code, code); // copy the code to the structure item
    // fflush(stdin);
    // printf("%s", item.product_code);
    // printf("%s", code);
    printf("\t\t\t\t\tEnter Product Name: ");
    scanf("%s", item.product_name);
    printf("\n\t\t\t\t\tEnter Product Rate: ");
    a = check_rate();
    item.rate = a;
    printf("\n\t\t\t\t\tEnter Quantity: ");
    scanf("%d", &item.quantity);
    printf("\n\t\t\t\t\tEnter product Weight(in gram): ");
    scanf("%f", &item.weight);
    printf("\n\t\t\t\t\tEnter product descriptions: ");
    scanf(" %s", item.description);

    // writing structure to a file
    fwrite(&item, sizeof(item), 1, file);
    fclose(file);

} // End of addproduct function

void display()
{
    printf("\v\v\t\t\t\t\t\t\tAvailable Products\n");
    printf("\t\t\t\t\t\t====================================\n");
    FILE *file;
    int count = 0;
    file = fopen("Record.txt", "rb");
    printf("\t\t\t------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\tCODE\t||\tNAME\t||\tPRICE\t||\tQUANTITY\t||\tWEIGHT\t||\tDESCRIPTION\n");
    printf("\t\t\t------------------------------------------------------------------------------------------------------\n");
    if (file == NULL)
    {
        printf("\t\t\t\tNo Product is inserted.");
        options();
    }
    while (fread(&item, sizeof(item), 1, file))
    {
        printf("\t\t\t%s\t||\t%s\t||\t%d\t||\t %d\t\t||\t%.2f\t||\t%s \n", item.product_code, item.product_name, item.rate, item.quantity, item.weight, item.description);
        count++;
    }
    printf("\n\t\t\t------------------------------------------------------------------------------------------------------\n");
    if (count == 0)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Product is not available.\n");
        printf("\033[0m");
    }
    fclose(file);
} // End of display functions

void close_app()
{
    char choice;
    printf("\n\n\n\n\n\n\t\t\t\t\tThank You for Using My Software\n\n\n\n\n\t\t\t\t\tMade By Adam Faasil CYX28656");
    printf("\n\n\n\n\n\n\t\t\t\t\tDo you want to close the applications?(Y/y):");
    scanf("%s", &choice);
    if (choice == 'Y' || choice == 'y')
    {

        exit(0);
    }
}

// search function start
void search()
{

    FILE *file;
    char code[MAX], product[MAX];
    int available;
    // if (file == NULL)
    // {
    //     printf("\t\t\t\tNo Product is inserted.");
    //     options();
    // }
    printf("\v\t\t\t\t\tEnter \"end\" for back to menu.\n");
    printf("\v\t\t\t\t\tEnter the Product code to search: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0)
    {
        system("clear");
        options();
    }
    system("cls");
    printf("\v\v\t\t\t\t\t\t>>Product Information<<\n");
    printf("\t\t\t\t\t\t=========================\n");
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("clS");
        printf("\033[1;31m");
        printf("\n\t\t\t\t\t\tProduct code is not found.\n");
        printf("\033[0m");
    }
    else
    {
        file = fopen("Record.txt", "rb");
        while (fread(&item, sizeof(item), 1, file))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) == 0)
            {
                printf("\n\t\t\t\t\t\tProduct Code:        %s", item.product_code);
                printf("\n\t\t\t\t\t\tName of Product:     %s", item.product_name);
                printf("\n\t\t\t\t\t\tRate of Product(MVR): %d", item.rate);
                printf("\n\t\t\t\t\t\tProduct Weight:      %.2f", item.weight);
                printf("\n\t\t\t\t\t\tProduct Description: %s\n", item.description);
            }
        }
        fclose(file);
    }
} // end of the search function

// Delete function start

void deleteRecord()
{
    // printf("\v\v\t\t\t\t\t\t\tDelete Product\n");
    // printf("\t\t\t\t\t\t************************\n");
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    file1 = fopen("Record.txt", "rb");
    // if (file1 == NULL)
    // {
    //     printf("\t\t\t\tNo Product is inserted.");
    //     options();
    // }
    display();
    printf("\n\t\t\t\t\t\tEnter the Product code to delete: ");
    scanf("%s", code);
    system("clear");
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("clear");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Product is not available.\n");
        printf("\033[0m");
    }
    else
    {

        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        printf("\n\v\t\t\t\t\t\tProduct deleted sucessfully!!\n\n");
        fclose(file1);
        fclose(file2);
    }

} // end of delete file

// Function to update the Products.
void updateProduct()
{
    printf("\v\v\t\t\t\t\t\t\tUpdate Product\n");
    printf("\t\t\t\t\t\t************************\n");
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    // if (file1 == NULL)
    // {
    //     printf("\t\t\t\tNo Product is inserted.");
    //     options();
    // }
    printf("enter the Product code to update the record:");
    scanf("%s", code);
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* no Product is found for update.\n");
        printf("\033[0m");
    }
    else
    {
        file1 = fopen("Record.txt", "rb");
        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
            else
            {
                printf("\n Updating data for the privious product %s\n", code);
                printf("Enter new product code: ");
                scanf("%s", item.product_code);
                fflush(stdin);
                printf("enter Product Name: ");
                scanf("%s", item.product_name);
                printf("Enter Product Rate: ");
                scanf("%d", &item.rate);
                printf("Enter Quantity: ");
                scanf("%d", &item.quantity);
                printf("Enter weight: ");
                scanf("%f", item.weight);
                printf("enter product descriptions: ");
                scanf("%s", item.description);
                printf("\n\n");
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
} //end of update file.

void pwellcome(){
	char welcome[50]="WELCOME.......";
	char welcome2[50]=" TO";
	char welcome3[50]=" X ELECTRONICS STORE";
	char welcome4[50]=" MANAGEMENT SYSTEM";
	char welcome5[50]=" MADE BY ADAM FAASIL CYX28656.\n";
	printf("\n\n\n\n\n\t\t\t");
	for(int wlc=0; wlc<strlen(welcome);wlc++){

		printf(" %c",welcome[wlc]);
		Sleep(100);
	}
	printf("\n\n\t\t\t\t ");
	for(int wlc2=0; wlc2<strlen(welcome2) ;wlc2++){

		printf(" %c",welcome2[wlc2]);
		Sleep(100);
	}
	printf("\n\n\n\t\t\t ");
	for(int wlc3=0; wlc3<strlen(welcome3) ;wlc3++){
		if(welcome3[wlc3]!='D'){

			printf(" %c",welcome3[wlc3]);
		}
		else{

			printf(" %c",welcome3[wlc3]);
		}

		Sleep(100);
	}
	printf("\n\n\n\t\t\t\t ");
	for(int wlc3=0; wlc3<strlen(welcome4) ;wlc3++){
		if(welcome4[wlc3]!='A' && welcome4[wlc3]!='E'){

			printf(" %c",welcome4[wlc3]);
		}
		else{

			printf(" %c",welcome4[wlc3]);
		}
		Sleep(100);
	}
	printf("\n\n\n\t\t\t\t");
	for(int wlc4=0; wlc4<strlen(welcome5) ;wlc4++){
		if(welcome4[wlc4]!='A' && welcome5[wlc4]!='E'){

			printf(" %c",welcome5[wlc4]);
		}
		else{

			printf(" %c",welcome5[wlc4]);
		}
		Sleep(100);
	}
}
void loadingbar(void){
	for (int i=15;i<=100;i+=5){
		printf("\n\t\t\t\t\t\t\t %d %% LOADING........",i);
		for (int j=0; j<i;j+=2){
		}
		Sleep(100);
		if(i==90 || i==50 || i==96 || i==83){
        Sleep(100);
		}

	}

}
void login()
{
    system("cls");
    printf("\v\v\t\t\t\t\t\t\t>>LOGIN<< \n");
    printf("\t\t\t=======================================================================\n");
    char username[15], password[10];
    // loginAgain:
    //system("cls");
    printf("\v\v\t\t\tEnter username: ");
    scanf("%s", username);
    printf("\t\t\tEnter password: ");
    scanf("%s", password);
    while (1)
    {
        if ((strcmp(USERNAME, username)) == 0 && (strcmp(PASSWORD, password)) == 0)
        {
            printf("\033[1;32m");
            printf("\t\t\t\t\tLOGIN SUCCESSFULLY!!");
            printf("\033[0m");
            //printf("\v\v\t\t\t--Welcome to the X Electronics--\n");
            loadingbar();
            options();
            system("cls");
        }
        else
        {
            system("cls");
            printf("\033[1;31m");
            printf("\n\t\t\tSorry you enter the worng information.\n");
            printf("\n\t\t\tPlease try again.\n");
            printf("\033[0m");
            //goto loginAgain;
            login();
            break;
        }
    }
} //end of login function

// start main funcion
int main()
{
    system("title Store MS v0.5 JUN-3 (ALPHA)");
	system("mode con: cols=88 lines=30");
    pwellcome();
    loadingbar();
    login();
    return 0;
} // end of main

void saleProduct()
{
    loadingbar();
    printf("\n\n\n\n\n\n\v\v\t\t\t\t\t\t\tMake A Sale\n");
    printf("\t\t\t\t\t\t===================================\n");
    char x[4] = {0}; // for item code
    int q = 0, size = 0, i = 1;
    int total = 0, gtotal = 0;
    FILE *file;
    // if (file == NULL)
    // {
    //     printf("\t\t\tno product is found.");
    //     options();
    // }
    file = fopen("Record.txt", "r+b");
    rewind(file);
    system("cls");
    //dbill();
    int availableC, availableQ;
    printf("\t\t\t\t\tEnter  \" end \" to finish input");
    int qty = item.quantity;
    while (1)
    {
        printf("                    ");
        printf("                    ");
        printf("\n\v\t\t\t\tEnter Item Code:");
        // printf("\n\v\vEnter Item Code:");
        scanf("%s", x);
        if (strcmp(x, "end") == 0)
        {
            system("cls");
            break;
        }
        availableC = isCodeAvailable(x);
        if (availableC == 0)
        {
            system("cls");
            printf("\033[1;31m");
            printf("\n\v\t\t\t\t\t\t* no Product is found.\n");
            printf("\033[0m");
            options();
        }

        printf("\t\t\t\tEnter Quantity:");
        scanf("%d", &q);
        printf("item%d", item.quantity);

        //printf("beg%d", qty);
        qty = qty - q;
        if (qty < 0)
        {
            system("cls");
            printf("\033[1;31m");
            system("cls");
            printf("\n\t\t\t\t\t\t* Out of stock.\n");
            printf("\033[0m");
            break;
        }

         printf("qqqq%d", qty);

         availableQ = isProductAvailable(q);
         if (availableQ == 0)
         {
             system("cls");
             printf("\033[1;31m");
             printf("\n\v\t\t\t\t\t\t* This product has 0 quantity.");
             printf("\033[0m");
             options();
         }
        rewind(file);
        while (fread(&item, sizeof(item), 1, file))
        {
            if ((strcmp(item.product_code, x) == 0))
            {
                total = item.rate * q;
                printf("\n\t\t\t%d ", i);
                printf("\t\t\t%s ", item.product_name);
                printf("\t\t\t%d ", q);
                printf("\t\t\t%d ", item.rate);
                printf("\t\t\t%d ", total);
                gtotal = gtotal + total;
                size = sizeof(item);
                item.quantity = item.quantity - q;

                i++;
                fseek(file, -size, SEEK_CUR);
                fwrite(&item, sizeof(item), 1, file);
                break;
            }
        }
    }
    if (gtotal != 0)
    {
         system("cls");
        printf("\n\v\t\t\t\t\t\tTOTAL AMOUNT = MVR. %d", gtotal);
    }
    fclose(file);
     options();
}
// display of the bill.
 //void dbill()
// {
//    int i;
//     for (i = 1; i <= 10; i++)
//         printf("-");
//     printf(" X Electronic Store");
//     for (i = 1; i <= 10; i++)
//         printf("-");
//     printf("\n\n");
//     printf("CUSTOMER'S BILL\n");
//    printf("SN.   Item Name     Quantity     Rate          Total\n");
// }

void options()
{
    system("cls");
    printf("\n\n\n\n\n\n");
    printf("\v\v\t\t\t\t\t\t--X ELECTRONIC STORE--\n");
    printf("\v\v\t\t\t\t\t\t   >>MAIN MENU<<\n");
    printf("\t\t\t=======================================================================\n");
    int num, choice;
    while (1)
    {
        printf("\n\t\t\t\t\t\t[1] ADD\n\t\t\t\t\t\t[2] DISPLAY");
        printf("\n\t\t\t\t\t\t[3] SEARCH\n\t\t\t\t\t\t[4] DELETE\n\t\t\t\t\t\t[5] UPDATE");
        printf("\n\t\t\t\t\t\t[6] CLOSE\n\t\t\t\t\t\t[7] MAKE A SALE\n\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        choice = get_int(num);
        switch (choice)
        {
        case 1:
            system("cls");
            addProduct();
            system("cls");
            break;
        case 2:
            system("cls");
            display();

            break;
        case 3:
            system("cls");
            search();
            break;
        case 4:
            system("cls");
            deleteRecord();
            break;
        case 5:
            system("cls");
            updateProduct();
            break;

        case 6:
            system("cls");
            close_app();
            break;
        case 7:
            system("cls");
            saleProduct();
            break;
        default:
            system("cls");
            printf("\033[1;31m");
            printf("\t\t* Invalid choice.\n");
            printf("\033[0m");
            break;
        } // end of switch
    }
}
