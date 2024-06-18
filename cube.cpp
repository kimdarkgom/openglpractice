#include "DrawComponent.h"
#include "gl/freeglut.h"

#include "pmp/io/io.h"
#include "pmp/algorithms/normals.h"

void DrawComponent::Init()
{
	//pmp::read(mesh, "obj\\bear_bis.obj");
	
	const auto v0 = mesh.add_vertex(pmp::Point(0, 0, 0));
	const auto v1 = mesh.add_vertex(pmp::Point(2, 0, 0));
	const auto v2 = mesh.add_vertex(pmp::Point(0, 2, 0));
	const auto v3 = mesh.add_vertex(pmp::Point(0, 0, 2));
	const auto v4 = mesh.add_vertex(pmp::Point(2, 2, 0));
	const auto v5 = mesh.add_vertex(pmp::Point(2, 2, 2));
	const auto v6 = mesh.add_vertex(pmp::Point(2, 0, 2));
	const auto v7 = mesh.add_vertex(pmp::Point(0, 2, 2));
	

	mesh.add_quad(v7, v3, v6, v5);
	mesh.add_quad(v3, v0, v1, v6);
	mesh.add_quad(v6, v1, v4, v5);
	mesh.add_quad(v7, v2, v0, v3);
	mesh.add_quad(v0, v2, v4, v1);
	mesh.add_quad(v2, v7, v5, v4);
	

	
	

	std::cout << "vertices:" << mesh.n_vertices() << std::endl;
	std::cout << "edges:" << mesh.n_edges() << std::endl;
	std::cout << "faces:" << mesh.n_faces() << std::endl;

	pmp::vertex_normals(mesh);
	pmp::write(mesh, "obj\\output.obj");
}

void DrawComponent::Draw()
{

	auto n = mesh.get_vertex_property<pmp::Normal>("v:normal");
	
	for (auto f : mesh.faces()) {
		glBegin(GL_POLYGON);
		for (auto v : mesh.vertices(f))
		{
			auto p = mesh.position(v);
			glNormal3dv(n[v].data());
			glVertex3dv(p.data());
		}
		glEnd();
		
	}
}