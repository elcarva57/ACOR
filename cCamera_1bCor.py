# Filename: cCamera_1b.py

import time
import os
import win32com.client

LIGHT_PATH = r"c:\\inetpub\\"
ERROR = True
NOERROR = False

##------------------------------------------------------------------------------
## Class: cCamera
##------------------------------------------------------------------------------
class cCamera:
    """
    Implements command and control of a CCD camera using MaxIm DL
    Professional.  All functions verified using version 5.08 of MaxIm DL.

    """
    def __init__(self):
        """
        Establishes the connection to MaxIm DL CCDCamera object.  Verifies
        the link has been established. Note: Open MaxIm DL and manually
        establish the camera link prior to running this script.

        """
        print "Connecting to ACOR..."
        self.__CAMERA = win32com.client.Dispatch("RocPcServidor.CCD1")
        self.__CAMERA.DisableAutoShutdown = True
        try:
            self.__CAMERA.LinkEnabled = True
        except:
            print "... cannot connect to camera"
            print "--> Is camera hardware attached?"
            print "--> Is some other application already using camera hardware?"
            raise EnvironmentError, 'Halting program'
        if not self.__CAMERA.LinkEnabled:
            print "... camera link DID NOT TURN ON; CANNOT CONTINUE"
            raise EnvironmentError, 'Halting program'

    def generateFilename(self,path,baseName):
        """
        Generates a filename in the form basename plus '_' plus a five digit
        sequence number (ex. m51_L_00025.fit where basename is 'm51_L').
        Converts any ':', '\', or ' ' in basename to '_'.

        Arguments:
            path: image directory path
            baseName: image file basename (string)

        Returns:
            path and filename
            
        """
        # path is the path to where the file will be saved
        baseName.replace(':', '_')      # colons become underscores
        baseName.replace(' ', '_')      # blanks become underscores
        baseName.replace('\\', '_')     # backslash becomes underscore
        # make sure the base filename has an '_' at the end
        if not baseName.endswith("_"):
            baseName = baseName + "_"
        # add 1 to use next available number
        seqMax = self.getSequenceNumber(path,baseName) 
        seqNext = seqMax + 1
        filename = "%s%s%05d.fit" % (path,baseName,seqNext)
        return filename

    def getSequenceNumber(self,path,baseName):
        """
        Scans all filenames in the image directory, finds files with starting
        filename that matches the baseName and returns the highest sequence
        number of a matching filename.

        Arguments:
            path: image directory path
            baseName: image file baseName (string)

        Returns:
            highest sequence number found (int)

        """
        # get a list of files in the image directory
        col = os.listdir(path)
        # Loop over these filenames and see if any match the basename
        retValue = 0
        for name in col:
            front = name[0:-9]
            back = name[-9:]
            if front == baseName:
                # baseName match found, now get sequence number for this file
                seqString = name[-9:-4]  # get last 5 chars of name (seq number)
                try:
                    seqInt = int(seqString)
                    if seqInt > retValue:
                        retValue = seqInt    # store greatest sequence number
                except:
                    pass
        return retValue

    def exposeLight(self,length,filterSlot,name):
        """
        Initiates an image exposure.  Waits for exposure and image download
        to complete then saves the image to the directory specified by the
        constant LIGHT_PATH.

        Arguments:
            length: time (in seconds) for the exposure
            filterslot: zero-based location of the filter to be used
                        (0 is filter in slot 1, 1 is filter in slot 2,...)
            name: base name of the image's filename

        Returns:
            Nothing

        """
        print "Exposing light frame..."
        self.__CAMERA.Expose(length,0,filterSlot)
        while not self.__CAMERA.ImageReady:
            time.sleep(1)
        print "Light frame exposure and download complete!"
        # save image
        filename = self.generateFilename(LIGHT_PATH,name)
        print "Saving light image -> %s" % filename
        self.__CAMERA.SaveImage(filename)

    def setFullFrame(self):
        """
        Sets camera in full-frame mode (cancels any sub-frame setup)

        """
        self.__CAMERA.SetFullFrame()
        print "Camera set to full-frame mode"
        
    def setBinning(self,binmode):
        """
        Sets binning of camera

        Arguments:
            binmode: Integers 1, 2, or 3 are valid (1=1x1,2=2x2,3=3x3)

        Returns:
            True: if error occurred
            False: if no errors
        
        """
        tup = (1,2,3)
        if binmode in tup:
            self.__CAMERA.BinX = binmode
            self.__CAMERA.BinY = binmode
            print "Camera binning set to %dx%d" % (binmode,binmode)
            return NOERROR
        else:
            print "ERROR: Invalid binning specified"
            return ERROR

##
##    END OF 'cCamera' Class
##

if __name__ == "__main__":

    # Create an instance of the cCamera class
    testCamera = cCamera()

    # Setup MaxIm DL to take a full frame image 
    testCamera.setFullFrame()
    # Setup binning for 2x2
    if not testCamera.setBinning(2):
        for i in range(4):
            # Expose filter slot 0 (Red) for 3 seconds
            testCamera.exposeLight(5,0,'m51_R_2x2')
    else:
        print "Images not taken due to previous error"
    
