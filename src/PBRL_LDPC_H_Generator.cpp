#include "PBRL_LDPC_H_Generator.h"

std::vector<std::vector<int>> ACE_PEG_generator(std::vector<std::vector<int>> proto_matrix, int high_rate_row_ind,
                                                int high_rate_column_ind, int cirsize, int d_ace, int eta_ace)
{

    // This function generates full parity check matrix of PBRL-LDPC code using ACE-PEG algorithm
    // To realize this algotrithm we need propomatrix and corresponding information, and parameters
    // of ACE algorithm as input.

    std::vector<std::vector<int>> parity_check_matrix(proto_matrix.size()*cirsize), temp_parity_check, rank_check_matrix, column_circulant, cn_neighors, vn_neighbors;
    std::vector<int> column_vector;
    bool rank_detection_not_pass = true;
    bool ACE_detection_pass = true;
    unsigned start_point, end_point;
    unsigned row_number = proto_matrix.size();
    unsigned column_number = proto_matrix[0].size();
    int full_rank_try_time;
    int ace_try_time;
    //first step: we design H_HRC and H_IRC together
    for (int column = 0; column <= high_rate_column_ind; column++)
    {
        // generate column vectror
        std::cout<<"Info: Start to construct column circulant for column "<<column<<"..."<<std::endl;
        column_vector.clear();
        for (unsigned jj = 0; jj < row_number; jj++)
        {
            column_vector.push_back(proto_matrix[jj][column]);
        }
        ace_try_time=0;
        ACE_detection_pass = false;
        while (!ACE_detection_pass)
        {
            ace_try_time++;
            std::cout<<"Info: building ace-accepetd column circulant for column: "<<column<<", try time index: "<<ace_try_time<<"."<<std::endl;
            if (column < high_rate_row_ind)
            {
                // rank condition detection needed
                rank_detection_not_pass = true;
                full_rank_try_time=0;
                do
                {
                    // generate column circulant
                    full_rank_try_time++;
                    std::cout<<"Info: building full rank matrix for column: "<<column<<", try time index: "<<full_rank_try_time<<"."<<std::endl;
                    column_circulant = column_circulant_generator(column_vector, cirsize);
                    temp_parity_check = parity_check_matrix;
                    add_new_colum_circulant(temp_parity_check, column_circulant);
                    
                    rank_check_matrix.clear();
                    for (int jj = 0; jj < (column + 1) * cirsize; jj++)
                    {
                        rank_check_matrix.push_back(temp_parity_check[jj]);
                    }
                    if (rank_check_matrix.size()!= rank_check_matrix[0].size())
                    {
                        std::cout<<"Warning: Row and column are not consistant!"<<std::endl;
                    }
                    std::cout<<"temp_parity_check_size: ("<<rank_check_matrix.size()<<", "<<rank_check_matrix[0].size()<<")."<<std::endl;
                    std::cout<<"start to check rank..."<<std::endl;
                    // std::cout<<rankOfMatrix(rank_check_matrix)<<std::endl;
                    int rank=rankOfMatrix(rank_check_matrix);
                    if (rank == (int)(column + 1) * cirsize)
                    {
                        std::cout<<"try time "<<full_rank_try_time<<". Success to find full rank matrix."<<std::endl;
                        rank_detection_not_pass = false;
                    }
                    else
                    {
                        if(rank==257)
                        {
                            std::ofstream myfile("check.txt");
                            for(const auto aa:rank_check_matrix)
                            {
                                for(const auto bb:aa)
                                {
                                    myfile<<bb<<"  ";
                                }
                                myfile<<std::endl;
                            }
                            myfile.close();
                            return parity_check_matrix;
                        }
                    
                        std::cout<<"try time "<<full_rank_try_time<<". Fail.to find full rank matrix. Current rank is: "<<rank<<"."<<std::endl;
                    }
                    
                } while (rank_detection_not_pass);
            }
            else
            {
                // no need to do rank detection
                column_circulant = column_circulant_generator(column_vector, cirsize);
                temp_parity_check = parity_check_matrix;
                add_new_colum_circulant(temp_parity_check, column_circulant);
            }

            // ACE detection for new variable nodes
            cn_neighors = find_cn_neighbors(temp_parity_check);
            vn_neighbors = find_vn_neighbers(temp_parity_check);
            start_point = column * cirsize;
            end_point = (column + 1) * cirsize - 1;
            std::cout<<"end piont.." <<end_point<<std::endl;
            ACE_detection_pass = true;
            for (unsigned jj = start_point; jj <= end_point; jj++)
            {
                if (!ACE_detection(vn_neighbors, cn_neighors, d_ace, eta_ace, jj))
                {
                    ACE_detection_pass = false;
                    std::cout<<"try time: " <<ace_try_time<<". Fail to obtian ace-paseed colum."<<std::endl;
                    break;
                }
            }
            //update parity check matrix
            //std::cout<<"here"<<std::endl;
            if (ACE_detection_pass)
            {
                parity_check_matrix = temp_parity_check;
                std::cout<<"try time: " <<ace_try_time<<". Success to obtian ace-paseed colum."<<std::endl;
            }
        }
    }

    // insert identity matrices to each column
    for (unsigned column = high_rate_column_ind + 1; column < column_number; column++)
    {
        // generate column vectror
        std::cout<<"Info: Start to construct column circulant for column "<<column<<"..."<<std::endl;
        column_vector.clear();
        for (unsigned jj = 0; jj < row_number; jj++)
        {
            column_vector.push_back(proto_matrix[jj][column]);
        }
        column_circulant=column_circulant_generator(column_vector, cirsize,"identity");
        add_new_colum_circulant(parity_check_matrix, column_circulant);
        std::cout<<"Indentity added: Successfully."<<std::endl;
    }

    std::cout<<"parity check matrix is successfully generated!"<<std::endl;
    std::cout<<"codeword length(n): "<<parity_check_matrix[0].size();
    std::cout<<"parity length(k): "<<parity_check_matrix.size();
    return parity_check_matrix;
}