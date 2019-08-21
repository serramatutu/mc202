#include <stdio.h>
#define MAX 100

void printMatrix(float matrix[][], int m, int n) {
    for (int i=0; i < m; i++) {
        for (int j=0; j < n-1; j++) {
            printf("%.1f ", m[i][j]);
        }
        // o último elemento de cada linha não tem espaço depois, então é printado separadamente
        printf("%.1f\n", m[i][n-1]);
    }
}

void buildSpiralMatrix(float matrix[][], float vec[], int m, int n) {

}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    float vec[MAX];
    float matrix[MAX][MAX];

    for (int i=0; i < m*n; i++)
        scanf("%d", &vec[i]);
    
    buildSpiralMatrix(matrix, vec, m, n);
    printMatrix(matrix, m, n);

    return 0;
}