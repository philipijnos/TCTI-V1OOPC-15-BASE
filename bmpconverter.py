# =================================================================================
# 			Bmpconverter script
#
#           Copyright Philippe Zwietering 2016.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)
#
# =================================================================================
import binascii

#This function converts a string of integers into binary data.
def int2bin(input):
    table = ["0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"]
    output = ""
    for i in range(len(input)):
        output += table[int(input[i], 16)]
    return output

#This function returns the dimensions of a bitmap file
def bmpdimensions(filename):
    with open(filename, 'rb') as f:
        content = f.read()
    hC = str(binascii.hexlify(content))[2:-1]       #hC == hexContent
    if hC[:4] != "424d":
        print("This file is not allowed. Please use a correct file.")
        return 0
    else:
        bitmapBase = int(hC[58:60]+hC[56:58], 16)
        if bitmapBase != 1 and bitmapBase != 4 and bitmapBase != 8:
            print("This script only supports 1-, 4- and 8-bits bitmaps.")
            return 0
        else:
            imageWidth = int(hC[42:44]+hC[40:42]+hC[38:40]+hC[36:38], 16)
            imageHeight = int(hC[50:52]+hC[48:50]+hC[46:48]+hC[44:46], 16)
    return "("+str(imageWidth)+", "+str(imageHeight)+", "+filename[:-4]+"array);"

#This function converts a bitmap to an array of pixels.
def bmp2array(filename):
    with open(filename, 'rb') as f:
        content = f.read()
    hC = str(binascii.hexlify(content))[2:-1]       #hC == hexContent
    if hC[:4] != "424d":
        print("This file is not allowed. Please use a correct file.")
        return 0
    else:
        bitmapBase = int(hC[58:60]+hC[56:58], 16)
        if bitmapBase != 1 and bitmapBase != 4 and bitmapBase != 8:
            print("This script only supports 1-, 4- and 8-bits bitmaps.")
            return 0
        else:
            colorAmount = pow(2, bitmapBase)
            # imageOffset = int(hC[26:28]+hC[24:26]+hC[22:24]+hC[20:22], 16)
            imageWidth = int(hC[42:44]+hC[40:42]+hC[38:40]+hC[36:38], 16)
            imageHeight = int(hC[50:52]+hC[48:50]+hC[46:48]+hC[44:46], 16)
            dibHeaderLength = 2 * int(hC[34:36]+hC[32:34]+hC[30:32]+hC[28:30], 16)
            hL = 28+dibHeaderLength         #hL == headerLength
            colorTable = []
            imageTable = []
            for i in range(colorAmount):
                colorDummy = (int(hC[hL+8*i:hL+2+8*i], 16), int(hC[hL+2+8*i:hL+4+8*i], 16), int(hC[hL+4+8*i:hL+6+8*i], 16))
                if colorDummy[0]< 129 and colorDummy[1] < 129 and colorDummy[2] < 129:
                    colorTable.append("1")
                else:
                    colorTable.append("0")
            bmpData = hC[hL+8+8*(colorAmount-1):]
            dataLength = len(bmpData)
            if bitmapBase == 1:
                if imageWidth % 32 == 0:
                    dataWidth = int(imageWidth/32*8)
                else:
                    dataWidth = ((imageWidth//32)+1)*8
                for y in range(imageHeight):
                    dataDummy = int2bin(bmpData[dataLength-(y+1)*dataWidth:dataLength-y*dataWidth])
                    for x in range(imageWidth):
                        imageTable.append("{"+str(x)+","+str(y)+","+str(colorTable[int(dataDummy[x])])+"}")
            elif bitmapBase == 4:
                if imageWidth % 8 == 0:
                    dataWidth = imageWidth
                else:
                    dataWidth = (imageWidth//8)*8+8
                for y in range(imageHeight):
                    dataDummy = bmpData[dataLength-(y+1)*dataWidth:dataLength-y*dataWidth]
                    for x in range(imageWidth):
                        imageTable.append("{"+str(x)+","+str(y)+","+str(colorTable[int(dataDummy[x], 16)])+"}")
            elif bitmapBase == 8:
                if imageWidth % 8 == 0:
                    dataWidth = imageWidth*2
                else:
                    dataWidth = ((imageWidth//8)*8+8)*2
                for y in range(imageHeight):
                    dataDummy = bmpData[dataLength-(y+1)*dataWidth:dataLength-y*dataWidth]
                    for x in range(imageWidth):
                        if dataDummy[2*x:2*x+2] != '':
                            imageTable.append("{"+str(x)+","+str(y)+","+str(colorTable[int(dataDummy[2*x:2*x+2], 16)])+"}")
            if imageTable:
                outputStringDummy = str(imageTable)+";"
                outputString = ""
                for c in outputStringDummy:
                    if c != "'":
                        if c == "[":
                            outputString += "{"
                        elif c == "]":
                            outputString += "}"
                        else:
                            outputString += c
                return outputString
            else:
                print("This file is totally empty, there is nothing to show.")
                return 0

profoutput = bmp2array("prof.bmp")
profdimensions = bmpdimensions("prof.bmp")
hulogooutput = bmp2array("hulogo.bmp")
hulogodimensions = bmpdimensions("hulogo.bmp")

paint1output = bmp2array("paint1.bmp")
paint1dimensions = bmpdimensions("paint1.bmp")
paint2output = bmp2array("paint2.bmp")
paint2dimensions = bmpdimensions("paint2.bmp")

file = open("ImageShower/main.cpp", "w")
file.write('#include "hwlib.hpp"\n#include "image.hpp"\nint main(void){\n\tWDT->WDT_MR = WDT_MR_WDDIS;//Killing the watchdog\n\thwlib::wait_ms(1000);\n\t')
file.close()
file = open("ImageShower/main.cpp", "a")

# file.write('int profarray[][3] = '+str(profoutput)+'\n\t')
# file.write('image prof'+str(profdimensions)+'\n\tprof.draw();\n\thwlib::wait_ms(5000);\n\t')
# file.write('int hulogoarray[][3] = '+str(hulogooutput)+'\n\timage hulogo'+str(hulogodimensions)+'\n\t')
# file.write('hulogo.draw(hwlib::location{64, 0});\n\thwlib::wait_ms(5000);\n\tinvert inverthulogo(hulogo);\n\t')
# file.write('inverthulogo.draw();\n\thwlib::wait_ms(5000);\n\t')
# file.write('imagepart partinverthulogo(inverthulogo, 28, 64);\n\tpartinverthulogo.draw(hwlib::location{32, 0});\n')

file.write('int paint1array[][3] = '+str(paint1output)+'\n\timage paint1'+str(paint1dimensions)+'\n\tpaint1.draw();')
file.write('hwlib::wait_ms(5000);\n\t')
file.write('int paint2array[][3] = '+str(paint2output)+'\n\timage paint2'+str(paint2dimensions)+'\n\t')
file.write('invert invertpaint2(paint2);\n\tinvertpaint2.draw();\n')
file.write("}")
file.close()