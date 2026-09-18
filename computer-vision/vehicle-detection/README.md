# Day/Night Vehicle Detection

**MATLAB · Computer Vision · Image Processing**

A MATLAB video-processing pipeline for road-intersection vehicle detection under separate daytime and nighttime conditions.

[**Open Project Page**](https://soroushhaghi.github.io/bachelor-engineering-projects/vehicle-detection/)

## Processing
### Daytime
- Day/night routing from HSV value-channel statistics
- Gaussian-mixture foreground detection
- Morphological cleanup
- Connected-component and bounding-box analysis
- Region-based vehicle filtering

### Nighttime
- Binary thresholding
- Morphological opening
- Bright-component analysis
- Headlight-based vehicle-counting logic

## Source
- [vehicle_detection.m](src/vehicle_detection.m)

The daytime foreground stage uses standard MATLAB Computer Vision Toolbox techniques. The project adds its own day/night routing and subsequent filtering/counting logic.
