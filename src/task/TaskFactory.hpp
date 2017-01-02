#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include "Task.hpp"
#include "TaskUtil.hpp"
#include "src/mesh/MeshBase.hpp"

class TaskFactory
{
public:
    TaskFactory(const std::string &output_dir);

    std::shared_ptr<Task> create_task_from_json(json task) const;

private:

    const std::string output_dir;
    std::shared_ptr<SolverBase>
    create_solver(const json &solver_properties, std::shared_ptr<MeshBase> mesh) const;
    dealii::SolverGMRES<>::AdditionalData get_gmres_additional_data(const json &linear_solver_properties) const;
};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
