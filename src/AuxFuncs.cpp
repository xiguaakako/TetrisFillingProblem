# include "AuxFuncs.h"

void AuxFuncs::shiftToOtherCellPairListByStateIndex    (std::vector<std::pair<int, std::pair<int, int> > >& _shiftToOtherCellPairList, 
                                                        int _stateIndex, 
                                                        const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed, 
                                                        std::unordered_map<char, std::vector<std::vector<std::vector<int> > > >&_rotationBlockCoordinates)
{
    std::pair<char, int> blockAndRelativeIndex = getBlockAndRelativeIndexByStateIndex(_stateIndex, _rotationStateNumIsUsed);
    char block = blockAndRelativeIndex.first;
    int relativeIndex = blockAndRelativeIndex.second;
    int blockIndex = (relativeIndex % 4)? (relativeIndex % 4):4;
    int rotationState = std::ceil(double(relativeIndex) / 4.0);
    std::vector<int> tempSet;
    for (int i = 1; i <= 4; ++i) {
        if (i != blockIndex) tempSet.push_back(i);
    }
    //1 -> {2, 3, 4}, 2 -> {1, 3, 4}...
    for (int i = 0; i < 3; ++i) {
        _shiftToOtherCellPairList.push_back(std::make_pair(_stateIndex + tempSet[i] - blockIndex, std::make_pair(_rotationBlockCoordinates[block][rotationState-1][tempSet[i]-1][0]-_rotationBlockCoordinates[block][rotationState-1][blockIndex-1][0], _rotationBlockCoordinates[block][rotationState-1][tempSet[i]-1][1]-_rotationBlockCoordinates[block][rotationState-1][blockIndex-1][1])));
    }
}

std::pair<char, int> AuxFuncs::getBlockAndRelativeIndexByStateIndex(int _stateIndex, 
                                                                    const std::unordered_map<char, 
                                                                    std::pair<int, bool> >& _rotationStateNumIsUsed)
{
    int stateIndexCounter = 0;
    for (const auto& pair : _rotationStateNumIsUsed) {
        if (stateIndexCounter + pair.second.first * pair.second.second * 4 >= _stateIndex) {
            return std::make_pair(pair.first, _stateIndex - stateIndexCounter);
        }
       stateIndexCounter += pair.second.first * pair.second.second * 4;
    }
    return std::make_pair(' ', -1);
}