# include "Clauses.h"
# include "Cell.h"
# include "AuxFuncs.h"

void Clauses::UniqueConditions (std::vector<std::vector <int> >& _clauseNegArrUCList, 
                                int _rowNum, 
                                int _colNum, 
                                int _stateNum, 
                                int _bbb,  
                                int _varNum) 
{
    for (int row = 1; row <= _rowNum; ++row) {
        for (int col = 1; col <= _colNum; ++col) {
            std::vector<int> clauseNegArr1(_varNum, -1); // Big OR
            for (int state = 1; state <= _stateNum; ++state)
                clauseNegArr1[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] = 1;

            _clauseNegArrUCList.push_back(clauseNegArr1);
            
            for (int state1 = 1; state1 <= _stateNum; ++state1) {
                for (int state2 = state1 + 1; state2 <= _stateNum; ++state2) {
                    std::vector<int> clauseNegArr2(_varNum, -1); // Big OR
                    clauseNegArr2[Cell::getSerialNumber(row, col, state1, _colNum, _bbb, _stateNum) - 1] = 0;
                    clauseNegArr2[Cell::getSerialNumber(row, col, state2, _colNum, _bbb, _stateNum) - 1] = 0;
                    _clauseNegArrUCList.push_back(clauseNegArr2);
                }
            }
        }
    }
}

void Clauses::BoundaryConditions   (std::vector<std::vector <int> >& _clauseNegArrBCList, 
                                    int _rowNum, 
                                    int _colNum, 
                                    int _stateNum, 
                                    int _bbb, 
                                    int _varNum) 
{
    for (int row = -2; row <= 0; ++row) {
        for (int col = -2; col <= _colNum+3; ++col) {
            for (int state = 1; state <= _stateNum; ++state) {
                std::vector<int> clauseNegArr(_varNum, -1);
                clauseNegArr[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] = 0;
                _clauseNegArrBCList.push_back(clauseNegArr);
            }
        }
    }
    for (int row = _rowNum+1; row <= _rowNum+3; ++row) {
        for (int col = -2; col <= _colNum+3; ++col) {
            for (int state = 1; state <= _stateNum; ++state) {
                std::vector<int> clauseNegArr(_varNum, -1);
                clauseNegArr[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] = 0;
                _clauseNegArrBCList.push_back(clauseNegArr);
            }
        }
    }
    for (int row = 1; row <= _rowNum; ++row) {
        for (int col = -2; col <= 0; ++col) {
            for (int state = 1; state <= _stateNum; ++state) {
                std::vector<int> clauseNegArr(_varNum, -1);
                clauseNegArr[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] = 0;
                _clauseNegArrBCList.push_back(clauseNegArr);
            }
        }
    }
    for (int row = 1; row <= _rowNum; ++row) {
        for (int col = _colNum+1; col <= _colNum+3; ++col) {
            for (int state = 1; state <= _stateNum; ++state) {
                std::vector<int> clauseNegArr(_varNum, -1);
                clauseNegArr[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] = 0;
                _clauseNegArrBCList.push_back(clauseNegArr);
            }
        }
    }
}


void Clauses::PlacementConditions  (std::vector<std::vector <int> >& _clauseNegArrPCList, 
                                    int _rowNum, 
                                    int _colNum, 
                                    int _stateNum, 
                                    int _bbb, 
                                    int _varNum, 
                                    const std::unordered_map<char, std::pair<int, bool> >& _rotationStateNumIsUsed, 
                                    std::unordered_map<char, std::vector<std::vector<std::vector<int> > > >& _rotationBlockCoordinates) 
{
    for (int row = 1; row <= _rowNum; ++row) {
        for (int col = 1; col <= _colNum; ++col) {
            for (int state = 1; state <= _stateNum; ++state) {
                std::vector<std::pair<int, std::pair<int, int> > > shiftToOtherCellPairList;
                AuxFuncs::shiftToOtherCellPairListByStateIndex(shiftToOtherCellPairList, state, _rotationStateNumIsUsed, _rotationBlockCoordinates);
                for (int i = 0; i < shiftToOtherCellPairList.size(); ++i) { // size == 3
                    std::vector<int> clauseNegArr(_varNum, -1);
                    clauseNegArr[Cell::getSerialNumber(row, col, state, _colNum, _bbb, _stateNum) - 1] = 0;
                    clauseNegArr[Cell::getSerialNumber(row + shiftToOtherCellPairList[i].second.first, col + shiftToOtherCellPairList[i].second.second, shiftToOtherCellPairList[i].first, _colNum, _bbb, _stateNum) - 1] = 1;
                    _clauseNegArrPCList.push_back(clauseNegArr);
                }
            }
        }
    }
}


