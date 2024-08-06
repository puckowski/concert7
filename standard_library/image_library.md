[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Standard library](https://github.com/puckowski/concert7/blob/master/standard_library/standard_library.md)

# Image library

Provides standard image functions. 

| Version              | Extensions (Ignoring case) |
|:---------------------|:---------------------------|
| 9.5.beta             | .jpg, .jpeg                |
| 9.5.rc               | .jpg, .jpeg, .png         |

## Import

The following statement may be used to import the image library:

```cpp
import image;
```

## Functions

| Name                 | Description                                                                            |
|:---------------------|:---------------------------------------------------------------------------------------|
| read_channel_data    | Read (A)RGB channel data, width, and height from a JPEG image into an object.          |
| write_channel_data   | Write (A)RGB channel data with optional quality using data from an object into a JPEG. |

## Examples

### read_channel_data

Creates an object with ```width``` int, ```height``` int, ```red``` int array, ```green``` int array, ```blue``` int array, and ```alpha``` int array.
The ```alpha``` int array is only defined when reading images with extension ```.png```.

```cpp
string imgData1 = "imgData1";
call read_channel_data : "1Hill.JPG", imgData1;

int redIdx = 0;
int imageChannelLength = imgData1.width * imgData1.height;
println "Width x Height: ", imgData1.width, " ", imgData1.height;
println "Image channel length: ", imageChannelLength;
int redLength = 0;
sizeof imgData1.red redLength;
println "Size of red channel: ", redLength;

while redIdx < imageChannelLength;
	print imgData1.red[redIdx], ", ";
	redIdx += 1;
	
	if redIdx > 100;
		break;
	end;
end;

println "";
```

### write_channel_data

Arguments:

```
filename: string, channelObjectName: string, outputQuality?: number
```

The ```outputQuality``` argument is optional for ```.jpg``` and ```.jpeg``` extensions, and should not be provided for ```.png``` extensions.

```cpp
int writeResult = 0;
int outputQuality = 90;
call write_channel_data : "out.JPG", "imgData1", outputQuality -> writeResult;
println "Image write result: ", writeResult;
```
