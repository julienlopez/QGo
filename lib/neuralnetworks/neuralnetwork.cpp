#include "neuralnetwork.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

#include <boost/filesystem.hpp>

#ifdef WIN32
#include <windows.h>
#endif

namespace NeuralNetworks
{

    namespace
    {
        std::vector<float> sotfmax(std::vector<float> values)
        {
            std::transform(begin(values), end(values), begin(values), [](const float f){ return std::exp(f); });
            const auto sum = std::accumulate(begin(values), end(values), 0.f);
            std::transform(begin(values), end(values), begin(values), [sum](const float f){ return f / sum; });
            return values;
        }
    }

    class NeuralNetworkImpl
    {
    public:
        using CreateNetCallback = int (*)(const char*);
        using ReleaseNetCallback = void (*)();
        using AnalyzeCallback = int (*)(const float* const, float* res);

        NeuralNetworkImpl(const boost::filesystem::path& model_file)
        {
            assert(boost::filesystem::exists(model_file));
#ifdef WIN32
            const auto* dll_path = L"GoNet1.dll";
            auto hModule = LoadLibrary(dll_path);
            if(!hModule)
            {
                throw std::runtime_error("unable to load dll");
            }

            auto procAddress = GetProcAddress(hModule, "createNet");
            m_createNetCallback = (CreateNetCallback)procAddress;
            if(!m_createNetCallback) throw std::runtime_error("unable to retrieve creation callback");

            procAddress = GetProcAddress(hModule, "releaseNet");
            m_releaseNetCallback = (ReleaseNetCallback)procAddress;
            if(!m_releaseNetCallback) throw std::runtime_error("unable to retrieve releasing callback");

            procAddress = GetProcAddress(hModule, "analyze");
            m_analyzeCallback = (AnalyzeCallback)procAddress;
            if(!m_analyzeCallback) throw std::runtime_error("unable to retrieve analyze callback");

            auto res = m_createNetCallback(model_file.string().c_str());
            if(!res) throw std::runtime_error("unable to create network");
#else
            throw std::runtime_error("platform not supported")
#endif
        }

        ~NeuralNetworkImpl()
        {
            ReleaseNetCallback();
        }

        /**
        * @pre inputs.size() == 19*19
        * @post res.size() == 19*19
        */
        std::vector<float> operator()(const std::vector<float>& inputs) const
        {
            assert(inputs.size() == 19*19);
            std::vector<float> outputs(19*19, 0.f);
            auto res = m_analyzeCallback(inputs.data(), outputs.data());
            if(!res) throw std::runtime_error("unable to run CNN");
            return sotfmax(std::move(outputs));
        }

    private:
        CreateNetCallback m_createNetCallback = nullptr;
        ReleaseNetCallback m_releaseNetCallback = nullptr;
        AnalyzeCallback m_analyzeCallback = nullptr;
    };

    NeuralNetwork::NeuralNetwork(const boost::filesystem::path& model_file)
        : m_impl(std::make_unique<NeuralNetworkImpl>(model_file))
    {
    }

    NeuralNetwork::~NeuralNetwork() = default;

    std::vector<float> NeuralNetwork::operator()(const std::vector<float>& inputs) const
    {
        return (*m_impl)(inputs);
    }

}
