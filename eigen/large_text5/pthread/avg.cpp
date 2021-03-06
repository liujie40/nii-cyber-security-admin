#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>

#include <string>
#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Dense>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/SVD>

#include <random>

#define THREAD_NUM 719
#define CLUSTER_NUM 10
#define ITEM_NUM 3

using namespace Eigen;
using namespace std;

Eigen::MatrixXd avg;

Eigen::MatrixXd readCSV(std::string file, int rows, int cols) {
  
  std::ifstream in(file.c_str());

  std::string line;

  int row = 0;
  int col = 0;

  Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);

  if (in.is_open()) {

    while (std::getline(in, line)) {

      char *ptr = (char *) line.c_str();
      int len = line.length();

      col = 0;

      char *start = ptr;
      for (int i = 0; i < len; i++) {

	if (ptr[i] == ',') {
	  res(row, col++) = atof(start);
	  start = ptr + i + 1;
	}
      }
      res(row, col) = atof(start);

      row++;
    }

    in.close();
  }
  return res;
}

typedef struct _result {
  int cluster_no[CLUSTER_NUM];  
  double item_sum[CLUSTER_NUM][ITEM_NUM];
  pthread_mutex_t mutex;    
} result_t;
result_t result;

typedef struct _thread_arg {
    int id;
    int rows;
    int columns;
} thread_arg_t;

void thread_func(void *arg) {
    thread_arg_t* targ = (thread_arg_t *)arg;
    int i, j, k;
    int label = 0;
    long tmpNo;
    int my_cluster_no[CLUSTER_NUM];
    double my_item_sum[CLUSTER_NUM][ITEM_NUM];     

    string fname = std::to_string(targ->id) + ".labeled";

    for(i=0;i<CLUSTER_NUM;i++)
      {
	my_cluster_no[i]=0;
	for(j=0;j<ITEM_NUM;j++)
	  my_item_sum[i][j]=0;
      }

    /*
        targ[i].id = i;
        targ[i].rows = atoi(argv[4]);
	targ[i].columns = atoi(argv[5]);
        pthread_create(&handle[i], NULL, (void*)thread_func, (void*)&targ[i]);
    */

    Eigen::MatrixXd res = readCSV(fname, targ->rows,targ->columns);
    Eigen::MatrixXd res2 = res.leftCols(1);
    Eigen::MatrixXd res3 = res.rightCols(3);
    
    // for(i=0; i< res2.rows(); i++)
    for(i=0; i< res2.rows(); i++)
      {
	tmpNo = res2.row(i).col(0)(0);
	my_cluster_no[tmpNo]++;

	for(j=0; j < ITEM_NUM; j++)
	  my_item_sum[tmpNo][j] += res3.row(i).col(j)(0);
      }

    /*
    for(i=0; i< CLUSTER_NUM; i++)
      {
	std::cout << my_cluster_no[i] << std::endl;
      }
    */    

    pthread_mutex_lock(&result.mutex);

    for(i=0; i<CLUSTER_NUM; i++)
      {
	result.cluster_no[i] += my_cluster_no[i];
	
	for(j=0; j < ITEM_NUM; j++)
	  result.item_sum[i][j] += my_item_sum[i][j];
      }
      
      /*
      	result.item3_sum += my_item3_sum;
	result.item4_sum += my_item4_sum;
	result.item5_sum += my_item5_sum;
      */
      
    pthread_mutex_unlock(&result.mutex);
    
    /*
    std::string ofname = fname + ".labeled";      
    ofstream outputfile(ofname);

    std::random_device rnd;
    */

    /*
    for (int i = 0; i < 10; ++i) {
      tmp = rnd() % 10;
      std::cout << tmp << "\n";
    }
    */

    std::cout << "thread ID: " << targ->id << " - done." << std::endl;

    return;
}

int main(int argc, char *argv[])
{
    pthread_t handle[THREAD_NUM];
    thread_arg_t targ[THREAD_NUM];
    int i,j;

    double avg_item_tmp[ITEM_NUM];
    MatrixXd centroid(CLUSTER_NUM,ITEM_NUM);
    
    /* 処理開始 */
    for (i = 0; i < THREAD_NUM; i++) {
        targ[i].id = i;
        targ[i].rows = atoi(argv[1]);
	targ[i].columns = atoi(argv[2]);
        pthread_create(&handle[i], NULL, (void*)thread_func, (void*)&targ[i]);
    }

    /* 終了を待つ */
    for (i = 0; i < THREAD_NUM; i++) 
        pthread_join(handle[i], NULL);

    std::string ofname = "centroid";      
    ofstream outputfile(ofname);
    
    for(i=0; i<CLUSTER_NUM; i++)
      {
	// std::cout << result.cluster_no[i] << endl;
	for(j=0; j<ITEM_NUM-1; j++)
	  {
	    avg_item_tmp[j] = result.item_sum[i][j] / result.cluster_no[i];
	    centroid(i,j) = avg_item_tmp[j];    
	    outputfile << avg_item_tmp[j] << ","; 
	    
	  }

        avg_item_tmp[j] = result.item_sum[i][j] / result.cluster_no[i];
	centroid(i,j) = avg_item_tmp[j];    
	outputfile << avg_item_tmp[j]; 

	outputfile << std::endl;
      }

      outputfile.close();
    
    std::cout << centroid << endl;
}

