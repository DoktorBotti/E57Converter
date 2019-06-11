#pragma once

#include <vector>

#include "Common.h"

#include "PointType.h"

#include <pcl/point_cloud.h>
#include <pcl/outofcore/outofcore.h>

#include "nlohmann/json.hpp"

//
namespace e57
{
	class Converter
	{
	protected:
		using OCT = pcl::outofcore::OutofcoreOctreeBase<pcl::outofcore::OutofcoreOctreeDiskContainer<PointE57>, PointE57>;
		OCT::Ptr oct;
		boost::filesystem::path octPath;
		std::vector<ScanInfo> scanInfo;

		void LoadScanInfo(const boost::filesystem::path& octPath);
		void DumpScanInfo(const boost::filesystem::path& octPath);

	public:
		// This constructor will create a new OCT (need input a not exist folder)
		Converter(const boost::filesystem::path& octPath, const Eigen::Vector3d& min, const Eigen::Vector3d& max, const double resolution, const std::string& coordSys);

		// This constructor will load exist OCT
		Converter(const boost::filesystem::path& octPath);

		// minRGB: Mean a point will be kept only if one of R, G, B is larger than minRGB, This parameters is to filter out the black noise which is generated by some scanner (such as BLK360).
		void LoadE57(const boost::filesystem::path& e57Path, const double LODSamplePercent, const uint8_t minRGB, const Scanner& scanner);

		//raeMode only for CoodSys::RAE, fovy only for CoodSys::XYZ
		void ReconstructScanImages(pcl::PointCloud<PointPCD>& cloud, const boost::filesystem::path& scanImagePath, const CoodSys coodSys, const RAEMode raeMode, const float fovy, const unsigned int width, const unsigned int height);

		// 
		void LoadScanHDRI(const boost::filesystem::path& filePath);

		//
		void BuildLOD(const double sample_percent_arg);
		void ExportToPCD(const double voxelUnit, const unsigned int searchRadiusNumVoxels, const int meanK, const int polynomialOrder, bool reconstructAlbedo, pcl::PointCloud<PointPCD>& out);
	};
}