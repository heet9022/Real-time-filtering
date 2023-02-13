## Real-time-filtering

# Summary

This project is based on C++. It is set up so that it accesses the computer's webcam and applies a series of filters to it. The user has a choice about which filter they want to use by pressing keyboard keys like 'b', 'g' etc. 

# Grayscale Filter
The grayscale filter was produced using the OpenCV function `cvtColor`. The most accurate method to convert a color image is by doing a weighted sum of the RGB channels, also known as channel-dependent luminance perception. However, this method is computationally expensive, so OpenCV uses a linear approximation instead. The formula used for linear approximation is `Y = 0.299R + 0.587G + 0.114B`.

An alternative grayscale method was also implemented, using the formula `Y = 0.0722B + 0.7152G + 0.2126R`. This conversion method is based on channel-dependent luminance perception, taking into account the perceived brightness of red, green, and blue channels.

# Gaussian Blur
The Gaussian blur filter was implemented using two separable filters of size 5x1 and 1x5, which were applied successively to achieve the same result as a 5x5 Gaussian blur filter matrix. Using separable filters is more computationally efficient.

# Sobel Filter for Edge Detection
The Sobel filter for edge detection was created by first defining two base filters (SobelX and SobelY) and then calculating the magnitude of these base filters.

# Quantized Gaussian Filter
The quantized Gaussian filter was created by first applying a Gaussian filter, and then quantizing the filter into 15 levels.

# Cartoon Filter
The cartoon filter was created by creating a pipeline of the Sobel filter for edge detection and the quantized Gaussian filter. The Sobel filter was used to detect edges, and the corresponding pixels in the Gaussian-quantized image were made black, which created a border-like effect.

# Negative Filter
The negative filter was implemented by subtracting each pixel value from 255, creating a bitwise inversion effect.

# Effects on Still Image
The filters were also applied to still images, as a video is essentially a collection of frames.

# Save Video with Special Effects
A function was implemented that allows users to record video with the special effects applied.

## Key Takeaways
- As a Python user, this project was challenging, as it required a deeper understanding of variable storage in OpenCV and the importance of considering data types.
- Implementing the filters reinforced the concept of convolving filters over images.
- Applying filters in separable form is more efficient than applying the entire matrix.
- It was learned that assigning a matrix `A` to another matrix `B` (i.e. `Mat A = B`) creates a reference to the same matrix, and changes in one will affect all others.

## Acknowledgement
The following websites were consulted in the development of this project:
- https://docs.opencv.org/3.4/index.html
- https://www.learnpythonwithrune.org/opencv-python-webcam-create-a-ghost-effect/
- https://www.geeksforgeeks.org/negative-transformation-of-an-image-using-python-and-opencv/
- https://stackoverflow.com/questions/53111837/align-text-in-the-puttext-in-opencv
- https://learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
- https://docs.opencv.org/3.4/de/d25/imgproc_color_conversions.html#color_con
