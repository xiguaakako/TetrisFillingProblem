# include <chrono>
# include "TetrisSolver.h"
# include "TetrisData.h"
# include "Cell.h"
# include "Clauses.h"
# include "AuxFuncs.h"
# include "IO.h"

int main() {
    int rowNum, colNum;
    std::string blockUsed;
    IO::handleInput(rowNum, colNum, blockUsed);

    (blockUsed == "All")? blockUsed = "SIOJZTL":blockUsed;
    std::unordered_map<char, std::pair<int, bool>> rotationStateNumIsUsed = TetrisData::getRotationStateNumIsUsed(blockUsed);
    std::unordered_map<char, std::vector<std::vector<std::vector<int>>>> rotationBlockCoordinates = TetrisData::getRotationBlockCoordinates();

    auto start = std::chrono::high_resolution_clock::now();

    int bbb = 3; // boardBoundaryBias
    int stateNum = 0;
    for (const auto& pair : rotationStateNumIsUsed)
        stateNum += pair.second.first * pair.second.second * 4;
    //std::cout << "stateNum: " << stateNum << std::endl;
    int varNum = (rowNum + 2 * bbb) * (colNum + 2 * bbb) * stateNum;
    
    
    Minisat::Solver solver;
    std::vector<Minisat::Var> varList;
    TetrisSolver::declareVar(varList, varNum, solver);
    
    std::vector<std::vector <int> > clauseNegArrUCList;
    Clauses::UniqueConditions(clauseNegArrUCList, rowNum, colNum, stateNum, bbb, varNum);

    std::vector<std::vector <int> > clauseNegArrPCList;
    Clauses::PlacementConditions(clauseNegArrPCList, rowNum, colNum, stateNum, bbb, varNum, rotationStateNumIsUsed, rotationBlockCoordinates);

    std::vector<std::vector <int> > clauseNegArrBCList;
    Clauses::BoundaryConditions(clauseNegArrBCList, rowNum, colNum, stateNum, bbb, varNum);

    int clauseNum = clauseNegArrUCList.size() + clauseNegArrPCList.size() + clauseNegArrBCList.size();

    for (int i = 0; i < clauseNegArrUCList.size(); ++i) {
        // std::cout << "UC: ";
        // printClause(clauseNegArrUCList[i], colNum, bbb, stateNum, rotationStateNum_isUsed);
        TetrisSolver::solverAddClause (solver, varList, clauseNegArrUCList[i]);
    }
    for (int i = 0; i < clauseNegArrPCList.size(); ++i) {
        // std::cout << "PC: ";
        // printClause(clauseNegArrPCList[i], colNum, bbb, stateNum, rotationStateNum_isUsed);
        TetrisSolver::solverAddClause (solver, varList, clauseNegArrPCList[i]);
    }
    for (int i = 0; i < clauseNegArrBCList.size(); ++i) {
        // std::cout << "BC: ";
        // printClause(clauseNegArrBCList[i], colNum, bbb, stateNum, rotationStateNum_isUsed);
        TetrisSolver::solverAddClause (solver, varList, clauseNegArrBCList[i]);
    }


    bool isSAT;
    std::vector<int> varValueIfSAT(varNum, -1);
    TetrisSolver::SATSolver (isSAT, solver, varValueIfSAT);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    IO::handleOutput(isSAT, varValueIfSAT, rowNum, colNum, bbb, stateNum, rotationStateNumIsUsed, varNum, clauseNum, duration);

    return 0;
}