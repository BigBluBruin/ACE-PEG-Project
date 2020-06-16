# include<read_H_matrix.h>


void get_whole_H(std::vector<std::vector<int>>&  H,std::string filename, const char type[])
{
    // this function get M*N whold parity check matrix
    // it can get H from different tyope of files

    if(strcmp(type,"classic")==0)
    {
        std::ifstream myfile(filename);
        if(myfile.is_open())
        {
            int row, column;
            myfile>>column>>row;
            H.assign(row, std::vector<int> (column,0));
            for (int ii = 0; ii<row ;ii++)
            {
                for(int jj=0;jj<column;jj++)
                {
                    myfile>>H[ii][jj];
                }
            }
            std::cout<<"File :" << filename<<" is successfully read." <<std::endl;           
        }
        else
        {
            std::cout<<"can't open file :" << filename<<". check again plz." <<std::endl;
        }
        
    }
    else
    {
        std::cout<<"Info: No such type: "<<type<<". Check again, please. "<<std::endl;
    }

    
}