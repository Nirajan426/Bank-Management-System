#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

// Structure to store user details
struct User
{
    int accountNumber;
    char username[50];
    char password[50];
    char phone[15];
    float balance;
    char dateOfBirth[11];
    char address[100];
    char email[50];
};

// Function prototypes
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
void lowercase(char str[]);
void continueKey();
void Bufferflush();
int main()
{
    
}