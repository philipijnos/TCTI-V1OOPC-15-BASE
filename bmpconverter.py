#====================================================================
#
#       Created by Philippe Zwietering
#
#====================================================================
import binascii

#Aangezien er geen goede functie is die integers omzet naar binair in stringformaat waarbij overbodige nullen bewaard blijven,
#heb ik er maar zelf een gemaakt, want dat is verderop echt nodig.
def int2bin(input):
    table = ["0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"]
    output = ""
    for i in range(len(input)):
        output += table[int(input[i], 16)]
    return output

filename = "upton.bmp"
with open(filename, 'rb') as f:
    content = f.read()
hC = str(binascii.hexlify(content))[2:-1]       #hC == hexContent

if hC[:4] != "424d":
    print("Dit bestand is ongeldig. Voer een correct bestand in.")
else:
    bitmapBase = int(hC[58:60]+hC[56:58], 16)
    if bitmapBase != 1 and bitmapBase != 4 and bitmapBase != 8:
        print("Dit script ondersteunt alleen 1-, 4- en 8-bits bitmaps.")
    else:
        colorAmount = pow(2, bitmapBase)
        imageOffset = int(hC[26:28]+hC[24:26]+hC[22:24]+hC[20:22], 16)
        imageWidth = int(hC[42:44]+hC[40:42]+hC[38:40]+hC[36:38], 16)
        imageHeight = int(hC[50:52]+hC[48:50]+hC[46:48]+hC[44:46], 16)
        dibHeaderLength = 2 * int(hC[34:36]+hC[32:34]+hC[30:32]+hC[28:30], 16)
        hL = 28+dibHeaderLength         #hL == headerLength
        colorTable = []
        imageTable = []
        for i in range(colorAmount):
            colorDummy = (int(hC[hL+8*i:hL+2+8*i], 16), int(hC[hL+2+8*i:hL+4+8*i], 16), int(hC[hL+4+8*i:hL+6+8*i], 16))
            if colorDummy[0] < 129 and colorDummy[1] < 129 and colorDummy[2] < 129:
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
                    imageTable.append("{"+str(x)+", "+str(y)+", "+colorTable[int(dataDummy[x])]+"}")
        elif bitmapBase == 4:
            if imageWidth % 8 == 0:
                dataWidth = imageWidth
            else:
                dataWidth = (imageWidth//8)*8+8
            for y in range(imageHeight):
                dataDummy = bmpData[dataLength-(y+1)*dataWidth:dataLength-y*dataWidth]
                for x in range(imageWidth):
                    imageTable.append("{"+str(x)+", "+str(y)+", "+colorTable[int(dataDummy[x], 16)]+"}")
        elif bitmapBase == 8:
            if imageWidth % 8 == 0:
                dataWidth = imageWidth
            else:
                dataWidth = (imageWidth//8)*8+8
            for y in range(imageHeight):
                dataDummy = bmpData[dataLength-(y+1)*dataWidth:dataLength-y*dataWidth]
                for x in range(imageWidth):
                    imageTable.append("{"+str(x)+", "+str(y)+", "+colorTable[int(dataDummy[2*x:2*x+2], 16)]+"}")
        if imageTable:
            outputStringDummy = "("+str(imageWidth)+", "+str(imageHeight)+");\n"+str(imageTable)+";\n"
            outputString = ""
            for c in outputStringDummy:
                if c != "'":
                    if c == "[":
                        outputString += "{"
                    elif c == "]":
                        outputString += "}"
                    else:
                        outputString += c
            file = open("imagestring.txt", "w")
            #file.write('#include "hwlib.hpp"\n#include "image.hpp\nint main(void){\n"')
            #file.write('\t//kill the watchdog\n\tWDT->WDT_MR = WDT_MR_WDDIS;')
            file.write(outputString)
            file.close()