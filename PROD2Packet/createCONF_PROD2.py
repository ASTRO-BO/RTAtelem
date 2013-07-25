from ROOT import *
import numpy as np
import matplotlib.pyplot as plt

import pyfits

plt.ion()

# open the file
myfile = TFile( '/home/rta/Projects/PROD2/Aar.prod2.a2.root' )
myfile.ls()

#############################################################
#                CONFIGURATION TREE                         #
#############################################################

# retrieve the tree of interest
conf_tree = gDirectory.Get( 'telconfig' )

NTel = conf_tree.GetEntriesFast()
print 'Number of telescopes:', NTel

TelID = []
TelType = []
TelX = []
TelY = []
TelZ = []
FocalLength = []
FOV = []
CameraScaleFactor = []
CameraCentreOffset = []
CameraRotation = []
NPixel = []
NPixel_active = []
NSamples = []
Sample_time_slice = []
NGains = []
HiLoScale = []
HiLoThreshold = []
HiLoOffset = []

XTubeMM = np.zeros(NTel, dtype=np.object)
YTubeMM = np.zeros(NTel, dtype=np.object)
RTubeMM = np.zeros(NTel, dtype=np.object)
XTubeDeg = np.zeros(NTel, dtype=np.object)
YTubeDeg = np.zeros(NTel, dtype=np.object)
RTubeDeg = np.zeros(NTel, dtype=np.object)
TubeOFF = np.zeros(NTel, dtype=np.object)

NTubesOFF = []
NMirrors = []
MirrorArea = []

for jtel in xrange( NTel ):
   nb = conf_tree.GetEntry( jtel )
   if nb <= 0:
      continue

   TelID.append(conf_tree.TelID)
   TelType.append(conf_tree.TelType)
   TelX.append(conf_tree.TelX)
   TelY.append(conf_tree.TelY)
   TelZ.append(conf_tree.TelZ)
   FocalLength.append(conf_tree.FocalLength)
   FOV.append(conf_tree.FOV)
   CameraScaleFactor.append(conf_tree.CameraScaleFactor)
   CameraCentreOffset.append(conf_tree.CameraCentreOffset)
   CameraRotation.append(conf_tree.CameraRotation)
   NPixel.append(conf_tree.NPixel)
   NPixel_active.append(conf_tree.NPixel_active)
   NSamples.append(conf_tree.NSamples)
   Sample_time_slice.append(conf_tree.Sample_time_slice)
   NGains.append(conf_tree.NGains)
   HiLoScale.append(conf_tree.HiLoScale)
   HiLoThreshold.append(conf_tree.HiLoThreshold)
   HiLoOffset.append(conf_tree.HiLoOffset)
   NTubesOFF.append(conf_tree.NTubesOFF)
   NMirrors.append(conf_tree.NMirrors)
   MirrorArea.append(conf_tree.MirrorArea)


   XTubeMM_list = list(conf_tree.XTubeMM)
   YTubeMM_list = list(conf_tree.YTubeMM)
   RTubeMM_list = list(conf_tree.RTubeMM)
   XTubeDeg_list = list(conf_tree.XTubeDeg)
   YTubeDeg_list = list(conf_tree.YTubeDeg)
   RTubeDeg_list = list(conf_tree.RTubeDeg)

   TubeOFF_list = list(conf_tree.TubeOFF)

   NPixel_current = int(conf_tree.NPixel)

   XTubeMM[jtel] = XTubeMM_list
   YTubeMM[jtel] = YTubeMM_list
   RTubeMM[jtel] = RTubeMM_list
   XTubeDeg[jtel] = XTubeDeg_list
   YTubeDeg[jtel] = YTubeDeg_list
   RTubeDeg[jtel] = RTubeDeg_list
   TubeOFF[jtel] = TubeOFF_list


colTelID = pyfits.Column(name='TelID', format='I', array=TelID)
colTelType = pyfits.Column(name='TelType', format='D', array=TelType)
colTelX = pyfits.Column(name='TelX', format='D', array=TelX)
colTelY = pyfits.Column(name='TelY', format='D', array=TelY)
colTelZ = pyfits.Column(name='TelZ', format='D', array=TelZ)
colFocalLength = pyfits.Column(name='FL', format='D', array=FocalLength)
colFOV = pyfits.Column(name='FOV', format='D', array=FOV)
colCameraScaleFactor = pyfits.Column(name='CameraScaleFactor', format='D', array=CameraScaleFactor)
colCameraCentreOffset = pyfits.Column(name='CameraCentreOffset', format='D', array=CameraCentreOffset)
colCameraRotation = pyfits.Column(name='CameraRotation', format='D', array=CameraRotation)
colNPixel = pyfits.Column(name='NPixel', format='D', array=NPixel)
colNPixel_active = pyfits.Column(name='NPixel_active', format='D', array=NPixel_active)
colNSamples = pyfits.Column(name='NSamples', format='D', array=NSamples)
colSample_time_slice = pyfits.Column(name='Sample_time_slice', format='D', array=Sample_time_slice)
colNGains = pyfits.Column(name='NGains', format='D', array=NGains)
colHiLoScale = pyfits.Column(name='HiLoScale', format='D', array=HiLoScale)
colHiLoThreshold = pyfits.Column(name='HiLoThreshold', format='D', array=HiLoThreshold)
colHiLoOffset = pyfits.Column(name='HiLoOffset', format='D', array=HiLoOffset)

max_NPixel = max(NPixel)
print 'Maximum number of Pixels:', max_NPixel
colXTubeMM = pyfits.Column(name='XTubeMM', format='PD('+str(max_NPixel)+')', array=XTubeMM)
colYTubeMM = pyfits.Column(name='YTubeMM', format='PD('+str(max_NPixel)+')', array=YTubeMM)
colRTubeMM = pyfits.Column(name='RTubeMM', format='PD('+str(max_NPixel)+')', array=RTubeMM)
colXTubeDeg = pyfits.Column(name='XTubeDeg', format='PD('+str(max_NPixel)+')', array=XTubeDeg)
colYTubeDeg = pyfits.Column(name='YTubeDeg', format='PD('+str(max_NPixel)+')', array=YTubeDeg)
colRTubeDeg = pyfits.Column(name='RTubeDeg', format='1PD('+str(max_NPixel)+')', array=RTubeDeg)

colNTubesOFF = pyfits.Column(name='NTubesOFF', format='D', array=NTubesOFF)
colTubeOFF = pyfits.Column(name='TubeOFF', format='PD('+str(max_NPixel)+')', array=TubeOFF)
colNMirrors = pyfits.Column(name='NMirrors', format='D', array=NMirrors)
colMirrorArea = pyfits.Column(name='MirrorArea', format='D', array=MirrorArea)


conf_cols = pyfits.ColDefs([colTelID, colTelType, colTelX, colTelY,colTelZ,colFocalLength, colFOV, colCameraScaleFactor, colCameraCentreOffset,colCameraRotation, colNPixel,colNPixel_active, colNSamples, colSample_time_slice, colNGains,colHiLoScale, colHiLoThreshold, colHiLoOffset, colXTubeMM, colYTubeMM, colRTubeMM, colXTubeDeg, colYTubeDeg, colRTubeDeg, colNTubesOFF, colTubeOFF, colNMirrors, colMirrorArea])


conf_tbhdu = pyfits.new_table(conf_cols)
conf_tbhdu.writeto('PROD2_telconfig.fits.gz', clobber=1)



