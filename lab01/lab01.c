#include <stdio.h>
#define MAX 100

void printMatrix(int m, int n, float matrix[m][n]) {
    for (int i=0; i < m; i++) {
        for (int j=0; j < n-1; j++) {
            printf("%.1f ", matrix[i][j]);
        }
        // o último elemento de cada linha não tem espaço depois, 
        // então é printado separadamente
        printf("%.1f\n", matrix[i][n-1]);
    }
}

void buildSpiralMatrix(int m, int n, float matrix[m][n], float vec[]) {
    int passes = n > m ? 2*m : 2*n-1; // qtd de "lados" da espiral 
    int vecIndex = 1;
    
    matrix[m-1][n-1] = vec[0];
    for (int pass=0; pass < passes; pass++) {
        // qtd de quadradinhos nesse "lado" da espiral
        int steps = pass % 2 == 0 ? m-1 : n-1;
        steps -= (int)((pass - 1)/2);

        int vOffset = (pass-1)/4+1,
            hOffset = (pass/4)+1;

        for (int step=0; step < steps; step++, vecIndex++) {
            switch (pass % 4) {
            case 0: // direita
                matrix[m-1-step-vOffset][n-hOffset] = vec[vecIndex];
                break;
            case 1: // topo
                matrix[vOffset-1][n-1-step-hOffset] = vec[vecIndex];
                break;
            case 2: // esquerda
                matrix[step+vOffset][hOffset-1] = vec[vecIndex];
                break;
            case 3: // baixo
                matrix[m-vOffset][step+hOffset] = vec[vecIndex];
                break;
            }
        }
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    float vec[MAX*MAX];
    float matrix[MAX][MAX];

    for (int i=0; i < m*n; i++) {
        scanf("%f", &vec[i]);
    }
    
    buildSpiralMatrix(m, n, matrix, vec);
    printMatrix(m, n, matrix);

    return 0;
}