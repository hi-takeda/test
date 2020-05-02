#include <vcg/complex/complex.h>
#include <vcg/complex/allocate.h>

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
                                 vcg::face::BitFlags > {};
class MyEdge : public vcg::Edge< MyUsedTypes > {};
class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>,
                                         std::vector<MyFace> ,
                                         std::vector<MyEdge> > {};

int main( int argc, char **argv ) {
  MyMesh m;
  MyMesh::VertexIterator vi = vcg::tri::Allocator<MyMesh>::AddVertices(m, 3);
  MyMesh::FaceIterator fi = vcg::tri::Allocator<MyMesh>::AddFaces(m, 1);

  MyMesh::VertexPointer vp[3];
  vp[0] = &*vi; vi->P() = MyMesh::CoordType(0.0, 0.0, 0.0); vi++;
  vp[1] = &*vi; vi->P() = MyMesh::CoordType(1.0, 0.0, 0.0); vi++;
  vp[2] = &*vi; vi->P() = MyMesh::CoordType(0.0, 1.0, 0.0); vi++;

  fi->V(0) = vp[0];
  fi->V(1) = vp[1];
  fi->V(2) = vp[2];

  for (auto vi=m.vert.begin(); vi!=m.vert.end(); vi++) {
    std::cout << vi->P().X() << " "
              << vi->P().Y() << " "
              << vi->P().Z() << std::endl;
  }

  for (auto fi=m.face.begin(); fi!=m.face.end(); fi++) {
    std::cout << vcg::tri::Index(m, fi->V(0)) << " "
              << vcg::tri::Index(m, fi->V(1)) << " "
              << vcg::tri::Index(m, fi->V(2)) << std::endl;
  }

  vcg::tri::Allocator<MyMesh>::DeleteFace(m, m.face[0]);

  std::cout << m.face.size() << " "
            << m.FN() << std::endl;

  vcg::tri::Allocator<MyMesh>::CompactFaceVector(m);

  std::cout << m.face.size() << " "
            << m.FN() << std::endl;
  
 return 0;
}
