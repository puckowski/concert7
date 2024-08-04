[Home](https://github.com/puckowski/concert7/blob/master/) <span>&emsp;</span> [Standard library](https://github.com/puckowski/concert7/blob/master/standard_library/standard_library.md)

# Image library

Provides standard image functions. Since 9.5.beta.

## Import

The following statement may be used to import the image library:

```cpp
import image;
```

## Functions

| Name                 | Description                                                                         |
|:---------------------|:------------------------------------------------------------------------------------|
| read_channel_data    | Read RGB channel data, width, and height from a JPEG image into an object.          |
| write_channel_data   | Write RGB channel data with optional quality using data from an object into a JPEG. |

## Examples

### read_channel_data

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

```cpp
int writeResult = 0;
int outputQuality = 90;
call write_channel_data : "out.JPG", "imgData1", outputQuality -> writeResult;
println "Image write result: ", writeResult;
```
