#ifndef _MD2X_MESH_LOADER_H_
#define _MD2X_MESH_LOADER_H_

#include <irrlicht.h>
#include "IMeshLoader.h"

using irr::c8;
using irr::scene::IMeshLoader;
using irr::scene::IAnimatedMesh;
using irr::io::IReadFile;

class CPingPangMeshLoader
: public IMeshLoader
{
public:
	CPingPangMeshLoader(irr::video::IVideoDriver* driver
        )
		:m_driver(driver)
    {
    }

	virtual ~CPingPangMeshLoader()
    {
    }

	bool isALoadableFileExtension(
        const c8* f
        )
    {
        return !!strstr( f, ".md2" ) || !!strstr( f, ".sam" ) || !!strstr( f, ".ms3d" );
    }

	IAnimatedMesh* createMesh(
        IReadFile* file
        );

private:
	// Modified by Huang Liang
	irr::video::IVideoDriver* m_driver;
	// Modified end
};

#endif //_MD2X_MESH_LOADER_H_

