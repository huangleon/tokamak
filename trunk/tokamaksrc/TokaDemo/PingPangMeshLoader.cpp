#include "PingPangMeshLoader.h"
#include "PingPangMD2XMesh.h"
#include "PingPangSAMMesh.h"
#include "CMilkShape3DMesh.h"

IAnimatedMesh* CPingPangMeshLoader::createMesh(
    IReadFile* file
    )
{
	IAnimatedMesh* msh = 0;

	if( strstr( file->getFileName(), ".md2" ) )
	{
		msh = new CPingPangMD2XMesh();
		if( ((CPingPangMD2XMesh*)msh)->loadFile( file ) )
			return msh;

		msh->drop();
	}
	else if( strstr( file->getFileName(), ".sam" ) )
	{
		msh = new CPingPangSAMMesh();
		if( ((CPingPangSAMMesh*)msh)->loadFile( file ) )
			return msh;

		msh->drop();
	}
	// Modified by Huang Liang
	else if ( strstr( file->getFileName(), ".ms3d" ) )
	{
		msh = new irr::scene::sklani::CSkeletonAni(m_driver);
//		if ( ((irr::scene::sklani::CSkeletonAni*)msh)->LoadOldMs3Mesh(file) )
		if ( ((irr::scene::sklani::CSkeletonAni*)msh)->Import(file) )
			return msh;
	}
	// Modified end

	return 0;
}
