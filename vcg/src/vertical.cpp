#include <iostream>
#include <exception>

#include <vcg/complex/complex.h>
#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export.h>

namespace vcg {
namespace tri {
template <class MeshType>
class Vertical
{
public:
  typedef typename MeshType::FaceIterator   FaceIterator;

  static FaceIterator NearestFace( MeshType & m, const vcg::Point3f & p ) // assume |fn| == 1
  {
    FaceIterator nearest_fi = m.face.begin();
    float len;
    float len_min = (p - vcg::Barycenter(*(m.face.begin()))).Norm();
    for (FaceIterator fi=m.face.begin(); fi!=m.face.end(); fi++) {
      len = (p - vcg::Barycenter(*fi)).Norm();
      if (len < len_min) {
        len_min = len;
        nearest_fi = fi;
      }
    }
    return nearest_fi;
  }
  
  static bool IsInFacePillar( const FaceIterator & fi, const vcg::Point3f & p )
  {
    vcg::Point3f n01 = fi->N() ^ (fi->cP(1) - fi->cP(0));
    vcg::Point3f n12 = fi->N() ^ (fi->cP(2) - fi->cP(1));
    vcg::Point3f n20 = fi->N() ^ (fi->cP(0) - fi->cP(2));
    return ( n01.dot( p - fi->cP(0) ) >= 0 &&
             n12.dot( p - fi->cP(1) ) >= 0 &&
             n20.dot( p - fi->cP(2) ) >= 0    );
  }

  static vcg::Point3f VerticalWeightedVertexNormal( const FaceIterator & fi, const vcg::Point3f & p )
  {
    float S_p01 = ( (fi->cP(0) - p) ^ (fi->cP(1) - p) ).Norm();
    float S_p12 = ( (fi->cP(1) - p) ^ (fi->cP(2) - p) ).Norm();
    float S_p20 = ( (fi->cP(2) - p) ^ (fi->cP(0) - p) ).Norm();
    float S_sum = S_p01 + S_p12 + S_p20;
    vcg::Point3f weighted_vn = fi->V(0)->N() * (S_p12 / S_sum)
                             + fi->V(1)->N() * (S_p20 / S_sum)
                             + fi->V(2)->N() * (S_p01 / S_sum);
    return weighted_vn;
  }

  static vcg::Point3f VerticalNearPoint( MeshType & m, const vcg::Point3f & p )
  {
    FaceIterator face = NearestFace(m, p);
    if ( !IsInFacePillar(face, p) ) {
      throw std::runtime_error("Your specified point is not in the nearest face's pillar.");
    }
    if (false) {
      return face->N();
    }
    else {
      return VerticalWeightedVertexNormal(face, p);
    }
  }
  
};
} // end namespace vcg
} // end namespace tri

class MyVertex; class MyFace;
struct MyUsedTypes : public vcg::UsedTypes< vcg::Use<MyVertex>   ::AsVertexType,
                                            vcg::Use<MyFace>     ::AsFaceType >{};
class MyVertex : public vcg::Vertex< MyUsedTypes,
                                     vcg::vertex::Coord3f,
                                     vcg::vertex::Normal3f,
                                     vcg::vertex::BitFlags > {};
class MyFace : public vcg::Face< MyUsedTypes,
                                 vcg::face::VertexRef,
                                 vcg::face::Normal3f,
                                 vcg::face::BitFlags > {};
class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>,
                                         std::vector<MyFace> > {};

int main( int argc, char **argv ) {
  // Import STL file
  if(argc<2) {
    std::cout << "This program needs an STL file as input." << std::endl;
    return -1;
  }
  MyMesh m;
  int mask;
  if(vcg::tri::io::ImporterSTL<MyMesh>::Open(m, argv[1], mask)) {
    std::cout << "Error reading file " << argv[1] << std::endl;
    exit(0);
  }
  std::cout << "Input mesh has " << m.VN()
            << " vertices, " << m.FN() << " faces." << std::endl;

  // Remove duplicated vertices
  vcg::tri::Clean<MyMesh>::RemoveDuplicateVertex(m);
  vcg::tri::Allocator<MyMesh>::CompactEveryVector(m);
  std::cout << "Input mesh has " << m.VN()
            << " vertices, " << m.FN() << " faces." << std::endl;

  // Calc normal
  vcg::tri::UpdateNormal<MyMesh>::PerVertexNormalized(m);
  vcg::tri::UpdateNormal<MyMesh>::PerFaceNormalized(m);

  // define input point
  vcg::Point3f point(25.0, -10.0, 12.0);

  // search the nearest face
  MyMesh::FaceIterator ans = vcg::tri::Vertical<MyMesh>::NearestFace(m, point);
  std::cout << (int)vcg::tri::Index(m, ans->V(0)) << ", "
            << (int)vcg::tri::Index(m, ans->V(1)) << ", "
            << (int)vcg::tri::Index(m, ans->V(2)) << std::endl;

  // check the point is in the face pillar
  std::cout << vcg::tri::Vertical<MyMesh>::IsInFacePillar(ans, point) << std::endl;

  // calc norm from the input point
  try {
    vcg::Point3f ans = vcg::tri::Vertical<MyMesh>::VerticalNearPoint(m, point);
    std::cout << "ans: " << ans.X() << ", " << ans.Y() << ", " << ans.Z() << std::endl;
  } catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}
