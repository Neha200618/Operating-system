#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m; // n = number of processes, m = number of resources
    int Allocation[MAX][MAX], Max[MAX][MAX], Need[MAX][MAX];
    int Available[MAX], Finish[MAX] = {0}, SafeSeq[MAX];
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canExecute = true;
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Available[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (k = 0; k < m; k++)
                        Available[k] += Allocation[i][k];
                    SafeSeq[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is in UNSAFE state. Deadlock may occur.\n");
            return 1;
        }
    }

    printf("\nSystem is in SAFE state.\nSafe sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", SafeSeq[i]);
    printf("\n");

    return 0;
}

