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
#include <map>

#define THREAD_NUM 2

using namespace Eigen;
using namespace std;

map<string, string> m2;

typedef struct _thread_arg {
    int id;
} thread_arg_t;

/* srcIP, destIP */
typedef struct _result {
  map<string, string> m;
  pthread_mutex_t mutex;
} result_t;
result_t result;

/* dataNo(counter), bytes */
typedef struct _result2 {
  map<int, int> m;
  pthread_mutex_t mutex;
} result2_t;
result2_t result2;

void thread_func(void *arg) {
    thread_arg_t* targ = (thread_arg_t *)arg;
    int i, j, k;
    int label = 0;
    unsigned int key = 0;
    unsigned int value = 0;
    int counter = 0;
    string src;
    string dst;

    map<int, int> myAddrPair;

    std::cout << "FUNC1:thread ID: " << targ->id << " - start." << std::endl; 
    
    string fname = std::to_string(targ->id);

    ifstream ifs(fname);
 
    string str;
    while(getline(ifs,str)){
      string token;
      istringstream stream(str);
      counter = 0;
      while(getline(stream,token,',')){
	// std::cout<< token << "(" << counter << "),";

	if(counter==7)
	  src = token;

	if(counter==9)
	  dst = token;
      
	counter = counter + 1;
      }

      result.myAddrPair.insert(pair<string, string>(src,dst));

      /*
      pthread_mutex_lock(&result.mutex);
      result.m.insert(pair<string, string>(src,dst));
      pthread_mutex_unlock(&result.mutex);
      */
      
      // cout<<endl;
    } // while(getline(ifs,str)){

    std::cout << "FUNC1:thread ID: " << targ->id << " - done." << std::endl; 
    
}

void thread_func2(void *arg) {
    thread_arg_t* targ = (thread_arg_t *)arg;
    int i, j, k;
    int label = 0;
    unsigned int key = 0;
    unsigned int value = 0;
    int counter = 0;
    int counter2 = 0;
    string src;
    string dst;
    int bytes;
    int sum_tmp = 0;

    int counter_display = 0;
    int counter_display2 = 0;
    
    std::cout << "FUNC2:thread ID: " << targ->id << " - start." << std::endl; 
    
    string fname = std::to_string(targ->id);

    ifstream ifs(fname);
 
    string str;
    while(getline(ifs,str)){
      string token;
      istringstream stream(str);
      counter = 0;
      while(getline(stream,token,',')){
	// std::cout<< token << "(" << counter << "),";

	if(counter==7)
	  {
	    src = token;
	  }
	if(counter==9)
	{
	  dst = token;
	}

	if(counter==25)
	  {
	    bytes =  std::atoi(token.c_str());
	  }
	
        counter = counter + 1;
      }
      
      map<string, string>::iterator itr;

      // m2 = result.m;
      
      counter2 = 0;
      sum_tmp = 0;
      for (itr = m2.begin(); itr != m2.end(); itr++)
	{
	  if(src == itr->first && dst == itr->second) {
	    
	    //std::cout << "MATCH" << std::endl;
	    //std::cout << src << ":" << dst << ":" << bytes << std::endl;

	    pthread_mutex_lock(&result2.mutex);
	    
	    sum_tmp = sum_tmp + bytes;
	    result2.m.insert(pair<int, int>(counter2,sum_tmp));
	      
	    pthread_mutex_unlock(&result2.mutex);
	    
	  } // if(src == itr->first && dst == itr->second) {
	  
	  counter2 = counter2 + 1;	  
      }

      if(counter_display % 100000 ==0)
	{
	  std::cout << "thread:" << targ->id << ": " << counter_display2 << " - done." << std::endl;
	  
	  counter_display2++;
	}
      counter_display = counter_display + 1;
      
    } // while(getline(ifs,str)){

    std::cout << "FUNC2:thread ID: " << targ->id << " - done." << std::endl; 
    
}

int main(int argc, char *argv[])
{
    pthread_t handle[THREAD_NUM];
    thread_arg_t targ[THREAD_NUM];
    int counter = 0;
    
    int i;

    /* 処理開始 */
    for (i = 0; i < THREAD_NUM; i++) {
        targ[i].id = i;
	/* size of data */
        // targ[i].rows = atoi(argv[1]);
	// targ[i].columns = atoi(argv[2]);
        pthread_create(&handle[i], NULL, (void*)thread_func, (void*)&targ[i]);
    }

    /* 終了を待つ */
    for (i = 0; i < THREAD_NUM; i++) 
        pthread_join(handle[i], NULL);

    std::cout << "map size() is " << result.m.size() << std::endl;

    m2 = result.m;

    /* 処理開始 */
    for (i = 0; i < THREAD_NUM; i++) {
        targ[i].id = i;
        pthread_create(&handle[i], NULL, (void*)thread_func2, (void*)&targ[i]);
    }

    /* 終了を待つ */
    for (i = 0; i < THREAD_NUM; i++) 
        pthread_join(handle[i], NULL);

    /* srcIP, destIP */
    /*
    map<string, string>::iterator itr;

    counter = 0;
    for (itr = result.m.begin(); itr != result.m.end(); itr++)
      {
	std::cout << itr->first << "," << itr->second << std::endl;

	if(counter==10)
	  break;
	
	counter = counter + 1;
      }
    */    

    map<int, int>::iterator itr2;
    std::vector<int> v;

    counter = 0;
    for (itr2 = result2.m.begin(); itr2 != result2.m.end(); itr2++)
      {
	/* first is counter */
	// std::cout << (unsigned int)itr2->first << "," << (unsigned int)itr2->second << std::endl;
	v.push_back((unsigned int)itr2->second);
	
	if(counter==10)
	  break;
	
	counter = counter + 1;
      }

    map<string, string>::iterator itr;

    counter = 0;
    for (itr = result.m.begin(); itr != result.m.end(); itr++)
      {

	int last = v.back();
	v.pop_back();
	
	std::cout << itr->first << "," << itr->second << "," << last << std::endl;

	if(counter==10)
	  break;
	
	counter = counter + 1;
      }
    
}
