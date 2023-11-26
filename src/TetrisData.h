#ifndef _TETRISDATA_H_
#define _TETRISDATA_H_

# include <unordered_map>
# include <vector>
# include <utility>
# include <string>

class TetrisData {
public:
    static std::unordered_map<char, std::pair<int, bool>> getRotationStateNumIsUsed(const std::string& _blockUsed);
    static std::unordered_map<char, std::vector<std::vector<std::vector<int>>>> getRotationBlockCoordinates();
    static std::unordered_map<char, std::vector<int>> getBlockColor();
};

#endif
