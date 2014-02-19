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
			conf_Nheader = conf_file.getHeadersNum();
            cout << "Number of headers: " << conf_Nheader << endl;
 
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

            L0ID = conf_file.read64i(L0ID_colnum, 0, conf_Nrows_L0-1);
            TelID = conf_file.read16i(TelID_colnum, 0, conf_Nrows_L0-1);
            TelType = conf_file.read64i(TelType_colnum, 0, conf_Nrows_L0-1);
            TelX = conf_file.read32f(TelX_colnum, 0, conf_Nrows_L0-1);
            TelY = conf_file.read32f(TelY_colnum, 0, conf_Nrows_L0-1);   
            TelZ = conf_file.read32f(TelZ_colnum, 0, conf_Nrows_L0-1);  
            FL = conf_file.read32f(FL_colnum, 0, conf_Nrows_L0-1);  
            FOV = conf_file.read32f(FOV_colnum, 0, conf_Nrows_L0-1);  
            CameraScaleFactor = conf_file.read32f(CameraScaleFactor_colnum, 0, conf_Nrows_L0-1);  
            CameraCentreOffset = conf_file.read32f(CameraCentreOffset_colnum, 0, conf_Nrows_L0-1);  
            CameraRotation = conf_file.read32f(CameraRotation_colnum, 0, conf_Nrows_L0-1);  
            NPixel = conf_file.read16i(NPixel_colnum, 0, conf_Nrows_L0-1);  
            NPixel_active = conf_file.read16i(NPixel_active_colnum, 0, conf_Nrows_L0-1);  
            NSamples = conf_file.read16i(NSamples_colnum, 0, conf_Nrows_L0-1);  
            Sample_time_slice = conf_file.read32f(Sample_time_slice_colnum, 0, conf_Nrows_L0-1);  
            NGains = conf_file.read16i(NGains_colnum, 0, conf_Nrows_L0-1);  
            HiLoScale = conf_file.read32f(HiLoScale_colnum, 0, conf_Nrows_L0-1);  
            HiLoThreshold = conf_file.read16i(HiLoThreshold_colnum, 0, conf_Nrows_L0-1);  
            HiLoOffset = conf_file.read32f(HiLoOffset_colnum, 0, conf_Nrows_L0-1);  
            NTubesOFF = conf_file.read16i(NTubesOFF_colnum, 0, conf_Nrows_L0-1);  
            NMirrors = conf_file.read16i(NMirrors_colnum, 0, conf_Nrows_L0-1);  
            MirrorArea = conf_file.read32f(MirrorArea_colnum, 0, conf_Nrows_L0-1);
            
            /*
            for(int i=0; i<conf_Nrows_L0; i++) {
            	cout << "NPixel: " << NPixel[i] << endl;
            }*/
            
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
          
            L1ID = conf_file.read64i(L1ID_colnum, 0, conf_Nrows_L1-1);
            L0ID_L1 = conf_file.read64i(L0ID_L1_colnum, 0, conf_Nrows_L1-1);
            PixelID = conf_file.read16i(PixelID_colnum, 0, conf_Nrows_L1-1);
            XTubeMM = conf_file.read32f(XTubeMM_colnum, 0, conf_Nrows_L1-1);
            YTubeMM = conf_file.read32f(YTubeMM_colnum, 0, conf_Nrows_L1-1);   
            RTubeMM = conf_file.read32f(RTubeMM_colnum, 0, conf_Nrows_L1-1);  
            XTubeDeg = conf_file.read32f(XTubeDeg_colnum, 0, conf_Nrows_L1-1);
            YTubeDeg = conf_file.read32f(YTubeDeg_colnum, 0, conf_Nrows_L1-1);   
            RTubeDeg = conf_file.read32f(RTubeDeg_colnum, 0, conf_Nrows_L1-1);  
            TubeOFF = conf_file.read16i(TubeOFF_colnum, 0, conf_Nrows_L1-1);         

		}


	}
	catch (qlbase::IOException& e) {
		cout << "ERROR: File "<< confInputFileName <<" does not exist. Error code: " << e.getErrorCode() << endl;
	}
}

RTATelem::CTAConfig::~CTAConfig() {
	conf_file.close();

}



