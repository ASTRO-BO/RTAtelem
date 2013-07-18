#include "CTATriggeredEvent.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_SAMPLE 0
#define APID 100

void RTATelem::CTATriggeredEvent::printListOfString(char** r) {
	int i=0;
	while(r[i] != 0)
		cout << r[i++] << endl;
}

void RTATelem::CTATriggeredEvent::printListOfString(string* r) {
	
		cout << *r<< endl;
}

void RTATelem::CTATriggeredEvent::printPacket_output() {
	cout << "HEADER ----------" << endl;
	char** r = outputPacket->header->printValue();
	printListOfString(r);
	cout << "DATA FIELD HEADER ----------" << endl;
 	r = outputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	cout << "SOURCE DATA FIELD ----------" << endl;
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	r = sdf->printValue();
	printListOfString(r);
	
}
	
RTATelem::CTATriggeredEvent::CTATriggeredEvent(string packetConfig, string tmInputFileName, string tmOutputFileName) {
	
	in = 0;
	out = 0;
	ips = 0;
	ops = 0;
	outputPacket = 0;
	inputPacket = 0;
	
	try{
		char** param = (char**) new char* [2];
		
		if(tmOutputFileName != "") {
			//create output packet stream
			ops = new OutputPacketStream();
			ops->setFileNameConfig(packetConfig.c_str());
			ops->createStreamStructure();
			outputPacket = ops->getPacketType(1);
			outputPacket->header->setFieldValue(3, APID);
			cout << (const char*) outputPacket->getName() << endl;
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
	SDFRBBlock* telescope = (SDFRBBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	telescope->setFieldValue(1, telescopeID);
}

void RTATelem::CTATriggeredEvent::setNumberOfPixels(word telescopeIndex, word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* telescope = (SDFRBBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	telescope->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
	

}

void RTATelem::CTATriggeredEvent::setPixelId(word telescopeIndex, word pixelIndex, word pixelID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* telescope = (SDFRBBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) telescope->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setFieldValue(1, pixelID);
}

void RTATelem::CTATriggeredEvent::setNumerOfSamples(word telescopeIndex, word pixelIndex, word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* telescope = (SDFRBBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) telescope->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void RTATelem::CTATriggeredEvent::setSampleValue(word telescopeIndex, word pixelIndex, word sampleIndex, word FADC) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* telescope = (SDFRBBlock*) sdf->getBlock(telescopeIndex, RBLOCK_TELESCOPE); //get the block i of type RBLOCK_TELESCOPE of the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) telescope->getBlock(pixelIndex, RBLOCK_PIXEL);
	SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	sample->setFieldValue(0, FADC);
}

void RTATelem::CTATriggeredEvent::writePacket() {
	ops->writePacket(outputPacket);
}
