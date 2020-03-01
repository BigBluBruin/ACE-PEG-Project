using namespace std; 
#include <ACE_toolbox.h>
#include <CPEG_toolbox.h>


  
// Driver program to test above functions 
int main() 
{ 

    std::vector<int> column_vector1{0,1,2};
    std::vector<int> column_vector2{0,1,0};
    std::cout<<"now testing random column circulant generator ..." <<std::endl;
    std::vector<std::vector<int>> column_circulant1=column_circulant_generator(column_vector1,6);
    display(column_circulant1);
    std::cout<<"--------------------------------"<<std::endl;
    std::cout<<"now testing identity column circulant generator ..." <<std::endl;
    std::vector<std::vector<int>> column_circulant2=column_circulant_generator(column_vector2,6,"identity");
    display(column_circulant2);
    std::cout<<"--------------------------------"<<std::endl;
    std::cout<<"now testing identity column circulant combination ..." <<std::endl;
    add_new_colum_circulant(column_circulant1,column_circulant2);
    display(column_circulant1);
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