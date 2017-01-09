#ifndef SHELL_PROBLEM_CIRCLE_MARKER_HPP
#define SHELL_PROBLEM_CIRCLE_MARKER_HPP

#include "BoundaryMarker.hpp"

class CircleMarker: public BoundaryMarker
{
public:
    CircleMarker(const dealii::types::boundary_id boundary_id,
                 const dealii::Point<3> &center,
                 const double radius,
                 const unsigned int axis);
protected:
    void apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const override;
private:
    const dealii::types::boundary_id boundary_id;
    const dealii::Point<3> center;
    const double radius;
    const unsigned int axis;
};


#endif //SHELL_PROBLEM_CIRCLE_MARKER_HPP
