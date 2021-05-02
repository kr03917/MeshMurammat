#include <iostream>
#include <fstream>
#include <CGAL/boost/graph/IO/PLY.h>
#include "mesh_type.h"
#include "nonmanifold_mesh.h"
#include <iterator>

typedef boost::graph_traits<Mesh>::vertex_descriptor vertexDescriptor;
typedef boost::graph_traits<Mesh>::halfedge_descriptor halfedgeDescriptor;


int main()
{
	//Loading input mesh in off file
	/*const char* filename = "blobby.off";
	std::ifstream input(filename);
	Mesh mesh;
	if (!input || !(input >> mesh) || num_vertices(mesh) == 0)
	{
		std::cerr << filename << " is not a valid off file." << std::endl;
		return EXIT_FAILURE;
	}
	*/

	//Get input mesh and load it
	/*std::ifstream ply_input("nonmanifold_bun_zipper.ply");
	if (!ply_input)
	{
		std::cerr << "Cannot open file " << std::endl;
		return EXIT_FAILURE;
	}
	Mesh mesh;
	std::vector<Point_3> points;
	std::vector<std::vector<std::size_t> > polygons;
	read_PLY(ply_input, points, polygons);
	ply_input.close();

	CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(points, polygons, mesh);*/

	Nonmanifold_Mesh m;
	if (!m.read_input("nonmanifold_bunny.ply")) {
		return EXIT_FAILURE;
	}
	m.check_nonmanifold();

	Mesh mesh = m.get_mesh();
	Mesh_holes a;
	a.set_mesh(mesh);

	a.holefill_benchmark();
	//Mesh output_mesh = a.generate_hole_highlight();
	//std::vector<Hole> hole_list = a.get_hole_list();
	//a.hole_fill(hole_list[1]);
	Mesh output_mesh = a.get_mesh();
	//faces not getting merged with mesh...
	//std::cout << output_mesh.number_of_faces() << std::endl;
	//std::cout << output_mesh.number_of_vertices() << std::endl;
	a.~Mesh_holes();

	//Open output stream and write the output file
	std::filebuf fb;
	fb.open("holefill.ply", std::ios::out);
	std::ostream os(&fb);
	write_PLY(os, output_mesh);
	fb.close();

    return 0;
}