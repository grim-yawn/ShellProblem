#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_reordering.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/grid_generator.h>

#include "MeshCreator.hpp"
#include "Utilities.hpp"

using namespace Utilities;

bool Utilities::is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                                  const dealii::Point<3> &center,
                                  const double radius,
                                  const double tolerance)
{
    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v)
    {
        const dealii::Point<3> current_vertex = face->vertex(v);
        const double distance_to_center = (current_vertex - center).norm();
        if (!fuzzy_equal(distance_to_center, radius, tolerance))
        {
            return false;
        }
    }

    return true;
}

bool Utilities::is_face_on_cylinder(const dealii::Triangulation<3>::active_face_iterator &face,
                         const dealii::Point<3> &center,
                         const size_t axis,
                         const double radius,
                         const double length,
                         const double tolerance)
{
    dealii::Point<3> axis_vector = get_axis_from_number(axis);

    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v)
    {
        const dealii::Point<3> shifted_vertex = face->vertex(v) + (-center);
        const double distance_to_axis = (shifted_vertex - (axis_vector * shifted_vertex) * axis_vector).norm();

        if (!fuzzy_equal(distance_to_axis, radius, tolerance))
        {
            return false;
        }
        else if (shifted_vertex(axis) > length / 2 || shifted_vertex(axis) < -length / 2)
        {
            return false;
        }
    }
    return true;
}

bool Utilities::is_face_inscribed_in_circle(const dealii::Triangulation<3>::active_face_iterator &face,
                                 const dealii::Point<3> &center,
                                 const double radius,
                                 const size_t axis,
                                 const double tolerance)
{
    if (!is_face_on_plane(face, center, axis))
    {
        return false;
    }

    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v)
    {
        const dealii::Point<3> current_point = face->vertex(v);
        const double distance_from_center = (current_point - center).norm();
        if (!fuzzy_equal(distance_from_center, radius, tolerance))
        {
            return false;
        }
    }
    return true;
}

bool Utilities::is_face_inside_circle(const dealii::Triangulation<3>::active_face_iterator &face,
                           const dealii::Point<3> &center,
                           const double radius,
                           const size_t axis,
                           const double tolerance)
{
    if (!is_face_on_plane(face, center, axis))
    {
        return false;
    }

    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v)
    {
        const dealii::Point<3> current_point = face->vertex(v);
        const double distance_from_center = (current_point - center).norm();
        if (distance_from_center > radius + tolerance)
        {
            return false;
        }
    }

    return true;
}

bool Utilities::is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                      const dealii::Point<3> &point_on_plane,
                      const size_t axis,
                      const double tolerance)
{
    //Plane: (n, r) = d, d = (n, r_0)
    const dealii::Point<3> axis_vector = get_axis_from_number(axis);
    const double d = point_on_plane * axis_vector;
    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v)
    {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!fuzzy_equal(current_point * axis_vector, d, tolerance))
        {
            return false;
        }
    }
    return true;
}

bool Utilities::fuzzy_equal(const double x, const double y, const double tolerance)
{
    return std::fabs(x - y) < tolerance;
}

dealii::Point<3> Utilities::get_axis_from_number(size_t axis_no)
{
    switch (axis_no)
    {
        case 0:
            return dealii::Point<3>(1, 0, 0);
        case 1:
            return dealii::Point<3>(0, 1, 0);
        case 2:
            return dealii::Point<3>(0, 0, 1);
        default:
            AssertThrow(false, dealii::StandardExceptions::ExcIndexRange(axis_no, 0, 3));
    }
    return dealii::Point<3>();
}