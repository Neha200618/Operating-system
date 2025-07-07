#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10

struct Directory {
    char uname[30];
    char files[MAX_FILES][30];
    int file_count;
};

int main() {
    struct Directory dir[MAX_USERS];
    int user_count = 0;
    int choice;
    char uname[30], fname[30];
    int i, j;

    while (1) {
        printf("\n--- Two Level Directory Menu ---\n");
        printf("1. Create User Directory\n");
        printf("2. Create File under User\n");
        printf("3. Delete File under User\n");
        printf("4. Search File under User\n");
        printf("5. Display Files under User\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new user name: ");
                scanf("%s", uname);
                for (i = 0; i < user_count; i++) {
                    if (strcmp(dir[i].uname, uname) == 0) {
                        printf("User already exists!\n");
                        break;
                    }
                }
                if (i == user_count) {
                    strcpy(dir[user_count].uname, uname);
                    dir[user_count].file_count = 0;
                    user_count++;
                    printf("User directory created.\n");
                }
                break;

            case 2:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (i = 0; i < user_count; i++) {
                    if (strcmp(dir[i].uname, uname) == 0)
                        break;
                }
                if (i == user_count) {
                    printf("User not found.\n");
                    break;
                }
                printf("Enter file name: ");
                scanf("%s", fname);
                for (j = 0; j < dir[i].file_count; j++) {
                    if (strcmp(dir[i].files[j], fname) == 0) {
                        printf("File already exists under this user.\n");
                        break;
                    }
                }
                if (j == dir[i].file_count) {
                    strcpy(dir[i].files[dir[i].file_count++], fname);
                    printf("File created under user '%s'.\n", uname);
                }
                break;

            case 3:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (i = 0; i < user_count; i++) {
                    if (strcmp(dir[i].uname, uname) == 0)
                        break;
                }
                if (i == user_count) {
                    printf("User not found.\n");
                    break;
                }
                printf("Enter file name to delete: ");
                scanf("%s", fname);
                for (j = 0; j < dir[i].file_count; j++) {
                    if (strcmp(dir[i].files[j], fname) == 0) {
                        for (int k = j; k < dir[i].file_count - 1; k++) {
                            strcpy(dir[i].files[k], dir[i].files[k + 1]);
                        }
                        dir[i].file_count--;
                        printf("File deleted from user '%s'.\n", uname);
                        break;
                    }
                }
                if (j == dir[i].file_count) {
                    printf("File not found under this user.\n");
                }
                break;

            case 4:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (i = 0; i < user_count; i++) {
                    if (strcmp(dir[i].uname, uname) == 0)
                        break;
                }
                if (i == user_count) {
                    printf("User not found.\n");
                    break;
                }
                printf("Enter file name to search: ");
                scanf("%s", fname);
                for (j = 0; j < dir[i].file_count; j++) {
                    if (strcmp(dir[i].files[j], fname) == 0) {
                        printf("File '%s' found under user '%s'.\n", fname, uname);
                        break;
                    }
                }
                if (j == dir[i].file_count) {
                    printf("File not found under this user.\n");
                }
                break;

            case 5:
                printf("Enter user name: ");
                scanf("%s", uname);
                for (i = 0; i < user_count; i++) {
                    if (strcmp(dir[i].uname, uname) == 0)
                        break;
                }
                if (i == user_count) {
                    printf("User not found.\n");
                    break;
                }
                printf("Files under user '%s':\n", uname);
                if (dir[i].file_count == 0) {
                    printf("No files.\n");
                } else {
                    for (j = 0; j < dir[i].file_count; j++) {
                        printf("%s\n", dir[i].files[j]);
                    }
                }
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

