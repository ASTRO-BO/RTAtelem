from ROOT import TFile, gDirectory
import numpy as np
import matplotlib.pyplot as plt

import pyfits

import CTATriggeredTel_ext
import convert_ext

plt.ion()

fig = plt.figure(1)
ax1 = fig.add_subplot(121)
ax2 = fig.add_subplot(122)

#plt.show()


# open the file
myfile = TFile( '/home/rta/Projects/PROD2/Aar.prod2.a2.root' )
myfile.ls()

hdulist_conf = pyfits.open('/home/rta/Projects/PROD2/PROD2_telconfig.fits.gz')
data_conf = hdulist_conf[1].data
cols_conf = hdulist_conf[1].columns
names_field = cols_conf.names

TelID = data_conf.field(names_field[0])
TelType = data_conf.field(names_field[1])
TelX = data_conf.field(names_field[2])
TelY = data_conf.field(names_field[3])
TelZ = data_conf.field(names_field[4])
FocalLength = data_conf.field(names_field[5])
FOV = data_conf.field(names_field[6])
CameraScaleFactor = data_conf.field(names_field[7])
CameraCentreOffset = data_conf.field(names_field[8])
CameraRotation = data_conf.field(names_field[9])
NPixel = data_conf.field(names_field[10])
NPixel_active = data_conf.field(names_field[11])
NSamples = data_conf.field(names_field[12])
Sample_time_slice = data_conf.field(names_field[13])
NGains = data_conf.field(names_field[14])
HiLoScale = data_conf.field(names_field[15])
HiLoThreshold = data_conf.field(names_field[16])
HiLoOffset = data_conf.field(names_field[17])

XTubeMM = data_conf.field(names_field[18])
YTubeMM = data_conf.field(names_field[19])
RTubeMM = data_conf.field(names_field[20])
XTubeDeg = data_conf.field(names_field[21])
YTubeDeg = data_conf.field(names_field[22])
RTubeDeg = data_conf.field(names_field[23])

NTubesOFF = data_conf.field(names_field[24])
TubeOFF = data_conf.field(names_field[25])
NMirrors = data_conf.field(names_field[26])
MirrorArea = data_conf.field(names_field[27])

NTel = len(TelID)
max_NPixel = int(max(NPixel))

#############################################################
#                        DST TREE                           #
#############################################################

# retrieve the tree of interest
dst_tree = gDirectory.Get( 'dst' )

NTrig = dst_tree.GetEntriesFast()
NTrig = 2


trtel = CTATriggeredTel_ext.RTATelem.CTATriggeredTelescope("../conf/rta.stream", "", "out.raw")


for jtrig in xrange( NTrig ):
   nb = dst_tree.GetEntry( jtrig )
   if nb <= 0:
      continue

   print 'jtrig', jtrig 

   # N entries = N trig

   eventID = jtrig  # event ID starting from 0 (0,1,2,...)
   runNumber = dst_tree.runNumber
   eventNumber = dst_tree.eventNumber
   eventtype = dst_tree.eventtype
   ntel_dst = dst_tree.ntel
   ltrig = dst_tree.ltrig
   ntrig = dst_tree.ntrig
   ntel_data = dst_tree.ntel_data
   
   NTel_trig = dst_tree.ntel_data # Number of triggered telescopes

   #MC info
   MCprim = dst_tree.MCprim
   MCe0 = dst_tree.MCe0
   MCxcore = dst_tree.MCxcore
   MCycore = dst_tree.MCycore
   MCze = dst_tree.MCze
   MCaz = dst_tree.MCaz
   MCxoff = dst_tree.MCxoff
   MCyoff = dst_tree.MCyoff

   # 26536 elements (62 x 428)
   Paz = list(dst_tree.Paz)
   Pel = list(dst_tree.Pel)

   # 2550 elements 
   ltrig_list = list(dst_tree.ltrig_list)
   LTtime = list(dst_tree.LTtime)
   L2TrigType = list(dst_tree.L2TrigType)
   tel_data = list(dst_tree.tel_data)
   tel_zero_suppression = list(dst_tree.tel_zero_suppression)
   nL1trig = list(dst_tree.nL1trig)
   numSamples = list(dst_tree.numSamples)

   NTel_trig_id = tel_data  # ID of triggered telescopes

   print 'Number of triggered telescopes:', NTel_trig
   print 'ID of triggered telescopes:', NTel_trig_id
   
   
   NPixel_trig = np.zeros(NTel_trig) # Number of pixel of the triggered telescopes

   for jtel_trig in xrange(NTel_trig):
       where_NPixel_trig = np.where(np.array(TelID) == NTel_trig_id[jtel_trig])
       NPixel_trig[jtel_trig] = int(NPixel[where_NPixel_trig])
   
   print 'NPixel of triggered telescopes:', NPixel_trig
   print 'NSamples of triggered telescopes:', numSamples


   # 25500 elements 
   pulsetiminglevel_list = list(dst_tree.pulsetiminglevel)
   N_pulsetiminglevel = len(pulsetiminglevel_list)/NTel_trig  # number of pulse timing levels (10)

   pulsetiminglevel = np.zeros((NTel_trig, N_pulsetiminglevel))  #25500 total elements
   
   el_id = 0
   for jtel_trig in xrange(NTel_trig):
       for jpulse in xrange(N_pulsetiminglevel):
           el_id = jtel_trig*N_pulsetiminglevel + jpulse
           pulsetiminglevel[jtel_trig, jpulse] = pulsetiminglevel_list[el_id]


   # >7x10^7 elements 
   pulsetiming_list = list(dst_tree.pulsetiming) 
   FakePix_dim = len(pulsetiming_list)/(N_pulsetiminglevel*NTel_trig)   
   
   pulsetiming = np.zeros((NTel_trig, N_pulsetiminglevel, FakePix_dim)) #>7x10^7 total elements
   
   el_id = 0
   for jtel_trig in xrange(NTel_trig):
       for jpulse in xrange(N_pulsetiminglevel):
           for jpix in xrange(FakePix_dim):
	        el_id = N_pulsetiminglevel*FakePix_dim*jtel_trig + jpulse*FakePix_dim + jpix
		pulsetiming[jtel_trig, jpulse, jpix] = pulsetiming_list[el_id] 

   chan = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   recorded = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   L1trig = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   sum_dst = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   dead = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   zerosuppressed = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   sumwindow = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   sumfirst = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   tzero = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   Width = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements

   Max = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements
   HiLo = np.zeros((NTel_trig, FakePix_dim)) #7395000 total elements

   # 7395000 elements 
   chan_list = list(dst_tree.chan)
   recorded_list = list(dst_tree.recorded)
   L1trig_list = list(dst_tree.L1trig)
   sum_dst_list = list(dst_tree.sum)
   dead_list = list(dst_tree.dead)
   zerosuppressed_list = list(dst_tree.zerosuppressed)
   sumwindow_list = list(dst_tree.sumwindow)
   sumfirst_list = list(dst_tree.sumfirst)
   tzero_list = list(dst_tree.tzero)
   Width_list = list(dst_tree.Width)
   Max_list = list(dst_tree.Max)
   HiLo_list = list(dst_tree.HiLo)

   el_id = 0
   for jtel_trig in xrange(NTel_trig):
       for jpix in xrange(FakePix_dim):
           el_id = jtel_trig*FakePix_dim + jpix
           chan[jtel_trig, jpix] = chan_list[el_id]
           recorded[jtel_trig, jpix] = recorded_list[el_id]
           L1trig[jtel_trig, jpix] = L1trig_list[el_id]
           sum_dst[jtel_trig, jpix] = sum_dst_list[el_id]
           dead[jtel_trig, jpix] = dead_list[el_id]
           zerosuppressed[jtel_trig, jpix] = zerosuppressed_list[el_id]
           sumwindow[jtel_trig, jpix] = sumwindow_list[el_id]
           sumfirst[jtel_trig, jpix] = sumfirst_list[el_id]
           tzero[jtel_trig, jpix] = tzero_list[el_id]
           Width[jtel_trig, jpix] = Width_list[el_id]
           Max[jtel_trig, jpix] = Max_list[el_id]
           HiLo[jtel_trig, jpix] = HiLo_list[el_id]

   ###########################################################################################  
   #                   Trace = NTrig x NCamera x NPixel x N_slice
   ###########################################################################################  

    	
   Trace_list = list(dst_tree.Trace)

   MaxNSamples = len(Trace_list)/(NTel_trig*FakePix_dim)  # number of pulse timing levels (10)

   print 'Max number of samples:', MaxNSamples
   Trace = np.zeros((NTel_trig, FakePix_dim, MaxNSamples)) #NTel_trig x NPixel x NSamples 

   el_id = 0
   tot_slice_pix = 0

   for jtel_trig in xrange(NTel_trig):

       #trtel.setMetadata(1, convert_ext.convert(int(runNumber)), convert_ext.convert(int(jtrig)))
       #trtel.setNumberOfTriggeredTelescopes(convert_ext.convert(int(NTel_trig)))
       #trtel.setIndexOfCurrentTriggeredTelescopes(convert_ext.convert(int(jtel_trig)))

       #trtel.setTelescopeId(convert_ext.convert(int(NTel_trig_id[jtel_trig])));
       #trtel.setNumberOfPixels(convert_ext.convert(int(NPixel_trig[jtel_trig])))

       #testSlice = []
       #testPixel = []
       for jslice in xrange(MaxNSamples):
           for jpix in xrange(FakePix_dim):
               el_id = tot_slice_pix + jslice*FakePix_dim + jpix
               Trace[jtel_trig, jpix, jslice] = Trace_list[el_id] 
               #if (jpix==0): testSlice.append(Trace_list[el_id])
               #if (jslice==0): testPixel.append(Trace_list[el_id])

               #if (jpix<NPixel_trig[jtel_trig]): 
                  #trtel.setNumberOfSamples(convert_ext.convert(int(jpix)), convert_ext.convert(int(numSamples[jtel_trig])))
                  #trtel.setPixelId(convert_ext.convert(int(jpix)), convert_ext.convert(int(jpix)))
                  #if (jslice<numSamples[jtel_trig]):
                     #trtel.setSampleValue(convert_ext.convert(int(jpix)), convert_ext.convert(int(jslice)), convert_ext.convert(int(Trace_list[el_id])))

       tot_slice_pix = tot_slice_pix + MaxNSamples*FakePix_dim 
       #testSlice = testSlice[:int(numSamples[jtel_trig])]
       #testPixel = testPixel[:int(NPixel_trig[jtel_trig])]

       #trtel.writePacket();
       #trtel.printPacket_output();
    		
   # Packet in process
   for jtel_trig in xrange(NTel_trig):
       print 'Packet building for Event ID '+str(jtrig)+' and Telescope index '+str(jtel_trig)

       testSlice = []
       testPixel = []


       trtel.setMetadata(1, convert_ext.convert(int(runNumber)), convert_ext.convert(int(jtrig)))
       trtel.setNumberOfTriggeredTelescopes(convert_ext.convert(int(NTel_trig)))
       trtel.setIndexOfCurrentTriggeredTelescopes(convert_ext.convert(int(jtel_trig)))

       trtel.setTelescopeId(convert_ext.convert(int(NTel_trig_id[jtel_trig])));
       trtel.setNumberOfPixels(convert_ext.convert(int(NPixel_trig[jtel_trig])))

       for jpix in xrange(int(NPixel_trig[jtel_trig])):
           trtel.setNumberOfSamples(convert_ext.convert(int(jpix)), convert_ext.convert(int(numSamples[jtel_trig])))
           trtel.setPixelId(convert_ext.convert(int(jpix)), convert_ext.convert(int(jpix)))

           for jslice in xrange(int(numSamples[jtel_trig])):
               trtel.setSampleValue(convert_ext.convert(int(jpix)), convert_ext.convert(int(jslice)), convert_ext.convert(int(Trace[jtel_trig, jpix, jslice])))
 
               if (jpix==0): testSlice.append(Trace[jtel_trig, jpix, jslice])
               if (jslice==0): testPixel.append(Trace[jtel_trig, jpix, jslice])
       
       trtel.writePacket();
       trtel.printPacket_output();

       # Plotting
       xslice = range(int(numSamples[jtel_trig]))
       xpixel = range(int(NPixel_trig[jtel_trig]))
        
       ax1.clear()
       ax1.bar(xslice, testSlice, linewidth=1.0)
       ax1.set_xlim(0,40)
       ax1.set_ylim(50,200)
       ax1.set_xlabel('Sample number')
       ax1.set_ylabel('FADC (Pixel 0)')
       ax1.set_title('Event = '+str(jtrig)+', TelID = '+str(NTel_trig_id[jtel_trig])+', PixelID = 0')


       ax2.clear()
       ax2.bar(xpixel, testPixel, linewidth=1.0, color='r')
       ax2.set_xlim(0,1855)
       ax2.set_ylim(0,200)
       ax2.set_xlabel('Pixel number')
       ax2.set_ylabel('FADC (sample 0)')

       ax2.set_title('Event = '+str(jtrig)+', TelID = '+str(NTel_trig_id[jtel_trig])+', Sample = 0')

       if (jtrig==1): plt.savefig('testSlice_'+str(NTel_trig_id[jtel_trig])+'.png')

       plt.pause(0.00000000000000000000000000000000000000000001)
       plt.draw()

