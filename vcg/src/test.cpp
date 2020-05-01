#include <vcg/complex/complex.h>
#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export.h>

class MyVertex; class MyEdge; class MyFace;
struct MyUsedTypes : public vcg::UsedTypes< vcg::Use<MyVertex>   ::AsVertexType,
                                            vcg::Use<MyEdge>     ::AsEdgeType,
                                            vcg::Use<MyFace>     ::AsFaceType >{};
class MyVertex : public vcg::Vertex< MyUsedTypes,
                                     vcg::vertex::Coord3f,
                                     vcg::vertex::Normal3f,
                                     vcg::vertex::BitFlags > {};
class MyFace : public vcg::Face< MyUsedTypes,
                                 vcg::face::VertexRef,
                                 vcg::face::Normal3f,
                                 vcg::face::FFAdj,
                                 vcg::face::BitFlags > {};
class MyEdge : public vcg::Edge< MyUsedTypes > {};
class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>,
                                         std::vector<MyFace> ,
                                         std::vector<MyEdge> > {};

int main( int argc, char **argv ) {
  // Import STL file
  if(argc<2) {
    printf("This program needs an STL file as input.\n");
    return -1;
  }
  MyMesh m;
  int mask;
  if(vcg::tri::io::ImporterSTL<MyMesh>::Open(m, argv[1], mask)) {
    printf("Error reading file  %s\n",argv[1]);
    exit(0);
  }
  printf("Input mesh has %i vertices, %i faces\n", m.VN(), m.FN() );

  // Remove duplicated vertices
  vcg::tri::Clean<MyMesh>::RemoveDuplicateVertex(m);

  // Should garbage-collect after allocating or deleting mesh elements
  vcg::tri::Allocator<MyMesh>::CompactEveryVector(m);
  printf("Output mesh has %i vertices, %i faces\n", m.VN(), m.FN() );

  // Vertex
  for (MyMesh::VertexIterator vi=m.vert.begin(); vi!=m.vert.end(); vi++) {
    printf("v: %f, %f, %f\n", vi->P().X(), vi->P().Y(), vi->P().Z());
  }
  // printf("%f\n", m.vert[3].P()[0] );
  // printf("%f\n", m.vert[3].P().X() );

  // Face
  for (MyMesh::FaceIterator fi=m.face.begin(); fi!=m.face.end(); fi++) {
    printf("f: %d, %d, %d\n", (int)vcg::tri::Index(m, fi->V(0))
           , (int)vcg::tri::Index(m, fi->V(1)), (int)vcg::tri::Index(m, fi->V(2)));
  }
  // printf("%d\n", vcg::tri::Index(m, m.face[3].V(1)) );
  
  // Normal
  vcg::tri::UpdateNormal<MyMesh>::PerVertexNormalized(m);
  for (MyMesh::VertexIterator vi=m.vert.begin(); vi!=m.vert.end(); vi++) {
    printf("vn: %f, %f, %f\n", vi->N().X(), vi->N().Y(), vi->N().Z());
  }
  vcg::tri::UpdateNormal<MyMesh>::PerFaceNormalized(m);
  for (MyMesh::FaceIterator fi=m.face.begin(); fi!=m.face.end(); fi++) {
    printf("fn: %f, %f, %f\n", fi->N().X(), fi->N().Y(), fi->N().Z());
  }

  // Export OBJ file
  char* filename = argv[1];
  vcg::tri::io::ExporterOBJ<MyMesh>::Save(m, strcat(filename, ".obj"), mask);

  return 0;
}
