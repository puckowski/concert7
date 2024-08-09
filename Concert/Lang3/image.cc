import image;
import math;

string inputFile;
inputFile = "castle.jpg";

string imgData1 = "imgData1";
call read_channel_data : inputFile, imgData1;

int imageChannelLength = imgData1.width * imgData1.height;
println "Width x Height: ", imgData1.width, " ", imgData1.height;
println "Image channel length: ", imageChannelLength;
int outputLength = imageChannelLength * 3;

int homogeneityOutput outputLength;

int imageInput imageChannelLength;

function collapseChannels : using imageInput, using imgData1.red, using imgData1.green, using imgData1.blue, int as length;
	int index = 0;
	int accum;
	
	while index < length;
		accum = 0;
		
		accum += red[index];
		accum += green[index];
		accum += blue[index];
		
		accum = accum / 3;
		
		imageInput[index] = accum;
		
		index = index + 1;
		
		int mod = index % 1000;
		
		if mod == 0;
			println index;
		end;
	end;
return;

call collapseChannels : imageInput, imgData1.red, imageData1.green, imageData1.blue, imageChannelLength;

int high;
int new_hi;
int new_low;
int userThreshold;

userThreshold = 40;
high = userThreshold;

new_hi = 255;
new_low = 0;

function process : using imageInput, using homogeneityOutput, int as start, int as endIndex, using inputWidth;
	lock m;
	int rowStart;
	int colStart;
	
	int rowEnd;
	int colEnd;
	
	rowStart = start + 1; 
	rowEnd = endIndex - 1;
	unlock m;

	colEnd = inputWidth;

	int maxDiff;

	int aStart;
	int aEnd;
	int bStart;
	int bEnd;

	aEnd = 1;
	bEnd = 1;

	int index;
	int diff;
	int diff2;

	int tempRow;
	
	while rowStart <= rowEnd;
		colStart = 1;

		while colStart < colEnd;				
			maxDiff = 0;

			aStart = -1;
			bStart = -1;

			while aStart <= aEnd;
				while bStart <= bEnd;
					index = rowStart * inputWidth;
					index = index - inputWidth;
					index = index + colStart;
					
					diff = imageInput[index];

					index = (rowStart + aStart) * inputWidth;
					index = index - inputWidth;
					index = index + (colStart + bStart);
					
					diff2 = imageInput[index];

					diff = diff - diff2;
					call absolute_value : diff -> diff;

					if diff > maxDiff;
						maxDiff = diff;
					end;

					bStart = bStart + 1;
				end;

				aStart = aStart + 1;
				bStart = -1;
			end;
			
			index = rowStart * inputWidth;
			index = index - inputWidth;
			index = index + colStart;
			
			homogeneityOutput[index] = maxDiff;

			colStart = colStart + 1;
		end;

		rowStart = rowStart + 1;
	end;
return;

int targetNumberOfThreads;
targetNumberOfThreads = 4;

mutex m;

function createThreads : int as targetNumberOfThreads, using imgData1, using imageInput, using homogeneityOutput;
	int rowsPerThread = imgData1.height;
	int inputWidth = imgData1.width;
	rowsPerThread = rowsPerThread / targetNumberOfThreads;
	int start = 1;
	int endIndex = rowsPerThread;
		
	int numberOfThreads = 0;
	int oneLessThanTarget = targetNumberOfThreads - 1;
	
	while numberOfThreads < targetNumberOfThreads;
		if numberOfThreads < oneLessThanTarget;
			endIndex = endIndex + 1;
		end;
		
		detach process : imageInput, homogeneityOutput, start, endIndex, inputWidth;
		
		if numberOfThreads < oneLessThanTarget;
			endIndex = endIndex - 1;
		end;
		
		numberOfThreads = numberOfThreads + 1;
		
		start = endIndex;
		endIndex = endIndex + rowsPerThread;
		println endIndex;
	end;
return;

println "Starting...";

join createThreads : targetNumberOfThreads, imgData1, imageInput, homogeneityOutput;

println "Writing homogeneity array...";

object out1;
int out1.red imageChannelLength;
int out1.green imageChannelLength;
int out1.blue imageChannelLength;
int out1.width 1;
out1.width = imgData1.width;
int out1.height 1;
out1.height = imgData1.height;

int hi = 0;
int lastRow = imageChannelLength - out1.width;
int widthMinusOne = out1.width - 1;

while hi < imageChannelLength;
	if hi < out1.width;
		out1.red[hi] = 0;
		out1.green[hi] = 0;
		out1.blue[hi] = 0;
	
		hi = hi + 1;
		
		continue;
	end;

	if hi >= lastRow;
		out1.red[hi] = 0;
		out1.green[hi] = 0;
		out1.blue[hi] = 0;
	
		hi = hi + 1;
	
		continue;
	end;
	
	int mod = hi % out1.width;
	
	if mod == 0;
		out1.red[hi] = 0;
		out1.green[hi] = 0;
		out1.blue[hi] = 0;
	
		hi = hi + 1;
		
		continue;
	end;
	
	if mod == widthMinusOne;
		out1.red[hi] = 0;
		out1.green[hi] = 0;
		out1.blue[hi] = 0;
	
		hi = hi + 1;
		
		continue;
	end;
	
	out1.red[hi] = homogeneityOutput[hi];
	out1.green[hi] = homogeneityOutput[hi];
	out1.blue[hi] = homogeneityOutput[hi];
	
	hi = hi + 1;
end;

string outputFile = "homogeneity_test.jpg";
int writeResult = 0;
call write_channel_data : outputFile, "out1" -> writeResult;

println "Write result: ", writeResult;

println "Done.";