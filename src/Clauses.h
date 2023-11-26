# ifndef _CLAUSES_H_
# define _CLAUSES_H_

# include <utility>
# include <unordered_map>
# include <vector>
# include <cmath>

class Clauses {
public:
    static void UniqueConditions   (std::vector<std::vector <int> >& _clauseNegArrUCList, 
                                    int _rowNum, 
                                    int _colNum, 
                                    int _stateNum, 
                                    int _bbb,  
                                    int _varNum);
    static void BoundaryConditions (std::vector<std::vector <int> >& _clauseNegArrBCList, 
                                    int _rowNum, 
                                    int _colNum, 
                                    int _stateNum,
                                    int _bbb,  
                                    int _varNum);
    static void PlacementConditions(std::vector<std::vector <int> >& _clauseNegArrPCList, 
                                    int _rowNum, 
                                    int _colNum, 
                                    int _stateNum, 
                                    int _bbb,  
                                    int _varNum, 
                                    const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed, 
                                    std::unordered_map<char, std::vector<std::vector<std::vector<int> > > >& _rotationBlockCoordinates);
};

# endif