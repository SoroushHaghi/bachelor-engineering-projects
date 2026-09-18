# Day/Night Vehicle Detection

**MATLAB · Computer Vision · Vehicle Detection**

## Project
A MATLAB video-processing pipeline for vehicle detection under separate daytime and nighttime conditions.

## Processing
### Daytime
- Scene classification using HSV value-channel statistics
- Gaussian-mixture foreground detection
- Morphological cleanup
- Connected-component and bounding-box analysis
- Region-based vehicle filtering

### Nighttime
- Binary thresholding
- Morphological opening
- Bright-component analysis
- Simple headlight-based vehicle-counting logic

## Source
- [vehicle_detection.m](src/vehicle_detection.m)

The daytime foreground stage uses standard MATLAB Computer Vision Toolbox techniques; the project also contains its own day/night branching and filtering logic.