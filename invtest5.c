static char help[] = "Matrix inverse of upper triangular matrix\n\n";

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int n = 4;
const int m = 2*n;

void matrix_mult(double [][100], double [][100], double [][100], double [][100], int n);
void compute_inverse(double [][100], double [][100]);
void row_reduction(double [][m]);
double row_reduction_recursive1(double [][n], int size, int start);
double row_reduction_recursive4(double [][n], int size, int start);
void inverse_high(double [][m], double [][n]);

int main(int argc, char *argv[])
{
  int i, j;

  double A[n][n]; double csum[n]; double B [n][n]; double R[n][n]; double Ri[n][m]; double I[n][n];
    
  printf("initializing matrices and dynamically setting memory\n");

  printf("random filling----------------------------------------------\n");
  srand(time(NULL));
  for(i = 0; i<n; i++){ //row
    for(j = 0; j<n; j++){ //column
      A[j][i] = -1.00; //rand() %10 +1;//1.0
    }
  }
  for(i = 0; i<n; i++){ //row
    for(j = 0; j<n; j++){ //column
      printf("A[%d][%d]: %f\n", i, j, A[j][i]);
    }
    printf("\n");
  }
  
  printf("absolute value----------------------------------------------\n");
  for(j = 0; j<n; j++){
    for(i = 0; i<n; i++){
      if (A[j][i] < 0)
        A[j][i] = A[j][i] *(-1);
      printf("%f",A[j][i]);
      printf("\t");
    }
    printf("\n");
  }

  printf("sum of individual columns-----------------------------------\n");
  for(j = 0; j<n; j++){
    csum[j] = 0.0;
    for(i = 0; i<n; i++)
      csum[j] += A[i][j];
  }
  for(i = 0; i<n; i++){
    printf("csum[%d]: %f\n", i, csum[i]);
  }

  printf("creating new matrix from the column matrix sum--------------\n");
  for(i = 0; i<n; i++){
    for(j = 0; j<n; j++){
      if (i == j){
	B[i][j] = csum[j];
      } else {
	B[i][j] = 0.0;    
      }
      printf("%f",B[i][j]);
      printf("\t");
    }
    printf("\n");
  }
  
  printf("addition----------------------------------------------------\n");
  for(i = 0; i<n; i++){
    for(j = 0; j<n; j++){
      A[i][j] = A[i][j] + B[i][j];
      printf("S[%d][%d]: %f\n", i, j, A[i][j]);
    }
  }
   
  printf("upper triangular matrix-------------------------------------\n");
  for(i = 0; i<n; i++){
    for(j = 0; j<n; j++){    
      if (i > j){
	R[i][j] = 0.0;
      }
      else{
	R[i][j] = A[i][j];
      }
      printf("%f",R[i][j]);
      printf("\t");
    }
    printf("\n");
  }
  printf("saving R into Ri-------------------------------------\n");
  for(i = 0; i<n; i++){
    for(j = 0; j<m; j++){
      Ri[i][j] = 1.0;
    }
  }  
  for(i = 0; i<n; i++){
    for(j = 0; j<n; j++){
      Ri[i][j] = R[i][j];
    }
  }
  for(i = 0; i<n; i++){
    for(j = 0; j<m; j++){
      printf("%f",Ri[i][j]);
      printf("\t");
    }
    printf("\n");
  }
  
  printf("compute inverse-------------------------------------\n");
  inverse_high(Ri,R);
}

void inverse_high(double Ri[n][m], double R[n][n]) {
  int i; int k;int j; 

  if (n < 4){
    row_reduction(Ri);
  } else {
    int n1 = round(n/2);
    double temp_inv1[n1][n1], temp_inv2[n1][n1], temp_inv3[n1][n1], temp_inv4[n1][n1];
    double temp1[n1][n1], temp4[n1][n1], temp2[n1][n1], temp3[n1][n1];
    
    for(i = 0; i<n1; i++){
      for(j = 0; j<n1; j++){    
        temp1[i][j] = 0.0;
	temp2[i][j] = 0.0;
	temp3[i][j] = 0.0;
	temp4[i][j] = 0.0;
	temp_inv1[i][j]=0.0;
	temp_inv2[i][j]=0.0;
	temp_inv3[i][j]=0.0;
	temp_inv4[i][j]=0.0;
      }
    }    
    for(i = 0; i<n; i++){
      for(j = 0; j<m; j++){    
	printf("%f", Ri[i][j]);
	printf("\t");
      }
      printf("\n");
    }
    printf("block 1----------------------------------------------------\n");
    for(i = 0; i<n; i++){
      for(j = 0; j<2*n; j++){
	if (i < n1 && j < n1){
        temp1[i][j] = Ri[i][j];
	printf("%f", temp1[i][j]);
	printf("\t");
	} }
      printf("\n");
    }
    printf("block 2----------------------------------------------------\n");
    for(i = 0; i<n; i++){
      for(j = 0; j<2*n; j++){
	if (i< n1 && j >= n1 && j < n){
        temp2[i][j] = Ri[i][j];
	printf("%f", temp2[i][j]);
	printf("\t");
	}}
      printf("\n");
    }
    printf("block 3---------------------------------------------------\n");
    for(i = 0; i<n; i++){
      for(j = 0; j<2*n; j++){
	if (i>=n1 && j<n1){
        temp3[i][j] = Ri[i][j];
	printf("%f", temp3[i][j]);
	printf("\t");
	}}
      printf("\n");
    }
    printf("block 4---------------------------------------------------\n");
    for(i = 0; i<n; i++){
      for(j = 0; j<2*n; j++){
	if (i>=n1 && j>=n1 && j<n){
        temp4[i][j] = Ri[i][j];
	printf("%f", temp4[i][j]);
	printf("\t");
	}}
      printf("\n");
    }

    temp1[i][j] = row_reduction_recursive1(temp1,n1,0);

    printf("return R1 matrix----------------------------------------------------------------------------------------------------------\n");
    printf("inverse block 1\n");
    for(i = 0; i<n1; i++){
      for(j = n1; j<n; j++){    
        temp_inv1[i][j] = temp1[i][j];
	printf("%f", temp_inv1[i][j]);
	printf("\t");
      }
      printf("\n");
    }
    int aa =sizeof(temp4[0])/sizeof(temp4[0][0]); //length of dimension of array
    printf("size of temp4 dim: %d\n", aa);

    for(i = 0; i<n; i++){
      for(j = 0; j<n; j++){    
	printf("%f", R[i][j]);
	printf("\t");
      }
      printf("\n");
    }
    printf("block 4---------------------------------------------------\n");
    
    temp4[i][j] = row_reduction_recursive4(R,n,n1);
    printf("R4 matrix----------------------------------------------------------------------------------------------------------\n");
    printf("inverse block 4\n");/*
    for(i = n1; i<n; i++){
      for(j = n1; j<2*n; j++){    
        //temp_inv4[i][j] = temp4[i][j];
	printf("%f", temp4[i][j]);
	printf("\t");
      }
      printf("\n");
    }/*
    int size = sizeof(temp_inv4[0])/sizeof(temp_inv4[0][0]);
    printf("size for block inverse 4: %d\n", size);
    printf("matrix multiplication of R1inverse and R2------------------------------------------------------------------------------------------------\n");/*
    double mult[n1][n1]; int j,k;
    for (i = 0; i < n1; i++) {
      for (o = 0; o < n1; o++) {
	for (k = 0; k < n1; k++) {
	  mult[i][o] += temp_inv1[i][k] * temp2[k][o];
	}
      }
    }
    for(i = 0; i<n1; i++){
      for(o = 0; o<n1; o++){    
        printf("%f", mult[i][o]);
	printf("\t");
      }
      printf("\n");
      }*/
     
	     
  }  
}

void row_reduction(double Ri[n][m]){
  int i; int k;int j; 
  
  for(i = 0; i<n; i++){
    for(j = 0; j<m; j++){    
      printf("%f", Ri[i][j]);
      printf("\t");
    }
    printf("\n");
  }  
  //linear row reduction
  //creating identity matrix
  for(i = 0; i<n; i++){
    for(j = n; j<2*n; j++){
      if (i==j-n)
	Ri[i][j] = 1.0;
      else
	Ri[i][j] = 0.0;
    }
  }
  
  //row reduction
  for(i = 0; i<n; i++){
    for(j = 0; j<n; j++){
      if (i!=j){
	double red = Ri[j][i]/Ri[i][i];
	for(k = 0; k<2*n; k++)
	  Ri[j][k] -= red * Ri[i][k];
      }
    }
  }
  for(i = 0; i < n; i++){
    double inv = Ri[i][i];
    for(j = 0; j < 2*n; j++){
      Ri[i][j] /= inv;
    }
  }
  printf("The inverse matrix is: \n");
  for(i = 0; i < n; i++){
    for(j = n; j < 2*n; j++){
      printf("%f", Ri[i][j]);
      printf("\t");
    }
    printf("\n");
  }
  printf("compute_inverse function is done\n");
        
}

double row_reduction_recursive1(double temp1[][n], int size, int start){
  int i; int k;int j; 
  printf("start: %d, size %d\n", start, size);
  for(i = start; i<size; i++){
    for(j = start; j<size; j++){    
      printf("block[%d][%d]: %f\n", i, j, temp1[i][j]);
    }
  }  
  //linear row reduction
  //creating identity matrix
  //if (start == 1) {
  for(i = start; i<size; i++){
    for(j = size; j<2*size; j++){
      if (i==j-size)
	temp1[i][j] = 1.0;
      else
	temp1[i][j] = 0.0;
    }
  }
  //}
  //row reduction
  for(i = start; i<size; i++){
    for(j = start; j<size; j++){
      if (i!=j){
	double red = temp1[j][i]/temp1[i][i];
	for(k = 0; k<2*size; k++){
	  temp1[j][k] -= red * temp1[i][k];
	}}
    }
  }
  
  for(i = start; i < size; i++){
    double inv = temp1[i][i];
    for(j = start; j < 2*size; j++){
      temp1[i][j] /= inv;
    }
  }
  printf("The inverse matrix of block 1 is: \n");
  for(i = start; i < size; i++){
    for(j = size; j < 2*size; j++){
      printf("%f", temp1[i][j]);
      printf("\t");
    }
    printf("\n");
    }
  return (temp1[i][j]);
}

double row_reduction_recursive4(double R[][n], int size, int start){
  int i; int k;int j; double temp4[n/2][n/2];
  printf("start: %d, size %d\n", start, size);
      
    for(i = 0; i<size; i++){
      for(j = 0; j<size; j++){    
	printf("%f", R[i][j]);
	printf("\t");
      }
      printf("\n");
    }printf("space\n");
    for(i = 0; i<size; i++){
      for(j = 0; j<size; j++){
	if (i>=start && j>=start && j<size){
	temp4[i][j] = R[i][j];
	printf("temp[%d][%d]: %f", i,j,temp4[i][j]);
	printf("\t");
	}}
      printf("\n");
    }
     
  //linear row reduction
  //creating identity matrix
  //if (start == 1) {
  for(i = 2; i<4; i++){
    for(j = 4; j<6; j++){
      //if (i+2==j)
	//temp4[i][j] = 1.0;
      //else
	//temp4[i][j] = 0.0;
    }
  }
  printf("space2\n");
  for(i = 2; i<4; i++){
    for(j = 2; j<6; j++){    
      printf("temp[%d][%d]: %f", i,j,temp4[i][j]);
      printf("\t");
    }
    printf("\n");
  }




  /*
  //}
  //row reduction
  for(i = start; i<size; i++){
    for(j = start; j<size; j++){
      if (i!=j){
	double red = temp4[j][i]/temp4[i][i];
	for(k = 0; k<2*size; k++){
	  temp4[j][k] -= red * temp4[i][k];
	}}
    }
  }
  
  for(i = start; i < size; i++){
    double inv = temp4[i][i];
    for(j = start; j < 2*size; j++){
      temp4[i][j] /= inv;
    }
  }
  printf("The inverse matrix of block 4 is: \n");
  for(i = start; i < size; i++){
    for(j = size; j < 2*size; j++){
      printf("%f", temp4[i][j]);
      printf("\t");
    }
    printf("\n");
    }*/
    return (temp4[i][j]); 
}
