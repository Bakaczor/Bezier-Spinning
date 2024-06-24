# Bezier Spinning
Bezier Spinning is an application that allows generating and editing a Bezier curve (up to 20 control points), while displaying an image that either spins or moves on the created curve. The program is built on Qt 6.6.0, using the C++20 standard.

# Controls
This section contains information on how to use the application.

## Curve
### Generating
In order to generate a starting curve just enter a desired number of control points and hit `Generate` button.

### Editing
First, enable the polyline display with `Visible polyline` checkbox, then using **left mouse button** drag the control points.

## Rotations
To start, simply load and image with `Load` button, choose one of the availible rotations algorithms - *Naive* or *Triple shear* - and the type of animation - rotations in place or moving on the created curve. When you are ready start the animation with the `Play` button. 

---
*Copyright © 2023 Bartosz Kaczorowski*
