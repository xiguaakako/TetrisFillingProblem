# include "TetrisSolver.h"
# include <iostream>

int main() {
    Minisat::Solver solver;
    std::vector<Minisat::Var> varList;
    TetrisSolver::declareVar(varList, 2, solver);
    std::vector<int> isNegLit1 = {0, 0};
    std::vector<int> isNegLit2 = {0, 1};
    std::vector<int> isNegLit3 = {1, 0};
    std::vector<int> isNegLit4 = {1, 1};
    
    TetrisSolver::solverAddClause (solver, varList, isNegLit1);
    TetrisSolver::solverAddClause (solver, varList, isNegLit2);
    TetrisSolver::solverAddClause (solver, varList, isNegLit3);
    TetrisSolver::solverAddClause (solver, varList, isNegLit4);

    bool isSAT;
    std::vector<int> varValueIfSAT(2, -1);
    TetrisSolver::SATSolver (isSAT, solver, varValueIfSAT);
    std::cout << "isSAT: " << isSAT << std::endl;
    return 0;
}
