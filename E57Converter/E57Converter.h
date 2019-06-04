#pragma once

#include <boost/filesystem.hpp>

#include "PointType.h"

#include <pcl/point_cloud.h>
#include <pcl/outofcore/outofcore.h>

//
namespace e57
{
	class Converter
	{
	protected:
		using OCT = pcl::outofcore::OutofcoreOctreeBase<pcl::outofcore::OutofcoreOctreeDiskContainer<PointE57>, PointE57>;
		OCT::Ptr oct;
		boost::filesystem::path octPath;

	public:
		// This constructor will create a new OCT (need input a not exist folder)
		Converter(const boost::filesystem::path& octPath, const Eigen::Vector3d& min, const Eigen::Vector3d& max, const double resolution, const std::string& coordSys);

		// This constructor will load exist OCT
		Converter(const boost::filesystem::path& octPath);

		// minRGB: Mean a point will be kept only if one of R, G, B is larger than minRGB, This parameters is to filter out the black noise which is generated by some scanner (such as BLK360).
		void LoadE57(const boost::filesystem::path& e57Path, const double LODSamplePercent, const uint8_t minRGB);
		void SaveScanImages(const boost::filesystem::path& scanImagePath);
		void BuildLOD(const double sample_percent_arg);

		void ExportToPCD(const double voxelUnit, const unsigned int searchRadiusNumVoxels, pcl::PointCloud<PointPCD>& out);
	};
}