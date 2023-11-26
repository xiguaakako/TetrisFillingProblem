#include "TetrisData.h"

std::unordered_map<char, std::pair<int, bool>> TetrisData::getRotationStateNumIsUsed(const std::string& _blockUsed) {
    std::unordered_map<char, std::pair<int, bool>> rotationStateNumIsUsed = {
        {'S', std::make_pair(2, (_blockUsed.find('S') != std::string::npos))},
        {'I', std::make_pair(2, (_blockUsed.find('I') != std::string::npos))},
        {'O', std::make_pair(1, (_blockUsed.find('O') != std::string::npos))},
        {'J', std::make_pair(4, (_blockUsed.find('J') != std::string::npos))},
        {'Z', std::make_pair(2, (_blockUsed.find('Z') != std::string::npos))},
        {'T', std::make_pair(4, (_blockUsed.find('T') != std::string::npos))},
        {'L', std::make_pair(4, (_blockUsed.find('L') != std::string::npos))}
    };

    return rotationStateNumIsUsed;
}

std::unordered_map<char, std::vector<std::vector<std::vector<int>>>> TetrisData::getRotationBlockCoordinates() {
    std::unordered_map<char, std::vector<std::vector<std::vector<int>>>> rotationBlockCoordinates = {
        // (row shift, col shift)
        {'S', {
            {{0, 0}, {0, 1}, {1, -1}, {1, 0}}, 
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}}
        }},
        {'I', {
            {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}}
        }},
        {'O', {
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}}
        }},
        {'J', {
            {{0, 0}, {1, 0}, {2, -1}, {2, 0}},
            {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
            {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
            {{0, 0}, {1, 0}, {1, 1}, {1, 2}}
        }},
        {'Z', {
            {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
            {{0, 0}, {1, -1}, {1, 0}, {2, -1}}
        }},
        {'T', {
            {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
            {{0, 0}, {1, -1}, {1, 0}, {1, 1}},
            {{0, 0}, {1, -1}, {1, 0}, {2, 0}}
        }},
        {'L', {
            {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
            {{0, 0}, {1, -2}, {1, -1}, {1, 0}},
            {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
            {{0, 0}, {0, 1}, {0, 2}, {1, 0}}
        }}
    };

    return rotationBlockCoordinates;
}

std::unordered_map<char, std::vector<int>> TetrisData::getBlockColor() {
    std::unordered_map<char, std::vector<int>> blockColor = {
        {'S', {83, 218, 63}},
        {'I', {1, 237, 250}},
        {'O', {254, 251, 52}},
        {'J', {0, 119, 211}},
        {'Z', {234, 20, 28}},
        {'T', {120, 37, 111}},
        {'L', {255, 145, 12}}
    };

    return blockColor;
}
