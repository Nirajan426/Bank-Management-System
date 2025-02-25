
#include<stdlib.h>
#include<stdio.h>
#include <windows.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include <unistd.h> 

// Structure to store user details
struct User
{
    int accountNumber;
    char username[50];
    char password[50];
    char phone[15];
    float balance;
};

// Function prototypes
void packt();
void bflus();
void header();
void boot();
void createAccount();
int login(struct User *user);
void depositMoney(struct User *user);
void withdrawMoney(struct User *user);
void accountStatement(struct User *user);
void logTransaction(int accountNumber, const char *type, float amount, float balance);
void updateUserBalance(struct User *user);

int main()
{
    struct User currentUser;
    int choice;
    boot();
    mainmenu:
    header();
    // Ask for account creation or login
    printf("\t - - SYSTEM DASH - - \n");
    printf("\t1. Create Account\n");
    printf("\t2. Login\n");

    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    bflus();
    if (choice == 1)
    {
        createAccount();
    }
    else if (choice == 2)
    {
        if (login(&currentUser) != 1) // 1 for success and 0 for fail
        {

            printf("\tLogin failed.Try  again with different details.\n\t");
            packt();
            goto mainmenu;
        }
    }
    else
    {
        printf("\tInvalid choice.Enter 1 or 2\n\n");
        printf("Press any key to continue.");
        getch();
        goto mainmenu;
    }

    // Banking menu for logged-in users
    while (1)
    {
        header();
        printf("\t - - - HOME - - - \n");
        printf("\nWelcome, %s!\n", currentUser.username);
        printf("\t1. Deposit Money\n");
        printf("\t2. Withdraw Money\n");
        printf("\t3. Account Statement\n");
        printf("\t4. Exit\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);
        bflus();

        switch (choice)
        {
        case 1:
            depositMoney(&currentUser);
            break;
        case 2:
            withdrawMoney(&currentUser);
            break;
        case 3:
            accountStatement(&currentUser);
            break;
        case 4:
            printf("\tExiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("\tInvalid choice. Please try again.\n");
            printf("Press any key to continue.");
            getch();
        }
    }

    return 0;
}

// Function to create a new account
void createAccount() {
    struct User newUser,temp;
    FILE *f;
    int lastno = 12345677;
    printf("=====Creat Account=====\n");
    f=fopen("userdetail.txt","r");
        if(f!=NULL)
        {
             while (fscanf(f, "%d %s %s %s", &newUser.accountNumber, newUser.username, newUser.phone, newUser.password) != EOF)
			 {
              if(newUser.accountNumber>lastno)
              {
                lastno=newUser.accountNumber;
              }
        }
        }
    fclose(f);
    lastno++;
    newUser.accountNumber = lastno;
    printf("Please enter your full name: ");
    scanf(" %[^\n]",newUser.username);
    printf("Please enter your phone number: ");
    scanf(" %s", newUser.phone);
    f=fopen("userdetail.txt","r");
    if(f!=NULL){
	    
         while (fscanf(f, "%d %s %s %s", &temp.accountNumber, temp.username, temp.phone, temp.password) != EOF) 
        {
            if(strcmp(temp.phone,newUser.phone)==0)
            {
                printf("With this phone the account already exist\n");
                fclose(f);
                return;
            }
        }
        fclose(f);
    }
    printf("Please enter your password: ");
    scanf(" %s", newUser.password);
    f=fopen("userdetail.txt","a");
    if(f==NULL)
    {
        f=fopen("userdetail.txt","w");
    }
    fprintf(f, "%d \t%s \t%s \t%s\n", newUser.accountNumber, newUser.username, newUser.phone, newUser.password);
    printf("Account created successfully!\n");
    printf("\tYour account number is: %d\n", newUser.accountNumber);
    fclose(f);
}
//Function to authenticate user
int login(struct User *user)
{
    int accountNumber;
    char username[50];
    char password[50];
    FILE *file = fopen("userdetail.txt", "r");
    header();

    if (file == NULL)
    {
        printf("\tNo user accounts found. Please create an account first.\n");
        printf("Press any key to continue.");
        getch();
        return 0;
    }

    printf("\tEnter your account number: ");
    scanf("%d", &accountNumber);
    bflus();
    printf("\tEnter your username: ");
    scanf("%s", username);
    bflus();
    printf("\tEnter your password: ");
    scanf("%s", password);
    bflus();

    // Search for the user in the file
    while (fscanf(file, "%d %s %s %f", &user->accountNumber, user->username, user->password, &user->balance) != EOF)
    {
        if (user->accountNumber == accountNumber && strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0)
        {
            fclose(file);
            return 1; // Login successful
        }
    }

    fclose(file);
    return 0; // Login failed
}

// Function to deposit money
void depositMoney(struct User *user)
{
    float amount;
    header();

    printf("\tEnter the amount to deposit: ");
    scanf("%f", &amount);
    bflus();

    if (amount <= 0)
    {
        printf("\tInvalid amount. Please enter a positive value.\n");
        printf("Press any key to continue.");
        getch();
        return;
    }

    user->balance += amount;
    printf("\tDeposit successful. New balance: %.2f\n", user->balance);


    // Log the transaction
    logTransaction(user->accountNumber, "DEPOSIT", amount, user->balance);

    // Update user balance in the file
    updateUserBalance(user);
    printf("Press any key to continue.");
    getch();
}

// Function to withdraw money
void withdrawMoney(struct User *user)
{
    float amount;
    header();

    printf("\tEnter the amount to withdraw: ");
    scanf("%f", &amount);
    bflus();

    if (amount <= 0)
    {
        printf("\tInvalid amount. Please enter a positive value.\n");
        packt();
        return;
    }

    if (amount > user->balance)
    {
        printf("\tInsufficient balance.\n");
        packt();
        return ;
    }

    user->balance -= amount;
    printf("\tWithdrawal successful. New balance: %.2f\n", user->balance);

    // Log the transaction
    logTransaction(user->accountNumber, "WITHDRAW", amount, user->balance);

    // Update user balance in the file
    updateUserBalance(user);
    packt();
}

// Function to display account statement (only for the logged-in user)
void accountStatement(struct User *user)
{
    FILE *file = fopen("transaction_log.txt", "r");
    header();

    if (file == NULL)
    {
        printf("\tNo transactions found.\n");
        packt();
        return;
    }

    printf("\n\tAccount Statement for Account Number: %d\n", user->accountNumber);
    printf("\t Date       Time     Amount      Activity   Balance\n");

    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        int loggedAccountNumber;
        char date[20], time[20], activity[20];
        float amount, balance;

        // Parse the transaction log line
        sscanf(line, "%s %s %d %f %s %f", date, time, &loggedAccountNumber, &amount, activity, &balance);

        // Display only transactions for the logged-in user
        if (loggedAccountNumber == user->accountNumber)
        {
            printf("\t%s %s %.2f \t %s  %.2f\n", date, time, amount, activity, balance);
        }
    }
    packt();

}

// Function to log transactions
void logTransaction(int accountNumber, const char *type, float amount, float balance)
{
    FILE *file = fopen("transaction_log.txt", "a");
    header();

    if (file == NULL)
    {
        printf("\tError opening transaction log file.\n");
        packt();
        return;
    }

    // Get current time
    time_t now;
    time(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    // Log the transaction
    fprintf(file, "%s %d %.2f %s %.2f\n", timestamp, accountNumber, amount, type, balance);

    fclose(file);
}

// Function to update user balance in the file
void updateUserBalance(struct User *user)
{
    FILE *file = fopen("userdetail.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    header();

    if (file == NULL || tempFile == NULL)
    {
        printf("\tError updating user balance.\n");
        packt();
        return;
    }

    struct User tempUser;
    while (fscanf(file, "%d %s %s %f", &tempUser.accountNumber, tempUser.username, tempUser.password, &tempUser.balance) != EOF)
    {
        if (tempUser.accountNumber == user->accountNumber)
        {
            tempUser.balance = user->balance;
        }
        fprintf(tempFile, "%d %s %s %.2f\n", tempUser.accountNumber, tempUser.username, tempUser.password, tempUser.balance);
    }

    fclose(file);
    fclose(tempFile);

    remove("userdetail.txt");
    rename("temp.txt", "userdetail.txt");
}

//Press any key to continue
void packt(){
    printf("\tPress any key to continue.");
    getch();
}

//Buffer Flush
void bflus(){
    //Buffer Flush
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}



//Organization's Header                     --Ready
void header(){
    system("cls");
    printf("\n");
    printf("\t\t\t|| NAM BANK ||\n");
    printf("\n");
    printf("\t---------- Bank Management System ----------");
    //printf("\n====================================================");
    printf("\n\t___________________________________________________________");
    printf("\n");
}

//boot graphics
void boot(){
    printf("\n\n\n\n");
    printf("\t\t\tNNNN    N  AAAAA  M    M      BBBBB    AAAAA  NNNN    N  K   K\n");
    printf("\t\t\tN   N   N  A   A  MM  MM      B    B   A   A  N   N   N  K  K\n");
    printf("\t\t\tN    N  N  AAAAA  M MM M      BBBBB    AAAAA  N    N  N  KK\n");
    printf("\t\t\tN     N N  A   A  M    M      B    B   A   A  N     N N  K  K\n");
    printf("\t\t\tN      NN  A   A  M    M      BBBBB    A   A  N      NN  K   K\n");
    printf("\n\n\t\t\t\t\t\tWELCOMES YOU!\n\n");
    sleep(1);
    printf("\t\t\t");

    for(int i=0;i<62;i++){
        printf("_");
        usleep(1000);
    }
    usleep(100000);
}


