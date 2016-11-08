#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <memory>

#include <boost/filesystem/path.hpp>

namespace NeuralNetworks
{

    class NeuralNetworkImpl;

    class NeuralNetwork
    {
    public:
        /**
         * @pre model_file exists
        */
        NeuralNetwork(const boost::filesystem::path& model_file);

        ~NeuralNetwork();

        std::vector<float> operator()(const std::vector<float>& inputs) const;

    private:
        std::unique_ptr<NeuralNetworkImpl> m_impl;
    };

} // NeuralNetworks

#endif // NEURALNETWORK_HPP
