#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

void addEmployee(FILE *fp) {
    struct Employee emp;
    int pos;

    printf("Enter record position to add (0-indexed): ");
    scanf("%d", &pos);
    printf("Enter ID, Name, Salary: ");
    scanf("%d %s %f", &emp.id, emp.name, &emp.salary);

    fseek(fp, pos * sizeof(emp), SEEK_SET);
    fwrite(&emp, sizeof(emp), 1, fp);
    printf("Employee record added.\n");
}

void displayEmployees(FILE *fp) {
    struct Employee emp;
    rewind(fp);
    printf("\n--- Employee Records ---\n");
    int i = 0;
    while (fread(&emp, sizeof(emp), 1, fp)) {
        printf("Record %d: ID=%d, Name=%s, Salary=%.2f\n", i++, emp.id, emp.name, emp.salary);
    }
}

void modifyEmployee(FILE *fp) {
    struct Employee emp;
    int targetId;
    int found = 0;

    printf("Enter Employee ID to modify: ");
    scanf("%d", &targetId);

    rewind(fp);
    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == targetId) {
            found = 1;
            printf("Enter new Name and Salary: ");
            scanf("%s %f", emp.name, &emp.salary);

            fseek(fp, -sizeof(emp), SEEK_CUR);
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Record updated.\n");
            break;
        }
    }

    if (!found)
        printf("Employee with ID %d not found.\n", targetId);
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Unable to open file.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Menu ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Modify Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(fp); break;
            case 2: displayEmployees(fp); break;
            case 3: modifyEmployee(fp); break;
            case 4: break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 4);

    fclose(fp);
    return 0;
}

