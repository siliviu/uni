#include <iostream>
#include <omp.h>

using namespace std;

const int MAX = 20;
int a[MAX], b[MAX], m[MAX][MAX], c[MAX];

int produsScalar(int a[MAX], int b[MAX]) {
    int s = 0;

    for (int i = 0; i < MAX; i++) {
        s += a[i] * b[i];
    }

    return s;
}

int produsScalarParallel(int a[MAX], int b[MAX]) {
    int sum = 0;
    int partial_sum = 0;

    // public private firstprivate lastprivate
    #pragma omp parallel firstprivate(partial_sum) num_threads(16)
    {
        #pragma omp for
        for (int i = 0; i < MAX; i++) {
            partial_sum += a[i] * b[i];
        }

        #pragma omp critical
        {
            sum += partial_sum;
        }
    }

    return sum;
}

int produsScalarParallel2(int a[MAX], int b[MAX]) {
    int sum = 0;
    // omp parallel + omp for
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < MAX; i++) {
        sum += a[i] * b[i];
    }

    return sum;
}

void addVectors(int a[MAX], int b[MAX], int c[MAX])
{
    for (int i = 0; i < MAX; i++) {
        c[i] = a[i] + b[i];
    }
}

void multiplyVectors(int a[MAX], int b[MAX], int c[MAX])
{
    for (int i = 0; i < MAX; i++) {
        c[i] = a[i] * b[i];
    }
}


int main() {
    omp_set_num_threads(4);

    cout << "Thread num1: " << omp_get_num_threads() << endl;

    #pragma omp parallel num_threads(16)
    {

        cout << "Thread num2: " << omp_get_num_threads() << endl;

        #pragma omp critical
        {
            cout << "Hello from: " << omp_get_thread_num() << endl;
            cout << "Thread num3: " << omp_get_num_threads() << endl;
        }

        cout << "Thread num4: " << omp_get_num_threads() << endl;

        #pragma omp for schedule(static, 2) nowait 
        for (int i = 0; i < MAX; i++) {
            a[i] = omp_get_thread_num();
            b[i] = i;
        }

        #pragma omp for schedule(static, 2) collapse(2)
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                m[i][j] = omp_get_thread_num();
            }
        }
    }

    for (int i = 0; i < MAX; i++) {
        cout << a[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << produsScalar(a, b) << endl;
    cout << produsScalarParallel(a, b) << endl;
    cout << produsScalarParallel2(a, b) << endl;

    #pragma omp parallel num_threads(8)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                addVectors(a, b, c);
                #pragma omp critical
                {
                    cout << "Section add: " << omp_get_thread_num() << endl;
                }
            }
            #pragma omp section
            {
                multiplyVectors(a, b, c);
                #pragma omp critical
                {
                    cout << "Section multiply: " << omp_get_thread_num() << endl;
                }
            }
            #pragma omp section
            {
                produsScalar(a, b);
                #pragma omp critical
                {
                    cout << "Section produs: " << omp_get_thread_num() << endl;
                }
            }
        }
    }

    #pragma omp single
    {
        cout << "Doar eu execut: " << omp_get_thread_num() << endl;
    }
}