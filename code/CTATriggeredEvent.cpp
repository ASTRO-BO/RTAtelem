#include "CTATriggeredEvent.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_SAMPLE 0


RTATelem::CTATriggeredEvent::CTATriggeredEvent(string packetConfig, string tmInputFileName, string tmOutputFileName) {
	
	in = 0;
	out = 0;
	ips = 0;
	ops = 0;

	try{
		char** param = (char**) new char* [2];
		
		if(tmOutputFileName != "") {
			//create output packet stream
			ops = new OutputPacketStream();
			ops->setFileNameConfig(packetConfig.c_str());
			ops->createStreamStructure();
			outputPacket = ops->getPacketType(1);
			
			//parameter for the output: file
			out = (Output*) new OutputFile(ops->isBigEndian()); 
			param[0] = (char*)tmOutputFileName.c_str(); //file name
			param[1] = 0;
			
			//open output
			out->open(param);
			
       		//connect the output
  			ops->setOutput(out);
       		
		}
    	if(tmInputFileName != "") {
			//create input packet stream
			ips = new InputPacketStream();
			ips->setFileNameConfig(packetConfig.c_str());
			ips->createStreamStructure();
			inputPacket = ips->getPacketType(1);
			
			in = (Input*) new InputFile(ips->isBigEndian());
			param[0] = (char*) tmInputFileName.c_str(); //file name
			param[1] = 0;
			
			//open input
   			in->open(param);
   			
   			//set a particular input
   			ips->setInput(in);
   			
		}
    	
    } catch (PacketException* e) {
    	cout << "RTATelem::CTATriggeredEvent::CTATriggeredEvent(...): " << e->geterror() << endl;
    }
	
}

RTATelem::CTATriggeredEvent::~CTATriggeredEvent() {
	if(in) in->close();
	if(out) out->close();
}

void RTATelem::CTATriggeredEvent::setEvent(word arrayID, word runNumber, word eventNumber, word numberOfTelescopes, word numberOfPixels, word numberOfSamples) {
	setMetadata(arrayID, runNumber, eventNumber);
	setNumberOfTelescopes(numberOfTelescopes);
	for(int i=0; i<numberOfTelescopes; i++) {
		setNumberOfPixels(i, numberOfPixels);
		for(int j=0; j<numberOfPixels; j++)
			setNumerOfSamples(i, j, numberOfSamples);
	}
}

void RTATelem::CTATriggeredEvent::setMetadata(word arrayID, word runNumber, word eventNumber) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(3, arrayID);
	outputPacket->dataField->dataFieldHeader->setFieldValue(4, runNumber);
	outputPacket->dataField->dataFieldHeader->setFieldValue(5, eventNumber);
}


void RTATelem::CTATriggeredEvent::setNumberOfTelescopes(word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->setNumberOfRealDataBlock(number, RBLOCK_TELESCOPE); //N blocks for rtype RBLOCK_TELESCOPE
}


void RTATelem::CTATriggeredEvent::setTelescopeId(word telescopeIndex, word telescopeID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBlock* telescope = (SDFRBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	telescope->setFieldValue(1, telescopeID);
}

void RTATelem::CTATriggeredEvent::setNumberOfPixels(word telescopeIndex, word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBlock* telescope = (SDFRBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	telescope->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
	
}

void RTATelem::CTATriggeredEvent::setPixelId(word telescopeIndex, word pixelIndex, word pixelID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBlock* telescope = (SDFRBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	SDFRBlock* pixel = (SDFRBlock*) telescope->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setFieldValue(1, pixelID);
}

void RTATelem::CTATriggeredEvent::setNumerOfSamples(word telescopeIndex, word pixelIndex, word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBlock* telescope = (SDFRBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	SDFRBlock* pixel = (SDFRBlock*) telescope->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void RTATelem::CTATriggeredEvent::setSampleValue(word telescopeIndex, word pixelIndex, word sampleIndex, word FADC) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBlock* telescope = (SDFRBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	SDFRBlock* pixel = (SDFRBlock*) telescope->getBlock(pixelIndex, RBLOCK_PIXEL);
	SDFRBlock* sample = (SDFRBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	sample->setFieldValue(0, FADC);
}

void RTATelem::CTATriggeredEvent::writePacket() {
	ops->writePacket(outputPacket);
}
