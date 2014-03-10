#include "CTAPacket.h"
#include <packet/OutputFile.h>
#include <packet/InputFile.h>
#include <packet/PacketException.h>

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
	this->packetStreamConfig = packetConfig;

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
		cout << "RTATelem::CTAPacket::CTAPacket(string packetConfig, string tmInputFileName, string tmOutputFileName): " << e->geterror()
				<< endl;
	}

}

RTATelem::CTAPacket::CTAPacket(string packetConfig) {

	in = 0;
	out = 0;
	ips = 0;
	ops = 0;
	outputPacket = 0;
	inputPacket = 0;

	this->packetStreamConfig = packetConfig;

	try {
		/// create input packet stream
		ips = new InputPacketStream();
		ips->setFileNameConfig(packetConfig.c_str());
		ips->createStreamStructure();
		inputPacket = ips->getPacketType(1);
		//cout << "IP " << inputPacket << endl;
		//header = new CTAPacketHeader(inputPacket, outputPacket);

	}
	catch (PacketException* e) {
		cout << "RTATelem::CTAPacket::CTAPacket(string packetConfig): " << e->geterror()
				<< endl;
	}

}


RTATelem::CTAPacket::~CTAPacket() {
	delete ips;
	delete ops;
	if (in)
		in->close();
	if (out)
		out->close();
}

void RTATelem::CTAPacket::printPacket_output() {
	cout << "HEADER ----------" << endl;
	char** r = outputPacket->getPacketHeader()->printValue();
	printListOfString(r);
	cout << outputPacket->getPacketHeader()->outputstream->printStreamInHexadecimal()
			<< endl;
	cout << "max dimension: " << outputPacket->getPacketHeader()->size() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
	r = outputPacket->getPacketDataFieldHeader()->printValue();
	printListOfString(r);
	cout << "max dimension: "
			<< outputPacket->getPacketDataFieldHeader()->size() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	/// Get a pointer to the source data field
	SourceDataField* sdf = (SourceDataField*) outputPacket->getPacketSourceDataField();
	cout << "max dimension: " << sdf->size() << endl;
	sdf->printValueStdout();
	cout << "DIM: " << outputPacket->size() << endl;
	cout << "MAXDIM: " << outputPacket->sizeMax() << endl;

}

void RTATelem::CTAPacket::writePacket() {
	ops->writePacket(outputPacket);
}

ByteStreamPtr RTATelem::CTAPacket::readPacket() {
	inputPacket = ips->readPacket();
	if (inputPacket == 0)
		return 0;
	//cout << "BS: " << inputPacket->size() << endl;
	return inputPacket->getInputStream();
}

void RTATelem::CTAPacket::readPacketPy() {
	pyStream = readPacket();
}

void RTATelem::CTAPacket::printPacket_input() {
	cout << "HEADER ----------" << endl;
	char** r = inputPacket->getPacketHeader()->printValue();
	printListOfString(r);
	cout << inputPacket->getPacketHeader()->getByteStream()->printStreamInHexadecimal() << endl;
	cout << "max dimension in byte of the header: "
			<< inputPacket->getPacketHeader()->size() << endl;
	cout << "packet length " << inputPacket->getPacketHeader()->getPacketLength() << endl;
	cout << "DATA FIELD HEADER ----------" << endl;
	r = inputPacket->getPacketDataFieldHeader()->printValue();
	printListOfString(r);
	cout << "max dimension: "
			<< inputPacket->getPacketDataFieldHeader()->size() << endl;
	cout << "SOURCE DATA FIELD ----------" << endl;
	/// Get a pointer to the source data field
	SourceDataField* sdf = (SourceDataField*) inputPacket->getPacketSourceDataField();
	sdf->printValueStdout();
	cout << "TOTAL DIM OF THE PACKET : " << inputPacket->size() << endl;
	cout << "MAXDIM OF THE PACKET : " << inputPacket->sizeMax() << endl;

}

ByteStreamPtr RTATelem::CTAPacket::getInputPacketData() {
	return inputPacket->getBSPacket();
}

dword RTATelem::CTAPacket::getInputPacketDimension(ByteStreamPtr stream) {
	//cout << "C: " << inputPacket->size() << endl;
    //inputPacket->verifyPacketValue(stream);
    //return inputPacket->size();

	return ips->getPacketDimension(stream);
}

dword RTATelem::CTAPacket::getInputPacketDimension() {
	//cout << "C: " << inputPacket->size() << endl;
    //inputPacket->verifyPacketValue(stream);
    //return inputPacket->size();

	return ips->getPacketDimension(pyStream);
}

int RTATelem::CTAPacket::getInputPacketType(ByteStreamPtr stream) {

	return ips->detPacketType(stream);
}

bool RTATelem::CTAPacket::setStream(ByteStreamPtr stream, bool checkPacketLength) {
	this->stream = stream;
	
	//cout << inputPacket << endl;
	return inputPacket->set(stream, checkPacketLength);
}
