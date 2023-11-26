# ifndef _TETRISSOLVER_H_
# define _TETRISSOLVER_H_

# include <minisat/core/Solver.h>
# include <iostream>
# include <vector>

namespace TetrisSolver {
    void declareVar    (std::vector<Minisat::Var>& _varList,
                        int _varNum, Minisat::Solver& _solver);
    void solverAddClause   (Minisat::Solver& _solver, 
                            const std::vector<Minisat::Var>& _varList, 
                            const std::vector<int>& _clauseNegArr);
    void SATSolver (bool& _isSAT,
                    Minisat::Solver& _solver,
                    std::vector<int>& _varValueIfSAT);
}
# endif