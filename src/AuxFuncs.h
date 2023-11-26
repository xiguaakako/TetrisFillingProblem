# ifndef _AUXFUNCS_H_
# define _AUXFUNCS_H_
# include <utility>
# include <unordered_map>
# include <vector>
# include <cmath>

class AuxFuncs {
public:
    static void shiftToOtherCellPairListByStateIndex   (std::vector<std::pair<int, std::pair<int, int> > >& _shiftToOtherCellPairList, 
                                                        int _stateIndex, 
                                                        const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed, 
                                                        std::unordered_map<char, std::vector<std::vector<std::vector<int> > > >&_rotationBlockCoordinates);
    static std::pair<char, int> getBlockAndRelativeIndexByStateIndex   (int _stateIndex, 
                                                                        const std::unordered_map<char, 
                                                                        std::pair<int, bool> >& _rotationStateNumIsUsed);
};

# endif