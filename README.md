# LSB-Steganography
 Encoding secret data in lsb bits of a .bmp file.

## Abstarct:

Steganography is the art of hiding the fact that communication is taking place, by hiding information in other information. Many different carrier file formats can be used, but digital images are the most popular because of their frequency on the internet. For hiding secret information in images, there exists a large variety of steganography techniques some are more complex than others and all of them have respective strong and weak points. Different applications may require absolute invisibility of the secret information, while others require a large secret message to be hidden. <br />

Steganography is the practice of hiding private or sensitive information within something that appears to be nothing out to the usual. Steganography is often confused with cryptology because the two are similar in the way that they both are used to protect important information. The difference between two is that steganography involves hiding information so it appears that no information is hidden at all. If a person or persons views the object that the information is hidden inside of he or she will have no idea that there is any hidden information, therefore the person will not attempt to decrypt the information.<br />

What steganography essentially does is exploit human perception, human senses are not trained to look for files that have information inside of them, although this software is available that can do what is called Steganography. The most common use of steganography is to hide a file inside another file.<br /><br />

## LSB Bit Steganography
The type of steganography implemented by encoding the information in the LSB bit of carrier file data, in a way that does not affect the carrier output 
noticeably. <br />
Image files are composed of digital data in pixel formats that can be rasterized for use on a computer display or printer. It may store data in uncompressed,
compressed, or vector formats. Once rasterized, an image becomes a grid of pixels, each of which has a number of bits to designate its color equal to the color depth of the device displaying it.<br />
The colours of each pixel defined by the RGB data present in the image file. Each pixel colour data consists of RGB values with a magnitude one byte for each colour. So that one pixel has 3 bytes of RGB information to display the image. <b>The change in Least significant bit of a RGB data bytes affects the overall output minimally, which is undetectable with human eyes in the case of image file.</b><br />
<p align="left">
<img src="https://github.com/mshibili/LSB-Steganography/blob/main/1-References/ChangeInLsb.png" alt="LSB change" title="LSB change" >
</p>
We will take each colour info Byte and replace the last bit with secret information to be encoded.<br />
<b> Why .bmp ? </b><br />
The BMP file format (Windows bitmap) handles graphic files within the Microsoft Windows OS. Typically, BMP files are uncompressed, and therefore
large and lossless; their advantage is their simple structure and wide acceptance in Windows programs.<br />
<p align="left">
<img src="https://github.com/mshibili/LSB-Steganography/blob/main/1-References/bmpConfig.png" alt="bmp Overview" title=".bmp Overview" >
</p>


## Requirements:<br />

    • The application accept an image file say .bmp along with the a text file which contains the message to be steged
    • Analize the size of the message file and the data part of the .bmp file to check whether the messsage could fit in the provided .bmp image.
    • Provide a option to steg a magic string which could be usefull to identify whether the image is steged or not.
    • The appliaction should provide a option to decrpt the file. 
    • This has to be an command line apliaction and all the options has to be passed as an command line argument.

## Pre-requisite:
    • Knowledge of encryption and decryption.
    • File I/O.
    • Pointers and Structures.

## Design:
<p align="left">
<img src="https://github.com/mshibili/LSB-Steganography/blob/main/3-Design/ls_fc.jpg" alt="Design Overview" title="Design Overview" >
</p>

## Source Code:
Find the source files here - https://github.com/mshibili/LSB-Steganography/tree/main/4-SkeletonCode <br />

## Sample Outputs:
<p align="left">
<img src="https://github.com/mshibili/LSB-Steganography/blob/main/2-OutputImages/Decode_out.png" alt="Decode_out" title="Decode_out" >
</p>
<p align="left">
<img src="https://github.com/mshibili/LSB-Steganography/blob/main/2-OutputImages/Encode_out.png" alt="Encode_out" title="Encode_out" >
</p>
<p align="left">
<img src="https://github.com/mshibili/LSB-Steganography/blob/main/2-OutputImages/HexChange.png" alt="HexChange" title="HexChange" >
</p> <br />

## References:
https://en.wikipedia.org/wiki/Steganography <br />
https://en.wikipedia.org/wiki/BMP
