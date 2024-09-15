<img src="/assets/images/devices_happy.png" width="80%" height="80%" />
 
# 3D Printer

> Prototyping Parts, Creating Housings, Panels, Custom Button Faces, And So Much More

3D printing is a process where material is deposited layer by layer to create a physical object from a digital model. It is used in the industry as well as among DIY makers. While industrial 3D printing uses various materials like plastics, metals, or ceramics, affordable DIY 3D printing focuses on plastic printing materials.

## Quick Overview
Here is the typical process of generating physical objects via *3D printing*:

* **3D Model:** At the beginning, there is a *3D model* that describes the design of the object. You can download *3D models* created by others (i.e. [thingiverse.com](https://www.thingiverse.com/)), or design your own models with a variety of *3D Design Software* (i.e. [AutoDesk Fusion](https://www.autodesk.com/products/fusion-360/overview), formerly known as *Fusion 360*).
* **Slicer:** Since a *3D Printer* prints objects layer by layer, the *3D Model* needs to be converted to a series of *2D layers*. This is what a *Slicer Software* such as [Ultimaker Cura](https://ultimaker.com/de/software/ultimaker-cura) does. Slicers receive *3D Models* in certain file formats, i.e. *STL*, and send their sliced data either directly via *WiFi* or via a *SD Memory Card* to a *3D Printer*.
* **3D Printer:** Receives instructions on how to print a physical object layer by layer. *3D Printers* work similar to a CNC machine and can move a print head in *X* and *Y* direction. A heated *nozzle* melts plastics and deposits it onto the print bead. Once a layer is finished, the print head moves its *Z* axis one level up, and starts printing the next layer on top of the previous one.

There are two different printing methods typically used at home: *Filament* and *Resin*.

## Technique: Filament versus Resin 
Filament 3D printing, or *FDM* (*Fused Deposition Modeling*), uses a spool of plastic filament that is heated and extruded through a nozzle to build objects layer by layer. It is generally more affordable, easier to use, and suitable for creating sturdy parts with a more noticeable layer structure. 

Resin 3D printing, or *SLA* (*Stereolithography*), uses liquid resin that is cured by UV light to form highly detailed models with a smooth finish. Resin prints offer greater precision and surface quality but require more post-processing, like cleaning and curing the prints. Additionally, resin printing can be messier and more hazardous due to the chemicals involved compared to the relatively simple and cleaner filament process.

In a nutshell:

* **Filament (FDM):** Simple, easy to use, clean(er), with cheaper material cost, and not emitting hazardous fumes. The downside is *limited resolution* and visible *layer lines*  FDM is used for functional prototypes, housings, large models and even mechanical parts.
* **Resin (SLA):** More complex, involving handling of fluids and potential hazardous materials, requiring good ventilation, but offering a *higher resolution* and smoother finish. Popular for printing miniatures, figurines, custom jewelry and highly accurate models.

> [!NOTE]
> To safely use a *Resin printer* at home, you need proper *Ventilation*, *Protective Gear* such as nitrile gloves and safety goggles, a proper storage for the Resin (cool and dark), and the appropriate post-processing equipment (isopropyl alcohol for washing prints, UV light curing station), and safe disposal of potential toxic waste. That's why I do not use Resin. As you will see, modern *3D Filament Printers* can achieve excellent resolutions and perfect results at a fraction of cost and effort compared to Resin.

## 3D Printer Differences


> [!IMPORTANT]
> Since I am not using *Resin* printers for the reasons mentioned above, the remainder of this article **addresses 3D Filament Printers only**.

Today, you can choose from a huge number of *3D Filament Printer Models*. Here are aspects to look out for:

* **Build Volume:** Make sure the print bead and head room is large enough to actually print what you'd like to print. Print beads shouldn't be smaller than *200x200mm*, and the build volume shouldn't be less than *200x200x200mm*.
* **Materials:** The *maximum nozzle temperature* determines which *plastic materials* you can print. With temperatures of at least *250C*, you can print the two most popular materials *PLA* and *PETG*. With temperatures of at least *300C*, you can also print more sophisticated materials like *ABS*. The maximum *heat bead temperature* should match the material, or else it won't stick well enough during print.
* **Multi-Color:** Being able to print models with more than one color isn't just a creative edge. Sometimes, it can be crucial for creating backlit panels or transparent custom buttons. 
* **Speed:** Since printing *3D Models* layer by layer is taking a lot of time, the *print speed* is a crucial factor. 
* **Resolution:** Make sure you can easily adjust the diameter of the printing nozzle. Detail-rich prints may require a small diameter (such as 0.2mm), whereas printing large models may use a 0.8mm nozzle. The default nozzle size on most printers is 0.4mm. 
* **Vendor:** It seems there are new *3D Printers* and *Companies* surfacing (and vanishing) every other month. Make sure you pick a *renown manufacturer* that is established on the market. You may need support, you want to find plenty of *community examples* for your printer model, and you most likely **will** need replacement parts or different print heads over time. So you want the company to be still around in a few years' time.

### Materials

| Material              | Print Temperature (°C) | Bed Temperature (°C) |
|-----------------------|-------------------------|----------------------|
| PLA                   | 190-220°C                | 40-60°C              |
| TPU                   | 220-240°C                | 40-60°C              |
| ABS                   | 220-250°C                | 90-110°C             |
| HIPS                  | 230-250°C                | 90-110°C             |
| PETG                  | 230-250°C                | 70-90°C              |
| ASA                   | 240-260°C                | 90-110°C             |
| Nylon                 | 240-270°C                | 70-90°C              |
| Polycarbonate (PC)    | 260-300°C                | 90-120°C             |
| PEEK                  | 360-400°C                | 120-160°C            |

> [!TIP]
> The two most commonly used materials at home are *PLA* and *PETG* which are equally well manageable. *PETG* has better *heat resistance* and is easier to *sand*.


## Multi-Color
If you are new to *3D Printing*, you may want to stick to monochrome models. If you need more color, you can always *paint* your model later.

Printing in more than one color (i.e. filament type) may become a necessary in scenarios like these:

* **Labeling:** you want your housings or custom switches to have labels, and you may even want these labels to be backlit. In the latter, you may even need a *third* color (transparent filament) to allow for back lighting.
* **Easily Removable Supports:** *3D Models* with *overhangs* need *supports*: since a new layer cannot start in mid-air, abrupt overhangs require printing support structures that keep them from falling down. Such supports can be printed automatically and removed later. When printed with the same material, though, supports are hard to remove, and leave behind marks. A better way is to use a water-soluble filament such as *PVA (Polyvinyl Alcohol) for supports that can simply be washed off after the print is done.

To print in more than one color (or filament type), it is necessary to change the filament in mid-print. This can be done in two ways:

* **IDEX (Independent Dual Extruder):** IDEX-printers have two print heads, one per color, i.e. [Snapmaker J1](https://eu.snapmaker.com/de/products/snapmaker-j1-independent-dual-extruder-3d-printer)). The printer is using the head with the color that is currently needed. While such printers are initially more expensive, this investment often pays off because printing models with two colors isn't more expensive than printing monochrome models. IDEX printers cannot print more than two colors, though.
* **Automatic Material Systems (AMS):** Such systems are typically specific add-ons for certain printers (so you cannot hook up an *AMS* from one vendor to a printer from another vendor, i.e. [Bambulab AMS](https://wiki.bambulab.com/en/x1/manual/intro-ams)). The AMS manages more than one filament spool, and can automatically and in mid-print change the filament that is used by the single print head. This allows for as many different colors as the AMS can handle. The downside is *time*, *cost*, and *trouble*: changing the filament *takes time*, slowing down the print time. It also requires that a lot of good filament needs to be *purged* so that the new color filament can be inserted, easily doubling the material (and cost) that is required for a print, especially when there are color changes in each layer. And since *AMS* have a lot of mechanical parts, it is not uncommon for these systems to cause malfunctions and require manual interaction.

> [!TIP]
> Since *IDEX* printers have two independent print heads, they can also *print at the same time*, effectively printing *duplicates* or *mirrored copies* of a monochrome model. So when you need many objects of the same kind, *IDEX* printers can cut printing time in half by printing two objects at the same time. Unfortunately, this type of duplex print often requires vendor-specific slicer software.

## Print Speed
Printing a large *3D Model* can take many hours (smaller models print in a few minutes, too). That's why print speed is a major factor.

However, print speed is not just affected by the printer speed:

* **Printer Speed:** defined as *mm/s*. The printer speed is typically *the fastest speed* under *perfect conditions* with *perfect materials*. Most printers do not reach their fastest speed in real world scenarios. 
* **Hotend:** the "hotend* (the heated print nozzle and its diameter) limit the maximum print speed. If the diameter is very small (i.e. *0.2mm*), if the print filament melts slowly (i.e. *PLA* or *PETG*), and/or if the *heater capacity* isn't heating *enough* plastics per second, then a fast-moving print head won't do any good.
* **Filament:** For fast printing, the filament material needs to *melt quickly*, and the filament quality must be uniform and good. Cheap filaments cause *clogs* and can interrupt printing.
* **Print Quality:** the faster you print, the poorer is the resulting print quality. Cutting print speed in half can improve the print quality remarkable, and vice versa.

For practical purposes and typical materials (such as *PLA* and *PETG*), a print speed of *100-180mm/sec* is recommended: it provides good results with a reasonable speed. Most modern printers support this speed.

> [!TIP]
> If *print quality* is crucial, you may want to reduce print speed to *50mm/sec* or even less, even on high-speed printers. Let the printer do its thing over night, and enjoy a great result.   

## Resolution (Print Quality)
One of the most important advantages of *Resin* printers is their good *resolution* and *smooth finish*. 

With the right setup and settings, you can enjoy similar results with Filament Printers, too:

* **Small Nozzle Diameter:** Reduce the nozzle size from the standard *0.4mm* diameter to a *0.2mm* nozzle size (don't forget to set the new nozzle size in your *Slicer Software*).
* **Quality Filament:** cheap filament from unknown vendors often produces low quality print results. Expensive filament isn't needed. Just make sure the vendor has a good reputation, i.e. [Sunlu](https://sunlu.com/).
* **Filament Heater:** when using hygroscopic materials (i.e. *PETG*), keep it dry, and use a *filament dryer* when using filament that has been opened a while ago (or dry cautionsly in the kitchen oven at 70C for 3 hours). If you left such material in open air for a few days, your print results may degrade severely without using a filament dryer.
* **Slow Print Speed:** Slow down the print speed considerably. Do a few tests, and go as low as *50mm/sec* to see where the sweet spot for your printer is.


> [!TIP]
> Filament prices for *PLA* and *PETG* can be crazy: you may pay almost €30 at amazon for the very same filament that is sold at *AliExpress* for under €10 (shipped out of local warehouses within 2 days). Just make sure you are comparing **prices* *and* *vendor**. Cheap filament I got from unknown vendors was so bad that I could only throw it away, whereas filaments from renown Chinese vendors like [Sunlu](https://sunlu.com/) weren't more expensive and have always performed excellently. 

> Tags: FDM, SLA, Filament, Resin, Fused Deposition Modeling, Stereolithography, Resolution, Filament Dryer, Nozzle Diameter, Heater, Print Speed, Hotend, Print Quality, PLA, PETG, IDEX, Independent Dual Extruder, AMS, Automatic Material System, Color

[Visit Page on Website](https://done.land/tools/devices/3dprinter?265565091515242307) - created 2024-09-14 - last edited 2024-09-14
