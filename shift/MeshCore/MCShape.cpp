#include "MCShape.h"
#include "XRenderer.h"
#include "XLine.h"
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>

S_IMPLEMENT_PROPERTY(MCShape)

void MCShape::createTypeInformation(SPropertyInformation *info, const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&MCShape::geometry, "geometry");
    }
  }

MCShape::MCShape()
  {
  }

void MCShape::render(XRenderer *r) const
  {
  r->drawGeometry(geometry.runtimeGeometry());
  }

typedef CGAL::AABB_polyhedron_triangle_primitive<MCKernel, MCPolyhedron> Primitive;
typedef CGAL::AABB_traits<MCKernel, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;
typedef Tree::Object_and_primitive_id Object_and_primitive_id;
typedef Tree::Primitive_id Primitive_id;

void MCShape::intersect(const XLine& line, Selector *s) const
  {
  // need to be able to get a non const iterator for cgal.
  MCPolyhedron& polyhedron = const_cast<MCPolyhedron&>(geometry.polygons());

  // constructs AABB tree
  Tree tree(polyhedron.facets_begin(), polyhedron.facets_end());

  MCKernel::Point_3 start = line.position();
  MCKernel::Point_3 end = XVector3D(line.position() + line.direction());

  // constructs segment query
  MCKernel::Segment_3 segment(start, end);

  class Inserter
    {
  public:
    Inserter(Selector *s) : _s(s) { }
    Object_and_primitive_id &operator*()
      {
      static Object_and_primitive_id a;
      return a;
      }
    Inserter operator++()
      {
      return *this;
      }
    Inserter operator++(int)
      {
      return *this;
      }
  private:
    Selector *_s;
    };
  Inserter insertor(s);

  // computes all intersections with segment query (as pairs object - primitive_id)
  tree.all_intersections(segment, insertor);

  // computes all intersected primitives with segment query as primitive ids
  /*std::list<Primitive_id> primitives;
  tree.all_intersected_primitives(segment_query, std::back_inserter(primitives));

  // constructs plane query
  Vector vec(0.0,0.0,1.0);
  Plane plane_query(a,vec);

  // computes first encountered intersection with plane query
  // (generally a segment)
  intersection = tree.any_intersection(plane_query);
  if(intersection)
  {
      // gets intersection object
      Object_and_primitive_id op = *intersection;
      CGAL::Object object = op.first;
      Segment segment;
      if(CGAL::assign(segment,object))
          std::cout << "intersection object is a segment" << std::endl;
  }*/
  }

void MCShape::intersect(const XFrustum& frus, Selector *) const
  {
  }
