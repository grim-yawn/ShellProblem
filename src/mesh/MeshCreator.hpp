#ifndef SHELL_PROBLEM_MESHCREATOR_HPP
#define SHELL_PROBLEM_MESHCREATOR_HPP

#include "deal.II/grid/tria.h"
#include "TaskReader.hpp"

namespace MeshCreators
{

class SimpleShellMesh
{
public:
    SimpleShellMesh(const TaskReader::GeometryProperties &geometry);

    void write_msh(const std::string &output_file);
    void write_vtu(const std::string &output_file);
protected:
    void create_coarse_mesh();
    void apply_manifold_ids();
    void apply_boundary_ids();
    void refine_mesh(size_t n_refines);
private:
    dealii::Triangulation<3> tria;

    const double inner_radius;
    const double outer_radius;
    const double thickness;
    const double cylinder_length;

    const size_t n_refinements;
};

}

#endif //SHELL_PROBLEM_MESHCREATOR_HPP
