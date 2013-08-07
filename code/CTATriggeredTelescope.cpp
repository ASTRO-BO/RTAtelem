/***************************************************************************
                          CTATriggeredTelescope.cpp  -  description
                             -------------------
    copyright            : (C) 2013 Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/


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
	cout << "max dimension: " << outputPacket->dataField->dataFieldHeader->getDimension() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; 
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
			/// create output packet stream
			ops = new OutputPacketStream();
			ops->setFileNameConfig(packetConfig.c_str());
			ops->createStreamStructure();
			outputPacket = ops->getPacketType(1);
			outputPacket->header->setFieldValue(3, APID);
			cout << (const char*) outputPacket->getName() << endl;
			/// parameter for the output: file
			out = (Output*) new OutputFile(ops->isBigEndian()); 
			/// file name
			param[0] = (char*)tmOutputFileName.c_str(); 
			param[1] = 0;
			
			/// open output
			out->open(param);
			
       		/// connect the output
  			ops->setOutput(out);
       		
		}
    	if(tmInputFileName != "") {
			///create input packet stream
			ips = new InputPacketStream();
			ips->setFileNameConfig(packetConfig.c_str());
			ips->createStreamStructure();
			inputPacket = ips->getPacketType(1);
			
			in = (Input*) new InputFile(ips->isBigEndian());
			/// file name
			param[0] = (char*) tmInputFileName.c_str(); 
			param[1] = 0;
			
			/// open input
   			in->open(param);
   			
   			/// set a particular input
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



void RTATelem::CTATriggeredTelescope::setMetadata(byte arrayID, word runNumberID, dword eventNumberID) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(3, arrayID);
	outputPacket->dataField->dataFieldHeader->setFieldValue(4, runNumberID);
	outputPacket->dataField->dataFieldHeader->setFieldValue_4_14(5, eventNumberID);
}

void RTATelem::CTATriggeredTelescope::setTelescopeTime(signed long trigTime) {
	outputPacket->dataField->dataFieldHeader->setFieldValue_4_14(7, trigTime);
}

void RTATelem::CTATriggeredTelescope::setSSC(word counter) {
	outputPacket->header->setFieldValue(5, counter);
}

word RTATelem::CTATriggeredTelescope::getSSC() {
	return inputPacket->header->getFieldValue(5);
}

void RTATelem::CTATriggeredTelescope::setNumberOfTriggeredTelescopes(word number) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(9, number);	
}

void RTATelem::CTATriggeredTelescope::setIndexOfCurrentTriggeredTelescopes(word telescopeIndex) {
	outputPacket->dataField->dataFieldHeader->setFieldValue(10, telescopeIndex);
}


void RTATelem::CTATriggeredTelescope::setTelescopeId(word telescopeID) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; 
	sdf->setFieldValue(0, telescopeID);
}

void RTATelem::CTATriggeredTelescope::setNumberOfPixels(word number) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; 
	sdf->setNumberOfRealDataBlock(number, RBLOCK_PIXEL);
}

void RTATelem::CTATriggeredTelescope::setPixelId(word pixelIndex, word pixelID) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; 
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setFieldValue(0, pixelID);
}

void RTATelem::CTATriggeredTelescope::setNumberOfSamples(word pixelIndex, word number) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; 
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	pixel->setNumberOfRealDataBlock(number, RBLOCK_SAMPLE);
}

void RTATelem::CTATriggeredTelescope::setSampleValue(word pixelIndex, word sampleIndex, word FADC) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField; 
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	/// VARIABLE FORMAT
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
	cout << inputPacket->header->stream->printStreamInHexadecimal() << endl;
	cout << "max dimension in byte of the header: " << inputPacket->header->getDimension() << endl;
	cout << "packet length " << inputPacket->header->getPacketLength() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
 	r = inputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	cout << "max dimension: " << inputPacket->dataField->dataFieldHeader->getDimension() << endl;	
	cout << "SOURCE DATA FIELD ----------" << endl;
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; 
	sdf->printValueStdout();
	cout << "TOTAL DIM OF THE PACKET : " << inputPacket->getDimension() << endl;
	cout << "MAXDIM OF THE PACKET : " << inputPacket->getMaxDimension() << endl;
	
}


void RTATelem::CTATriggeredTelescope::getMetadata(byte &arrayID, word &runNumberID, dword &eventNumberID) {
	arrayID = inputPacket->dataField->dataFieldHeader->getFieldValue(3);
	runNumberID = inputPacket->dataField->dataFieldHeader->getFieldValue(4);
	eventNumberID = inputPacket->dataField->dataFieldHeader->getFieldValue_4_14(5);
}

signed long RTATelem::CTATriggeredTelescope::getTelescopeTime() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue_4_14(7);
}

word RTATelem::CTATriggeredTelescope::getNumberOfTriggeredTelescopes() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue(9);	
}

word RTATelem::CTATriggeredTelescope::getIndexOfCurrentTriggeredTelescopes() {
	return inputPacket->dataField->dataFieldHeader->getFieldValue(10);	
}

word RTATelem::CTATriggeredTelescope::getTelescopeId() {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; 
	return sdf->getFieldValue(0);
}

word RTATelem::CTATriggeredTelescope::getNumberOfPixels() {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; 
	return sdf->getNumberOfRealDataBlock();
}

word RTATelem::CTATriggeredTelescope::getPixelId(word pixelIndex) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; 
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	return pixel->getFieldValue(0);
}

word RTATelem::CTATriggeredTelescope::getNumberOfSamples(word pixelIndex) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; 
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	return pixel->getNumberOfRealDataBlock();
}

word RTATelem::CTATriggeredTelescope::getSampleValue(word pixelIndex, word sampleIndex) {
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField; 
	SDFRBBlock* pixel = (SDFRBBlock*) sdf->getBlock(pixelIndex, RBLOCK_PIXEL);
	/// VARIABLE FORMAT
	SDFRBBlock* sample = (SDFRBBlock*) pixel->getBlock(sampleIndex, RBLOCK_SAMPLE);
	return sample->getFieldValue(0);
}
