#include <vcg/complex/complex.h>
#include <wrap/io_trimesh/import.h>

class MyVertex; class MyEdge; class MyFace;
struct MyUsedTypes : public vcg::UsedTypes< vcg::Use<MyVertex>   ::AsVertexType,
                                            vcg::Use<MyEdge>     ::AsEdgeType,
                                            vcg::Use<MyFace>     ::AsFaceType >{};
class MyVertex : public vcg::Vertex< MyUsedTypes,
                                     vcg::vertex::Coord3f,
                                     vcg::vertex::Normal3f,
                                     vcg::vertex::BitFlags > {};
class MyFace : public vcg::Face< MyUsedTypes,
                                 vcg::face::FFAdj,
                                 vcg::face::VertexRef,
                                 vcg::face::BitFlags > {};
class MyEdge : public vcg::Edge< MyUsedTypes > {};
class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>,
                                         std::vector<MyFace> ,
                                         std::vector<MyEdge> > {};

int main( int argc, char **argv ) {
  if(argc<2) {
    printf("This program needs an STL file as input.\n");
    return -1;
  }
  MyMesh m;
  int loadmask;
  if(vcg::tri::io::ImporterSTL<MyMesh>::Open(m, argv[1], loadmask)) {
    printf("Error reading file  %s\n",argv[1]);
    exit(0);
  }
  printf("Input mesh has %i vert, %i faces, and %i edges.\n", m.VN(), m.FN(), m.EN() );

  vcg::tri::UpdateNormal<MyMesh>::PerVertexNormalized(m);
  return 0;
}
