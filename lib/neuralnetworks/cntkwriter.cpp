#include "cntkwriter.hpp"

#include <random>

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
    assert(current_state.size() == 19*19 && next_move.size() == 19*19);
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

int8_t encodeColor(QGo::Case color, QGo::Case color_to_play)
{
    if(color == QGo::EMPTY) return 0;
    return color == color_to_play ? 1 : -1;
}

CntkWriter::GobanVector_t encode(const Goban& goban, QGo::Case color_to_play)
{
    CntkWriter::GobanVector_t res(goban.size() * goban.size(), 0);
    for(uint8_t y = 0; y < goban.size(); y++)
    {
        for(uint8_t x = 0; x < goban.size(); x++)
        {
            res[x + y * goban.size()] = encodeColor(goban(x, y), color_to_play);
        }
    }
    return res;
}