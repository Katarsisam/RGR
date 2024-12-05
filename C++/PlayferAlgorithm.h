#ifndef PLAYFER_ALGORITHM_H
#define PLAYFER_ALGORITHM_H

#include <string>
 
class PlayferAlgorithm {
public:
    void execute(std::string inputX);

private:
    int var;
    std::string keyword;
    std::string message;
    char matrix[5][5];
    
    void generate_matrix(const std::string& alphabet);
    std::pair<int, int> find_position(char c);
    std::string encode_bigram(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2);
    std::string decode_bigram(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2);
};

#endif // PLAYFER_ALGORITHM_H
