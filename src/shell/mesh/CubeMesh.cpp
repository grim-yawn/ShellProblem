#include "CubeMesh.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

using namespace dealii;

CubeMesh::CubeMesh(const double size,
                   const Point<3> & center,
                   unsigned int n_refines,
                   const MeshMarkersGroup marker)
    :
    GeneratedMesh(n_refines, marker),
    size(size),
    center(center)
{
    create();
}

void CubeMesh::create_coarse_mesh()
{
    GridGenerator::hyper_cube(tria, -size / 2, size / 2);
    GridTools::shift(center, tria);
}

void CubeMesh::apply_manifold_ids()
{
    static const dealii::FlatManifold<3> flat_manifold(Point<3>(0, 0, 0));
    tria.set_manifold(0, flat_manifold);
    tria.set_all_manifold_ids(0);
}