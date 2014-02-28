/***************************************************************************
                          CTAConfig.cpp  -  description
                             -------------------
    copyright            : (C) 2014 Valentina Fioretti
    email                : fioretti@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#include "CTAConfig.h"

#define CONF_L0HEADER 1
#define CONF_L1HEADER 2

RTATelem::CTAConfig::CTAConfig(const string& confInputFileName) {
	
	try {
		
		
		if (confInputFileName != "") {
			/// open FITS file
			conf_file.open(confInputFileName);
			//conf_Nheader = conf_file.getHeadersNum();
            //cout << "Number of headers: " << conf_Nheader << endl;
 						
			
            /// Moving to the Telescope level Header L0
            conf_file.moveToHeader(CONF_L0HEADER);
            
            /// Loading the number of rows
            conf_Nrows_L0 = conf_file.getNRows();
           
            /// Loading the data
            L0ID_colnum = conf_file.getColNum("L0ID");
            TelID_colnum = conf_file.getColNum("TelID");
            TelType_colnum = conf_file.getColNum("TelType");
            TelX_colnum = conf_file.getColNum("TelX");
            TelY_colnum = conf_file.getColNum("TelY");
            TelZ_colnum = conf_file.getColNum("TelZ");
            FL_colnum = conf_file.getColNum("FL");
            FOV_colnum = conf_file.getColNum("FOV");
            CameraScaleFactor_colnum = conf_file.getColNum("CameraScaleFactor");
            CameraCentreOffset_colnum = conf_file.getColNum("CameraCentreOffset");
            CameraRotation_colnum = conf_file.getColNum("CameraRotation");
            NPixel_colnum = conf_file.getColNum("NPixel");
            NPixel_active_colnum = conf_file.getColNum("NPixel_active");
            NSamples_colnum = conf_file.getColNum("NSamples");
            Sample_time_slice_colnum = conf_file.getColNum("Sample_time_slice");
            NGains_colnum = conf_file.getColNum("NGains");
            HiLoScale_colnum = conf_file.getColNum("HiLoScale");
            HiLoThreshold_colnum = conf_file.getColNum("HiLoThreshold");
            HiLoOffset_colnum = conf_file.getColNum("HiLoOffset");
            NTubesOFF_colnum = conf_file.getColNum("NTubesOFF");
            NMirrors_colnum = conf_file.getColNum("NMirrors");
            MirrorArea_colnum = conf_file.getColNum("MirrorArea");
            
			vecL0ID = conf_file.read64i(L0ID_colnum, 0, conf_Nrows_L0-1);
			vecTelID = conf_file.read16i(TelID_colnum, 0, conf_Nrows_L0-1);
			vecTelType = conf_file.read64i(TelType_colnum, 0, conf_Nrows_L0-1);
			vecTelX = conf_file.read32f(TelX_colnum, 0, conf_Nrows_L0-1);
			vecTelY = conf_file.read32f(TelY_colnum, 0, conf_Nrows_L0-1);   
			vecTelZ = conf_file.read32f(TelZ_colnum, 0, conf_Nrows_L0-1);   
			vecFL = conf_file.read32f(FL_colnum, 0, conf_Nrows_L0-1);  
			vecFOV = conf_file.read32f(FOV_colnum, 0, conf_Nrows_L0-1);  
			vecCameraScaleFactor = conf_file.read32f(CameraScaleFactor_colnum, 0, conf_Nrows_L0-1);  
			vecCameraCentreOffset = conf_file.read32f(CameraCentreOffset_colnum, 0, conf_Nrows_L0-1);  
			vecCameraRotation = conf_file.read32f(CameraRotation_colnum, 0, conf_Nrows_L0-1);  
			vecNPixel = conf_file.read16i(NPixel_colnum, 0, conf_Nrows_L0-1);  
			vecNPixel_active = conf_file.read16i(NPixel_active_colnum, 0, conf_Nrows_L0-1);  
			vecNSamples = conf_file.read16i(NSamples_colnum, 0, conf_Nrows_L0-1);  
			vecSample_time_slice = conf_file.read32f(Sample_time_slice_colnum, 0, conf_Nrows_L0-1);  
			vecNGains = conf_file.read16i(NGains_colnum, 0, conf_Nrows_L0-1);  
			vecHiLoScale = conf_file.read32f(HiLoScale_colnum, 0, conf_Nrows_L0-1);  
			vecHiLoThreshold = conf_file.read16i(HiLoThreshold_colnum, 0, conf_Nrows_L0-1);  
			vecHiLoOffset = conf_file.read32f(HiLoOffset_colnum, 0, conf_Nrows_L0-1);  
			vecNTubesOFF = conf_file.read16i(NTubesOFF_colnum, 0, conf_Nrows_L0-1);  
			vecNMirrors = conf_file.read16i(NMirrors_colnum, 0, conf_Nrows_L0-1);  
			vecMirrorArea = conf_file.read32f(MirrorArea_colnum, 0, conf_Nrows_L0-1);
			
			/// Moving to the Pixel level Header L1
			conf_file.moveToHeader(CONF_L1HEADER);
			                        
			/// Loading the number of rows
			conf_Nrows_L1 = conf_file.getNRows();
			     
			/// Loading the data
			L1ID_colnum = conf_file.getColNum("L1ID");
			L0ID_L1_colnum = conf_file.getColNum("L0ID");
			PixelID_colnum = conf_file.getColNum("PixelID");
			XTubeMM_colnum = conf_file.getColNum("XTubeMM");
			YTubeMM_colnum = conf_file.getColNum("YTubeMM");
			RTubeMM_colnum = conf_file.getColNum("RTubeMM");
			XTubeDeg_colnum = conf_file.getColNum("XTubeDeg");
			YTubeDeg_colnum = conf_file.getColNum("YTubeDeg");
			RTubeDeg_colnum = conf_file.getColNum("RTubeDeg");
			TubeOFF_colnum = conf_file.getColNum("TubeOFF");
			          
			vecL1ID = conf_file.read64i(L1ID_colnum, 0, conf_Nrows_L1-1);
			vecL0ID_L1 = conf_file.read64i(L0ID_L1_colnum, 0, conf_Nrows_L1-1);
			vecPixelID = conf_file.read16i(PixelID_colnum, 0, conf_Nrows_L1-1);
			vecXTubeMM = conf_file.read32f(XTubeMM_colnum, 0, conf_Nrows_L1-1);
			vecYTubeMM = conf_file.read32f(YTubeMM_colnum, 0, conf_Nrows_L1-1);   
			vecRTubeMM = conf_file.read32f(RTubeMM_colnum, 0, conf_Nrows_L1-1);  
			vecXTubeDeg = conf_file.read32f(XTubeDeg_colnum, 0, conf_Nrows_L1-1);
			vecYTubeDeg = conf_file.read32f(YTubeDeg_colnum, 0, conf_Nrows_L1-1);   
			vecRTubeDeg = conf_file.read32f(RTubeDeg_colnum, 0, conf_Nrows_L1-1);  
			vecTubeOFF = conf_file.read16i(TubeOFF_colnum, 0, conf_Nrows_L1-1);         

			
			/// Setting the dummy array
			array.ArrayID = 1;
			array.NTel = conf_Nrows_L0;

			/// Setting the Telescope structure objects							
			for(int i=0; i<array.NTel; i++) {
				temp_tel.TelID = vecTelID[i];
				temp_tel.fromTeltoTelType.TelType = vecTelType[i];
				temp_tel.TelX = vecTelX[i];
				temp_tel.TelY = vecTelY[i];
				temp_tel.TelZ = vecTelZ[i]; 
				telescope.push_back(temp_tel);
			}
			
			/// Setting the TelescopeType structure
			
			vecUniqueMirrorArea = vecMirrorArea;
			sort( vecUniqueMirrorArea.begin(), vecUniqueMirrorArea.end() );
			vecUniqueMirrorArea.erase( unique( vecUniqueMirrorArea.begin(), vecUniqueMirrorArea.end() ), vecUniqueMirrorArea.end() );
			
			NTelType = vecUniqueMirrorArea.size();
			int pos;
			for(int i=0; i<NTelType; i++) {
				pos = -1;
				while (pos < 0){
					pos = find(vecMirrorArea.begin(), vecMirrorArea.end(), vecUniqueMirrorArea[i]) - vecMirrorArea.begin();
				}
				vecUniqueTelType.push_back(vecTelType[pos]);
			    vecUniqueFL.push_back(vecFL[pos]);  
			    vecUniqueFOV.push_back(vecFOV[pos]);  
			    vecUniqueCameraScaleFactor.push_back(vecCameraScaleFactor[pos]);  
			    vecUniqueCameraCentreOffset.push_back(vecCameraCentreOffset[pos]);  
			    vecUniqueCameraRotation.push_back(vecCameraRotation[pos]);  
			    vecUniqueNTubesOFF.push_back(vecNTubesOFF[pos]);  
			    vecUniqueNMirrors.push_back(vecNMirrors[pos]);  
			    vecUniqueMirrorArea.push_back(vecMirrorArea[pos]);  
			    vecUniqueNPixel.push_back(vecNPixel[pos]);  
			    vecUniqueNPixel_active.push_back(vecNPixel_active[pos]); 
			    vecUniqueNSamples.push_back(vecNSamples[pos]);  
			    vecUniqueSample_time_slice.push_back(vecSample_time_slice[pos]);  
			    vecUniqueNGains.push_back(vecNGains[pos]);  
			    vecUniqueHiLoScale.push_back(vecHiLoScale[pos]);  
			    vecUniqueHiLoThreshold.push_back(vecHiLoThreshold[pos]);  
			    vecUniqueHiLoOffset.push_back(vecHiLoOffset[pos]); 
			    
			    for(int j=0; j<vecUniqueNPixel[i]; j++) {
			    	vecUniquePixelID.push_back(vecPixelID[pos + j]);
			    	vecUniqueXTubeMM.push_back(vecXTubeMM[pos + j]);
			    	vecUniqueYTubeMM.push_back(vecYTubeMM[pos + j]);
			    	vecUniqueRTubeMM.push_back(vecRTubeMM[pos + j]);
			    	vecUniqueXTubeDeg.push_back(vecXTubeDeg[pos + j]);
			    	vecUniqueYTubeDeg.push_back(vecYTubeDeg[pos + j]);
			    	vecUniqueRTubeDeg.push_back(vecRTubeDeg[pos + j]);
			    	vecUniqueTubeOFF.push_back(vecTubeOFF[pos + j]);
			    }
			}
			
			/// The telescopes size increases as the index in the vector increases
			
			//cout << "Small telescope: " << vecUniqueTelType[0] << endl;
			//cout << "Medium telescope: " << vecUniqueTelType[1] << endl;
			//cout << "Large telescope: " << vecUniqueTelType[2] << endl;
			
			for(int i=0; i<NTelType; i++) {
				temp_teltype.TelType = vecUniqueTelType[i];
				temp_teltype.fromTelTypetoMirType.mirType = i+1;
				temp_teltype.fromTelTypetoCamType.camType = i+1;
				telescopeType.push_back(temp_teltype);
			}

			for(int i=0; i<NTelType; i++) {
				temp_mirtype.mirType = i+1;
				temp_mirtype.FL =  vecUniqueFL[i];
				temp_mirtype.FOV =  vecUniqueFOV[i];
				temp_mirtype.NTubesOFF =  vecUniqueNTubesOFF[i];
				temp_mirtype.NMirrors =  vecUniqueNMirrors[i];
				temp_mirtype.MirrorArea =  vecUniqueMirrorArea[i];
				mirrorType.push_back(temp_mirtype);
			}
			
			
			int prevNPixel = 0;
			for(int i=0; i<NTelType; i++) {
				temp_camtype.camType = i+1;
				temp_camtype.CameraScaleFactor = vecUniqueCameraScaleFactor[i];
				temp_camtype.CameraCentreOffset = vecUniqueCameraCentreOffset[i];
				temp_camtype.CameraRotation = vecUniqueCameraRotation[i];
				temp_camtype.NPixel = vecUniqueNPixel[i];
				temp_camtype.NPixel_active = vecUniqueNPixel_active[i];
				temp_camtype.fromCameratoPixType.pixType = i+1;
				 
				for(int j=0; j<temp_camtype.NPixel; j++) {
					temp_pixel.PixelID = vecUniquePixelID[prevNPixel + j];					                  					
					temp_pixel.XTubeMM = vecUniqueXTubeMM[prevNPixel + j];					                  					
					temp_pixel.YTubeMM = vecUniqueYTubeMM[prevNPixel + j];
					temp_pixel.RTubeMM = vecUniqueRTubeMM[prevNPixel + j];
					temp_pixel.XTubeDeg = vecUniqueXTubeDeg[prevNPixel + j];
					temp_pixel.YTubeDeg = vecUniqueYTubeDeg[prevNPixel + j];
					temp_pixel.RTubeDeg = vecUniqueRTubeDeg[prevNPixel + j];
					temp_pixel.TubeOFF = vecUniqueTubeOFF[prevNPixel + j];
					temp_camtype.fromCameratoPixel.push_back(temp_pixel);   
				}

				cameraType.push_back(temp_camtype);
				prevNPixel = prevNPixel + temp_camtype.NPixel; 
			}	
			
			for(int i=0; i<NTelType; i++) {
				temp_pixtype.pixType = i+1;
				temp_pixtype.NSamples =  vecUniqueNSamples[i];
				temp_pixtype.Sample_time_slice =  vecUniqueSample_time_slice[i];
				temp_pixtype.NGains =  vecUniqueNGains[i];
				temp_pixtype.HiLoScale =  vecUniqueHiLoScale[i];
				temp_pixtype.HiLoThreshold =  vecUniqueHiLoThreshold[i];
				temp_pixtype.HiLoOffset =  vecUniqueHiLoOffset[i];
				pixelType.push_back(temp_pixtype);
			}
			
            
		}


	}
	catch (qlbase::IOException& e) {
		cout << "ERROR: File "<< confInputFileName <<" does not exist. Error code: " << e.getErrorCode() << endl;
	}
}


struct RTATelem::CTAConfig::Telescope *RTATelem::CTAConfig::getTelescopeStruct(int TelID) {
	struct Telescope *selTelescope;
	for (int i=0; i<array.NTel; i++) {
    	if (telescope[i].TelID == TelID){
    		selTelescope = &telescope[i];
    		break;                          
    	}
    }
	
	return selTelescope;
}


RTATelem::CTAConfig::~CTAConfig() {
	conf_file.close();

}



