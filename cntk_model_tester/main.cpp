#include "neuralnetworks/neuralnetwork.hpp"

#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>w

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "expected usage : cntk_model_tester trained_model dataset" << std::endl;
        return 1;
    }
    if(!boost::filesystem::exists(argv[1]))
    {
        std::cerr << "unable to find " << argv[1] << std::endl;
        return 2;
    }
    if(!boost::filesystem::exists(argv[2]))
    {
        std::cerr << "unable to find " << argv[2] << std::endl;
        return 3;
    }
    const NeuralNetworks::NeuralNetwork model(argv[1]);
    std::ifstream dataset(argv[2]);
    std::string line;
    while(std::getline(dataset, line))
    {
        boost::trim(line);
        std::cout << line << std::endl;
        assert(boost::starts_with(line, "|labels "));
        line = line.substr(8);
        std::cout << line << std::endl;
        std::vector<std::string> parts;
        //boost::split(parts, line, boost::algorithm::is_equal("|features "));
        assert(parts.size() == 2);

        int tmp;
        std::cin >> tmp;
    }
    return 0;
}
