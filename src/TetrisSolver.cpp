# include "TetrisSolver.h"

namespace TetrisSolver {
    void declareVar    (std::vector<Minisat::Var>& _varList,
                        int _varNum, Minisat::Solver& _solver)
    {  
        for (int i = 0; i < _varNum; ++i) _varList.push_back(_solver.newVar());
    }
    
    void solverAddClause   (Minisat::Solver& _solver,
                            const std::vector<Minisat::Var>& _varList,
                            const std::vector<int>& _clauseNegArr)
    {
        Minisat::vec<Minisat::Lit> newClause;
        for (int i = 0; i < _clauseNegArr.size(); ++i)
            if (_clauseNegArr[i] != -1)
                newClause.push(Minisat::mkLit(_varList[i], bool(_clauseNegArr[i])));
        _solver.addClause(newClause);
    }

    void SATSolver (bool& _isSAT,
                    Minisat::Solver& _solver,
                    std::vector<int>& _varValueIfSAT)
    {
        _isSAT = bool(_solver.solve());
        int varNum = _solver.model.size();
        if (_isSAT)
            for (int i = 0; i < varNum; ++i)
                if (_solver.model[i] != Minisat::l_Undef)
                    _varValueIfSAT[i] = (_solver.model[i] == Minisat::l_True)? 0 : 1;
    }
}
