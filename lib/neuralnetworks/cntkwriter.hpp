#ifndef __CNTKWRITER_HPP__
#define __CNTKWRITER_HPP__

#include "goban.hpp"

#include <fstream>

#include <boost/filesystem/path.hpp>

class CntkWriter
{
public:

    using GobanVector_t = std::vector<int8_t>;

    /**
     * @brief CntkWriter
     * @param train_path
     */
    CntkWriter(const boost::filesystem::path& train_path);

    /**
     * @brief CntkWriter
     *
     * @pre 0 < percentage < 1
     *
     * @param train_path
     * @param test_path
     * @param percentage likelihood the move will be added to the test file instead of the train file
     */
    CntkWriter(const boost::filesystem::path& train_path, const boost::filesystem::path& test_path, double percentage);

    void addLine(const GobanVector_t& current_state, const GobanVector_t& next_move);

private:
    std::ofstream m_train_file;
    std::ofstream m_test_file;
    const double m_percentage;
};

CntkWriter::GobanVector_t encode(const Goban& goban, QGo::Case color_to_play);

#endif // CNTKWRITER_H
