#include "CTAPedestalHigh.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketDataField.h"
#include "SDFRBlock.h"

#define RBLOCK_TELESCOPE 0
#define RBLOCK_PIXEL 0
#define APID 100

void RTATelem::CTAPedestalHigh::printListOfString(char** r) {
	int i=0;
	while(r[i] != 0)
		cout << r[i++] << endl;
}

void RTATelem::CTAPedestalHigh::printListOfString(string* r) {
	
		cout << *r << endl;
}

void RTATelem::CTAPedestalHigh::printPacket_output() {
	cout << "HEADER ----------" << endl;
	char** r = outputPacket->header->printValue();
	printListOfString(r);
	cout << outputPacket->header->outputstream->printStreamInHexadecimal() << endl;
	cout << "max dimension: " << outputPacket->header->getDimension() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
 	r = outputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	//cout << outputPacket->dataField->dataFieldHeader->outputstream->printStreamInHexadecimal() << endl;
	cout << "max dimension: " << outputPacket->dataField->dataFieldHeader->getDimension() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	cout << "max dimension: " << sdf->getDimension() << endl;
	sdf->printValueStdout();
	cout << "DIM: " << outputPacket->getDimension() << endl;
	cout << "MAXDIM: " << outputPacket->getMaxDimension() << endl;
	
}
	
RTATelem::CTAPedestalHigh::CTAPedestalHigh(string packetConfig, string tmInputFileName, string tmOutputFileName) {
	
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
    	cout << "RTATelem::CTAPedestalHigh::CTAPedestalHigh(...): " << e->geterror() << endl;
    }
	
}

RTATelem::CTAPedestalHigh::~CTAPedestalHigh() {
	if(in) in->close();
	if(out) out->close();
}



void RTATelem::CTAPedestalHigh::setMetadata(byte arrayID) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(3, arrayID);
}


void RTATelem::CTAPedestalHigh::setSSC(word counter) {
	outputPacket->header->setFieldValue(5, counter);
}

word RTATelem::CTAPedestalHigh::getSSC() {
	return inputPacket->header->getFieldValue(5);
}

void RTATelem::CTAPedestalHigh::setNumberOfTelescopes(word number) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(4, number);	
}

void RTATelem::CTAPedestalHigh::setIndexOfCurrentTelescopes(word telescopeIndex) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(5, telescopeIndex);
}


void RTATelem::CTAPedestalHigh::setTelescopeId(word telescopeID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->setFieldValue(0, telescopeID);
}

void RTATelem::CTAPedestalHigh::setNumberOfPixels(word number) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}

void RTATelem::CTAPedestalHigh::setPixelId(word pixelIndex, word pixelID) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setFieldValue(0, pixelID);
}


void RTATelem::CTAPedestalHigh::setPedestalHighValue(word pixelIndex, word PED_HIGH) {
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setFieldValue(1, PED_HIGH);
	//FIXED FORMAT
	//pixel->setFieldValue(sampleIndex+2, FADC);
}

void RTATelem::CTAPedestalHigh::writePacket() {
	ops->writePacket(outputPacket);
}

//*************************************************


byte* RTATelem::CTAPedestalHigh::readPacket() {
	inputPacket = ips->readPacket();
	if(inputPacket == 0)
		return 0;
	return inputPacket->getInputStream()->stream;
}

void RTATelem::CTAPedestalHigh::printPacket_input() {
	cout << "HEADER ----------" << endl;
	char** r = inputPacket->header->printValue();
	printListOfString(r);
	cout << inputPacket->header->stream->printStreamInHexadecimal() << endl;
	cout << "max dimension in byte of the header: " << inputPacket->header->getDimension() << endl;
	cout << "packet length " << inputPacket->header->getPacketLength() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
 	r = inputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	//cout << inputPacket->dataField->dataFieldHeader->stream->printStreamInHexadecimal() << endl;
	cout << "max dimension: " << inputPacket->dataField->dataFieldHeader->getDimension() << endl;	
	cout << "SOURCE DATA FIELD ----------" << endl;
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	sdf->printValueStdout();
	cout << "TOTAL DIM OF THE PACKET : " << inputPacket->getDimension() << endl;
	cout << "MAXDIM OF THE PACKET : " << inputPacket->getMaxDimension() << endl;
	
}


void RTATelem::CTAPedestalHigh::getMetadata(byte &arrayID) {
	arrayID = inputPacket->dataField->dataFieldHeader->getFieldValue(3);
}


word RTATelem::CTAPedestalHigh::getNumberOfTelescopes() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue(4);	
}

word RTATelem::CTAPedestalHigh::getIndexOfCurrentTelescopes() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue(5);	
}

word RTATelem::CTAPedestalHigh::getTelescopeId() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	return sdf->getFieldValue(0);
}

word RTATelem::CTAPedestalHigh::getNumberOfPixels() {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	return sdf->getNumberOfRealDataBlock();
}

word RTATelem::CTAPedestalHigh::getPixelId(word pixelIndex) {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	return pixel->getFieldValue(0);
}


word RTATelem::CTAPedestalHigh::getPedestalHighValue(word pixelIndex) {
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; //Get a pointer to the source data field
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	return pixel->getFieldValue(1);
	//FIXED FORMAT
	//return pixel->getFieldValue(sampleIndex+2);
}
