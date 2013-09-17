#include "CTAPacket.h"
#include "OutputFile.h"
#include "InputFile.h"
#include "PacketException.h"

void RTATelem::CTAPacket::printListOfString(char** r) {
	int i = 0;
	while (r[i] != 0)
		cout << r[i++] << endl;
}

void RTATelem::CTAPacket::printListOfString(string* r) {

	cout << *r << endl;
}

RTATelem::CTAPacket::CTAPacket(string packetConfig, string tmInputFileName,
		string tmOutputFileName) {

	in = 0;
	out = 0;
	ips = 0;
	ops = 0;
	outputPacket = 0;
	inputPacket = 0;

	try {
		char** param = (char**) new char*[2];

		if (tmOutputFileName != "") {
			/// create output packet stream
			ops = new OutputPacketStream();
			ops->setFileNameConfig(packetConfig.c_str());
			ops->createStreamStructure();
			outputPacket = ops->getPacketType(1);
			//cout << (const char*) outputPacket->getName() << endl;
			/// parameter for the output: file
			out = (Output*) new OutputFile(ops->isBigEndian());
			/// file name
			param[0] = (char*) tmOutputFileName.c_str();
			param[1] = 0;

			/// open output
			out->open(param);

			/// connect the output
			ops->setOutput(out);

		}
		if (tmInputFileName != "") {
			/// create input packet stream
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

		header = new CTAPacketHeader(inputPacket, outputPacket);

	}
	catch (PacketException* e) {
		cout << "RTATelem::CTAPedestal::CTAPedestal(...): " << e->geterror()
				<< endl;
	}

}

RTATelem::CTAPacket::~CTAPacket() {
	if (in)
		in->close();
	if (out)
		out->close();
}

void RTATelem::CTAPacket::printPacket_output() {
	cout << "HEADER ----------" << endl;
	char** r = outputPacket->header->printValue();
	printListOfString(r);
	cout << outputPacket->header->outputstream->printStreamInHexadecimal()
			<< endl;
	cout << "max dimension: " << outputPacket->header->getDimension() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
	r = outputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	cout << "max dimension: "
			<< outputPacket->dataField->dataFieldHeader->getDimension() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) outputPacket->dataField->sourceDataField;
	cout << "max dimension: " << sdf->getDimension() << endl;
	sdf->printValueStdout();
	cout << "DIM: " << outputPacket->getDimension() << endl;
	cout << "MAXDIM: " << outputPacket->getMaxDimension() << endl;

}

void RTATelem::CTAPacket::writePacket() {
	ops->writePacket(outputPacket);
}

byte* RTATelem::CTAPacket::readPacket() {
	inputPacket = ips->readPacket();
	if (inputPacket == 0)
		return 0;
	//cout << "BS: " << inputPacket->getDimension() << endl;
	return inputPacket->getInputStream()->stream;
}

void RTATelem::CTAPacket::printPacket_input() {
	cout << "HEADER ----------" << endl;
	char** r = inputPacket->header->printValue();
	printListOfString(r);
	cout << inputPacket->header->getByteStream()->printStreamInHexadecimal() << endl;
	cout << "max dimension in byte of the header: "
			<< inputPacket->header->getDimension() << endl;
	cout << "packet length " << inputPacket->header->getPacketLength() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
	r = inputPacket->dataField->dataFieldHeader->printValue();
	printListOfString(r);
	cout << "max dimension: "
			<< inputPacket->dataField->dataFieldHeader->getDimension() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	/// Get a pointer to the source data field
	SDFRBlock* sdf = (SDFRBlock*) inputPacket->dataField->sourceDataField;
	sdf->printValueStdout();
	cout << "TOTAL DIM OF THE PACKET : " << inputPacket->getDimension() << endl;
	cout << "MAXDIM OF THE PACKET : " << inputPacket->getMaxDimension() << endl;

}

ByteStream* RTATelem::CTAPacket::getInputPacketData() {
	return inputPacket->packet;
}

dword RTATelem::CTAPacket::getInputPacketDimension(byte* stream) {
	//cout << "C: " << inputPacket->getDimension() << endl;
    //inputPacket->verifyPacketValue(stream);
    //return inputPacket->getDimension();

	return ips->getPacketDimension(stream);
}
