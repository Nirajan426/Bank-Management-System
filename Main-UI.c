#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// Structure to store user details
struct User
{
    int accountNumber;
    char username[50];
    char password[50];
    char phone[15];
    float balance;
    char dateOfBirth[11]; // YYYY-MM-DD
    char address[100];
    char email[50];
};

// Function prototypes
void continueKey();
void Bufferflush();
void header();
void boot();
void viewinfo(struct User *user);
void changePassword(struct User *user);    // yet to program this code
void changeEmail(struct User *user);       // yet to program this code
void changePhoneNumber(struct User *user); // yet to program this code
void createAccount();
int login(struct User *user);
void depositMoney(struct User *user);
void withdrawMoney(struct User *user);
void accountStatement(struct User *user);
void logTransaction(int accountNumber, const char *type, float amount, float balance);
void updateUserBalance(struct User *user);
int isValidUsername(char *username);
int isValidPassword(char *password);
int main()
{
    struct User currentUser;
    int choice;
    boot();
System_dash:
    header();
    // Ask for account creation or login
    printf("\t - - SYSTEM DASH - - \n");
    printf("\t1. Create Account\n");
    printf("\t2. Login\n");
    printf("\t3. Exit\n");

    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    Bufferflush();
    if (choice == 1)
    {
        createAccount();
        if (login(&currentUser) != 1) // 1 for success and 0 for fail
        {

            printf("\tLogin failed.Try  again with different details.\n\t");
            continueKey();
            goto System_dash;
        }
    }
    else if (choice == 2)
    {
        if (login(&currentUser) != 1) // 1 for success and 0 for fail
        {

            printf("\tLogin failed.Try  again with different details.\n\t");
            continueKey();
            goto System_dash;
        }
    }
    else if (choice == 3)
    {
        exit(0);
    }

    else
    {
        printf("\tInvalid choice\n\n");
        printf("Press any key to continue.");
        getch();
        goto System_dash;
    }

// Banking menu for logged-in users
mainmenu2:
    while (1)
    {
        header();
        printf("\t - - - HOME - - - \n");
        printf("\nWelcome, %s!\n", currentUser.username);
        printf("\t1. Deposit Money\n");
        printf("\t2. Withdraw Money\n");
        printf("\t3. Account Statement\n");
        printf("\t4. Setting\n");
        printf("\t5. Log Out\n");
        printf("\t6. Exit\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);
        Bufferflush();

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
            while (1)
            {

                printf("\t - - - SETTINGS - - - \n");
                printf("\t1.Personal Information \n");
                printf("\t2. Change Password\n");
                printf("\t3. Change Email\n");
                printf("\t4. Change Phone Number\n");
                printf("\t5. Back\n");
                printf("\tEnter your choice: ");
                scanf("%d", &choice);
                Bufferflush();
                switch (choice)
                {
                case 1:
                    viewinfo(&currentUser);
                    break;
                case 2:
                    changePassword(&currentUser);
                    break;
                case 3:
                    changeEmail(&currentUser);
                    break;
                case 4:
                    changePhoneNumber(&currentUser);
                    break;

                case 5:
                    goto mainmenu2;
                default:

                    printf("\tInvalid choice. Please try again.\n");
                    printf("Press any key to continue.");
                    getch();
                }
            }
            break;
        case 5:
            goto System_dash;
            break;
        case 6:
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
void createAccount()
{
    struct User newUser, temp;
    FILE *file = fopen("userdetail.txt", "a");
    FILE *f;
    int lastAccNo = 1000;
    header();

    // Open the user details file to find the last account number
    f = fopen("userdetail.txt", "r");
    if (f != NULL)
    {
        while (fscanf(file, "%d %s %s %s %.2f %s %s %s\n", &newUser.accountNumber, newUser.username, newUser.phone, newUser.password, &newUser.balance, newUser.dateOfBirth, newUser.address, newUser.email) != EOF)
        {
            lastAccNo = newUser.accountNumber;
        }

        fclose(f);
    }

    // Getting user inputs
    // Getting user Full name
    while (1)
    {
        printf("\tEnter your full name: ");
        scanf("%s", newUser.username); //%[^\n]
        if (isValidUsername(newUser.username) != 1)
        {
            printf("Error! \n");
        }

        else
            break;
    }
    Bufferflush();

    // Get user date of birth
    printf("\tEnter your date of birth in BS (YYYY-MM-DD): ");
    scanf("%s", newUser.dateOfBirth);
    Bufferflush();

    // Get user address
    printf("\tEnter your address: ");
    scanf("%s", newUser.address);
    Bufferflush();

    // Get user email
    printf("\tEnter your email: ");
    scanf("%s", newUser.email);
    Bufferflush();

    // Get valid phone number and check for duplicates
    while (1)
    {
        printf("\tEnter your phone number: ");
        scanf("%s", newUser.phone);
        Bufferflush();

        // Check if phone number already exists
        f = fopen("userdetail.txt", "r");
        int phoneExists = 0;
        if (f != NULL)
        {
            while (fscanf(file, "%d %s %s %s %.2f %s %s %s\n", &temp.accountNumber, temp.username, temp.phone, temp.password, &temp.balance, temp.dateOfBirth, temp.address, temp.email) != EOF)
            {
                if (strcmp(temp.phone, newUser.phone) == 0)
                {
                    phoneExists = 1;
                    break;
                }
            }
            fclose(f);
        }

        if (phoneExists)
        {
            printf("An account with this phone number already exists. Try entering with a different phone number.\n");
        }
        else
        {
            break;
        }
    }

    while (1)
    {

        printf("\tEnter a valid and strong password: ");
        scanf("%s", newUser.password);
        if (isValidPassword(newUser.password) != 1)
        {
            printf("\tError! Too weak password. Try again.\n");
        }

        else
            break;
    }

    Bufferflush();

    newUser.accountNumber = lastAccNo + 1;
    newUser.balance = 0.0;

    // Save user details to file
    if (file == NULL)
    {
        printf("\tError opening user details file.\n");
        return;
    }
    fprintf(file, "%d %s %s %s %.2f %s %s %s\n", newUser.accountNumber, newUser.username, newUser.phone, newUser.password, newUser.balance, newUser.dateOfBirth, newUser.address, newUser.email);
    fclose(file);

    printf("\tAccount created successfully!\n");
    printf("\tYour account number is: %d\n", newUser.accountNumber);
    printf("Press any key to procced to Login Page.");
    getch();
}

// Function to authenticate user
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
    Bufferflush();
    printf("\tEnter your username: ");
    scanf("%s", username);
    Bufferflush();
    printf("\tEnter your password: ");
    scanf("%s", password);
    Bufferflush();

    // Search for the user in the file
    while (fscanf(file, "%d %s %s %s %.2f %s %s %s\n", &user->accountNumber, user->username, user->phone, user->password, &user->balance, user->dateOfBirth, user->address, user->email) != EOF)
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
    Bufferflush();

    if (amount <= 0)
    {
        printf("\tInvalid amount. Please enter a positive value.\n");
        printf("Press any key to continue.");
        getch();
        return;
    }

    user->balance += amount;
    printf("\tDeposit successful. New balance: %.2f\n", user->balance);
    continueKey();
    // Log the transaction
    logTransaction(user->accountNumber, "DEPOSIT", amount, user->balance);

    // Update user balance in the file
    updateUserBalance(user);
}

// Function to withdraw money
void withdrawMoney(struct User *user)
{
    float amount;
    header();

    printf("\tEnter the amount to withdraw: ");
    scanf("%f", &amount);
    Bufferflush();

    if (amount <= 0)
    {
        printf("\tInvalid amount. Please enter a positive value.\n");
        continueKey();
        return;
    }

    if (amount > user->balance)
    {
        printf("\tInsufficient balance.\n");
        continueKey();
        return;
    }

    user->balance -= amount;
    printf("\tWithdrawal successful. New balance: %.2f\n", user->balance);
    continueKey();
    // Log the transaction
    logTransaction(user->accountNumber, "WITHDRAW", amount, user->balance);

    // Update user balance in the file
    updateUserBalance(user);
    continueKey();
}

// Function to display account statement (only for the logged-in user)
void accountStatement(struct User *user)
{
    FILE *file = fopen("transaction_log.txt", "r");
    header();

    if (file == NULL)
    {
        printf("\tNo transactions found.\n");
        continueKey();
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
    continueKey();
}

// Function to log transactions
void logTransaction(int accountNumber, const char *type, float amount, float balance)
{

    FILE *file = fopen("transaction_log.txt", "a");
    header();

    if (file == NULL)
    {
        printf("\tError opening transaction log file.\n");
        continueKey();
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
        return;
    }

    struct User tempUser;

    while (fscanf(file, "%d %s %s %s %.2f %s %s %s\n", &tempUser.accountNumber, tempUser.username, tempUser.phone, tempUser.password, &tempUser.balance, tempUser.dateOfBirth, tempUser.address, tempUser.email)==8)
    {
        if (tempUser.accountNumber == user->accountNumber)
        {
            tempUser.balance = user->balance;
        }
        fprintf(tempFile, "%d %s %s %s %.2f %s %s %s\n", tempUser.accountNumber, tempUser.username, tempUser.phone, tempUser.password, tempUser.balance, tempUser.dateOfBirth, tempUser.address, tempUser.email);
    }

    fclose(file);
    fclose(tempFile);

    remove("userdetail.txt");
    rename("temp.txt", "userdetail.txt");
}

// Press any key to continue
void continueKey()
{
    printf("\tPress any key to continue.");
    getch();
}

// Buffer Flush
void Bufferflush()
{
    // Buffer Flush
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

// Organization's Header                     --Ready
void header()
{
    system("cls");
    printf("\n");
    printf("\t\t\t|| NAM BANK ||\n");
    printf("\n");
    printf("\t---------- Bank Management System ----------");
    // printf("\n====================================================");
    printf("\n\t___________________________________________________________");
    printf("\n");
}

// boot graphics
void boot()
{
    printf("\n\n\n\n");
    printf("\t\t\tNNNN    N  AAAAA  M    M      BBBBB    AAAAA  NNNN    N  K   K\n");
    printf("\t\t\tN   N   N  A   A  MM  MM      B    B   A   A  N   N   N  K  K\n");
    printf("\t\t\tN    N  N  AAAAA  M MM M      BBBBB    AAAAA  N    N  N  KK\n");
    printf("\t\t\tN     N N  A   A  M    M      B    B   A   A  N     N N  K  K\n");
    printf("\t\t\tN      NN  A   A  M    M      BBBBB    A   A  N      NN  K   K\n");
    printf("\n\n\t\t\t\t\t\tWELCOMES YOU!\n\n");
    sleep(1);
    printf("\t\t\t");

    for (int i = 0; i < 62; i++)
    {
        printf("_");
        usleep(1000);
    }
    usleep(100000);
}
int isValidPassword(char *password)
{
    int length = 0, hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    char specialChars[] = "@$!%*?&";

    length = strlen(password);
    if (length < 8)
        return 0; // Password must be at least 8 characters long

    for (int i = 0; i < length; i++)
    {
        if (isupper(password[i]))
            hasUpper = 1;
        if (islower(password[i]))
            hasLower = 1;
        if (isdigit(password[i]))
            hasDigit = 1;
        if (strchr(specialChars, password[i])) // check the character in string and return pointer if found
            hasSpecial = 1;
    }

    return (hasUpper && hasLower && hasDigit && hasSpecial); // logic AND (&&), Return 1 if every values has 1
}
int isValidUsername(char *username)
{
    int length = strlen(username);

    // Check length (5-15 charters)
    if (length < 5 || length > 40 || (isalpha(username[0]) != 1))
    {
        return 0;
    }
    return 1; // Valid username
}

// not completed.........................
void viewinfo(struct User *user)
{
    printf("Hello");
}
void changePassword(struct User *user)
{
    printf("Opps! Comming soon...");
}
void changeEmail(struct User *user)
{
    printf("Opps! Comming soon...");
}
void changePhoneNumber(struct User *user)
{
    printf("Opps! Comming soon...");
}
