PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /LOCAL_GTB/Python2.7/include/python$(PYTHON_VERSION)
 
# location of the Boost Python include files and library
 
BOOST_INC = /LOCAL_GTB/boost_1_53_0/boost/python
BOOST_LIB = /LOCAL_GTB/boost_1_53_0/stage/lib

# location of the RTAtelem code
 
RTAtelem_DIR = ../code

# compile mesh classes
TARGET = CTATriggeredTel_ext
 
$(TARGET).so: $(TARGET).o
	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -I $(GTB_PACKETLIB_INCLUDE) -L$(GTB_PACKETLIB_LIB) -lpacket -lboost_python -L/LOCAL_GTB/Python2.7/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
 
$(TARGET).o: $(TARGET).cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I $(GTB_PACKETLIB_INCLUDE) -I$(RTAtelem_DIR) -L$(GTB_PACKETLIB_LIB) -fPIC -c $(TARGET).cpp

clean:
	rm $(TARGET).o $(TARGET).so

