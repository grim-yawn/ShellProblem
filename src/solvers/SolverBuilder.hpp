#ifndef SHELLPROBLEM_SOLVERBUILDER_HPP
#define SHELLPROBLEM_SOLVERBUILDER_HPP

#include <memory>

#include "src/linear_solver/LinearSolverBase.hpp"
#include "src/boundaries/BoundariesMap.hpp"
#include "src/task/TaskUtil.hpp"
#include "SolverBase.hpp"

class SolverBuilder
{

public:
    static std::shared_ptr<SolverBase> create_solver(const json &solver_properties,
                                                     std::shared_ptr<MeshBase> mesh,
                                                     std::shared_ptr<LinearSolverBase> linear_solver,
                                                     BoundariesMap boundaries);
};


#endif //SHELLPROBLEM_SOLVERBUILDER_HPP
