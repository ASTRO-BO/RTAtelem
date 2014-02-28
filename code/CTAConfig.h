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

#include <qlbase/InputFileFITS.h>
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
    //int conf_Nheader;
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
    vector<int64_t> vecL0ID;
    vector<int16_t> vecTelID;
    vector<int64_t> vecTelType;
    vector<float> vecTelX;
    vector<float> vecTelY;   
    vector<float> vecTelZ;  
    vector<float> vecFL;  
    vector<float> vecFOV;  
    vector<float> vecCameraScaleFactor;  
    vector<float> vecCameraCentreOffset;  
    vector<float> vecCameraRotation;  
    vector<int16_t> vecNPixel;  
    vector<int16_t> vecNPixel_active;  
    vector<int16_t> vecNSamples;  
    vector<float> vecSample_time_slice;  
    vector<int16_t> vecNGains;  
    vector<float> vecHiLoScale;  
    vector<int16_t> vecHiLoThreshold;  
    vector<float> vecHiLoOffset;  
    vector<int16_t> vecNTubesOFF;  
    vector<int16_t> vecNMirrors;  
    vector<float> vecMirrorArea;  

    vector<int64_t> vecL1ID;
    vector<int64_t> vecL0ID_L1;
    vector<int16_t> vecPixelID;
    vector<float> vecXTubeMM;
    vector<float> vecYTubeMM;   
    vector<float> vecRTubeMM;  
    vector<float> vecXTubeDeg;
    vector<float> vecYTubeDeg;   
    vector<float> vecRTubeDeg;  
    vector<int16_t> vecTubeOFF;  
    
    /// Vectors for the identification of the telescope type metadata
    vector<int64_t> vecUniqueTelType;
    vector<float> vecUniqueMirrorArea;
    vector<float> vecUniqueFL;  
    vector<float> vecUniqueFOV;  
    vector<float> vecUniqueCameraScaleFactor;  
    vector<float> vecUniqueCameraCentreOffset;  
    vector<float> vecUniqueCameraRotation;  
    vector<int16_t> vecUniqueNTubesOFF;  
    vector<int16_t> vecUniqueNMirrors;   
    vector<int16_t> vecUniqueNPixel;  
    vector<int16_t> vecUniqueNPixel_active; 
    vector<int16_t> vecUniqueNSamples;  
    vector<float> vecUniqueSample_time_slice;  
    vector<int16_t> vecUniqueNGains;  
    vector<float> vecUniqueHiLoScale;  
    vector<int16_t> vecUniqueHiLoThreshold;  
    vector<float> vecUniqueHiLoOffset;  
    vector<int16_t> vecUniquePixelID;
    vector<float> vecUniqueXTubeMM;
    vector<float> vecUniqueYTubeMM;   
    vector<float> vecUniqueRTubeMM;  
    vector<float> vecUniqueXTubeDeg;
    vector<float> vecUniqueYTubeDeg;   
    vector<float> vecUniqueRTubeDeg;  
    vector<int16_t> vecUniqueTubeOFF; 
    
    /// Number of telescope types
    int NTelType;

    /// Struct declaration

    struct PixelType {
    	int pixType;
    	int16_t NSamples;  
    	float Sample_time_slice;  
    	int16_t NGains;  
    	float HiLoScale;  
    	int16_t HiLoThreshold;  
    	float HiLoOffset;     	
    };

    struct Pixel {
    	int16_t PixelID;
    	float XTubeMM;
    	float YTubeMM;   
    	float RTubeMM;  
    	float XTubeDeg;
    	float YTubeDeg;   
    	float RTubeDeg;  
    	int16_t TubeOFF;  	
    };


    struct CameraType {
    	int camType;
    	float CameraScaleFactor;  
    	float CameraCentreOffset;  
    	float CameraRotation;  
    	int16_t NPixel;  
    	int16_t NPixel_active; 
    	PixelType fromCameratoPixType;
    	vector<Pixel> fromCameratoPixel;    	
    };

    struct MirrorType {
    	int mirType;
        float FL;  
        float FOV;  
        int16_t NTubesOFF;  
        int16_t NMirrors;  
        float MirrorArea;  	
    };

    struct TelescopeType {
    	int64_t TelType;
    	MirrorType fromTelTypetoMirType;
    	CameraType fromTelTypetoCamType;    	 
    };

    struct Telescope {
        int16_t TelID;
        TelescopeType fromTeltoTelType;
        float TelX;
        float TelY;   
        float TelZ;  
    };    

    struct Array {
    	int16_t ArrayID;
    	int16_t NTel;	
    };

    /// structure declaration
    struct PixelType temp_pixtype;
    
    vector<PixelType> pixelType;

    struct Pixel temp_pixel;

    struct CameraType temp_camtype;
    vector<CameraType> cameraType;

    struct MirrorType temp_mirtype;
    vector<MirrorType> mirrorType;

    struct TelescopeType temp_teltype;
    vector<TelescopeType> telescopeType;

    struct Telescope temp_tel;    
    vector<Telescope> telescope;

    struct Array array;
    
	/// It gets the telescope structure from the identification number
	struct RTATelem::CTAConfig::Telescope *getTelescopeStruct(int TelID);
    
    
};
}

#endif
