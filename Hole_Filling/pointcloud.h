#include "MeshType.h"
typedef std::array<std::size_t, 3> Facet; // Triple of indices

class PointCloud:public MeshType {
public:
	PointCloud();
	void read_input(const char* filename);
	void removeOutliers();
	void simplifyPointset();
	void reconstructSurface();
	void convertToSoup();
	void write_output();
	Surface_mesh getMesh();
private:
	Point_set points;
	std::vector<Facet> facets;
	std::vector<Point> vertices;
};