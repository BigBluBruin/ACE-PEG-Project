using namespace std; 
#include <ACE_toolbox.h>


  
// Driver program to test above functions 
int main() 
{ 
   std::vector<std::vector<int>> mat {{1,1,0,0}, 
                  {1,0,1,1}, 
                   {1,0,1,1}}; 
    
    std::cout<<rankOfMatrix(mat)<<std::endl;; 
    return 0; 
} 