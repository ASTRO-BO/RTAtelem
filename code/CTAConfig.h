/***************************************************************************
                          CTAConfig.h  -  description
                             -------------------
    copyright            : (C) 2014 Valentina Fioretti
    email                : fioretti@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef _CTACONFIG_H
#define _CTACONFIG_H

#include "InputFileFITS.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
namespace RTATelem {

/// Uploading the CTA configuration parameters and converting
/// them to metadata
/// \brief CTA Configuration data conversion into metadata
class CTAConfig {

private:
	qlbase::InputFileFITS conf_file;
	
	
public:
    /// It takes the CTA configuration file in FITS format
    /// \param confInputFileName The input file name of the CTA configuration
	CTAConfig(const string& confInputFileName);

    ~CTAConfig();
    
    /// FITS structure parameters definition
    int conf_Nheader;
    int conf_Nrows_L0;
    int conf_Nrows_L1;
    
    /// Column number
    int L0ID_colnum;
    int TelID_colnum;
    int TelType_colnum;
    int TelX_colnum;
    int TelY_colnum;
    int TelZ_colnum;
    int FL_colnum;
    int FOV_colnum;
    int CameraScaleFactor_colnum;
    int CameraCentreOffset_colnum;
    int CameraRotation_colnum;
    int NPixel_colnum;
    int NPixel_active_colnum;
    int NSamples_colnum;
    int Sample_time_slice_colnum;
    int NGains_colnum;
    int HiLoScale_colnum;
    int HiLoThreshold_colnum;
    int HiLoOffset_colnum;
    int NTubesOFF_colnum;
    int NMirrors_colnum;
    int MirrorArea_colnum;
    
    int L1ID_colnum;
    int L0ID_L1_colnum;
    int PixelID_colnum;
    int XTubeMM_colnum;
    int YTubeMM_colnum;
    int RTubeMM_colnum;
    int XTubeDeg_colnum;
    int YTubeDeg_colnum;
    int RTubeDeg_colnum;
    int TubeOFF_colnum;
    
    /// Vector declaration
    vector<int64_t> L0ID;
    vector<int16_t> TelID;
    vector<int64_t> TelType;
    vector<float> TelX;
    vector<float> TelY;   
    vector<float> TelZ;  
    vector<float> FL;  
    vector<float> FOV;  
    vector<float> CameraScaleFactor;  
    vector<float> CameraCentreOffset;  
    vector<float> CameraRotation;  
    vector<int16_t> NPixel;  
    vector<int16_t> NPixel_active;  
    vector<int16_t> NSamples;  
    vector<float> Sample_time_slice;  
    vector<int16_t> NGains;  
    vector<float> HiLoScale;  
    vector<int16_t> HiLoThreshold;  
    vector<float> HiLoOffset;  
    vector<int16_t> NTubesOFF;  
    vector<int16_t> NMirrors;  
    vector<float> MirrorArea;  

    vector<int64_t> L1ID;
    vector<int64_t> L0ID_L1;
    vector<int16_t> PixelID;
    vector<float> XTubeMM;
    vector<float> YTubeMM;   
    vector<float> RTubeMM;  
    vector<float> XTubeDeg;
    vector<float> YTubeDeg;   
    vector<float> RTubeDeg;  
    vector<int16_t> TubeOFF;  

};
}

#endif
