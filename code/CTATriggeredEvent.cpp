#include "CTATriggeredEvent.h"
#include "OutputFile.h"
#include "InputFile.h"

RTATelem::CTATriggeredEvent::CTATriggeredEvent(string packetConfig, string tmInputFileName, string tmOutputFileName) {
	try{
		char** param = (char**) new (char*)[2];
		
		if(tmOutputFileName != "") {
			//create output packet stream
			ops = new OutputPacketStream();
			
			ops->setFileNameConfig(packetConfig);
			ops->createStreamStructure();
			
			//parameter for the output: file
			out = (Output*) new OutputFile(ops->isBigEndian()); 
			param[0] = tmOutputFileName; //file name
			param[1] = 0;
			
			//open output
       		out­>open(param);
       		
       		//connect the output
  			ops->setOutput(out);
       		
		}
    	if(tmInputFileName != "") {
			//create input packet stream
			ips = new InputPacketStream();
			ips->setFileNameConfig(packetConfig);
			ips->createStreamStructure();
			
			in = (Input*) new InputFile(ips->isBigEndian());
			param[0] = tmInputFileName; //file name
			param[1] = 0;
			
			//open input
   			in­>open(param);
   			
   			//set a particular input
   			ips->setInput(in);
   			
		}
    	
    } catch (PacketException* e) {
    	cout << "RTATelem::CTATriggeredEvent::CTATriggeredEvent(string packetConfig): " << e­>geterror() << endl;
    }
	
}
