#ifndef PCMS_COUPLING_POINT_SEARCH_H
#define PCMS_COUPLING_POINT_SEARCH_H
#include <unordered_map>
#include <Kokkos_Core.hpp>
#include <Omega_h_mesh.hpp>
#include "types.h"
#include <Omega_h_bbox.hpp>
#include <Omega_h_shape.hpp>
#include "pcms/uniform_grid.h"
#include "pcms/bounding_box.h"

namespace pcms
{
//
// TODO take a bounding box as we may want a bbox that's bigger than the mesh!
// this function is in the public header for testing, but should not be directly
// used
namespace detail {
Kokkos::Crs<LO, Kokkos::DefaultExecutionSpace, void, LO>
construct_intersection_map(Omega_h::Mesh& mesh, Kokkos::View<UniformGrid[1]> grid, int num_grid_cells);
}
KOKKOS_FUNCTION
Omega_h::Vector<3> barycentric_from_global(
  const Omega_h::Vector<2>& point, const Omega_h::Matrix<2, 3>& vertex_coords);

[[nodiscard]] KOKKOS_FUNCTION bool triangle_intersects_bbox(
  const Omega_h::Matrix<2, 3>& coords, const AABBox<2>& bbox);

class GridPointSearch
{
  using CandidateMapT = Kokkos::Crs<LO, Kokkos::DefaultExecutionSpace, void, LO>;

public:
  static constexpr auto dim = 2;
  struct Result {
    enum class Dimensionality
    {
      VERTEX = 0,
      EDGE = 1,
      FACE = 2
    };

    Dimensionality dimensionality;
    LO tri_id;
    Omega_h::Vector<dim + 1> parametric_coords;
  };

  GridPointSearch(Omega_h::Mesh& mesh, LO Nx, LO Ny);
  /**
   *  given a point in global coordinates give the id of the triangle that the
   * point lies within and the parametric coordinate of the point within the
   * triangle. If the point does not lie within any triangle element. Then the
   * id will be a negative number and (TODO) will return a negative id of the
   * closest element
   */
  Kokkos::View<Result*> operator()(Kokkos::View<Real*[dim] > point) const;

private:
  Omega_h::Mesh mesh_;
  Kokkos::View<UniformGrid[1]> grid_{"uniform grid"};
  CandidateMapT candidate_map_;
  Omega_h::LOs tris2verts_;
  Omega_h::Reals coords_;
};

} // namespace detail
#endif // PCMS_COUPLING_POINT_SEARCH_H
