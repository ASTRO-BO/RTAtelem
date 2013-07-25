#include "CTATriggeredTelescope.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define RBLOCK_SAMPLE 0
#define APID 100

void RTATelem::CTATriggeredTelescope::printListOfString(char** r) {
	int i=0;
	while(r[i] != 0)
		cout << r[i++] << endl;
}

void RTATelem::CTATriggeredTelescope::printListOfString(string* r) {
	
		cout << *r << endl;
}

void RTATelem::CTATriggeredTelescope::printPacket_output() {
	cout << "HEADER ----------" << endl;
	char** r = outputPacket->header->printValue();
	printListOfString(r);
	cout << outputPacket->header->outputstream->printStreamInHexadecimal() << endl;
	cout << "max dimension: " << outputPacket->header->getDimension() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
 	r = outputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	cout << outputPacket->dataField->dataFieldHeader->outputstream->printStreamInHexadecimal() << endl;
	cout << "max dimension: " << outputPacket->dataField->dataFieldHeader->getDimension() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	cout << "max dimension: " << sdf->getDimension() << endl;
	sdf->printValueStdout();
	cout << "DIM: " << outputPacket->getDimension() << endl;
	cout << "MAXDIM: " << outputPacket->getMaxDimension() << endl;
	
}
	
RTATelem::CTATriggeredTelescope::CTATriggeredTelescope(string packetConfig, string tmInputFileName, string tmOutputFileName) {
	
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
    	cout << "RTATelem::CTATriggeredTelescope::CTATriggeredTelescope(...): " << e->geterror() << endl;
    }
	
}

RTATelem::CTATriggeredTelescope::~CTATriggeredTelescope() {
	if(in) in->close();
	if(out) out->close();
}



void RTATelem::CTATriggeredTelescope::setMetadata(word arrayID, word runNumberID, word eventNumberID) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(3, arrayID);
	outputPacket->dataField->dataFieldHeader->setFieldValue(4, runNumberID);
	outputPacket->dataField->dataFieldHeader->setFieldValue(5, eventNumberID);
}


void RTATelem::CTATriggeredTelescope::setNumberOfTriggeredTelescopes(word number) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(6, number);	
}

void RTATelem::CTATriggeredTelescope::setIndexOfCurrentTriggeredTelescopes(word telescopeIndex) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(7, telescopeIndex);
}


void RTATelem::CTATriggeredTelescope::setTelescopeId(word telescopeID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->setFieldValue(1, telescopeID);
}

void RTATelem::CTATriggeredTelescope::setNumberOfPixels(word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}

void RTATelem::CTATriggeredTelescope::setPixelId(word pixelIndex, word pixelID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setFieldValue(0, pixelID);
}

void RTATelem::CTATriggeredTelescope::setNumberOfSamples(word pixelIndex, word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void RTATelem::CTATriggeredTelescope::setSampleValue(word pixelIndex, word sampleIndex, word FADC) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	sample->setFieldValue(0, FADC);
}

void RTATelem::CTATriggeredTelescope::writePacket() {
	ops->writePacket(outputPacket);
}

//*************************************************


byte* RTATelem::CTATriggeredTelescope::readPacket() {
	inputPacket = ips->readPacket();
	if(inputPacket == 0)
		return 0;
	return inputPacket->getInputStream()->stream;
}

void RTATelem::CTATriggeredTelescope::printPacket_input() {
	cout << "HEADER ----------" << endl;
	char** r = inputPacket->header->printValue();
	printListOfString(r);
	cout << "DATA FIELD HEADER ----------" << endl;
 	r = inputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	cout << "SOURCE DATA FIELD ----------" << endl;
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->printValueStdout();
	cout << "DIM: " << inputPacket->getDimension() << endl;
	cout << "MAXDIM: " << inputPacket->getMaxDimension() << endl;
	
}


void RTATelem::CTATriggeredTelescope::getMetadata(word &arrayID, word &runNumberID, word &eventNumberID) {
	arrayID = inputPacket->dataField->dataFieldHeader->getFieldValue(3);
	runNumberID = inputPacket->dataField->dataFieldHeader->getFieldValue(4);
	eventNumberID = inputPacket->dataField->dataFieldHeader->getFieldValue(5);
}

word RTATelem::CTATriggeredTelescope::getNumberOfTriggeredTelescopes() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue(6);	
}

word RTATelem::CTATriggeredTelescope::getIndexOfCurrentTriggeredTelescopes() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue(7);	
}

word RTATelem::CTATriggeredTelescope::getTelescopeId() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	return sdf->getFieldValue(1);
}

word RTATelem::CTATriggeredTelescope::getNumberOfPixels() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	return sdf->getNumberOfRealDataBlock();
}

word RTATelem::CTATriggeredTelescope::getPixelId(word pixelIndex) {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	return pixel->getFieldValue(0);
}

word RTATelem::CTATriggeredTelescope::getNumberOfSamples(word pixelIndex) {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	return pixel->getNumberOfRealDataBlock();
}

word RTATelem::CTATriggeredTelescope::getSampleValue(word pixelIndex, word sampleIndex) {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	return sample->getFieldValue(0);
}
