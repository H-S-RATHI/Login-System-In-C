#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user {
    char fullName[50];
    char email[50];
    char password[50];
    char username[50];
    char phone[50];
};

void takeinput(char ch[50]) {
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = '\0';  // Remove newline character
}

void generateUsername(const char email[50], char username[50]) {
    int usernameIndex = 0;

    for (size_t i = 0; i < strlen(email); i++) {
        char currentChar = email[i];

        // Stop generating username when "@" is encountered
        if (currentChar == '@') {
            break;
        }

        // Only add alphanumeric characters to the username
        if (isalnum(currentChar)) {
            username[usernameIndex] = currentChar;
            usernameIndex++;
        }
    }

    // Terminate the username string
    username[usernameIndex] = '\0';
}

void takepassword(char pwd[50]) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == ENTER || ch == TAB) {
            pwd[i] = '\0';
            break;
        } else if (ch == BCKSPC) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++] = ch;
            printf("*");
        }
    }
}

int main() {
    struct user user;
    system("color 0b");
    FILE *fp;
    char start = 'y';
    int opt;
    char password2[50];

    printf("\n\t\t\t--------------WELCOME TO AUTHENTICATION SYSTEM-----------------");

    while (start == 'y') {
        printf("\n\n\t\t\t\t\tPlease choose your operation");
        printf("\n\n\t\t\t\t\t\t1.Signup");
        printf("\n\t\t\t\t\t\t2.Login");
        printf("\n\t\t\t\t\t\t3.Exit");

        printf("\n\n\t\t\t\t\tYour choice->");
        scanf("%d", &opt);
        fgetc(stdin);

        switch (opt) {
            case 1:
                printf("\n\t\t\t\t\tEnter Your Full Name   :->");
                takeinput(user.fullName);
                printf("\t\t\t\t\tEnter Your Email       :->");
                takeinput(user.email);
                printf("\t\t\t\t\tEnter Your Contact no. :->");
                takeinput(user.phone);
                printf("\t\t\t\t\tEnter Your Password    :->");
                takepassword(user.password);
                printf("\n\t\t\t\t\tConfirm Your Password  :->");
                takepassword(password2);
                system("cls");
                printf("\n\t\t\t\t\tAccount Created Successfully");
                if (!strcmp(user.password, password2)) {
                    generateUsername(user.email, user.username);
                    printf("\n\t\t\t\t\t----------------------------");
                    printf("\n\n\t\t\t\t\tYOUR USERNAME IS: %s\n", user.username);
                    

                    // Open a file for writing
                    fp = fopen("user_data.txt", "a");  //
                                        if (fp != NULL) {
                        // Write user information to the file
                        fprintf(fp, "Username: %s\nFull Name: %s\nEmail: %s\nPhone: %s\nPassword: %s\n\n",
                                user.username, user.fullName, user.email, user.phone, user.password);

                        // Close the file
                        fclose(fp);
                    } else {
                        printf("\n\n\t\t\t\t\t\tFailed to open file for writing.");
                    }
                } else {
                    printf("\n\n\t\t\t\t\t\tPasswords do not match\n");
                }
                break;

                        
            // Inside the case 2 block
case 2:
    system("cls");
    printf("\n\t\t\t\t\tEnter Your Username  :->");
    takeinput(user.username);
    printf("\n\t\t\t\t\tEnter Your Password  :->");
    takepassword(user.password);

    fp = fopen("user_data.txt", "r");  // Open the user data file for reading
    int userFound = 0;

    if (fp != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, "Username:") != NULL) {
                char savedUsername[50];
                sscanf(line, "Username: %[^\n]", savedUsername);

                if (strcmp(savedUsername, user.username) == 0) {
                    fgets(line, sizeof(line), fp);  // Skip Full Name line
                    system("cls");
                    printf("\n\n\t\t\t\t\t--------User Details--------");
                    printf("\n\t\t\t\t\t----------------------------");
                    printf("\n\n\t\t\t\t\t%s", line);

                    fgets(line, sizeof(line), fp);  // Skip Email line
                    printf("\t\t\t\t\t%s", line);

                    fgets(line, sizeof(line), fp);  // Skip Phone line
                    printf("\t\t\t\t\t%s", line);
                    
                    fgets(line, sizeof(line), fp);  // Get Password line
                    char savedPassword[50];
                    sscanf(line, "Password: %[^\n]", savedPassword);
                    
                    if (strcmp(savedPassword, user.password) == 0) {
                        userFound = 1;
                        break;
                    }
                }
            }
        }
        fclose(fp);
        Sleep(2000);

        if (userFound) {
            printf("\n\n\t\t\t\t\t--------Login Successful--------\n");
        } else {
            printf("\n\n\t\t\t\t\t\tLogin failed.\n");
        }
    } else {
        printf("\n\n\t\t\t\t\t\tFailed to open file for reading.\n");
    }
    break;







            case 3:
                system("cls");
                printf("\n\n\t\t\t\t\t----------------------------\n");
                printf("\t\t\t\t\t-----Exiting the program-----\n");
                printf("\t\t\t\t\t----------------------------");
                start = 'n';
                break;

            default:
                printf("\n\n\t\t\t\t\t\tInvalid option\n");
                break;
        }
    }

    return 0;
}

