﻿<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# Tools

> **Introducing Tools and Utilities that I Love and Recommend - Better Results in Less Time**

Good tools save time and nerve, plus they often improve the quality of your work. 

In this section I am introducing all *tools* and *utilities* that help me do electronics and documenting what I do.

## Creating Great Schematics

Here is an example: I use the free *KiCAD* software to draw schematics (so *KiCad* definitely is a mention in my *software* category). While *KiCAD* is an excellent software for doing schematics, once you want to *export* them to file, there are severe limitations: all you can do is "plot" the entire schematics page to *SVG* vector image.

If you just want a hi-res *png* schematics image file, a lot of post-processing steps are needed. I automated them with the help of *PowerShell* and created a *PowerShell* module with all the necessary commands to *crop* the excessive whitespace, replace it by a margin, optionally add a solid color background, and then convert the *svg* file to a hi-res *PNG*.

<sup><sub>*(article:802658022319242618)*</sub></sup>