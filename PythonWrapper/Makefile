PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /LOCAL_GTB/Python2.7/include/python$(PYTHON_VERSION)
 
# location of the Boost Python include files and library
 
BOOST_INC = /LOCAL_GTB/boost_1_53_0/boost/python
BOOST_LIB = /LOCAL_GTB/boost_1_53_0/stage/lib

# location of the RTAtelem code
 
RTAtelem_DIR = $(HOME)/Projects/RTAtelem/code

# compile mesh classes

.PHONY: all
all: CTACameraTriggerData_ext.so CTACameraPedestal_ext.so

CTACameraTriggerData_ext.so: CTACameraTriggerData_ext.o
	g++ -shared -Wl,--export-dynamic CTACameraTriggerData_ext.o -L$(BOOST_LIB) -I $(GTB_PACKETLIB_INCLUDE) -L$(GTB_PACKETLIB_LIB) -lpacket -lboost_python -L/LOCAL_GTB/Python2.7/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o CTACameraTriggerData_ext.so
 
CTACameraTriggerData_ext.o:CTACameraTriggerData_ext.cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I $(GTB_PACKETLIB_INCLUDE) -I$(RTAtelem_DIR) -L$(GTB_PACKETLIB_LIB) -fPIC -c CTACameraTriggerData_ext.cpp

CTACameraPedestal_ext.so: CTACameraPedestal_ext.o
	g++ -shared -Wl,--export-dynamic CTACameraPedestal_ext.o -L$(BOOST_LIB) -I $(GTB_PACKETLIB_INCLUDE) -L$(GTB_PACKETLIB_LIB) -lpacket -lboost_python -L/LOCAL_GTB/Python2.7/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o CTACameraPedestal_ext.so
 
CTACameraPedestal_ext.o:CTACameraPedestal_ext.cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I $(GTB_PACKETLIB_INCLUDE) -I$(RTAtelem_DIR) -L$(GTB_PACKETLIB_LIB) -fPIC -c CTACameraPedestal_ext.cpp

clean:
	@- $(RM) CTACameraTriggerData_ext.o CTACameraTriggerData_ext.so
	@- $(RM) CTACameraPedestal_ext.o CTACameraPedestal_ext.so

distclean: clean
