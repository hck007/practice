#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

typedef struct matrix {
	    int rows;
	    int cols;
            int* data;
	    int ref_cnt;
            struct matrix *parent;
} matrix;


int main() {
	  test_mul_matrix();
	  return 0;
          
					  
}
void test_mul_matrix() {
	struct matrix* mat1 = (struct matrix*) malloc(sizeof(matrix));
	struct matrix* mat2 = (struct matrix*) malloc(sizeof(matrix));
	struct matrix* result = (struct matrix*) malloc(sizeof(matrix));
	mat1->rows = 4;
	mat1->cols = 3;
	mat2->rows = 3;
	mat2->cols = 6;
	result->rows = 4;
	result->cols = 6;
	int* array1 = (int*) malloc(sizeof(int) * 12);
	for (int i = 0; i < 12; i++) {
		array1[i] = i + 1;
	}
	int* array2 = (int*) malloc(sizeof(int) * 18);
	for (int i = 0; i < 18; i++) {
		array2[i] = i + 1;
	}
	int* array3 = (int*) malloc(sizeof(int) * 24);
	for (int i = 0; i < 24; i++) {
		array3[i] = 0;
	}
	mat1->data = array1;
	mat2->data = array2;
	result->data = array3;
	int ok = mul_matrix(result, mat1, mat2);
	for (int i = 0; i < 24; i++) {
		printf("%d\n", result->data[i]);
	}

}

int mul_matrix(matrix *result, matrix *mat1, matrix *mat2) {
	    /* TODO: YOUR CODE HERE */
	for (int i = 0; i < mat1->rows; i++) {
		for (int j = 0; j < mat2->cols / 4 * 4; j += 4) {
			__m128i sum = _mm_setzero_si128();
			for (int k = 0; k < mat2->rows; k++) {
				__m128i vA = _mm_set1_epi32(mat1->data[i * (mat1->cols) + k]);
				__m128i vB = _mm_loadu_si128((__m128i*) &(mat2->data[k * (mat2->cols) + j]));
				__m128i intermediate = _mm_mullo_epi32(vA, vB);
				sum = _mm_add_epi32(sum, intermediate);
			}
			_mm_storeu_si128((__m128i*) &(result->data[i * (mat2->cols) + j]), sum);
		}
		//tail case if mat2->cols is not multiple of 4
		for (int y = mat2->cols / 4 * 4; y < mat2->cols; y++) {
			int sum = 0;
			for (int z = 0; z < mat2->rows; z++) {
				sum += mat1->data[i * (mat1->cols) + z] * mat2->data[z * (mat2->cols) + y];
			}
			result->data[i * (mat2->cols) + y] = sum;
		}
		
	}
	return 0;
	        
}

int pow_matrix(matrix *result, matrix *mat, int pow) {
    /* TODO: YOUR CODE HERE */
        return 0;
}
