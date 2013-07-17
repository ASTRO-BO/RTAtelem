module CTAData {
	
	struct CTAPixelSampleData {
		int FADC;
	};

	sequence<CTAPixelSampleData> SampleList;
	
	struct CTAPixelData {
		int pixelID;
		SampleList samples;	
	};

	sequence<CTAPixelData> PixelList;

	struct CTACameraData {
		int cameraID;
		PixelList pixels;
	};

	sequence<CTACameraData> CameraList;
	
	struct CTATriggeredEvent {
		int arrayID;
		int runNumber;
		int eventNumber;
		CameraList cameras;	
	};

	
};
