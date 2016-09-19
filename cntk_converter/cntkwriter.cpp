#include "cntkwriter.hpp"

CntkWriter::CntkWriter(const boost::filesystem::path &train_path): m_train_file(train_path.string()), m_test_file(), m_percentage(0.)
{
    assert(m_train_file);
}

CntkWriter::CntkWriter(const boost::filesystem::path& train_path, const boost::filesystem::path& test_path, double percentage)
    : m_train_file(train_path.string()), m_test_file(test_path.string()), m_percentage(percentage)
{
    assert(m_train_file);
    assert(m_test_file);
}


void CntkWriter::addLine(const GobanVector_t& current_state, const GobanVector_t& next_move)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<> distrib(0, 1);
    auto& o = (m_test_file && distrib(generator) < m_percentage)? m_test_file : m_train_file;
    static auto conv = [](const int8_t i){ return std::to_string(i); };
    o << "|labels ";
    std::transform(begin(next_move), end(next_move), std::ostream_iterator<std::string>(o, " "), conv);
    o << "|features ";
    std::transform(begin(current_state), end(current_state), std::ostream_iterator<std::string>(o, " "), conv);
    o << "\n";
}
