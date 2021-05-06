#include "MeshType.h"
class PolygonMesh:public MeshType {
public:
	PolygonMesh();
	void read_input(const char* filename);
	void triangulateSurface();
	void addingFacesVertices();
	void write_output_triangle();
	void write_output_poly();
private:
	std::vector<face_descriptor> newFaces;
	std::vector<vertex_descriptor> newVertices;
	Surface_mesh copiedMesh;
};