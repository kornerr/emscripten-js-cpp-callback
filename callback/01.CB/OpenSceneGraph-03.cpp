#include "src/osg/glu/libtess/mesh.cpp"
#include "src/osg/glu/libtess/priorityq.cpp"
#include "src/osg/Matrixd.cpp"
#include "src/osg/ShadowVolumeOccluder.cpp"
// NOTE This is a fake osg::Billboard implementation
// NOTE to be able to build OpenSceneGraph without additional patching.

#include <osg/Billboard>

namespace osg
{

Billboard::Billboard()
{
    OSG_WARN << "osg::Billboard is not implemented\n";
}
Billboard::Billboard(const Billboard &, const CopyOp &)
{
    OSG_WARN << "osg::Billboard is not implemented\n";
}
Billboard::~Billboard() { } 
void Billboard::setAxis(const Vec3 &) { }
void Billboard::setNormal(const Vec3 &) { }
void Billboard::setMode(Mode mode) {}
bool Billboard::addDrawable(Drawable *)
{
    return false;
}
bool Billboard::addDrawable(Drawable *, const Vec3 &)
{
    return false;
}
bool Billboard::removeDrawable(Drawable *)
{
    return false;
}
BoundingSphere Billboard::computeBound() const
{
    BoundingSphere bsphere;
    return bsphere;
}
bool Billboard::computeMatrix(Matrix &, const Vec3 &, const Vec3 &) const
{
    return false;
}

} // namespace osg
#include "src/osgDB/Archive.cpp"
#include "src/osgDB/ConvertBase64.cpp"
#include "src/osgDB/DatabasePager.cpp"
#include "src/osgDB/DatabaseRevisions.cpp"
#include "src/osgDB/DynamicLibrary.cpp"
#include "src/osgDB/FileCache.cpp"
#include "src/osgDB/FileNameUtils.cpp"
#include "src/osgDB/fstream.cpp"
#include "src/osgDB/ImagePager.cpp"
#include "src/osgDB/InputStream.cpp"
#include "src/osgDB/MimeTypes.cpp"
#include "src/osgDB/ObjectCache.cpp"
#include "src/osgDB/ObjectWrapper.cpp"
#include "src/osgDB/Options.cpp"
#include "src/osgDB/OutputStream.cpp"
#include "src/osgDB/Registry.cpp"
#include "src/osgDB/ReaderWriter.cpp"
#include "src/osgDB/ReadFile.cpp"
#include "src/osgDB/SharedStateManager.cpp"
#include "src/osgDB/StreamOperator.cpp"
#include "src/osgDB/XmlParser.cpp"
#include "src/osgDB/WriteFile.cpp"
// osgDB plugins.
#include "src/osgDB/DotOsgWrapper.cpp"
#include "src/osgDB/Input.cpp"
#include "src/osgDB/Output.cpp"
#include "src/osgDB/Field.cpp"
#include "src/osgDB/FieldReader.cpp"
#include "src/osgDB/FieldReaderIterator.cpp"
