#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Somente inclui se for compatível com o processador
#ifdef _OPENMP
#include <omp.h>
#endif

/* count sort paralelo */
double count_sort_parallel(double b[], int n, int nt) {
	#ifdef _OPENMP
		int i, j, count;
		double *temp;
		double start, end, duracao;

		temp = (double *)malloc(n*sizeof(double));

		start = omp_get_wtime();

		//Paralel for
		#pragma omp parallel for num_threads (nt) \
		private(count, j)
			for (i = 0; i < n; i++) {
				count = 0;
				for (j = 0; j < n; j++)
					if (b[j] < b[i])
						count++;
					else if (b[j] == b[i] && j < i)
						count++;
				temp[count] = b[i];
			}

			end = omp_get_wtime();


			duracao = end - start;

			memcpy(b, temp, n*sizeof(double));
			free(temp);

			return duracao;

	#endif
}

int main(int argc, char * argv[]) {
	int i, n, nt;
	double  *b, t_p;

	/* numero de threads */
	scanf("%d",&nt);

	/* numero de valores */
	scanf("%d",&n);

	/* aloca os vetores de valores para o teste em serial(b) e para o teste em paralelo(a) */
	b = (double *)malloc(n*sizeof(double));

	/* entrada dos valores */
	for(i=0;i<n;i++) {
		scanf("%lf",&b[i]);
	}

	/* chama as funcoes de count sort em paralelo e em serial */
	t_p = count_sort_parallel(b, n, nt);

	/* imprime o vetores ordenado */

	for(i=0;i<n;i++)
		printf("%.2lf ",b[i]);

	printf("\n");

	/* imprime o tempo obtido*/
	printf("%lf\n", t_p);

	return 0;
}
