#include "svm.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct point {
        double x, y;
        signed char value;
};

const int current_value = 1;
list<point> point_list;

vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

void insertValues(double x, double y, int XLEN, int YLEN)
{
        point p = {x / XLEN, y / YLEN, current_value};
        point_list.push_back(p);
}

int main(int argc,char *argv[])
{
        svm_parameter param;
        int i,j;        

	std::string filename = argv[3];

	int XLEN;
	int YLEN;

	XLEN = atoi(argv[1]);
	YLEN = atoi(argv[2]);

	printf("matrix size %d %d \n", XLEN, YLEN);
     
	char c;

	ifstream ifs(filename);

	string line;
	while (getline(ifs, line)) {
        
        vector<string> strvec = split(line, ',');

	printf("%5f %5f \n", stof(strvec.at(0)), stof(strvec.at(1)));
	insertValues(stof(strvec.at(0)), stof(strvec.at(1)), XLEN, YLEN);
        
	/*
        for (int i=0; i<strvec.size();i++){
            printf("%5f ", stof(strvec.at(i)));
	}
	printf("\n");
	*/

	}

        // default
        param.svm_type = ONE_CLASS;
        param.kernel_type = RBF;
        param.degree = 3;
        param.gamma = 0;
        param.coef0 = 0;
        param.nu = 0.5;
        param.cache_size = 100;

        param.C = 1;
        param.eps = 1e-3;
        param.p = 0.1;
        param.shrinking = 1;

        param.probability = 0;
        param.nr_weight = 0;
        param.weight_label = NULL;
        param.weight = NULL;

	/*
        insertValues(0.0, 5.0);
        insertValues(5.0, 0.0);
        insertValues(5.0, 9.0);                                                                                         
        insertValues(9.0, 5.0);
	*/

        svm_problem prob;

        prob.l = point_list.size();
        prob.y = new double[prob.l];

        if(param.gamma == 0){
                param.gamma = 0.5;
        }

        svm_node *x_space = new svm_node[3 * prob.l];
        prob.x = new svm_node *[prob.l];

        i = 0;
        for (list <point>::iterator q = point_list.begin(); q != point_list.end(); q++, i++){
                x_space[3 * i].index = 1;
                x_space[3 * i].value = q->x;
                x_space[3 * i + 1].index = 2;
                x_space[3 * i + 1].value = q->y;
                x_space[3 * i + 2].index = -1;
                prob.x[i] = &x_space[3 * i];
                prob.y[i] = q->value;
        }

            
        // building models and classification
        svm_model *model = svm_train(&prob, &param);

	/*
        svm_node x[3];
        x[0].index = 1;
        x[1].index = 2;
        x[2].index = -1;

        for (i = 0; i < XLEN; i++){
                for (j = 0; j < YLEN ; j++) {
                        x[i].value = array[i][j];
                        x[j].value = array[i][j];

                        double d = svm_predict(model, x);

                        cout << d << " ";
                }
                cout << endl;
        }
	*/
	
        svm_free_and_destroy_model(&model);
        delete[] x_space;
        delete[] prob.x;
        delete[] prob.y;

        free(param.weight_label);
        free(param.weight);
       
        return 0;
}
