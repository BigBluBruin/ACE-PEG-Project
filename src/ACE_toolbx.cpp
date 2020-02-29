#include "ACE_toolbox.h"

bool ACE_detection(std::vector<std::vector<int>> vn_neighbor, std::vector<std::vector<int>> cn_neighbor, int d_ace, int eta_ace, int starting_v)
{
    /* 
    This algorithm analyze the ACE peropety given a matrix
    One has to provide the cn indecs (starting from 0) conncoted to each vn
    One has to provide the vn indeces (staring from 0) connected to each cn
    One has to prvoide two critical facors d_ace and eta_ace
    One has to provide the variable node it exmines, see paper in detail if you want to know the exat meaning of these two dectors 
    Function returns true, if the metrix passes ace dectction,
    Function returns false, otherwise
    */

    //Initialization
    std::vector<std::vector<int>> node_ace(2); //[0] -> check node ; [1] -> variable node
    std::vector<std::vector<int>> p(2);        //[0] -> check node; [1] -> variable node
    int p_tempt;
    int zero = 0;
    std::vector<int> node_set_kids, node_set_parents;
    std::vector<int> his_kids;
    int node_type_kid, node_type_parent;

    //Do some precomputation
    node_ace[0].assign(cn_neighbor.size(), 0);
    node_ace[1].assign(vn_neighbor.size(), 0);
    for (int ii = 0; ii < vn_neighbor.size(); ii++)
    {
        node_ace[1][ii] = std::max(zero, (int)vn_neighbor[ii].size() - 2);
    }
    p[0].assign(cn_neighbor.size(), 10000);
    p[1].assign(vn_neighbor.size(), 10000);
    node_set_parents.clear();
    node_set_parents.push_back(starting_v);

    for (int l = 1; l < d_ace; l++)
    {
        if (l % 2 == 0)
        {
            node_type_parent = 0;
            node_type_kid = 1;
        }
        else
        {
            node_type_parent = 1;
            node_type_kid = 0;
        }
    }

    if (node_set_parents.size() == 0)
    {
        std::cout << "There is no node in parent set. Returned Success" << std::endl;
        return true;
    }
    else
    {
        node_set_kids.clear();
        for (auto this_parent : node_set_parents)
        {
            if(node_type_parent==0)
            {
                his_kids=cn_neighbor[this_parent];
            }
        }
    }
}