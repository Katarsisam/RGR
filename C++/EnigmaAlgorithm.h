#ifndef ENIGMA_ALGORITHM_H
#define ENIGMA_ALGORITHM_H

#include <string>
#include <vector>

class EnigmaAlgorithm {
public:
   void execute(std::string inputX);
private:
    int var;
    std::string message;
    std::vector<std::string> rotors;
    std::vector<int> rotor_shifts;

    void encode_message(const std::string& alphabet);
    void decode_message(const std::string& alphabet);
};

#endif // ENIGMA_ALGORITHM_H