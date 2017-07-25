#include <stdio.h>
#include <stdlib.h>

/**
	Supported formats
*/
typedef enum videoFormat{ UYVY422, YUVp422, YUVp420, YV12 } VIDEO_FORMAT;
typedef enum status{ FAILURE = -1, SUCCESS = 0, END_OF_FILE = 2} STATUS;

/**
	Structure to hold YUV video details
*/
typedef struct YUV_Video {
	int width;
	int height;
	VIDEO_FORMAT format;
	/**
		Array to store 
	*/
	short int* yArray;
	short int* vArray;
	short int* uArray;

	/**
		Combined array of Y, U and V for display purpose
	*/
	short int* frameArray;
} YUVVideo;

/**
	Read bytes from file
*/
STATUS readBytes(char* filePath, char* buff, int frameSize, int frameNumber) {
	FILE *fptr;
	int readSize;
	fptr = fopen(filePath, "r");
	if (!fptr) {
		printf("Error:: Unable to open the file %s.\n", filePath);
		return FAILURE;
	}
	fseek(fptr, frameSize*frameNumber, 0);
	readSize = fread(buff, frameSize, 1, fptr);
	if (readSize == 0) {
		printf("End of File..\n");
		return END_OF_FILE;
	}
	else if (readSize < 0) {
		printf("Error:: while reading file %s.\n", filePath);
		return FAILURE;
	}
	else {
		printf("Read Success..\n");
	}
	fclose(fptr);
	return SUCCESS;
}

/**
	Convert YUV To RGB
*/
STATUS convertToRGB(YUVVideo *yuvVideo) {
	int i;
	short int Y, U, V;

	/**
		Convert each Y, U and V to R, G and B
	*/
	for (i = 0; i < yuvVideo->width * yuvVideo->height; ++i) {
		Y = yuvVideo->yArray[i];
		U = yuvVideo->uArray[i];
		V = yuvVideo->vArray[i];

		/**
			Reassign Y, U and V errors with the corresponding R, G and B values
		*/
		yuvVideo->yArray[i] = Y + 1.13983f * V;  // R
		yuvVideo->uArray[i] = Y - 0.39465f * U - 0.58060f * V;  // G
		yuvVideo->vArray[i] = Y + 2.03211f * U;                 // B
	}
	return SUCCESS;
}

/**
	Combine R, G and B to a single buffer
*/
STATUS combineRGB(YUVVideo *yuvVideo) {
	int i;
	int frameBufferCount = 0;

	for (i = 0; i < yuvVideo->width * yuvVideo->height; ++i) {
		yuvVideo->frameArray[frameBufferCount++] = yuvVideo->yArray[i];
		yuvVideo->frameArray[frameBufferCount++] = yuvVideo->uArray[i];
		yuvVideo->frameArray[frameBufferCount++] = yuvVideo->vArray[i];
	}

	return SUCCESS;
}

/**
	Read UYVY video from file
*/
STATUS readUYVY422(char* filePath, YUVVideo *yuvVideo, int frameNumber) {
	char* bytesRead;
	int i, yCount = 0, uCount = 0, vCount = 0;
	bytesRead = (char *)malloc(sizeof(char) * yuvVideo->height * yuvVideo->width);

	/**
		Read the buffer
	*/
	readBytes(filePath, bytesRead, yuvVideo->height * yuvVideo->width * 2, frameNumber);

	/**
		Create Array according to the format
	*/
	for (i = 0; i < yuvVideo->height * yuvVideo->width * 2; i+=4) {
		yuvVideo->uArray[uCount++] = *(bytesRead++);
		yuvVideo->yArray[yCount++] = *(bytesRead++);
		yuvVideo->vArray[vCount++] = *(bytesRead++);
		yuvVideo->yArray[yCount++] = *(bytesRead++);
	}

	/**
		Convert the video to RGB color space
	*/
	convertToRGB(yuvVideo);

	/**
		Combine RGB for Open GL display
	*/
	combineRGB(yuvVideo);
	return SUCCESS;
}

/**
	Set the format we want
*/
STATUS initYUV(int height, int width, VIDEO_FORMAT format, YUVVideo *yuvVideo) {
	yuvVideo = {};
	yuvVideo->height = height;
	yuvVideo->width = width;
	yuvVideo->format = format;
	return SUCCESS;
}

/**
	Read YUV of the given format
*/
STATUS readYUV(char* filePath, YUVVideo *yuvVideo, int frameNumber) {
	switch (yuvVideo->format)
	{
	case UYVY422: 
		readUYVY422(filePath, yuvVideo, frameNumber); break;
	default:
		printf("The format is not yet supported");
		break;
	}
	return SUCCESS;
}