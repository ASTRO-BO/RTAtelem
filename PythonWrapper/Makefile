PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /opt/local/Library/Frameworks/Python.framework/Versions/2.7/include/python$(PYTHON_VERSION)
PYTHON_LIB = /opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python$(PYTHON_VERSION)/config/
 
# location of the Boost Python include files and library
 
BOOST_INC = /opt/local/include/boost/python
BOOST_LIB = /opt/local/lib

# location of the RTAtelem code
 
RTAtelem_DIR = $(HOME)/Projects/RTAtelem/code

# Boost Python library keyword (for Macports Boost installation use -lboost_python-mt)
BOOST_PYTHON_LIB = -lboost_python-mt

CXX ?= g++

# compile mesh classes

.PHONY: all
all: CTACameraTriggerData_ext.so CTACameraPedestal_ext.so CTACameraConv_ext.so 

CTACameraTriggerData_ext.so: CTACameraTriggerData_ext.o
	g++ -shared CTACameraTriggerData_ext.o -L$(BOOST_LIB) -I $(GTB_PACKETLIB_INCLUDE) -L$(GTB_PACKETLIB_LIB) -lpacket $(BOOST_PYTHON_LIB) -L$(PYTHON_LIB) -lpython$(PYTHON_VERSION) -o CTACameraTriggerData_ext.so
 
CTACameraTriggerData_ext.o:CTACameraTriggerData_ext.cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I $(GTB_PACKETLIB_INCLUDE) -I$(RTAtelem_DIR) -L$(GTB_PACKETLIB_LIB) -fPIC -c CTACameraTriggerData_ext.cpp

CTACameraPedestal_ext.so: CTACameraPedestal_ext.o
	g++ -shared CTACameraPedestal_ext.o -L$(BOOST_LIB) -I $(GTB_PACKETLIB_INCLUDE) -L$(GTB_PACKETLIB_LIB) -lpacket $(BOOST_PYTHON_LIB) -L$(PYTHON_LIB) -lpython$(PYTHON_VERSION) -o CTACameraPedestal_ext.so
 
CTACameraPedestal_ext.o:CTACameraPedestal_ext.cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I $(GTB_PACKETLIB_INCLUDE) -I$(RTAtelem_DIR) -L$(GTB_PACKETLIB_LIB) -fPIC -c CTACameraPedestal_ext.cpp

CTACameraConv_ext.so: CTACameraConv_ext.o
	g++ -shared CTACameraConv_ext.o -L$(BOOST_LIB) -I $(GTB_PACKETLIB_INCLUDE) -L$(GTB_PACKETLIB_LIB) -lpacket $(BOOST_PYTHON_LIB) -L$(PYTHON_LIB) -lpython$(PYTHON_VERSION) -o CTACameraConv_ext.so
 
CTACameraConv_ext.o:CTACameraConv_ext.cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I $(GTB_PACKETLIB_INCLUDE) -I$(RTAtelem_DIR) -L$(GTB_PACKETLIB_LIB) -fPIC -c CTACameraConv_ext.cpp

clean:
	@- $(RM) CTACameraTriggerData_ext.o CTACameraTriggerData_ext.so
	@- $(RM) CTACameraPedestal_ext.o CTACameraPedestal_ext.so
	@- $(RM) CTACameraConv_ext.o CTACameraConv_ext.so
	
distclean: clean
