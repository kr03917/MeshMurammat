#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Kernel/global_functions.h>
#include <CGAL/Surface_mesh.h>
//#include <CGAL/IO/OFF_reader.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/repair.h>


namespace NP = CGAL::parameters;
namespace PMP = CGAL::Polygon_mesh_processing;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;
typedef Mesh::Vertex_index vertex_descriptor;
typedef Mesh::Halfedge_index halfedge_descriptor;
typedef Mesh::Face_index face_descriptor;

class Nonmanifold_Mesh{
public:
	void set_mesh(Mesh, std::vector<Point_3>, std::vector<std::vector<std::size_t>>);
	bool read_input(const char* filename);
	void merge_vertices(vertex_descriptor, vertex_descriptor, Mesh&);
	void create_nonmanifold();
	void check_nonmanifold();
	void fix_nonmanifold1();
	void fix_nonmanifold2();
	Mesh get_mesh();

private:
	Mesh mesh;
	std::vector<Point_3> points;
	std::vector<std::vector<std::size_t>> polygons;
};