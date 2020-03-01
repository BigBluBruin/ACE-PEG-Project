#include "PBRL_LDPC_H_Generator.h"

std::vector<std::vector<int>> ACE_PEG_generator(std::vector<std::vector<int>> proto_matrix, int high_rate_row_ind,
                                                int high_rate_column_ind, int cirsize, int d_ace, int eta_ace)
{

    // This function generates full parity check matrix of PBRL-LDPC code using ACE-PEG algorithm
    // To realize this algotrithm we need propomatrix and corresponding information, and parameters
    // of ACE algorithm as input.

    std::vector<std::vector<int>> parity_check_matrix, temp_parity_check, rank_check_matrix, column_circulant, cn_neighors, vn_neighbors;
    std::vector<int> column_vector;
    bool rank_detection_not_pass = true;
    bool ACE_detection_pass = true;
    unsigned start_point, end_point;
    unsigned row_number = proto_matrix.size();
    unsigned column_number = proto_matrix[0].size();

    //first step: we design H_HRC and H_IRC together
    for (int column = 0; column <= high_rate_column_ind; column++)
    {
        // generate column vectror
        column_vector.clear();
        for (unsigned jj = 0; jj < row_number; jj++)
        {
            column_vector.push_back(proto_matrix[jj][column]);
        }

        ACE_detection_pass = false;
        while (!ACE_detection_pass)
        {
            if (column < high_rate_row_ind)
            {
                // rank condition detection needed
                rank_detection_not_pass = true;
                do
                {
                    // generate column circulant
                    column_circulant = column_circulant_generator(column_vector, cirsize);
                    temp_parity_check = parity_check_matrix;
                    add_new_colum_circulant(temp_parity_check, column_circulant);
                    rank_check_matrix.clear();
                    for (int jj = 0; jj < (column + 1) * cirsize; jj++)
                    {
                        rank_check_matrix.push_back(temp_parity_check[jj]);
                    }
                    if (rankOfMatrix(rank_check_matrix) == (int)(column + 1) * cirsize)
                    {
                        rank_detection_not_pass = false;
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
            end_point = row_number * cirsize;
            for (unsigned jj = start_point; jj <= end_point; jj++)
            {
                if (!ACE_detection(vn_neighbors, cn_neighors, d_ace, eta_ace, jj))
                {
                    ACE_detection_pass = false;
                    break;
                }
            }
        }
        //update parity check matrix
        parity_check_matrix = temp_parity_check;
    }


    // insert identity matrices to each column
    for (unsigned column = high_rate_column_ind + 1; column < column_number; column++)
    {
        // generate column vectror
        column_vector.clear();
        for (unsigned jj = 0; jj < row_number; jj++)
        {
            column_vector.push_back(proto_matrix[jj][column]);
        }
        column_circulant=column_circulant_generator(column_vector, cirsize,"identity");
        add_new_colum_circulant(parity_check_matrix, column_circulant);
    }
    return parity_check_matrix;
}