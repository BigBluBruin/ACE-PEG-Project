using namespace std; 
#include <ACE_toolbox.h>
#include <CPEG_toolbox.h>
#include "PBRL_LDPC_H_Generator.h"

// Driver program to test above functions
int main()
{

    std::vector<std::vector<int>> protomatrix{
        {3, 3, 3, 3, 1, 1, 1, 2, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 3, 3, 3, 1, 2, 2, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0},
        {2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}
        };
    int high_rate_row=2;
    int high_rate_column=10;
    int d_ace=5;
    int eta_ace=3;
    int cir_size=129;
    std::vector<std::vector<int>> maxrix=ACE_PEG_generator(protomatrix,high_rate_row,high_rate_column,cir_size,d_ace,eta_ace);

    // std::vector<std::vector<int>> mat{
    //     {1,1,0,0},
    //     {1,1,0,1},
    //     {0,0,1,1},
    //     {1,1,1,1}
    // };
    // int a=rankOfMatrix(mat);
    return 0;
}

// std::cout << "test generating random desigend circulant.." << std::endl;
// std::vector<std::vector<int>> test1 = single_circulant_generator(2, 8);
// std::cout << "result is:" << std::endl;
// display(test1);
// std::cout << "test idenity matrix generator.." << std::endl;
// std::vector<std::vector<int>> test2 = identity_circulant_generator(8);
// std::cout << "result is:" << std::endl;
// display(test2);

// std::vector<int> column_vector1{0,1,2};
// std::vector<int> column_vector2{0,1,0};
// std::cout<<"now testing random column circulant generator ..." <<std::endl;
// std::vector<std::vector<int>> column_circulant1=column_circulant_generator(column_vector1,6);
// display(column_circulant1);
// std::cout<<"--------------------------------"<<std::endl;
// std::cout<<"now testing identity column circulant generator ..." <<std::endl;
// std::vector<std::vector<int>> column_circulant2=column_circulant_generator(column_vector2,6,"identity");
// display(column_circulant2);
// std::cout<<"--------------------------------"<<std::endl;
// std::cout<<"now testing identity column circulant combination ..." <<std::endl;
// add_new_colum_circulant(column_circulant1,column_circulant2);
// display(column_circulant1);

// std::cout << "the matrix we used is..." << std::endl;
// display(matrix);
// std::cout << "-------------------------" << std::endl;
// std::cout << "now testing find_cn_neighbors" << std::endl;
// std::vector<std::vector<int>> cn_neighbor = find_cn_neighbors(matrix);
// display(cn_neighbor);
// std::cout << "-------------------------" << std::endl;
// std::cout << "now testing find_vn_neighbors" << std::endl;
// std::vector<std::vector<int>> vn_neighbor = find_vn_neighbers(matrix);
// display(vn_neighbor);